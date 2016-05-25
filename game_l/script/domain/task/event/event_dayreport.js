/**
 * 渠道日报的一天统计任务
 */
var dbmanager_catchfish = require('../../../db/dbmanager_catchfish.js');
var event_dayreport_db = require('./event_dayreport_db.js');

/**
 * dayNum， 日期的数字格式
 */
function startOneDayTask(dayNum) {
  console.log('[event]startOneDayTask : ' + dayNum);

  fishInfo(dayNum);
  bankruptInfo(dayNum);
  mermaidTaskInfo(dayNum);
  pageChangeInfo(dayNum);
  presentedUserInfo(dayNum);
  skillUserInfo(dayNum);
  turrentLevelUpdateInfo(dayNum);
  turntableInfo(dayNum);
  turntableInfoForNew(dayNum);
  expendInfo(dayNum);
  turrentLevelGroup(dayNum);
  userExpInfo(dayNum);
  userExpInfoForNew(dayNum);
}

function test(dayNum) {
}

exports.test = test;

function userExpInfo(dayNum) {
  event_dayreport_db.getUserExpInfo(dbmanager_catchfish.getClientS(), dayNum,
      function(success, results, dayNum){
    if(success && results.length > 0) {
      var items = [];
      for(var i=0;i<results.length; i++) {
        // day, exp_level, nums
        var item = [dayNum, results[i]['exp_level'], results[i]['nums']];
        items[i] = item;
      }
      event_dayreport_db.insertUserExpInfo(dbmanager_catchfish.getClient(), items, function(success){
      });
    }
  });
}

function userExpInfoForNew(dayNum) {
  event_dayreport_db.getUserExpInfoForNew(dbmanager_catchfish.getClientS(), dayNum,
      function(success, results, dayNum){
    if(success && results.length > 0) {
      var items = [];
      for(var i=0;i<results.length; i++) {
        // day, exp_level, nums
        var item = [dayNum, results[i]['exp_level'], results[i]['nums']];
        items[i] = item;
      }
      event_dayreport_db.insertUserExpInfoForNew(dbmanager_catchfish.getClient(), items, function(success){
      });
    }
  });
}


function bankruptInfo(dayNum) {
  bankruptInfoByType(dayNum, 2);
  bankruptInfoByType(dayNum, 1);
  bankruptInfoByTypeForNew(dayNum, 2);
  bankruptInfoByTypeForNew(dayNum, 1);
}

/**
 * 破产-计算基本信息
 */
function bankruptInfoByType(dayNum, type) {
  event_dayreport_db.getBankruptInfo(dbmanager_catchfish.getClientS(), dayNum, type,
      function(success, results, dayNum, type){
    if(success && results.length > 0) {
      var items = [];
      for(var i=0;i<results.length; i++) {
        var item = [dayNum,
          results[i]['nums'] === null ? 0 : results[i]['nums'],
          results[i]['counts'] === null ? 0 : results[i]['counts'] ];
        items[i] = item;
      }
      event_dayreport_db.insertBankruptInfo(dbmanager_catchfish.getClient(), type, items, function(success){
      });
    }
  });
}

function bankruptInfoByTypeForNew(dayNum, type) {
  event_dayreport_db.getBankruptInfoForNew(dbmanager_catchfish.getClientS(), dayNum, type,
      function(success, results, dayNum, type){
    if(success && results.length > 0) {
      var items = [];
      for(var i=0;i<results.length; i++) {
        var item = [dayNum,
          results[i]['nums'] === null ? 0 : results[i]['nums'],
          results[i]['counts'] === null ? 0 : results[i]['counts'] ];
        items[i] = item;
      }
      event_dayreport_db.insertBankruptInfoForNew(dbmanager_catchfish.getClient(), type, items, function(success){
      });
    }
  });
}


function mermaidTaskInfo(dayNum) {
  mermaidTaskInfoBase(dayNum);
  mermaidTaskInfoSuccess(dayNum);
}

/**
 * 美人鱼任务-计算基本信息
 */
function mermaidTaskInfoBase(dayNum) {
  event_dayreport_db.getMermaidTaskInfoBase(dbmanager_catchfish.getClientS(), dayNum,
      function(success, results, dayNum){
    if(success && results.length > 0) {
      var items = [];
      for(var i=0;i<results.length; i++) {
        var item = [dayNum, results[i]['nums'], results[i]['user_nums']];
        items[i] = item;
      }
      event_dayreport_db.insertMermaidTaskInfoBase(dbmanager_catchfish.getClient(), items, function(success){
      });
    }
  });
}

/**
 * 美人鱼任务-计算成功信息
 */
function mermaidTaskInfoSuccess(dayNum) {
  event_dayreport_db.getMermaidTaskInfoSuccess(dbmanager_catchfish.getClientS(), dayNum,
      function(success, results, dayNum){
    if(success && results.length > 0) {
      var items = [];
      for(var i=0;i<results.length; i++) {
        var item = [dayNum, results[i]['nums'], results[i]['user_nums'],
            results[i]['user_times'] === null ? 0 : results[i]['user_times'],
            results[i]['rewards']  === null ? 0 : results[i]['rewards'] ];
        items[i] = item;
      }
      event_dayreport_db.insertMermaidTaskInfoSuccess(dbmanager_catchfish.getClient(), items, function(success){
      });
    }
  });
}

