'use strict';

var bag_service = require('../bag/bag_service.js');
var bag_logic = require('./bag_logic.js');
var redishelper = require('../../mem/redishelper.js');
var session_manager = require('../../session_manager.js');

function syncRewardsInfo(reward_lists, user_info) {
  syncPlayerCoinsAndDiamonds(reward_lists, user_info);
  bag_logic.addBagItems(user_info.session_id, reward_lists, function(result){});
}

exports.syncRewardsInfo = syncRewardsInfo;

function syncMoInfo(user_info, type) {
  bag_service.syncUserInfoDb(user_info.user_id, user_info.fortune_id, type,
      user_info.mo, function(result){});
}

exports.syncMoInfo = syncMoInfo;

function syncPlayerCoinsAndDiamonds(reward_lists, user_info) {
  for(var j=0;j<reward_lists.length;j++) {
    if(reward_lists[j].item_id === 1001) {
      user_info.coins += reward_lists[j].nums;
      bag_service.syncUserInfoDb(user_info.user_id, user_info.fortune_id, reward_lists[j].item_id,
          user_info.coins, function(result){});
    } else if(reward_lists[j].item_id === 1002) {
      user_info.diamonds += reward_lists[j].nums;
      bag_service.syncUserInfoDb(user_info.user_id, user_info.fortune_id, reward_lists[j].item_id,
          user_info.diamonds, function(result){});
    }
  }
  redishelper.setValueWithExpire(user_info.session_id, JSON.stringify(user_info), session_manager.SESSION_EXPIRE);
}
