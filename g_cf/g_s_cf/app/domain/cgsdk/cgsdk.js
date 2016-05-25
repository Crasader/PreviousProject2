'use strict';
var request = require('request');

var APIKEY = '14bba4b760b80073b064569a4087d3c6';
var URL_HEAD_TBULOOK = 'http://106.75.141.82:1701/';

var session_manager = require('./session_manager.js');
var agreement = require('./agreement.js');
var redishelper = require('../../environment/mem/redishelper.js');
var dbmanager = require('../../environment/db/dbmanager.js');
var player_db = require('./player/player_db.js');

var noderice = require('noderice');
noderice.time_init();

/**
 * 玩家基本信息同步
 */
function addPlayerBaseInfoChangeBySessionId(session_id, coins, diamonds, exps, turrent_level, callback) {
  // TODO : 需要添加序列保证执行顺序
  // TODO : 主要是redis的信息需要保证[因此采用全覆盖的写法而不是增量计算的方式更合适]
  (function(coins, diamonds, exps, turrent_level){
    session_manager.isLogin(session_id, function(login, data){
  		if(!login) {
  			callback(false, data);
  			return ;
  		}
      console.log('kangjun_new [1]: ' + JSON.stringify(data));
      data.coins =  parseInt(coins);
      data.diamonds = parseInt(diamonds) ;
      data.exps = parseInt(exps) ;
      data.turrent_level = parseInt(turrent_level) ;
      redishelper.setValueWithExpire(data.session_id, JSON.stringify(data), session_manager.SESSION_EXPIRE);
      var sync_info = {
        user_id : data.user_id,
        fortune_id : data.fortune_id,
        coins : data.coins,
        diamonds : data.diamonds,
        exps : data.exps,
        turrent_level : data.turrent_level
      };

      player_db.syncPlayerBaseFortuneInfo(dbmanager.getClient(), sync_info, function(result){});
      callback(true, {});
  	});
  })(coins, diamonds, exps, turrent_level);
}

exports.addPlayerBaseInfoChangeBySessionId = addPlayerBaseInfoChangeBySessionId;

/**
 * 获取用户基本信息
 */
function getPlayerBaseInfoBySessionId(session_id, callback) {
  session_manager.isLogin(session_id, function(login, data){
    if(!login) {
      callback(false, data);
      return ;
    }
    var result = {
      errorcode : 0,
      errormsg : '',
      user_info : {
        user_id : data.user_id,
        nick_name : data.nick_name,
        coins : data.coins === undefined ? 0 : parseInt(data.coins),
        diamonds : data.diamonds === undefined ? 0 :parseInt(data.diamonds),
        exps : data.exps === undefined ? 0 : parseInt(data.exps),
        turrent_level : data.turrent_level === undefined ? 1 : parseInt(data.turrent_level),
        mo : data.mo === undefined ? 0 : data.mo,
        chest_level : data.chest_level === undefined ? 0 : parseInt(data.chest_level)
      }
    };
    console.log('MOLO_USERINFO : ' + JSON.stringify(result));
    callback(true, result);
  });
}

exports.getPlayerBaseInfoBySessionId = getPlayerBaseInfoBySessionId;




/**
 * 更新玩家背包信息
 */
function updatePlayerBagInfoBySessionId(session_id, user_id, item_change_lists, callback) {
  var r_key = 'BG_' + session_id;
  (function(r_key, user_id, item_change_lists){
    redishelper.getVaule(r_key, function(err, redis_result) {
      if(err) {
        callback(false);
        return ;
      }
      if(redis_result != undefined) {
        var bagInfoObj = JSON.parse(redis_result);
        for(var i=0;i<item_change_lists.length;i++) {
          if(item_change_lists[i].nums > 0) {
            var success = false;
            for(var j=0; j<bagInfoObj.item_lists.length; j++) {
              if( bagInfoObj.item_lists[j].item_id === item_change_lists[i].item_id ) {
                bagInfoObj.item_lists[j].nums = bagInfoObj.item_lists[j].nums + item_change_lists[i].nums;
                player_db.syncbagInfo(dbmanager.getClient(), user_id, bagInfoObj.item_lists[j].item_id, bagInfoObj.item_lists[j].nums, function(){});
                success = true;
                break;
              }
            }
            if(!success) {
              bagInfoObj.item_lists.push({
                item_id : item_change_lists[i].item_id,
                nums : item_change_lists[i].nums
              });
              player_db.syncbagInfo(dbmanager.getClient(), user_id, item_change_lists[i].item_id, item_change_lists[i].nums, function(){});
            }
          }else if(item_change_lists[i].nums <= 0) {
            for(var j=0; j<bagInfoObj.item_lists.length; j++) {
              if( bagInfoObj.item_lists[j].item_id === item_change_lists[i].item_id ) {
                if( bagInfoObj.item_lists[j].nums >= Math.abs(item_change_lists[i].nums) ) {
                  bagInfoObj.item_lists[j].nums = bagInfoObj.item_lists[j].nums + item_change_lists[i].nums;
                }else {
                  bagInfoObj.item_lists[j].nums = 0;
                }

                player_db.syncbagInfo(dbmanager.getClient(), user_id, bagInfoObj.item_lists[j].item_id, bagInfoObj.item_lists[j].nums, function(){});
                break;
              }
            }
          }
        }
        redishelper.setValueWithExpire(r_key, JSON.stringify(bagInfoObj), session_manager.SESSION_EXPIRE);//写入缓存
        callback(true); // 没有足够的道具，不能使用
        return ;
      }
      callback(false);
    });
  })(r_key, user_id, item_change_lists);
}