function fishInfo(dayNum) {
  for(var i=1; i<=4;i++) {  // 分4个房间计算
    fishInfoByRoomId(dayNum, i);
  }
}

/**
 * 鱼产生统计-单一房间计算
 */
function fishInfoByRoomId(dayNum, roomId) {
  event_dayreport_db.getFishInfoByRoomId(dbmanager_catchfish.getClientS(), dayNum, roomId,
      function(success, results, dayNum, roomId){
    if(success && results.length > 0) {
      var items = [];
      for(var i=0;i<results.length; i++) {
        var item = [dayNum, roomId, results[i]['fish_id'], results[i]['create_times'],
          results[i]['hit_times'], results[i]['hit_moneys'],
          results[i]['catch_times'], results[i]['catch_times_user']];
        items[i] = item;
      }
      event_dayreport_db.insertFishInfoByRoomId(dbmanager_catchfish.getClient(), items, function(success){
      });
    }
  });
}

/**
 * 页面跳转
 */
function pageChangeInfo(dayNum) {
  event_dayreport_db.getPageChangeInfo(dbmanager_catchfish.getClientS(), dayNum,
      function(success, results, dayNum){
    if(success && results.length > 0) {
      var items = [];
      for(var i=0;i<results.length; i++) {
        var item = [dayNum, results[i]['to_page'], results[i]['from_page'], results[i]['nums'], results[i]['user_nums']];
        items[i] = item;
      }
      event_dayreport_db.insertPageChangeInfo(dbmanager_catchfish.getClient(), items, function(success){
      });
    }else if(success) {  // 如果没有数据做默认插入
      var items = [];
      var item = [dayNum, 1, 2, 1, 1];
      items[0] = item;
      event_dayreport_db.insertPageChangeInfo(dbmanager_catchfish.getClient(), items, function(success){
      });
    }
  });
}

/**
 * 赠送体系统计
 */
function presentedUserInfo(dayNum) {
  event_dayreport_db.getPresentedUserInfo(dbmanager_catchfish.getClientS(), dayNum,
      function(success, results, dayNum){
    if(success && results.length > 0) {
      var items = [];
      for(var i=0;i<results.length; i++) {
        var item = [dayNum, results[i]['prop_id'], results[i]['nums'], results[i]['user_nums']];
        items[i] = item;
      }
      event_dayreport_db.insertPresentedUserInfo(dbmanager_catchfish.getClient(), items, function(success){
      });
    }
  });
}

function skillUserInfo(dayNum) {
  skillUserInfoBase(dayNum);
  skillUserInfoType(dayNum, 0);
  skillUserInfoType(dayNum, 1);
  skillUserInfoType(dayNum, 2);
}

/**
 * 计算技能使用-分类型
 */
function skillUserInfoType(dayNum, type) {
  event_dayreport_db.getSkillUserInfoType(dbmanager_catchfish.getClientS(), dayNum, type,
      function(success, results, dayNum, type){
    if(success && results.length > 0) {
      var items = [];
      for(var i=0;i<results.length; i++) {
        var item = [dayNum, results[i]['skill_id'], results[i]['nums'], results[i]['user_nums']];
        items[i] = item;
      }
      event_dayreport_db.insertSkillUserInfoType(dbmanager_catchfish.getClient(), type, items, function(success){
      });
    }
  });
}

/**
 * 计算技能使用-基础总和
 */
function skillUserInfoBase(dayNum) {
  event_dayreport_db.getSkillUserInfoBase(dbmanager_catchfish.getClientS(), dayNum,
      function(success, results, dayNum){
    if(success && results.length > 0) {
      var items = [];
      for(var i=0;i<results.length; i++) {
        var item = [dayNum, results[i]['skill_id'], results[i]['nums'], results[i]['user_nums']];
        items[i] = item;
      }
      event_dayreport_db.insertSkillUserInfoBase(dbmanager_catchfish.getClient(), items, function(success){
      });
    }
  });
}

/**
 * 计算分炮台等级的平均用户升级时间。
 */
function turrentLevelUpdateInfo(dayNum) {
  event_dayreport_db.getTurrentLevelUpdateInfo(dbmanager_catchfish.getClientS(), dayNum,
      function(success, results, dayNum){
    if(success && results.length > 0) {
      var items = [];
      for(var i=0;i<results.length; i++) {
        var item = [dayNum, results[i]['turrent_level'], results[i]['user_nums'], results[i]['avg_update_times']];
        items[i] = item;
      }
      event_dayreport_db.insertTurrentLevelUpdateInfo(dbmanager_catchfish.getClient(), items, function(success){
      });
    }
  });
}

