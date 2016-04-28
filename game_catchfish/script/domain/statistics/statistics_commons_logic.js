
var statistics_db = require('./statistics_db.js');
var dbmanager = require('../../db/dbmanager.js');
var agreement = require('../../agreement.js');

/**
 * 插入一天鱼捕获记录
 *
 */
function insertOneUserCommonEventData(user_id, data, callback) {
  statistics_db.insertOneUserCommonEventData(dbmanager.getClient(), user_id, data, new Date().Format("yyyyMMdd"), function(success){
  });
  callback(agreement.successDesc);
}

/**
 * 插入一个角色的某个等级升级用时
 *
 */
function insertOneUserTurrentLevelChangeData(user_id, data, callback) {
  statistics_db.insertOneUserTurrentLevelChangeData(dbmanager.getClient(), user_id, data, new Date().Format("yyyyMMdd"), function(success){
  });
  callback(agreement.successDesc);
}

exports.insertOneUserCommonEventData = insertOneUserCommonEventData;
exports.insertOneUserTurrentLevelChangeData = insertOneUserTurrentLevelChangeData;
