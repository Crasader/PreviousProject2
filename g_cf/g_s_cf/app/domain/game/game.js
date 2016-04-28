var userMap = new Map();
exports.userMap = userMap;

var fish_util = require('../fish/fishUtil.js');

var USER_KEY_HEAD = 'g_';

exports.USER_KEY_HEAD = USER_KEY_HEAD;

var config_turrent = require('../../../config/domain/config_turrent.json');
var config_exp = require('../../../config/domain/config_user_exp.json');

function init(){
  console.log('game init ... ');
  fish_util.init();
}
exports.init = init;

function getLevelUpdateRequireDiamond(turrent_level) {
  for ( var i=0; i<config_turrent.item_list.length; i++ ) {
    if(config_turrent.item_list[i].turrent_id === turrent_level) {
      if( (i+1) < config_turrent.item_list.length ) {
        return parseInt(config_turrent.item_list[i+1].unlock_price);
      } else {
        return 0; // 表示满级
      }
    }
  }
  console.log('ERROR TURRENT_LEVEL');
  return -1;  // 表示没有渠道配置
}

exports.getLevelUpdateRequireDiamond = getLevelUpdateRequireDiamond;

function getLevelUpdateRewardCoins(turrent_level) {
  for ( var i=0; i<config_turrent.item_list.length; i++ ) {
    if(config_turrent.item_list[i].turrent_id === turrent_level) {
      return parseInt(config_turrent.item_list[i].reward_list[0].num);
    }
  }
}

exports.getLevelUpdateRewardCoins = getLevelUpdateRewardCoins;

function getNextLevel(turrent_level) {
  for ( var i=0; i<config_turrent.item_list.length; i++ ) {
    if(config_turrent.item_list[i].turrent_id === turrent_level) {
      if( (i+1) < config_turrent.item_list.length) {
        return parseInt(config_turrent.item_list[i+1].turrent_id);
      }
      return 0;
    }
  }
}

exports.getNextLevel = getNextLevel;

function expUpdate(exp_before, exp_end) {
  var level_before = getExpLevel(exp_before);
  var level_end = getExpLevel(exp_end);
  var result = {
    errorcode : 0,
    user_level_up_infos : []
  };
  if(level_end > level_before) {
    for(var i=level_before+1; i<=level_end; i++) {
      result.user_level_up_infos.push({
        level : i,
        rewards : config_exp.item_list[i].reward_list
      });
    }
    return result;
  }
  return result;
}

exports.expUpdate = expUpdate;

function getExpLevel(exp) {
  for(var i=config_exp.item_list.length-1; i>=0; i--) {
    if(exp > config_exp.item_list[i].require_exp) {
      return config_exp.item_list[i].level_id;
    }
  }
  return 1;
}

function getCoinsByFishes(fishes) {
  var result = 0;
  for(var i=0; i<fishes.length; i++) {
    result += fish_util.getCoinsByFishId(fishes[i]);
  }
  return result;
}

exports.getCoinsByFishes = getCoinsByFishes;

function getExpsByFishes(fishes) {
  var result = 0;
  for(var i=0; i<fishes.length; i++) {
    result += fish_util.getExpsByFishId(fishes[i]);
  }
  return result;
}

exports.getExpsByFishes = getExpsByFishes;

/**
 * 是否为黄金鱼
 */
function isGoldFish(fish_id) {
  return  fish_util.isGoldFish(parseInt(fish_id));
}

exports.isGoldFish = isGoldFish;

/**
 * 是否为黄金鱼
 */
function getGoldFishNums(fishes) {
  var nums = 0;
  for(var i=0;i<fishes.length;i++) {
    if(isGoldFish(fishes[i])) {
      nums++;
    }
  }
  return nums;
}

exports.getGoldFishNums = getGoldFishNums;

/**
 * 是否为黄金鱼
 */
function getMagnateItem() {
  var nums = parseInt(Math.random()*20);
  if(nums < 4) {
    return 1005;
  } else if(nums < 10) {
    return 1003;
  }
  return 1004;
}

exports.getMagnateItem = getMagnateItem;

function allowEnter(room_id, turrent_level) {
  console.log('room_id = ' + room_id + ';turrent_level = ' + turrent_level);
  if(room_id === 1){
    return true;
  }else if(room_id === 2 && turrent_level >= 30) {
    return true;
  }else if(room_id === 3 && turrent_level >= 100) {
    return true;
  }else if(room_id === 4 && turrent_level >= 300) {
    return true;
  }
  return false;
}

exports.allowEnter = allowEnter;

fish_util.init();
// var current_level = 1;
// for(var i=0;i<36;i++){
//
//   console.log(current_level + ' : ' + getLevelUpdateRequireDiamond(current_level));
//   current_level = getNextLevel(current_level);
// }
