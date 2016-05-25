'use strict';
/**
 * 成就任务逻辑处理
 */

//--------------------------------------------------------------------------------
// 变量声明

var dbmanager = require('../../db/dbmanager.js');
var gametask_achievement_db = require('./gametask_achievement_db.js');

var gametask_config = require('./gametask_config.js');
var session_manager = require('../../session_manager.js');
var agreement = require('../../agreement.js');
var redishelper = require('../../mem/redishelper.js');

var gametask = require('./gametask.js');

//--------------------------------------------------------------------------------
// 公开方法

/**
 * 获取玩家的成就任务
 */
function getTasklists(session_id, callback) {
  session_manager.isLogin(session_id, function(login, data){
    if(!login) {
      callback(data);
      return ;
    }
    var user_info = data;
    (function(user_info){
      getTasklistsByUserInfo(user_info, callback);
    })(user_info);
  });
}

exports.getTasklists = getTasklists;


//--------------------------------------------------------------------------------
// 内部方法

function getTasklistsByUserInfo(user_info, callback) {
  gametask_achievement_db.getAchievementTasklists(dbmanager.getClientS(), user_info.user_id, function(success, result) {
    if(success) {
      var c_result = {
        errorcode : 0,
        task_lists : gametask_config.getPlayerTask(result)
      };
      callback(JSON.stringify(c_result));
      return ;
    } else {
      var c_result = {
        errorcode : 0,
        task_lists : gametask_config.getDefaultTask()
      };
      callback(JSON.stringify(c_result));
      return ;
    }
  });
}

// TODO : 领取成就任务[更新db,发放奖励]
function getRewards(session_id, task_id, callback){
  task_id = parseInt(task_id);
  if( isNaN(task_id) || !isTaskId(task_id) ) {
    callback(agreement.reqParamsErrorDesc);
    return;
  }
  (function(task_id){
    session_manager.isLogin(session_id, function(login, data){
      if(!login) {
        callback(data);
        return ;
      }
      var user_info = data;
      (function(user_info){
        gametask_achievement_db.getAchievementTaskInfoById(dbmanager.getClientS(), user_info.user_id, task_id, function(success, result) {
          if(!success) {
            var client_result = {
              errorcode : 2301,
              errormsg : '当前任务未完成,不能领取!'
            };
            callback(JSON.stringify(client_result));
            return ;
          }
          console.log('gametask_achievement_db result : ' + JSON.stringify(result));
          if(result.user_get === 0) {  // 领取条件判断
            var require_nums = gametask_config.getAchievementRequireNums(result.task_id, result.current_level);
            console.log('gametask_achievement_db require_nums : ' + require_nums);
            if(require_nums === 0) {
              var client_result = {
                errorcode : 2303,
                errormsg : '任务未配置!不能领取!'
              };
              callback(JSON.stringify(client_result));
              return ;
            }
            if( result.current_nums >= require_nums) {
              var client_result = {
                errorcode : 0,
                reward_lists : gametask_config.getAchievementRewards(result.task_id, result.current_level)
              };
              var nextLevel = gametask_config.getNextLevelInfo(task_id, result.current_level, result.current_nums, require_nums);
              console.log('gametask_achievement_db nextLevel : ' + JSON.stringify(nextLevel));
              if(nextLevel === null) {  // 满级
                gametask_achievement_db.updateAchievementTaskInfoById( dbmanager.getClient(),
                  user_info.user_id, result.task_id, result.current_level, result.current_nums, 1, // 1,完成
                  function(result){});
              } else {
                client_result.next_level = nextLevel;
                gametask_achievement_db.updateAchievementTaskInfoById( dbmanager.getClient(),
                  user_info.user_id, nextLevel.achievement_task_id, nextLevel.current_level, nextLevel.current_nums, nextLevel.user_get,
                  function(result){});
              }
              console.log('getRewards to client : ' + JSON.stringify(client_result));
              callback(JSON.stringify(client_result));
              gametask.syncRewardsInfo(client_result.reward_lists, user_info);//更新玩家奖励信息
            } else {
              var client_result = {
                errorcode : 2301,
                errormsg : '当前任务未完成,不能领取!'
              };
              callback(JSON.stringify(client_result));
              return ;
            }
          } else {
            var client_result = {
              errorcode : 2302,
              errormsg : '当前任务奖励已经领取,不能重复领取!'
            };
            callback(JSON.stringify(client_result));
            return ;
          }
        });
      })(user_info);
    });
  })(task_id);

}

exports.getRewards = getRewards;

//--------------------------------------------------------------------------------
// 工具方法

/**
 * 是否为成就任务
 */
function isTaskId(task_id) {
  if(task_id >= 1 && task_id<= 10){
    return true;
  }
  return false;
}
