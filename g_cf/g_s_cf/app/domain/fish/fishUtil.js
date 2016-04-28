
var config_fish = require('../../../config/domain/config_fish.json');

var coins = new Map();
var exps = new Map();

var success_init = false;

function init() { // 初始化配置金币和钻石信息
  if(success_init) {
    return ;
  }
  success_init = true;
  for( var i=0; i<config_fish.item_lists.length; i++ ) {
    coins.set(config_fish.item_lists[i].fish_id, config_fish.item_lists[i].baseReward.start);
    exps.set(config_fish.item_lists[i].fish_id, config_fish.item_lists[i].exp);
  }
}

exports.init = init;

function getCoinsByFishId(fish_id) {
  return coins.get(fish_id) === undefined ? 0 : coins.get(fish_id);
}

exports.getCoinsByFishId = getCoinsByFishId;


function getExpsByFishId(fish_id) {
  return exps.get(fish_id) === undefined ? 0 : exps.get(fish_id);
}

exports.getExpsByFishId = getExpsByFishId;

function isGoldFish(fish_id) {
  if(fish_id >= 40 && fish_id <= 59) {
    return true;
  } else if(fish_id >= 100 && fish_id <= 109) {
    return true;
  }
  return false;
}

exports.isGoldFish = isGoldFish;
