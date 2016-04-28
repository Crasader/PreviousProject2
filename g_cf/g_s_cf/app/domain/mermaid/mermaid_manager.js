'use strict';

var MERMAID_ROUND_TIME = 720;
var MERMAID_TASK_TIME = 300;

var current_start_time = 0;  // 计时器
var current_task_id = 0;  // 当前任务id
var current_task_info = null;

/**
 * 时间行者
 */
function nextStep(sec) {
  if(sec <=  0) {
    return null;
  }
  current_start_time -= sec;
  if(current_start_time >= 0) {
    if(current_start_time === (MERMAID_ROUND_TIME - MERMAID_TASK_TIME) ) { // 任务结束
      current_task_info = null;
    }
    return null;
  }
  current_start_time = MERMAID_ROUND_TIME;  // 重新设置
  current_task_id++;
  current_task_info = {
    task_id : current_task_id,  // 当前任务id
    fish_ids : [
      {fish_id : 1 + parseInt(Math.random()*10), nums : 2},
      {fish_id : 30 + parseInt(Math.random()*7), nums : 1},
      {fish_id : 40 + parseInt(Math.random()*4), nums : 1}
    ],  // 任务鱼列表[注意，当前客户端任务列表为3个写死，一定下发固定数目]
    start_time : new Date().getTime(),  // 任务开始时间
    task_time : MERMAID_TASK_TIME // 任务持续时间
  }
  return current_task_info;
}

exports.nextStep = nextStep;

/**
 * 获取当前的任务信息
 */
function getCurrentTaskInfo() {
  return current_task_info;
}

exports.getCurrentTaskInfo = getCurrentTaskInfo;

function getTaskLeftTime(start_time) {
  var last_time = parseInt( (new Date().getTime() - start_time)/1000 );
  if(MERMAID_TASK_TIME >= last_time) {
    return MERMAID_TASK_TIME - last_time;
  }
  return 0;
}
exports.getTaskLeftTime = getTaskLeftTime;

function getMermaidFishIds(fish_ids) {
  console.log('molo_debug_getMermaidFishIds, fish_ids = ' + fish_ids);
  console.log(JSON.stringify(current_task_info));
  var result = [];
  if(current_task_info === null || fish_ids.length <= 0) {
    return result;
  }

  for(var i=0;i<fish_ids.length;i++){
    if( isMermaiFishId(parseInt(fish_ids[i])) ){
      result.push(parseInt(fish_ids[i]));
    }
  }
  return result;
}

exports.getMermaidFishIds = getMermaidFishIds;


function isMermaiFishId(fish_id) {
  if(current_task_info === null) {
    return false;
  }
  for(var i=0;i<current_task_info.fish_ids.length;i++){
    if(current_task_info.fish_ids[i].fish_id === fish_id) {
      return true;
    }
  }
  return false;
}

function createNewUserTask(mermaid_new_fish_ids){
  var result = {
    task_id : current_task_info.task_id,
    fish_ids : [],
    coins : 0,
    success : 0
  }
  for(var i=0;i<current_task_info.fish_ids.length;i++) {
    result.fish_ids[i] = {
      fish_id : current_task_info.fish_ids[i].fish_id,
      nums : current_task_info.fish_ids[i].nums,
      current_nums : 0
    };
    for(var j=0;j<mermaid_new_fish_ids.length;j++) {
      if(result.fish_ids[i].fish_id === mermaid_new_fish_ids[j]) {
        result.fish_ids[i].current_nums += 1;
      }
    }
  }
  return result;
}

exports.createNewUserTask = createNewUserTask;

function isSuccess(mermaid_task_info) {
  console.log(JSON.stringify(mermaid_task_info));
  for(var i=0;i<mermaid_task_info.fish_ids.length;i++) {
    console.log(JSON.stringify(mermaid_task_info));
    if(mermaid_task_info.fish_ids[i].current_nums < mermaid_task_info.fish_ids[i].nums) {
      return false;
    }
  }
  return true;
}

exports.isSuccess = isSuccess;

// nextStep(20);
// nextStep(20);
// console.log(JSON.stringify(getCurrentTaskInfo()));
// var result = createNewUserTask([current_task_info.fish_ids[0].fish_id]);
// console.log(JSON.stringify(result));
// console.log(isSuccess(result));

// console.log(getMermaidFishIds([1,2,3,4,5,6,7,8,9,10]));
