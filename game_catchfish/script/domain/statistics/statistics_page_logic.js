
var statistics_db = require('./statistics_db.js');
var dbmanager = require('../../db/dbmanager.js');
var agreement = require('../../agreement.js');

/**
 * 插入一天鱼捕获记录
 *
 */
function insertOneUserPageChangeData(user_id, data, callback) {
  statistics_db.insertOneUserPageChangeData(dbmanager.getClient(), user_id, data, new Date().Format("yyyyMMdd"), function(success){
  });
  callback(agreement.successDesc);

}

exports.insertOneUserPageChangeData = insertOneUserPageChangeData;
