'use strict';
/**
 * 背包逻辑
 */

var dbmanager = require('../../db/dbmanager.js');
var bag_db = require('./bag_db.js');
var session_manager = require('../../session_manager.js');
var agreement = require('../../agreement.js');
var redishelper = require('../../mem/redishelper.js');

function getChest(session_id, item_id, callback) {
  if(!isChest(parseInt(item_id))) {
    callback(agreement.reqParamsErrorDesc);
    return ;
  }
  var item_id = parseInt(item_id);
  (function(session_id, item_id){
    session_manager.isLogin(session_id, function(login, data){
      if(!login) {
        callback(data);
        return ;
      }
      var userInfo = data;
      (function(userInfo){
        redishelper.getVaule('BG_' + session_id, function(err, redis_result) {
          if(err) {
            callback(agreement.redisErrorDesc);
            return ;
          }
          if(redis_result != undefined) { // TODO : 获取用户背包中宝箱的数目
            console.log('--MOLO_BG : ' + redis_result);
            var bagInfoObj = JSON.parse(redis_result);
            for(var i=0; i<bagInfoObj.item_lists.length; i++) {
              if(item_id === parseInt(bagInfoObj.item_lists[i].item_id)) {
                if(bagInfoObj.item_lists[i].nums > 0) {
                  var coins = 0;
                  console.log('userInfo.chest_level : ' + userInfo.chest_level + ';getItemLevel(item_id) = ' + getItemLevel(item_id));
                  if(userInfo.chest_level >= getItemLevel(item_id)) {
                    coins = getRewardCoins(item_id);
                    console.log('userInfo.coins[1] : ' + userInfo.coins);
                    userInfo.coins += coins;
                    console.log('userInfo.coins[2] : ' + userInfo.coins);
                    bag_db.syncUserInfo(dbmanager.getClient(), userInfo.user_id, userInfo.fortune_id, 'coins', userInfo.coins, function(result){});
                  } else {
                    userInfo.chest_level = getItemLevel(item_id);
                    bag_db.syncUserInfo(dbmanager.getClient(), userInfo.user_id, userInfo.fortune_id, 'chest_level', userInfo.chest_level, function(result){});
                  }
                  redishelper.setValueWithExpire(userInfo.session_id, JSON.stringify(userInfo), session_manager.SESSION_EXPIRE);

                  bagInfoObj.item_lists[i].nums -= 1;
                  redishelper.setValueWithExpire('BG_' + session_id, JSON.stringify(bagInfoObj), session_manager.SESSION_EXPIRE);
                  bag_db.syncbagInfo(dbmanager.getClient(), userInfo.user_id, item_id, bagInfoObj.item_lists[i].nums, function(result){});
                  var result = {
                    errorcode : 0,
                    reward_coins : coins,
                    chest_level : userInfo.chest_level
                  };
                  return callback(JSON.stringify(result));
                  return ;
                } else {
                  var result = {
                    errorcode : 2201,
                    errormsg : '宝箱数目不足,不能领取!'
                  };
                  return callback(JSON.stringify(result));
                }
              }
            }
          }
          var result = {
            errorcode : 2201,
            errormsg : '宝箱数目不足,不能领取!'
          };
          return callback(JSON.stringify(result));
        });
      })(userInfo);
    });
  })(session_id, item_id);
}


exports.getChest = getChest;

function isChest(item_id) {
  if(item_id >= 1009 && item_id <= 1011) {
    return true;
  }
  return false;
}

function getRewardCoins(item_id) {
  if(item_id === 1009){
    return 100000;
  } else if(item_id === 1010){
    return 300000;
  } else if(item_id === 1011){
    return 500000;
  }
  return 0;
}

function getItemLevel(item_id) {
  if(item_id === 1009){
    return 1;
  } else if(item_id === 1010){
    return 2;
  } else if(item_id === 1011){
    return 3;
  }
  return 0;
}

function getRewardPer(level) {
  if(item_id === 1){
    return 1.03;
  } else if(item_id === 2){
    return 1.06;
  } else if(item_id === 3){
    return 1.1;
  }
  return 1;
}

exports.getRewardPer = getRewardPer;
