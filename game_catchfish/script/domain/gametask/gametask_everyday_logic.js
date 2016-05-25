'use strict';
/**
 * 背包逻辑
 */

var gametask_config = require('./gametask_config.js');
var session_manager = require('../../session_manager.js');
var agreement = require('../../agreement.js');
var redishelper = require('../../mem/redishelper.js');

var bag_service = require('../bag/bag_service.js');
var bag_logic = require('../player/bag_logic.js');

var gametask = require('./gametask.js');

function getEveryday(session_id, callback) {
  session_manager.isLogin(session_id, function(login, data){
    if(!login) {
      callback(data);
      return ;
    }
    var user_info = data;
    var r_key = gametask.getRedisKey(user_info.user_id);
    (function(user_info, r_key){
      redishelper.getVaule(r_key, function(err, redis_result) {
        if(err) {
          callback(agreement.redisErrorDesc);
          return ;
        }
        if(redis_result != undefined && redis_result != null) {
          // redishelper.del(r_key);  // TODO : 调试测试
          callback(redis_result);
          return ;
        } else {
          var result = gametask_config.getEveryTask(user_info.turrent_level);
          redishelper.setValueWithExpire(r_key, JSON.stringify(result), redishelper.getTillTomorrowDayEndLeftSeconds());
          callback(JSON.stringify(result));
          return ;
        }
      });
    })(user_info, r_key);
  });
}

exports.getEveryday = getEveryday;

function getEverydayReward(session_id, every_task_id, callback) {
  if( isNaN(every_task_id) || !isEveryTaskId(parseInt(every_task_id)) ) {
    callback(agreement.reqParamsErrorDesc);
    return;
  }
  every_task_id = parseInt(every_task_id);
  (function(every_task_id){
    session_manager.isLogin(session_id, function(login, data){
      if(!login) {
        callback(data);
        return ;
      }
      console.log('getEverydayReward');
      var user_info = data;
      var r_key = gametask.getRedisKey(user_info.user_id);
      (function(user_info, r_key){
        redishelper.getVaule(r_key, function(err, redis_result) {
          if(err) {
            callback(agreement.redisErrorDesc);
            return ;
          }
          if(redis_result != undefined && redis_result != null) {
            var every_gametsk_info = JSON.parse(redis_result);
            for(var i=0;i<every_gametsk_info.task_lists.length;i++) {
              if(every_gametsk_info.task_lists[i].every_task_id === every_task_id) {
                if(every_gametsk_info.task_lists[i].user_get === 0 &&
                    every_gametsk_info.task_lists[i].task_require_nums <= every_gametsk_info.task_lists[i].current_nums) {
                  var client_result = {
                    errorcode : 0,
                    reward_lists : every_gametsk_info.task_lists[i].reward_lists
                  };
                  every_gametsk_info.task_lists[i].user_get = 1;
                  redishelper.setValueWithExpire(r_key, JSON.stringify(every_gametsk_info), redishelper.getTillTomorrowDayEndLeftSeconds());
                  callback(JSON.stringify(client_result));
                  gametask.syncRewardsInfo(every_gametsk_info.task_lists[i].reward_lists, user_info);
                  return ;
                }else {
                  var client_result = {
                    errorcode : 2302,
                    errormsg : '当前任务奖励已经领取,不能重复领取!'
                  };
                  callback(JSON.stringify(client_result));
                  return ;
                }
              }
            }
            var client_result = {
              errorcode : 2301,
              errormsg : '当前任务未完成,不能领取!'
            };
            callback(JSON.stringify(client_result));
            return ;
          } else {
            var result = gametask_config.getEveryTask(user_info.turrent_level);
            redishelper.setValueWithExpire(r_key, JSON.stringify(result), redishelper.getTillTomorrowDayEndLeftSeconds());
            var client_result = {
              errorcode : 2303,
              errormsg : '今日还没有开启任务!'
            };
            callback(JSON.stringify(client_result));
            return ;
          }
        });
      })(user_info, r_key);
    });
  })(every_task_id);
}

exports.getEverydayReward = getEverydayReward;

/**
 * 是否为每日任务
 */
function isEveryTaskId(every_task_id) {
  if(every_task_id >= 1 && every_task_id<= 4){  // TODO  :后期走配置
    return true;
  }
  return false;
}
