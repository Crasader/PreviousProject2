'use strict';
/**
 * 兑换码-逻辑
 */

var REDIS_HEAD_CDKEY = 'CDKEY_';

var ONE_CHANNEL_LIMIT = 1;  // 单渠道限制逻辑

var dbmanager = require('../../db/dbmanager.js');
var redishelper = require('../../mem/redishelper.js');
var session_manager = require('../../session_manager.js');
var agreement = require('../../agreement.js');
var schedule = require('node-schedule');
var cdkey_db = require('./cdkey_db.js');

var player_logic = require('../player/player_logic.js');
var bag_logic = require('../player/bag_logic.js');

function initConfig() {
  updateConfig();
  initTask();
}

exports.initConfig = initConfig;

function initTask() {
	var rule = new schedule.RecurrenceRule();
	var times = [];
	times.push(0);
	rule.minute = times;
　　 schedule.scheduleJob(rule, function(){
		console.log(' strat task for cdkey config at ' + new Date().Format("yyyy-MM-dd hh:mm:ss:S"));
		updateConfig();
	});
}

function updateConfig() {
  cdkey_db.getCdkeyConfig(dbmanager.getClientS(), function(success, results) {
    for(var i=0; i<results.length; i++) {
      var item = {
        cdkey : results[i]['cdkey'],
        reward_lists : JSON.parse(results[i]['reward_lists']).reward_lists,
        start_day : results[i]['start_day'],
        end_day : results[i]['end_day'],
        reward_times : results[i]['reward_times'], // 可领次数
        channel_lists : JSON.parse(results[i]['channel_lists']).channel_lists, //可用渠道列表
        one_channel : parseInt(results[i]['one_channel']),
        need_update_channel_config : false
      };
      if( item.one_channel === ONE_CHANNEL_LIMIT) { //包含单渠道限制

        if( results[i]['spec_channel'] !== 'NONE' ) {
          console.log('init with spec channel : ' + results[i]['spec_channel']);
          item.channel_lists = [results[i]['spec_channel']];
        } else {
          item.need_update_channel_config = true;
        }
      }
      var expire_times = getDayInterval( new Date().Format("yyyyMMdd"), ''+item.end_day)*1000*60*60*24 +
          getTillTomorrowDayEndLeftSeconds(); // 时间有效性，到截止日期
      console.log('config_cdkey : ' + REDIS_HEAD_CDKEY+item.cdkey + ';item : ' + JSON.stringify(item));
      redishelper.setValueWithExpire(REDIS_HEAD_CDKEY+item.cdkey, JSON.stringify(item), expire_times);
    }
  });
}

