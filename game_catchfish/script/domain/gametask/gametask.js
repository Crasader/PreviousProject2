'use strict';

var player_info_service = require('../player/player_info_service.js');

var REDIS_HEAD_GAMETASK = 'GAMETASK_';

function getRedisKey(user_id) {
  return REDIS_HEAD_GAMETASK + user_id + '_'+ new Date().Format("yyyyMMdd");
}

exports.getRedisKey = getRedisKey;

function syncRewardsInfo(reward_lists, user_info) {
  player_info_service.syncRewardsInfo(reward_lists, user_info);
}

exports.syncRewardsInfo = syncRewardsInfo;
