/**
 * 渠道日报的一天统计任务
 */
var dbmanager_catchfish = require('../../../db/dbmanager_catchfish.js');
var channel_dayreport_db = require('./channel_dayreport_db.js');

/**
 * dayNum， 日期的数字格式
 * dayStr, 日期的字符串格式
 * 两个值必须一致[TODO : 后期改为传入一个参数]
 */
function startOneDayTask(dayNum, dayStr, dayBefore1, dayBefore7, dayBefore30) {
  console.log('[channel]startOneDayTask : ' + dayStr + ';' + dayNum);
  newUser(dayNum, dayStr);
  activeUser(dayNum, dayStr);
  moReq(dayNum, dayStr);
  moSuccess(dayNum, dayStr);

  rSomeUser(dayNum, 1); // 次日
  rSomeUser(dayNum, 2); // 次2日
  rSomeUser(dayNum, 3); // 次3日
  rSomeUser(dayNum, 4); // 次4日
  rSomeUser(dayNum, 5); // 次5日
  rSomeUser(dayNum, 6); // 次6日
  rSomeUser(dayNum, 7); // 次7日

  rThirtyMUser(dayNum);
  rSeven2(dayNum, dayBefore1, dayBefore7);
  rThirty2(dayNum, dayBefore1, dayBefore30);

  mr(dayNum, dayStr);
}

/**
 * 计算某一天的mr
 */
function mr(dayNum, dayStr) {
  channel_dayreport_db.getSomeDayMr(dbmanager_catchfish.getClientS(), dayNum, dayStr,
      function(success, results, dayNum, dayStr) {
    if(success && results.length > 0) {
      var items = [];
      for(var i=0;i<results.length; i++) {
        var item = [dayNum, results[i]['channel_id'], results[i]['nums'],
            results[i]['money'], results[i]['user_nums']];
        items[i] = item;
      }
      channel_dayreport_db.insertOneDayMr(dbmanager_catchfish.getClient(), items, function(success){
      });
    }
  });
}

/**
 * 计算30日内来过2次的用户
 */
function rThirty2(dayNum, dayBefore1, dayBefore30) {
  channel_dayreport_db.getBeforeX2UserNum(dbmanager_catchfish.getClientS(), dayNum, dayBefore1, dayBefore30,
      function(success, results, dayNum){
    if(success && results.length > 0) {
      var items = [];
      for(var i=0;i<results.length; i++) {
        var item = [dayNum, results[i]['channel_id'], results[i]['r_beforex_2']];
        items[i] = item;
      }
      channel_dayreport_db.insertThirty2UserNum(dbmanager_catchfish.getClient(), items, function(success){
      });
    }
  });
}

/**
 * 计算7日内来过2次的用户[包含注册]
 */
function rSeven2(dayNum, dayBefore1, dayBefore7) {
  channel_dayreport_db.getBeforeX2UserNum(dbmanager_catchfish.getClientS(), dayNum, dayBefore1, dayBefore7,
      function(success, results, dayNum){
    if(success && results.length > 0) {
      var items = [];
      for(var i=0;i<results.length; i++) {
        var item = [dayNum, results[i]['channel_id'], results[i]['r_beforex_2']];
        items[i] = item;
      }
      channel_dayreport_db.insertSeven2UserNum(dbmanager_catchfish.getClient(), items, function(success){
      });
    }
  });
}

/**
 * 计算30日留存用户
 */
function rThirtyMUser(dayNum) {
  channel_dayreport_db.getThirtyMUserNum(dbmanager_catchfish.getClientS(), dayNum,
      function(success, results, dayNum){
    if(success && results.length > 0) {
      var items = [];
      for(var i=0;i<results.length; i++) {
        var item = [dayNum, results[i]['channel_id'], results[i]['r_thirty_m']];
        items[i] = item;
      }
      channel_dayreport_db.insertThirtyMUserNum(dbmanager_catchfish.getClient(), items, function(success){
      });
    }
  });
}

/**
 * 计算次日留存用户
 */