exports.updatePlayerBagInfoBySessionId = updatePlayerBagInfoBySessionId;


/**
 * 获取用户背包信息
 */
function getPlayerBagInfoBySessionId(session_id, callback) {
  redishelper.getVaule('BG_' + session_id, function(err, redis_result){
    if(err) {
      callback(false, agreement.redisErrorDesc);
      return ;
    }
    if(redis_result != undefined) {
      callback(true, JSON.parse(redis_result));
      return ;
    }
    callback(false, agreement.invalidSessionIdDesc);
  });
}

exports.getPlayerBagInfoBySessionId = getPlayerBagInfoBySessionId;

/**
 * 获取玩家奖池信息
 * http://106.75.135.78:1701/bonuspool/currentstate/TBU_1458718599826
 * {"errorcode":0,"fish_nums":1,"fish_coins":150,"user_nums":7}
 */
function getPlayerBonuspoolInfoBySessionId(session_id, callback) {
  var options = {
        url : URL_HEAD_TBULOOK + 'bonuspool/currentstate/' + session_id,
        timeout : 6000,
        headers : { 'apikey': APIKEY }
    };
    request(options, function (error, response, body) {
        if (error) {
            console.log('cgsdk->getPlayerBonuspoolInfoBySessionId, meet error : ' + error);
            callback(false, error);
            return ;
        }else if(response.statusCode != 200) {
          console.log('cgsdk->getPlayerBonuspoolInfoBySessionId response.statusCode = ' + response.statusCode);
          callback(false, error);
          return ;
        }
        callback(true, body);
        // console.log('tbulookdata->getDashboardUserInfo, resulut : ' + body
        //         + '; response.statusCode = ' + response.statusCode);
    });
}

exports.getPlayerBonuspoolInfoBySessionId = getPlayerBonuspoolInfoBySessionId;

/**
 * 获取玩家奖池信息
 * http://106.75.135.78:1701/bonuspool/catchfish/:session_id/:fish_id
 * {"errorcode":0,"fish_nums":1,"fish_coins":150,"user_nums":7}
 */
function addOneGoldFishForBonuspoolBySessionId(session_id, fish_id, callback) {
  var options = {
        url : URL_HEAD_TBULOOK + 'bonuspool/catchfish/' + session_id + '/' + fish_id,
        timeout : 6000,
        headers : { 'apikey': APIKEY }
    };
    request(options, function (error, response, body) {
        if (error) {
            console.log('cgsdk->addOneGoldFishForBonuspoolBySessionId, meet error : ' + error);
            callback(false, error);
            return ;
        }else if(response.statusCode != 200) {
          console.log('cgsdk->addOneGoldFishForBonuspoolBySessionId response.statusCode = ' + response.statusCode);
          callback(false, error);
          return ;
        }
        callback(true, body);
        // console.log('tbulookdata->getDashboardUserInfo, resulut : ' + body
        //         + '; response.statusCode = ' + response.statusCode);
    });
}

exports.addOneGoldFishForBonuspoolBySessionId = addOneGoldFishForBonuspoolBySessionId;

/**
 * 获取玩家奖池信息
 * http://106.75.135.78:1701/bonuspool/turntable/TBU_1458718599826
 * {"errorcode":0,"reward_lists":[{"item_id":1002,"nums":10}],"user_nums":6}
 */
function turntableForBonuspoolBySessionId(session_id, callback) {
  var options = {
        url : URL_HEAD_TBULOOK + 'bonuspool/turntable/' + session_id,
        timeout : 6000,
        headers : { 'apikey': APIKEY }
    };
    request(options, function (error, response, body) {
        if (error) {
            console.log('cgsdk->turntableForBonuspoolBySessionId, meet error : ' + error);
            callback(false, error);
            return ;
        }else if(response.statusCode != 200) {
          console.log('cgsdk->turntableForBonuspoolBySessionId response.statusCode = ' + response.statusCode);
          callback(false, error);
          return ;
        }
        callback(true, body);
        // console.log('tbulookdata->getDashboardUserInfo, resulut : ' + body
        //         + '; response.statusCode = ' + response.statusCode);
    });
}

