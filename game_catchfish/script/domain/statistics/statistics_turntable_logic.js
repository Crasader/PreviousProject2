
var statistics_db = require('./statistics_db.js');
var dbmanager = require('../../db/dbmanager.js');
var agreement = require('../../agreement.js');

/**
 * 插入一次玩家的抽奖统计
 *
 */
function insertOneUserTurnTableData(user_id, data, callback) {

  statistics_db.insertOneUserTurnTableData(dbmanager.getClient(), user_id, data, new Date().Format("yyyyMMdd"), function(success){
  });
  callback(agreement.successDesc);

}

exports.insertOneUserTurnTableData = insertOneUserTurnTableData;
