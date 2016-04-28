
var redishelper = require('../../mem/redishelper.js');
var player_logic =  require('../player/player_logic.js');
var bag_logic = require('../player/bag_logic.js');

var noderice = require('noderice');

var NOBILITY_REDIS_HEAD = 'NOBILITY_';

var ONE_DAY_SECONDS = 60*60*24;
var ONE_TIMES_DAY = 30;

var default_client_result = {
  errorcode : 0,
  errormsg : 'success',
  surplus_day : 0
};
var default_client_str = JSON.stringify(default_client_result);

var default_reward_result = {
  errorcode : 0,
  reward_lists : []
};
var default_reward_str = JSON.stringify(default_reward_result);

var default_reward_result_have = {
  errorcode : 0,
  reward_lists : [
    {item_id : 1001, nums : 20000},
    {item_id : 1002, nums : 20},
    {item_id : 1003, nums : 2},
    {item_id : 1004, nums : 5}
  ] // TODO : 写死的贵族奖励信息，客户端图片切死，不可随意更改
};
var default_reward_str_have = JSON.stringify(default_reward_result_have);


function getSurplusDay(user_id, callback) {
  getUserSurplusDay(user_id, function(success, result){
    if(success) {
      var result_to_c = {
        errorcode : 0,
        surplus_day : result.surplus_day
      }
      callback(JSON.stringify(result_to_c));
    }else {
      callback(result);
    }
  });
}

exports.getSurplusDay = getSurplusDay;

function getRewardDay(session_id, user_id, fortune_id, callback) {
  getUserSurplusDay(user_id, function(success, result){
    if(success) {
      var r_key = NOBILITY_REDIS_HEAD + noderice.GetDateNum(0) + user_id;
      redishelper.getVaule(r_key, function(err, redis_result){
        if(err) {
          var err_to_c = {
            errorcode : 500,
            errormsg : 'read redis error'
          }
          callback(JSON.stringify(err_to_c));
          return ;
        }
        if(redis_result === undefined || redis_result === null) {
          redishelper.setValueWithExpire(r_key, 1, redishelper.getCurrentDayLeftSeconds());
          syncUserInfoByReward(session_id, user_id, fortune_id); // 更新用户奖励
          callback(default_reward_str_have);
          return ;
        } else {  // 领过了
          callback(default_reward_str);
        }
      });
    }else {
      callback(default_reward_str);
    }
  });
}

exports.getRewardDay = getRewardDay;

function syncUserInfoByReward(session_id, user_id, fortune_id) {
  syncUserCoinsAndDiamonds(session_id, user_id, fortune_id);
  syncUserBagInfo(session_id, user_id);
}

function syncUserCoinsAndDiamonds(session_id, user_id, fortune_id) {
  var sync_info = {
    user_id : user_id,
    fortune_id : fortune_id,
    coins : 20000,
    diamonds : 20
  };
  player_logic.syncPlayerCoinsAndDiamonds(session_id, sync_info);
}

function syncUserBagInfo(session_id, user_id) {
  var item_lists = [
    {item_id : 1003, nums : 2},
    {item_id : 1004, nums : 5}
  ];
  bag_logic.addBagItems(session_id, item_lists, function(result){});
}

/**
 * 写入新的贵族购买记录
 */
function addNewNobilityInfo(user_id) {
  getUserSurplusDay(user_id, function(success, result){
    if(success) {
      var r_key = NOBILITY_REDIS_HEAD + user_id;
      var user_info = {
        buy_first_day : new Date().Format("yyyy-MM-dd"),
        times : result.times + 1
      };
      redishelper.setValueWithExpire(r_key, JSON.stringify(user_info), (result.surplus_day+ONE_TIMES_DAY)*ONE_DAY_SECONDS + redishelper.getCurrentDayLeftSeconds());
    }else {
      var r_key = NOBILITY_REDIS_HEAD + user_id;
      var user_info = {
        buy_first_day : new Date().Format("yyyy-MM-dd"),
        times : 1
      };
      redishelper.setValueWithExpire(r_key, JSON.stringify(user_info), 30*ONE_DAY_SECONDS + redishelper.getCurrentDayLeftSeconds());
    }
  });


}

exports.addNewNobilityInfo = addNewNobilityInfo;


function getUserSurplusDay(user_id, callback) {
  var r_key = NOBILITY_REDIS_HEAD + user_id;
  redishelper.getVaule(r_key, function(err, redis_result){
    if(err) {
      var err_to_c = {
        errorcode : 500,
        errormsg : 'read redis error'
      }
      callback(false, JSON.stringify(err_to_c));
      return ;
    }
    if(redis_result === undefined || redis_result === null) {
      callback(false, default_client_str);
      return ;
    }
    var nobility_info = JSON.parse(redis_result);
    var longDays = parseInt(nobility_info.times*ONE_TIMES_DAY);
    var surplus_day = longDays - parseInt(getStartDayToToday(nobility_info.buy_first_day));
    if(surplus_day > longDays || surplus_day < 0) {
      callback(false, default_client_str);
      return ;
    }else {
      var result = {
        surplus_day : surplus_day,
        times : nobility_info.times
      };
      callback(true, result);
    }
  });
}

/**
 * 计算开始日期到今天的天数
 * start_day格式为"YYYY-MM-dd"
 */
function getStartDayToToday(start_day) {
  var logs = (start_day).split('-');
  var login_day = parseInt( Math.abs( new Date() - new Date(logs[0],parseInt(logs[1])-1,logs[2]) ) / 1000 / 60 / 60 / 24);
  return login_day;
}
