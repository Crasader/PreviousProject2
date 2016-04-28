
var fish_normal_manager = require('./fishNormalManager.js');

var normal_lists = [1, 2, 3]; // 鱼群配置文件
var climax_lists = [2, 4, 5]; // 鱼潮的类型

var SEQ_TIMES = 20;       // 标准间隔时间：10秒
var MAX_SEQ_NORMAL = 15;  // 普通鱼群最大间隔：30次（300秒，5分钟）
var MAX_SEQ_CLIMAX = 3;   // 鱼潮最大间隔：30次（300秒，5分钟）

var TYPE_UNKONWN = -1;
var TYPE_NORMAL = 0;
var TYPE_CLIMAX = 1;

var STATE_UNKONWN = -1;
var STATE_NORMAL = 0;
var STATE_CLIMAX = 1;
var STATE_CHANGE = 2;

var current_state = STATE_UNKONWN;

/**
 * 基本模式为鱼群 + 鱼潮的固定模式
 * 鱼潮固定为50秒间隔，鱼群固定间隔为3分钟
 */
var group_config = {
  current_type : TYPE_UNKONWN, // -1, 未初始化。 0,普通鱼群；1，鱼潮
  normal_nums : 3,
  normal_last : 0,
  normal_step : 0,
  climax_nums : 3,
  climax_last : 0,
  climax_step : 0
};

var moment = {
  group_type : 0, // -1, 未初始化。 0,普通鱼群；1，鱼潮
  sub_type : 1, // 普通或者鱼潮的具体类型
  seq : 1,
  seq_time : 10
};



function getNextGroup() {
  if(current_state === STATE_UNKONWN) {  // 未初始化
    return initGroup();
  } else if(current_state === STATE_NORMAL) {  // 鱼群进行中
    return normalGroupUpdate();
  } else if(current_state === STATE_CLIMAX) {  // 鱼潮进行中
    return normalClimaxUpdate();
  } else if(current_state === STATE_CHANGE) {  // 鱼群、鱼潮切换
    return changeGroup();
  }
}

exports.getNextGroup = getNextGroup;

function initGroup() {
  return newNormalGroup();
}

function changeGroup() {
  if(group_config.current_type === TYPE_NORMAL) {
    return newClimaxGroup();
  } else {
    return newNormalGroup();
  }
}

function newClimaxGroup() {
  current_state = STATE_CLIMAX;
  group_config.current_type = TYPE_CLIMAX;
  var new_p = parseInt(Math.random()*group_config.climax_nums);
  if(new_p === group_config.climax_last) {
    new_p = new_p + 1;
    if(new_p >= group_config.climax_nums ) {
      new_p = 0;
    }
  }
  group_config.climax_last = new_p;
  group_config.climax_step = 1;

  return {
    group_type : TYPE_CLIMAX,
    sub_type : climax_lists[group_config.climax_last],
    seq : group_config.climax_step,
    seq_time : SEQ_TIMES
  };
}

function normalClimaxUpdate() {
  group_config.climax_step = group_config.climax_step + 1;
  if( group_config.climax_step === MAX_SEQ_CLIMAX ) {
    current_state = STATE_CHANGE;
  }
  return {
    group_type : TYPE_CLIMAX,
    sub_type : climax_lists[group_config.climax_last],
    seq : group_config.climax_step,
    seq_time : SEQ_TIMES
  };
}

var normalFishes;

function newNormalGroup() {
  current_state = STATE_NORMAL;
  group_config.current_type = TYPE_NORMAL;
  var new_p = parseInt(Math.random()*group_config.normal_nums);
  if(new_p === group_config.normal_last) {
    new_p = new_p + 1;
    if(new_p >= group_config.normal_nums ) {
      new_p = 0;
    }
  }
  group_config.normal_last = new_p;
  group_config.normal_step = 1;
  normalFishes = fish_normal_manager.createNormalFile(normal_lists[group_config.normal_last]);
  return {
    group_type : TYPE_NORMAL,
    sub_type : normal_lists[group_config.normal_last],
    seq : group_config.normal_step,
    seq_time : SEQ_TIMES,
    fishes : group_config.normal_step <= normalFishes.length ? normalFishes[group_config.normal_step - 1] : []
  };
}

function normalGroupUpdate() {
  group_config.normal_step = group_config.normal_step + 1;
  if( group_config.normal_step === MAX_SEQ_NORMAL ) {
    current_state = STATE_CHANGE;
  }
  return {
    group_type : TYPE_NORMAL,
    sub_type : normal_lists[group_config.normal_last],
    seq : group_config.normal_step,
    seq_time : SEQ_TIMES,
    fishes : group_config.normal_step <= normalFishes.length ? normalFishes[group_config.normal_step - 1] : []
  };
}
