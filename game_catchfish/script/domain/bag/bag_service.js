'use strict';
var dbmanager = require('../../db/dbmanager.js');
var bag_db = require('./bag_db.js');


function syncUserInfoDb(user_id, fortune_id, item_id, nums, callback) {
  if(item_id === 1001) {
    bag_db.syncUserInfo(dbmanager.getClient(), user_id, fortune_id, 'coins', nums, function(result){});
  }else if(item_id === 1002) {
    bag_db.syncUserInfo(dbmanager.getClient(), user_id, fortune_id, 'diamonds', nums, function(result){});
  }else if(item_id === 999) {  // mo金额更新
    bag_db.syncUserInfo(dbmanager.getClient(), user_id, fortune_id, 'mo', nums, function(result){});
  }else if(item_id === 998) {  // mo金额更新+首充礼包
    bag_db.syncUserInfo(dbmanager.getClient(), user_id, fortune_id, 'mo', nums, function(result){});
    bag_db.syncUserInfo(dbmanager.getClient(), user_id, fortune_id, 'mo_first', 1, function(result){});
  }else if(item_id === 997) {  // mo金额更新+金币首充
    bag_db.syncUserInfo(dbmanager.getClient(), user_id, fortune_id, 'mo', nums, function(result){});
    bag_db.syncUserInfo(dbmanager.getClient(), user_id, fortune_id, 'mo_coins', 1, function(result){});
  }
  callback(true);
}
exports.syncUserInfoDb = syncUserInfoDb;
