
var agreement = require('../../agreement.js');
var statistics_fish_logic = require('./statistics_fish_logic.js');
var statistics_gametask_logic = require('./statistics_gametask_logic.js');
var statistics_commons_logic = require('./statistics_commons_logic.js');
var statistics_page_logic = require('./statistics_page_logic.js');
var statistics_turntable_logic = require('./statistics_turntable_logic.js');
var statistics_expend_logic = require('./statistics_expend_logic.js');

/**
 * game_version : 游戏内部版本号
 *
 */
function insertOneUserData( user_id, dataStr, callback) {

  var data = JSON.parse(dataStr);
  var data_type = parseInt(data.data_type);
  // console.log('data_type = ' + data_type);
  // 根据marktype分发写入数据库
  if(data_type === 1) { // 鱼捕获
    statistics_fish_logic.insertOneUserFishData(user_id,  data, function(result){
      callback(result);
    });
    return ;
  } else if(data_type === 2) { // 游戏-美人鱼任务
    statistics_gametask_logic.insertOneMermaidTaskData(user_id,  data, function(result){
      callback(result);
    });
    return ;
  } else if(data_type === 3) { // 游戏-赠送统计
    statistics_gametask_logic.insertOnePresentedData(user_id,  data, function(result){
      callback(result);
    });
    return ;
  } else if(data_type === 4) { // 游戏-破产统计
    statistics_gametask_logic.insertOneBankruptData(user_id,  data, function(result){
      callback(result);
    });
    return ;
  } else if(data_type === 5) { // 游戏-道具使用统计
    statistics_gametask_logic.insertOneSkillUseData(user_id,  data, function(result){
      callback(result);
    });
    return ;
  } else if(data_type === 6) { // 页面跳转统计
    statistics_page_logic.insertOneUserPageChangeData(user_id,  data, function(result){
      callback(result);
    });
    return ;
  } else if(data_type === 7) { // 扩展事件统计
    statistics_commons_logic.insertOneUserCommonEventData(user_id,  data, function(result){
      callback(result);
    });
    return ;
  } else if(data_type === 8) { // 统计炮台升级用时
    statistics_commons_logic.insertOneUserTurrentLevelChangeData(user_id,  data, function(result){
      callback(result);
    });
    return ;
  } else if(data_type === 9) { // 统计抽奖活动
    statistics_turntable_logic.insertOneUserTurnTableData(user_id,  data, function(result){
      callback(result);
    });
    return ;
  }  else if(data_type === 10) { // 统计消耗信息
    statistics_expend_logic.insertOneUserExpendData(user_id,  data, function(result){
      callback(result);
    });
    return ;
  }
  callback(agreement.reqParamsErrorDesc);
}

exports.insertOneUserData = insertOneUserData;
