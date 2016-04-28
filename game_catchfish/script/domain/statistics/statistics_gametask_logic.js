
var statistics_db = require('./statistics_db.js');
var dbmanager = require('../../db/dbmanager.js');
var agreement = require('../../agreement.js');

/**
 * 记录一次美人鱼任务
 */
function insertOneMermaidTaskData(user_id, data, callback) {
  var roomId = parseInt(data.room_id);
  if(roomId <= 0 || roomId > 4) {
    callback(agreement.reqParamsErrorDesc);
    return ;
  }
  statistics_db.insertOneMermaidTaskData(dbmanager.getClient(), user_id, data, new Date().Format("yyyyMMdd"), function(success){
  });
  callback(agreement.successDesc);

}

function insertOnePresentedData(user_id, data, callback) {
  statistics_db.insertOnePresentedData(dbmanager.getClient(), user_id, data, new Date().Format("yyyyMMdd"), function(success){
  });
  callback(agreement.successDesc);

}

function insertOneBankruptData(user_id, data, callback) {
  var roomId = parseInt(data.room_id);
  if(roomId < 0 || roomId > 4) {
    callback(agreement.reqParamsErrorDesc);
  }
  statistics_db.insertOneBankruptData(dbmanager.getClient(), user_id, data, new Date().Format("yyyyMMdd"), function(success){
  });
  callback(agreement.successDesc);

}

function insertOneSkillUseData(user_id, data, callback) {
  statistics_db.insertOneSkillUseData(dbmanager.getClient(), user_id, data, new Date().Format("yyyyMMdd"), function(success){
  });
  callback(agreement.successDesc);
}




exports.insertOneMermaidTaskData = insertOneMermaidTaskData;
exports.insertOnePresentedData = insertOnePresentedData;
exports.insertOneBankruptData = insertOneBankruptData;
exports.insertOneSkillUseData = insertOneSkillUseData;
