'use strict';
/**
 * 每日任务和成就任务信息更新接口.
 *
 */

Date.prototype.Format = function (fmt) {
  var o = {
    "M+": this.getMonth() + 1,
    "d+": this.getDate(),
    "h+": this.getHours(),
    "m+": this.getMinutes(),
    "s+": this.getSeconds(),
    "q+": Math.floor((this.getMonth() + 3) / 3),
    "S": this.getMilliseconds()
  };
  if (/(y+)/.test(fmt)){
    fmt = fmt.replace(RegExp.$1, (this.getFullYear() + "").substr(4 - RegExp.$1.length));
  }
  for ( var k in o ) {
    if ( new RegExp("(" + k + ")").test(fmt) ) {
      fmt = fmt.replace(RegExp.$1, (RegExp.$1.length == 1) ?
          (o[k]) : (("00" + o[k]).substr(("" + o[k]).length)));
    }
  }
  return fmt;
}

var REDIS_HEAD_GAMETASK = 'GAMETASK_';
var gametask_config = require('./gametask_config.js');
var redishelper = require('../../../environment/mem/redishelper.js');

/**
 * 捕获黄金鱼
 * @param {Object} fish_nums 捕获的黄金鱼数目
 */
 function catchGoldfish(user_id, turrent_level, fish_nums, callback) {
   dealEverydayTask(user_id, turrent_level, 1, fish_nums, callback);
 }

 exports.catchGoldfish = catchGoldfish;

/**
 * 使用道具.每次使用一个道具.
 * @param {Object} fish_nums 捕获的黄金鱼数目
 */
function useSkill(user_id, turrent_level, item_id, callback) {
  console.log('useSkill : item_id = ' + item_id);
  var item_id = parseInt(item_id);
  if(item_id >= 1003 && item_id <= 1007) {
    dealEverydayTask(user_id, turrent_level, 2, 1, callback);
  }
  callback(false, '');
}

exports.useSkill = useSkill;

/**
 * 升级炮台.每次升一级.
 */
function upgradeTurrent(user_id, turrent_level, callback) {
  dealEverydayTask(user_id, turrent_level, 3, 1, callback);
}

exports.upgradeTurrent = upgradeTurrent;

function dealEverydayTask(user_id, turrent_level, task_id, addNums, callback) {
  var r_key = getRedisKey(user_id);
  (function(r_key){
    getEveryday(r_key, turrent_level, function(success, taskObj){
      if(!success) {
        callback(false, '');
        return ;
      }
      var result = updateEverytaskInfo(r_key, taskObj, task_id, addNums);
      callback(result === '' ? false : true, result);
    });
  })(r_key);
}

function updateEverytaskInfo(r_key, taskObj, task_id, addNums) {
  for(var i=0;i<taskObj.task_lists.length;i++) {
    if(taskObj.task_lists[i].every_task_id === task_id) {
      if(taskObj.task_lists[i].user_get === 0) {
        taskObj.task_lists[i].current_nums += addNums;
        updateEveryday(r_key, taskObj);
        if(taskObj.task_lists[i].current_nums === taskObj.task_lists[i].task_require_nums) {
          return '恭喜您完成每日任务：' + taskObj.task_lists[i].task_content + ',可返回大厅领取.';
        }else {
          return '';
          // return '每日任务' + taskObj.task_lists[i].task_content +
          //     '[' + taskObj.task_lists[i].current_nums + '/' + taskObj.task_lists[i].task_require_nums + ']';
        }
      }else {
        return '';
      }
    }
  }
  return '';
}

function getRedisKey(user_id) {
  return REDIS_HEAD_GAMETASK + user_id + '_'+ new Date().Format("yyyyMMdd");
}

function getEveryday(r_key, turrent_level, callback) {
  (function(r_key, turrent_level){
    redishelper.getVaule(r_key, function(err, redis_result) {
      if(err) {
        console.log('getEveryday err : ' + err);
        callback(false, agreement.redisErrorDesc);
        return ;
      }
      if(redis_result != undefined && redis_result != null) {
        callback(true, JSON.parse(redis_result));
        return ;
      } else {
        var result = gametask_config.getEveryTask(turrent_level);
        redishelper.setValueWithExpire(r_key, JSON.stringify(result), redishelper.getTillTomorrowDayEndLeftSeconds());
        callback(true, result);
        return ;
      }
    });
  })(r_key, turrent_level);
}

function updateEveryday(r_key, taskObj){
  redishelper.setValueWithExpire(r_key, JSON.stringify(taskObj), redishelper.getTillTomorrowDayEndLeftSeconds());
}
