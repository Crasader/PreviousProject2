'use strict';
/**
 * 成就任务和成就任务信息更新接口.
 *
 */

var dbmanager = require('../../../environment/db/dbmanager.js');
var gametask_achievement_db = require('./gametask_achievement_db.js');

/**
 *  成就任务：捕获鱼的条数[task_id = 3]
 */
function addCatchfishNums(user_id, add_nums, callback) {
  if(add_nums < 0){
    callback(false, '');
    return ;
  }
  gametask_achievement_db.addAchievementTaskCurrentNumsById(dbmanager.getClient(),
      user_id, 3, add_nums, function(result){
    callback(false, '');  // TODO : 目前全部返回false，true意味着消息推送
  });
}

exports.addCatchfishNums = addCatchfishNums;

/**
 *  成就任务：捕获黄金鱼的条数[task_id = 4]
 */
function addCatchGoldfishNums(user_id, add_nums, callback) {
  if(add_nums < 0){
    callback(false, '');
    return ;
  }
  gametask_achievement_db.addAchievementTaskCurrentNumsById(dbmanager.getClient(),
      user_id, 4, add_nums, function(result){
    callback(false, '');  // TODO : 目前全部返回false，true意味着消息推送
  });
}

exports.addCatchGoldfishNums = addCatchGoldfishNums;

/**
 *  成就任务：捕获BOSS鱼的条数[task_id = 5][霸炒鱿鱼]
 */
function addBossfishNums(user_id, add_nums, callback) {
  if(add_nums < 0){
    callback(false, '');
    return ;
  }
  gametask_achievement_db.addAchievementTaskCurrentNumsById(dbmanager.getClient(),
      user_id, 5, add_nums, function(result){
    callback(false, '');  // TODO : 目前全部返回false，true意味着消息推送
  });
}

exports.addBossfishNums = addBossfishNums;

/**
 *  成就任务：使用技能
 *  7-传奇射手(使用锁定[1004])
 *  8-鲨鱼冻饮(使用冰冻[1003])
 */
function useSkill(user_id, item_id, callback) {
  var task_id = 0;
  item_id = parseInt(item_id);
  if(item_id === 1004) {
    task_id = 7;
  }else if(item_id === 1003) {
    task_id = 8;
  }
  gametask_achievement_db.addAchievementTaskCurrentNumsById(dbmanager.getClient(),
      user_id, task_id, 1, function(result){
    callback(false, '');  // TODO : 目前全部返回false，true意味着消息推送
  });
}

exports.useSkill = useSkill;

/**
 *  成就任务：撸啊撸[task_id = 9]
 */
function fire(user_id, add_nums, callback) {
  if(add_nums < 0){
    callback(false, '');
    return ;
  }
  gametask_achievement_db.addAchievementTaskCurrentNumsById(dbmanager.getClient(),
      user_id, 9, add_nums, function(result){
    callback(false, '');  // TODO : 目前全部返回false，true意味着消息推送
  });
}

exports.fire = fire;

/**
 *  成就任务：同步升级后的炮台等级[task_id = 10][良师炮友]
 */
function syncMaxTurrentLevel(user_id, turrent_level, callback) {
  if(turrent_level <= 1){
    callback(false, '');
    return ;
  }
  gametask_achievement_db.changeAchievementTaskCurrentNumsById(dbmanager.getClient(),
      user_id, 10, turrent_level, function(result){
    callback(false, '');  // TODO : 目前全部返回false，true意味着消息推送
  });
}

exports.syncMaxTurrentLevel = syncMaxTurrentLevel;


/**
 *  成就任务：同步升级后的炮台等级[task_id = 6][疯狂海神]
 */
function newMaxCoins(user_id, max_coins, callback) {
  gametask_achievement_db.changeAchievementTaskCurrentNumsById(dbmanager.getClient(),
      user_id, 6, max_coins, function(result){
    callback(false, '');  // TODO : 目前全部返回false，true意味着消息推送
  });
}

exports.newMaxCoins = newMaxCoins;

/**
 *  获取玩家目前达到过的最大金币数目
 */
function getMaxCoins(user_id, callback) {
  getAchievementTaskInfoById(user_id, 6, function(success, result){
    if(success){
      callback(true, result.current_nums);
    }else {
      callback(true, 200);
    }
  });
}

exports.getMaxCoins = getMaxCoins;


/**
 *  查询某个成就任务的信息
 */
function getAchievementTaskInfoById(user_id, task_id, callback) {
  gametask_achievement_db.getAchievementTaskInfoById(dbmanager.getClient(),
      user_id, task_id, function(success, result){
    callback(success, result);
  });
}
