/**
 * 签到逻辑
 */

var dbmanager = require('../../db/dbmanager.js');
var schedule = require('node-schedule');
var sign_db = require('./sign_db.js');
var redishelper = require('../../mem/redishelper.js');
var player_logic = require('../player/player_logic.js');
var bag_logic = require('../player/bag_logic.js');


 var signAgreement = {
   version : 1,
   today : new Date().Format("yyyy-MM-dd"),
   item_lists : [
     {
       item_id : 1001,
       num : 500,
       probability : 70
     },
     {
       item_id : 1002,
       num : 5,
       probability : 30
     }
   ]
};

var signAgreementStr = JSON.stringify(signAgreement);

function initConfig() {
  updateSignConfig();
  initTask();
}

function initTask() {
	var rule = new schedule.RecurrenceRule();
	var times = [];
  for(var i=0;i<60;i++) { // TODO : 测试阶段签到信息改为每1分钟更新一次
    times.push(i);
  }
	rule.minute = times;
　　 schedule.scheduleJob(rule, function(){
		updateSignConfig();
	});
}

function updateSignConfig() {
  sign_db.getSignConfig(dbmanager.getClientS(), function(success, configSignAgreementStr){
    if(success) {
      signAgreement = JSON.parse(configSignAgreementStr);
      signAgreement.today = new Date().Format("yyyy-MM-dd");
      signAgreementStr = JSON.stringify(signAgreement);
    }else {
      console.log('sign_logic->updateSignConfig, fail : ' + signAgreementStr);
    }
  });
}

exports.initConfig = initConfig;
exports.getSignAgreementStr = getSignAgreementStr;
exports.updateSignConfig = updateSignConfig;

function getSignInfo(session_id, user_id, fortune_id, callback) {
  var r_key = 'SING_' + user_id;
  (function(session_id, user_id, fortune_id){
    redishelper.getVaule(r_key, function(err, redis_result){
      if(err) {
        var err_to_c = {
          errorcode : 500,
          errormsg : 'read redis error'
        }
        callback(JSON.stringify(err_to_c));
        return ;
      }
      if (redis_result === undefined || redis_result === null) {  // 没有签到过或者签到日期已经失效
        var signInfo = {
          start_day : new Date().Format("yyyy-MM-dd"),
          sign_day : 1
        };
        var client_result = {
          errorcode : 0,
          errormsg : 'success',
          rewards : getSignRewards(1)
        };
        updateRewards(session_id, user_id, fortune_id, client_result.rewards); // 更新用户奖励
        callback( JSON.stringify( client_result ) );
        redishelper.setValueWithExpire(r_key, JSON.stringify(signInfo), getTillTomorrowDayEndLeftSeconds());
        return ;
      }else {
        console.log(r_key + ' : ' + redis_result);
        var signInfo = JSON.parse(redis_result);
        var startDayNum = parseInt( getStartSignDay(signInfo.start_day) );
        if( startDayNum === parseInt(signInfo.sign_day) ) {
          if(startDayNum === 7) {
            signInfo.start_day = new Date().Format("yyyy-MM-dd");
            signInfo.sign_day = 1;
            var client_result = {
              errorcode : 0,
              errormsg : 'success',
              rewards : getSignRewards(1)
            };
            updateRewards(session_id, user_id, fortune_id, client_result.rewards);  // 更新用户奖励
            callback( JSON.stringify( client_result ) );
            redishelper.setValueWithExpire(r_key, JSON.stringify(signInfo), getTillTomorrowDayEndLeftSeconds());
            return ;
          }
          signInfo.sign_day = signInfo.sign_day + 1;
          var client_result = {
            errorcode : 0,
            errormsg : 'success',
            rewards : getSignRewards( parseInt(signInfo.sign_day) )
          };
          updateRewards(session_id, user_id, fortune_id, client_result.rewards);  // 更新用户奖励
          callback( JSON.stringify( client_result ) );
          redishelper.setValueWithExpire(r_key, JSON.stringify(signInfo), getTillTomorrowDayEndLeftSeconds());
          return ;
        } else if( (startDayNum+1) === parseInt(signInfo.sign_day) ) {
          var client_result = {
            errorcode : 0,
            errormsg : 'success',
            rewards : []
          };
          callback( JSON.stringify( client_result ) );
        } else {
          var signInfo = {
            start_day : new Date().Format("yyyy-MM-dd"),
            sign_day : 1
          };
          var client_result = {
            errorcode : 0,
            errormsg : 'success',
            rewards : getSignRewards(1)
          };
          updateRewards(session_id, user_id, fortune_id, client_result.rewards);  //  更新用户奖励
          callback( JSON.stringify( client_result ) );
          redishelper.setValueWithExpire(r_key, JSON.stringify(signInfo), getTillTomorrowDayEndLeftSeconds());
          return ;
        }
      }
    });
  })(session_id, user_id, fortune_id);

}

