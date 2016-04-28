/**
 * 渠道日报的一天统计任务
 */
var dbmanager_catchfish = require('../../../db/dbmanager_catchfish.js');
var pay_dayreport_db = require('./pay_dayreport_db.js');

/**
 * dayNum， 日期的数字格式
 * dayStr, 日期的字符串格式
 * 两个值必须一致
 */
function startOneDayTask(dayNum, dayStr) {
  console.log('[pay_dayreport]startOneDayTask : ' + dayStr + ';' + dayNum);
  moReq(dayNum, dayStr); // 增加mo请求统计
  moSuccess(dayNum, dayStr); // 增加mo成功统计
  mr(dayNum, dayStr); // 增加mr统计
}

/**
 * mr分布统计
 */
function mr(dayNum, dayStr) {
  pay_dayreport_db.getMr(dbmanager_catchfish.getClientS(), dayNum, dayStr,
      function(success, results, dayNum){
    if(success && results.length > 0) {
      var items = [];
      for(var i=0;i<results.length; i++) {
        var item = [dayNum,
          results[i]['pay_point_id'], results[i]['pay_event_id'],
          results[i]['mr_nums'], results[i]['mr_users'], results[i]['mr_moneys'] ];
        items[i] = item;
      }
      pay_dayreport_db.insertMr(dbmanager_catchfish.getClient(), items, function(success){
      });
    }
  });
}



/**
 * mo成功分布统计
 */
function moSuccess(dayNum, dayStr) {
  pay_dayreport_db.getMoSuccess(dbmanager_catchfish.getClientS(), dayNum, dayStr,
      function(success, results, dayNum){
    if(success && results.length > 0) {
      var items = [];
      for(var i=0;i<results.length; i++) {
        var item = [dayNum,
          results[i]['pay_point_id'], results[i]['pay_event_id'],
          results[i]['mo_success_nums'], results[i]['mo_success_users'], results[i]['mo_success_moneys'] ];
        items[i] = item;
      }
      pay_dayreport_db.insertMoSuccess(dbmanager_catchfish.getClient(), items, function(success){
      });
    }
  });
}

/**
 * mo请求分布统计
 */
function moReq(dayNum, dayStr) {
  pay_dayreport_db.getMoReq(dbmanager_catchfish.getClientS(), dayNum, dayStr,
      function(success, results, dayNum){
    if(success && results.length > 0) {
      var items = [];
      for(var i=0;i<results.length; i++) {
        var item = [dayNum,
          results[i]['pay_point_id'], results[i]['pay_event_id'],
          results[i]['mo_req_nums'], results[i]['mo_req_users'], results[i]['mo_req_moneys'] ];
        items[i] = item;
      }
      pay_dayreport_db.insertMoReq(dbmanager_catchfish.getClient(), items, function(success){
      });
    }
  });
}


exports.startOneDayTask = startOneDayTask;
