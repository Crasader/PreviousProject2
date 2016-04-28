
var fishGroups = [];
var current_seq = 0;

var fish_group_manager = require('./fishGroupManager.js');

var SEQ_INTERVAL_DEFAULT = 10; // 产生序列间隔，单位秒，目前为10妙

/**
 * 计算下一次步进的结果
 *
 */
function oneStepWorking() {
  current_seq++;
  var item = {
    seq_id :  current_seq,  // 产生序列号
    seq_interval : SEQ_INTERVAL_DEFAULT,   // 产生序列间隔，单位毫秒，目前为10妙
    seq_create_time : new Date().getTime(),
    fish_group_info : fish_group_manager.getNextGroup()
  };
  fishGroups.push(item);
  if(fishGroups.length > 2) { // 只保留2帧数据
    fishGroups.shift();
  }
}

/**
 * 获取一次鱼群计算信息，返回结构化类信息
 * 目前返回测试数据[TODO]
 *
 */
function getOnceFishGroup() {
  if(fishGroups.length > 0) {
    return fishGroups[fishGroups.length - 1];
  }
  return [];
}

/**
 * 获取初始化的鱼群配置
 *
 *
 */
function getInitFishGroup() {
  return fishGroups;
}

/**
 * 初始化鱼群产生信息
 *
 */
function init() {
  oneStepWorking();
  oneStepWorking();
}

exports.init = init;
exports.getOnceFishGroup = getOnceFishGroup;
exports.oneStepWorking = oneStepWorking;
exports.getInitFishGroup = getInitFishGroup;