function getRewards(session_id, cdkey, callback) {
  if(cdkey === undefined || cdkey === null || cdkey.length < 2) {
    callback(agreement.reqParamsErrorDesc);
    return ;
  }
  (function(session_id, cdkey){
    session_manager.isLogin(session_id, function(login, data){
      if(!login) {
        callback(data);
        return ;
      }

      var user_id = data.user_id;
      var channel_id = data.channel_id;
      var fortune_id = data.fortune_id;
      console.log('req_cdkey : ' + REDIS_HEAD_CDKEY+cdkey);
      (function(user_id, channel_id, fortune_id){
        redishelper.getVaule(REDIS_HEAD_CDKEY+cdkey, function(err, redis_result) { // 判断cdkey是否可用[缓存中是否存在可用的CDKEY]
          if(err) {
            var result = {
              errorcode : 2101,
              errormsg : '兑换服务忙，请稍后再试'
            }
            callback(JSON.stringify(result));
            return ;
          }
          if( !(redis_result === undefined || redis_result === null) ) {
            var cdkey_infos = JSON.parse(redis_result);
            if(cdkey_infos.channel_lists != null && cdkey_infos.channel_lists.length > 0) {
              // TODO : 没有判断渠道互斥
              console.log('user_channel_id : ' + channel_id);
              var allow_channel = false;
              for( var i=0; i<cdkey_infos.channel_lists.length;i++) {
                console.log('cdkey_infos.channel_lists[i] : ' + cdkey_infos.channel_lists[i]);
                if(cdkey_infos.channel_lists[i] === channel_id) {
                  allow_channel = true;
                  break;
                }
              }
              if(!allow_channel) {
                var result = {
                  errorcode : 2103,
                  errormsg : '您的渠道不能使用此兑换码'
                }
                callback(JSON.stringify(result));
                return ;
              }
              if(cdkey_infos.need_update_channel_config) {
                cdkey_infos.need_update_channel_config = false;
                cdkey_infos.channel_lists = [channel_id];
                var expire_times = getDayInterval( new Date().Format("yyyyMMdd"), ''+cdkey_infos.end_day)*1000*60*60*24 +
                    getTillTomorrowDayEndLeftSeconds();
                redishelper.setValueWithExpire(REDIS_HEAD_CDKEY+cdkey_infos.cdkey, JSON.stringify(cdkey_infos), expire_times);
                cdkey_db.setCdkeyChannelConfig(dbmanager.getClient(), cdkey_infos.cdkey, channel_id, function(result){});// TODO : 更新数据库配置
              }
            }

            var r_u_key = REDIS_HEAD_CDKEY+cdkey+user_id;
            (function(r_u_key, cdkey_infos){
              redishelper.getVaule(r_u_key, function(err, redis_result) { // 判断cdkey是否可用[缓存中是否存在可用的CDKEY]
                if(err) {
                  var result = {
                    errorcode : 2101,
                    errormsg : '兑换服务忙，请稍后再试'
                  }
                  callback(JSON.stringify(result));
                  return ;
                }
                console.log('redis_result : ' + redis_result);
                if( redis_result === undefined || redis_result === null ) {
                  redishelper.setVaule(r_u_key, 1);  // 记录用户领取记录，为1次
                  var result = {
                    errorcode : 0,
                    reward_lists : cdkey_infos.reward_lists
                  }
                  updateUserInfoByRewards(session_id, user_id, fortune_id, cdkey_infos.reward_lists);
                  callback(JSON.stringify(result));
                  return ;
                }else if(cdkey_infos.reward_times === 0 || cdkey_infos.reward_times > redis_result){
                  redishelper.setVaule(r_u_key, parseInt(redis_result)+1);
                  var result = {
                    errorcode : 0,
                    reward_lists : cdkey_infos.reward_lists
                  }
                  updateUserInfoByRewards(session_id, user_id, fortune_id, cdkey_infos.reward_lists);
                  callback(JSON.stringify(result));
                  return ;
                }else {
                  var result = {
                    errorcode : 2102,
                    errormsg : '您已经领取过兑换码'
                  }
                  callback(JSON.stringify(result));
                  return ;
                }
              });
            })(r_u_key, cdkey_infos);
          }else {
            var result = {
              errorcode : 2100,
              errormsg : '不存在的兑换码'
            }
            callback(JSON.stringify(result));
            return ;
          }
        });
      })(user_id, channel_id, fortune_id);

    });
  })(session_id, cdkey);
}

exports.getRewards = getRewards;

/**
 * 更新用户的奖励信息
 */
function updateUserInfoByRewards(session_id, user_id, fortune_id, store_reward_lists) {
  var coins = 0;
  var diamonds = 0;
  bag_logic.addBagItems(session_id, store_reward_lists, function(result){
    console.log('cdkey set item_id result : ' + result);
  });

  for(var i=0; i<store_reward_lists.length; i++) {
    if(store_reward_lists[i].item_id === 1001) {
      coins += store_reward_lists[i].nums;
    } else if(store_reward_lists[i].item_id === 1002) {
      diamonds += store_reward_lists[i].nums;
    }
  }
  if(coins > 0 || diamonds > 0) {
    updateUserCoinsOrDiamonds(session_id, user_id, fortune_id, coins, diamonds);
  }
}

function updateUserCoinsOrDiamonds(session_id, p_user_id, p_fortune_id, p_coins, p_diamonds) {
  var sync_info = {
    user_id : p_user_id,
    fortune_id : p_fortune_id,
    coins : p_coins,
    diamonds : p_diamonds
  };
  console.log('[cdkey] sync_info coins and diamonds : ' + JSON.stringify(sync_info));
  player_logic.syncPlayerCoinsAndDiamonds(session_id, sync_info);
}

/**
 * 计算两个日期之间的差值
 */
function getDayInterval(start_day, end_day) {
  var start_days = [start_day.substring(0, 4), start_day.substring(4, 6), start_day.substring(6, 8)];
  var end_days = [end_day.substring(0, 4), end_day.substring(4, 6), end_day.substring(6, 8)];

  var login_day = parseInt( Math.abs( new Date(end_days[0],parseInt(end_days[1])-1,end_days[2]) -
  			new Date(start_days[0],parseInt(start_days[1])-1,start_days[2]) ) / 1000 / 60 / 60 / 24);
  return login_day;
}

/**
 * 计算从现在到今天结束的秒数
 */
function getTillTomorrowDayEndLeftSeconds() {
	var myDate = new Date();
	return ( ( (24+23) - myDate.getHours() )*60 + ( 59 - myDate.getMinutes() ) )*60 +
		59 - myDate.getSeconds();
}