function turntableInfo(dayNum) {
  event_dayreport_db.getTurntableInfo(dbmanager_catchfish.getClientS(), dayNum,
      function(success, results, dayNum){
    if(success && results.length > 0) {
      var items = [];
      for(var i=0;i<results.length; i++) {
        // day, t_type, times, user_times, p_type_1_counts
        var item = [dayNum, results[i]['t_type'], results[i]['times'], results[i]['user_times'],
            results[i]['p_type_1_counts'], results[i]['p_type_2_counts'], results[i]['p_type_3_counts'],
            results[i]['p_type_4_counts'], results[i]['p_type_5_counts'], results[i]['p_type_6_counts']];
        items[i] = item;
      }
      event_dayreport_db.insertTurntableInfo(dbmanager_catchfish.getClient(), items, function(success){
      });
    }
  });
}

function turntableInfoForNew(dayNum) {
  event_dayreport_db.getTurntableInfoForNew(dbmanager_catchfish.getClientS(), dayNum,
      function(success, results, dayNum){
    if(success && results.length > 0) {
      var items = [];
      for(var i=0;i<results.length; i++) {
        // day, t_type, times, user_times, p_type_1_counts
        var item = [dayNum, 10 + parseInt(results[i]['t_type']), results[i]['times'], results[i]['user_times'],
            results[i]['p_type_1_counts'], results[i]['p_type_2_counts'], results[i]['p_type_3_counts'],
            results[i]['p_type_4_counts'], results[i]['p_type_5_counts'], results[i]['p_type_6_counts']];
        items[i] = item;
      }
      event_dayreport_db.insertTurntableInfoForNew(dbmanager_catchfish.getClient(), items, function(success){
      });
    }
  });
}

function turrentLevelGroup(dayNum) {
  event_dayreport_db.turrentLevelGroupActiveInfo(dbmanager_catchfish.getClientS(), dayNum,
      function(success, results, dayNum){
    if(success && results.length > 0) {
      var items = [];
      for(var i=0;i<results.length; i++) {
        var item = [dayNum, results[i]['turrent_level'], results[i]['active_user']];
        items[i] = item;
      }
      event_dayreport_db.insertTurrentLevelGroupActiveInfo(dbmanager_catchfish.getClient(), items, function(success){
      });
    }
  });
  event_dayreport_db.turrentLevelGroupNewInfo(dbmanager_catchfish.getClientS(), dayNum,
      function(success, results, dayNum){
    if(success && results.length > 0) {
      var items = [];
      for(var i=0;i<results.length; i++) {
        var item = [dayNum, results[i]['turrent_level'], results[i]['new_user']];
        items[i] = item;
      }
      event_dayreport_db.insertTurrentLevelGroupNewInfo(dbmanager_catchfish.getClient(), items, function(success){
      });
    }
  });
}


function expendInfo(dayNum) {
  event_dayreport_db.sqlWithParam(dbmanager_catchfish.getClient(), sqlStrCoinGet, dayNum, function(success){
  });
  event_dayreport_db.sqlWithParam(dbmanager_catchfish.getClient(), sqlStrCoinUse, dayNum, function(success){
  });
  event_dayreport_db.sqlWithParam(dbmanager_catchfish.getClient(), sqlStrDiamondGet, dayNum, function(success){
  });
  event_dayreport_db.sqlWithParam(dbmanager_catchfish.getClient(), sqlStrDiamondUse, dayNum, function(success){
  });
}


var sqlStrCoinGet = 'INSERT INTO report_expend_day(day, coin_get_user, coin_gets) ' +
    '(SELECT day, COUNT(user_id) AS coin_get_user, SUM(coin_get) AS coin_gets ' +
    'FROM statistics_expend WHERE day = ? AND coin_get > 0) ' +
    'ON DUPLICATE KEY UPDATE coin_get_user = VALUES(coin_get_user), coin_gets  = VALUES(coin_gets)';
var sqlStrCoinUse = 'INSERT INTO report_expend_day(day, coin_use_user, coin_uses) ' +
    '(SELECT day, COUNT(user_id) AS coin_use_user, SUM(coin_use) AS coin_uses ' +
    'FROM statistics_expend WHERE day = ? AND coin_use > 0) ' +
    'ON DUPLICATE KEY UPDATE coin_use_user = VALUES(coin_use_user), coin_uses  = VALUES(coin_uses)';
var sqlStrDiamondGet = 'INSERT INTO report_expend_day(day, diamond_get_user, diamond_gets) ' +
    '(SELECT day, COUNT(user_id) AS diamond_get_user, SUM(diamond_get) AS diamond_gets ' +
    'FROM statistics_expend WHERE day = ? AND diamond_get > 0) ' +
    'ON DUPLICATE KEY UPDATE diamond_get_user = VALUES(diamond_get_user), diamond_gets  = VALUES(diamond_gets)';
var sqlStrDiamondUse = 'INSERT INTO report_expend_day(day, diamond_use_user, diamond_uses) ' +
    '(SELECT day, COUNT(user_id) AS diamond_use_user, SUM(diamond_use) AS diamond_uses ' +
    'FROM statistics_expend WHERE day = ? AND diamond_use > 0) ' +
    'ON DUPLICATE KEY UPDATE diamond_use_user = VALUES(diamond_use_user), diamond_uses  = VALUES(diamond_uses)';

exports.startOneDayTask = startOneDayTask;
