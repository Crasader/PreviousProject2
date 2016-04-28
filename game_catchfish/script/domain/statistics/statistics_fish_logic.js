
var statistics_db = require('./statistics_db.js');
var dbmanager = require('../../db/dbmanager.js');
var agreement = require('../../agreement.js');

/**
 * 插入一天鱼捕获记录
 *
 */
function insertOneUserFishData(user_id, data, callback) {
  var roomId = parseInt(data.room_id);
  if(roomId <= 0 || roomId > 4) {
    callback(agreement.reqParamsErrorDesc);
  }
  statistics_db.insertOneUserFishData(dbmanager.getClient(), user_id, data, new Date().Format("yyyyMMdd"), function(success){
  });
  callback(agreement.successDesc);

}

exports.insertOneUserFishData = insertOneUserFishData;