exports.turntableForBonuspoolBySessionId = turntableForBonuspoolBySessionId;

/**
 * 破产接口
 * http://106.75.135.78:1701/bankrupt/broke/:session_id/:room_id
 * {"errorcode":0,"times":1,"wait_time":0, "left_times" : 3}
 */
function bankruptBrokeBySessionId(session_id, room_id, callback) {
  var options = {
        url : URL_HEAD_TBULOOK + 'bankrupt/broke/' + session_id + '/' + room_id,
        timeout : 6000,
        headers : { 'apikey': APIKEY }
    };
    request(options, function (error, response, body) {
        if (error) {
            console.log('cgsdk->bankruptBrokeBySessionId, meet error : ' + error);
            callback(false, error);
            return ;
        }else if(response.statusCode != 200) {
          console.log('cgsdk->bankruptBrokeBySessionId response.statusCode = ' + response.statusCode);
          callback(false, error);
          return ;
        }
        callback(true, body);
        // console.log('tbulookdata->getDashboardUserInfo, resulut : ' + body
        //         + '; response.statusCode = ' + response.statusCode);
    });
}

exports.bankruptBrokeBySessionId = bankruptBrokeBySessionId;


/**
 * 破产领取接口
 * http://106.75.135.78:1701/bankrupt/rebirth/:session_id/:room_id
 * {"errorcode":0,"times":1,"wait_time":0, "left_times" : 3}
 */
function bankruptRebirthBySessionId(session_id, room_id, callback) {
  var options = {
        url : URL_HEAD_TBULOOK + 'bankrupt/rebirth/' + session_id + '/' + room_id,
        timeout : 6000,
        headers : { 'apikey': APIKEY }
    };
    request(options, function (error, response, body) {
        if (error) {
            console.log('cgsdk->bankruptRebirthBySessionId, meet error : ' + error);
            callback(false, error);
            return ;
        }else if(response.statusCode != 200) {
          console.log('cgsdk->bankruptRebirthBySessionId response.statusCode = ' + response.statusCode);
          callback(false, error);
          return ;
        }
        callback(true, body);
        // console.log('tbulookdata->getDashboardUserInfo, resulut : ' + body
        //         + '; response.statusCode = ' + response.statusCode);
    });
}

exports.bankruptRebirthBySessionId = bankruptRebirthBySessionId;

// TODO : 增加破产状态查询接口

var MAX_BROKE_NUM = 3;

/**
 * 破产状态查询接口
 * {"errorcode":0,"times":1,"wait_time":0, "left_times" : 3}
 */
function bankruptBrokeStateByUserId(user_id, callback) {
  var r_key = noderice.GetDateNum(0) + '_' + user_id;
  console.log('bankruptBrokeStateByUserId, r_key = ' + r_key);
  (function(r_key){
    redishelper.getVaule(r_key, function(err, redis_result){
      if(err) {
        callback(false, '');
        return ;
      }
      console.log('bankruptBrokeStateByUserId, redis_result = ' + redis_result);
      if( redis_result !== undefined && redis_result !== null ) {
        var bankruptObj = JSON.parse(redis_result);
        if(bankruptObj.rebirth_num < MAX_BROKE_NUM) {
          var b_state_result = {
            errorcode : 0,
            times : bankruptObj.broke_num,      // 第几次破产
            coins : (bankruptObj.rebirth_num + 1)*1000, // 如果领取的金额
            wait_time : 0,  // 破产等待时间 : 秒
            left_times : MAX_BROKE_NUM + 1 - bankruptObj.broke_num  // 剩余可领取次数(包括本次)
          };

          callback(true, b_state_result);
          return ;
        }else {
          var b_state_result = {
            errorcode : 0,
            times : 100,      // 第几次破产
            coins : 0,
            wait_time : 0,  // 破产等待时间 : 秒
            left_times : 0  // 剩余可领取次数(包括本次)
          };
          callback(true, b_state_result);
        }
      }else {
        var key_info = {
          broke_num : 1,
          rebirth_num : 0
        };
        redishelper.setValueWithExpire(r_key, JSON.stringify(key_info), redishelper.getCurrentDayLeftSeconds());
        var b_state_result = {
              errorcode : 0,
              times : 1,      // 第几次破产
              coins : 1000,
              wait_time : 0,  // 破产等待时间 : 秒
              left_times : MAX_BROKE_NUM  // 剩余可领取次数(包括本次)
            };
        callback(true, b_state_result);
      }
    });
  })(r_key);

}

exports.bankruptBrokeStateByUserId = bankruptBrokeStateByUserId;