exports.getSignInfo = getSignInfo;

function updateRewards(session_id, user_id, fortune_id, rewards) {
  var coins = 0;
  var diamonds = 0;

  for(var i=0;i<rewards.length;i++) {
    if(rewards[i].item_id === 1001) {
      coins += rewards[i].nums;
    }else if(rewards[i].item_id === 1002) {
      diamonds += rewards[i].nums;
    }else {
      updateUserBag(session_id, rewards[i].item_id, rewards[i].nums);
    }
  }
  console.log('[sign] coins : ' + coins + ';diamonds : ' + diamonds);
  if(coins > 0 || diamonds > 0) {
    updateUserCoinsOrDiamonds(session_id, user_id, fortune_id, coins, diamonds);
  }
}

function updateUserCoinsOrDiamonds(session_id, user_id, fortune_id, coins, diamonds) {
  var sync_info = {
    user_id : user_id,
    fortune_id : fortune_id,
    coins : coins,
    diamonds : diamonds
  };
  console.log('[sign] sync_info : ' + JSON.stringify(sync_info));
  player_logic.syncPlayerCoinsAndDiamonds(session_id, sync_info);
}

function updateUserBag(session_id, item_id, nums) {
  // TODO : 目前的实现非常不好
  bag_logic.syncUserBagInfoBySessionId(session_id, item_id, nums, function(data){});
}

function getTillTomorrowDayEndLeftSeconds() {
	var myDate = new Date();
	return ( ( (24+23) - myDate.getHours() )*60 + ( 59 - myDate.getMinutes() ) )*60 +
		59 - myDate.getSeconds();
}

function getSignAgreementStr() {
  return signAgreementStr;
}

/**
 * 计算第N天的奖励物品信息
 */
function getSignRewards(someDay) {
  if(someDay === 0 || someDay > 7) {
    return [];
  }
  var rewards = [];
  for(var i=0; i<someDay;i++) {
    var randomnum = parseInt(100*Math.random());
    for(var j=0;j<signAgreement.item_lists.length;j++) {
      if(randomnum < parseInt(signAgreement.item_lists[j].probability)){
        rewards.push({
          item_id : signAgreement.item_lists[j].item_id,
          nums : signAgreement.item_lists[j].num
        });
        break;
      }
      randomnum = randomnum - parseInt(signAgreement.item_lists[j].probability);
    }
  }
  console.log('someday : ' + someDay + ', rewards : ' + JSON.stringify(rewards));
  return rewards;
}

/**
 * 计算开始签到时间到今天的天数
 * start_day格式为"YYYY-MM-dd"
 */
function getStartSignDay(start_day) {
  var logs = (start_day).split('-');
  var login_day = parseInt( Math.abs( new Date() - new Date(logs[0],parseInt(logs[1])-1,logs[2]) ) / 1000 / 60 / 60 / 24);
  return login_day;
}
