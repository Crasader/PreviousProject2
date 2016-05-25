
var help_db = require('./help_db.js');
var dbmanager = require('../../db/dbmanager.js');
var agreement = require('../../agreement.js');

function insertOneFeedBack(user_id, info, create_time, callback) {
  help_db.insertOneFeedBack(dbmanager.getClient(), user_id, info, create_time, function(success){
  });
  callback(agreement.successDesc);
}

exports.insertOneFeedBack = insertOneFeedBack;
