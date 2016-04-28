
var statistics_db = require('./statistics_db.js');
var dbmanager = require('../../db/dbmanager.js');
var agreement = require('../../agreement.js');

/**
 * 插入一次玩家的消耗统计
 *
 */
function insertOneUserExpendData(user_id, data, callback) {

  statistics_db.insertOneUserExpendData(dbmanager.getClient(), user_id, data, new Date().Format("yyyyMMdd"), function(success){
  });
  callback(agreement.successDesc);

}

exports.insertOneUserExpendData = insertOneUserExpendData;