function rSomeUser(dayNum, login_day) {
  (function(dayNum, login_day){
    channel_dayreport_db.getSomeDayUserNum(dbmanager_catchfish.getClientS(), dayNum, login_day,
        function(success, results, dayNum){
      if(success && results.length > 0) {
        var items = [];
        for(var i=0;i<results.length; i++) {
          var item = [dayNum, results[i]['channel_id'], results[i]['r_some_u']];
          items[i] = item;
        }
        channel_dayreport_db.insertSomeDayUserNum(dbmanager_catchfish.getClient(), login_day, items, function(success){
        });
      }
    });
  })(dayNum, login_day);

}


/**
 * 计算一天分渠道的新增用户数
 */
function activeUser(dayNum, dayStr) {
  var map = new Map();
  activeUserByOne(dayNum, dayStr, 1, map);
}

function activeUserByOne(dayNum, dayStr, pos, map) {
  channel_dayreport_db.getSomeDayActiveUser(dbmanager_catchfish.getClientS(), pos, dayNum, dayStr, map,
      function(success, results, pos, dayNum, dayStr, map){
    if(success && results.length > 0) {
      for(var i=0;i<results.length; i++) {
        if( map.has(results[i]['channel_id']) ){
          map.set(results[i]['channel_id'], map.get(results[i]['channel_id']) + parseInt(results[i]['user_active']) );
        }else {
          map.set(results[i]['channel_id'], parseInt(results[i]['user_active']) );
        }
      }
    }
    if(pos === 1) {
      channel_dayreport_db.insertSomeDayActiveUser(dbmanager_catchfish.getClient(), dayNum, map, function(success){
      });
    }else {
      activeUserByOne(dayNum, dayStr, pos+1, map);
    }
  });
}

/**
 * 计算一天分渠道的新增用户数
 */
function newUser(dayNum, dayStr) {
  var map = new Map();
  newUserByOne(dayNum, dayStr, 1, map);
}

function newUserByOne(dayNum, dayStr, pos, map) {
  channel_dayreport_db.getSomeDayNewUser(dbmanager_catchfish.getClientS(), pos, dayNum, dayStr, map,
      function(success, results, pos, dayNum, dayStr, map){
    if(success && results.length > 0) {
      for(var i=0;i<results.length; i++) {
        if( map.has(results[i]['channel_id']) ){
          map.set(results[i]['channel_id'], map.get(results[i]['channel_id']) + parseInt(results[i]['user_new']) );
        }else {
          map.set(results[i]['channel_id'], parseInt(results[i]['user_new']) );
        }
      }
    }
    if(pos === 10) {
      channel_dayreport_db.insertSomeDayNewUser(dbmanager_catchfish.getClient(), dayNum, map, function(success){
      });
    }else {
      newUserByOne(dayNum, dayStr, pos+1, map);
    }
  });
}

/**
 * 计算一天分渠道的mo请求金额和用户数
 */
function moReq(dayNum, dayStr) {
  channel_dayreport_db.getSomeDayMoReq(dbmanager_catchfish.getClientS(), dayNum, dayStr,
      function(success, results, dayNum, dayStr){
    if(success && results.length > 0) {
      var items = [];
      for(var i=0;i<results.length; i++) {
        var item = [dayNum, results[i]['channel_id'], results[i]['mo_req_time'], results[i]['mo_req_money'], results[i]['mo_req_user']];
        console.log(i + ' ->item[req] : ' + item);
        items[i] = item;
      }
      channel_dayreport_db.insertSomeDayMoReq(dbmanager_catchfish.getClient(), items, function(success){
      });
    }
  });
}

/**
 * 计算一天分渠道的mo请求金额和用户数
 */
function moSuccess(dayNum, dayStr) {
  channel_dayreport_db.getSomeDayMoSuccess(dbmanager_catchfish.getClientS(), dayNum, dayStr,
      function(success, results, dayNum, dayStr){
    if(success && results.length > 0) {
      var items = [];
      for(var i=0;i<results.length; i++) {
        var item = [dayNum, results[i]['channel_id'], results[i]['mo_success_time'], results[i]['mo_success_money'], results[i]['mo_success_user']];
        console.log(i + ' ->item[success] : ' + item);
        items[i] = item;
      }
      channel_dayreport_db.insertSomeDayMoSuccess(dbmanager_catchfish.getClient(), items, function(success){
      });
    }
  });
}

exports.startOneDayTask = startOneDayTask;
