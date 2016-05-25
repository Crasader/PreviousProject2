
/**
 * 查询某一天的分渠道mo请求金额和用户
 */
function getSomeDayMr(client, dayNum, dayStr, callback) {
  var day_start = dayStr + ' 00:00:00:000';
  var day_end = dayStr + ' 23:59:59:999';
  //
  client.query('SELECT channel_id, COUNT(order_id) AS nums, SUM(real_price) AS money, ' +
      'COUNT(DISTINCT user_id) AS user_nums  FROM mr_1 WHERE create_time BETWEEN ? AND ? GROUP BY channel_id',
      [day_start, day_end],
    function (err, results) {
      if(err) {
        console.log('err : ' + err);
        callback(false, results, dayNum, dayStr);
      }else {
        callback(true, results, dayNum, dayStr);
      }
    }
  );
}

function insertOneDayMr(client, items, callback) {
  client.query('INSERT INTO report_channel_day(day, channel_id, mr_time, mr_money, mr_user) VALUES ? ' +
      ' ON DUPLICATE KEY UPDATE mr_time = VALUES(mr_time), mr_money = VALUES(mr_money), mr_user = VALUES(mr_user) ',
      [items],
    function (err, results) {
      if(err) {
        console.log('err[insertOneDayMr] : ' + err);
        callback(false);
      }else {
        callback(true);
      }
    }
  );
}

exports.getSomeDayMr = getSomeDayMr;
exports.insertOneDayMr = insertOneDayMr;

function getSomeDayActiveUser(client, pos, dayNum, dayStr, map, callback) {
  client.query('SELECT channel_id, count(DISTINCT user_id) AS user_active FROM mark_user_login_' + pos +
      ' WHERE day = ? GROUP BY channel_id',
      [dayNum],
    function (err, results) {
      if(err) {
        console.log('err : ' + err);
        callback(false, results, pos, dayNum, dayStr, map);
      }else {
        callback(true, results, pos, dayNum, dayStr, map);
      }
    }
  );
}

function insertSomeDayActiveUser(client, dayNum, map, callback) {
  var values = [];
  var count = 0;
  for (var value of map) {
    var value = [dayNum, value[0], value[1]];
    console.log('dayNum = ' + dayNum + ';key = ' + value[0] + '; value = ' + value[1]);
    values[count] = value;
    count++;
  }
  client.query('INSERT INTO report_channel_day(day, channel_id, user_active) VALUES ? ' +
      ' ON DUPLICATE KEY UPDATE user_active = VALUES(user_active) ',
      [values],
    function (err, results) {
      if(err) {
        console.log('err : ' + err);
        callback(false);
      }else {
        callback(true);
      }
    }
  );
}

function getSomeDayNewUser(client, table_id, dayNum, dayStr, map, callback) {
  var day_start = dayStr + ' 00:00:00:000';
  var day_end = dayStr + ' 23:59:59:999';
  client.query('SELECT channel_id, count(DISTINCT user_id) AS user_new FROM user_guest_' + table_id +
      ' WHERE create_time BETWEEN ? AND ? GROUP BY channel_id',
      [day_start, day_end],
    function (err, results) {
      if(err) {
        console.log('err : ' + err);
        callback(false, results, table_id, dayNum, dayStr, map);
      }else {
        callback(true, results, table_id, dayNum, dayStr, map);
      }
    }
  );
}

function insertSomeDayNewUser(client, dayNum, map, callback) {
  var values = [];
  var count = 0;
  for (var value of map) {
    console.log('key = ' + value[0] + '; value = ' + value[1]);
    var value = [dayNum, value[0], value[1]];
    values[count] = value;
    count++;
  }
  if(count === 0) {
    callback(false);
    return ;
  }
  client.query('INSERT INTO report_channel_day(day, channel_id, user_new) VALUES ? ' +
      ' ON DUPLICATE KEY UPDATE user_new = VALUES(user_new) ',
      [values],
    function (err, results) {
      if(err) {
        console.log('err : ' + err);
        callback(false);
      }else {
        callback(true);
      }
    }
  );
}

/**
 * 查询某一天的分渠道mo请求金额和用户
 */
function getSomeDayMoReq(client, dayNum, dayStr, callback) {
  var day_start = dayStr + ' 00:00:00:000';
  var day_end = dayStr + ' 23:59:59:999';
  client.query('SELECT channel_id, COUNT(DISTINCT order_id) AS mo_req_time, SUM(price) AS mo_req_money, COUNT(DISTINCT user_id) AS mo_req_user FROM mo_1' +
      ' WHERE create_time BETWEEN ? AND ? AND type = 0 GROUP BY channel_id',
      [day_start, day_end],
    function (err, results) {
      if(err) {
        console.log('err : ' + err);
        callback(false, results, dayNum, dayStr);
      }else {
        callback(true, results, dayNum, dayStr);
      }
    }
  );
}

function insertSomeDayMoReq(client, items, callback){
  client.query('INSERT INTO report_channel_day(day, channel_id, mo_req_time, mo_req_money, mo_req_user) VALUES ? ' +
      ' ON DUPLICATE KEY UPDATE mo_req_time = VALUES(mo_req_time), mo_req_money = VALUES(mo_req_money), mo_req_user = VALUES(mo_req_user) ',
      [items],
    function (err, results) {
      if(err) {
        console.log('err : ' + err);
        callback(false);
      }else {
        callback(true);
      }
    }
  );
}

/**
 * 查询某一天的分渠道mo成功金额和用户
 */
function getSomeDayMoSuccess(client, dayNum, dayStr, callback) {
  var day_start = dayStr + ' 00:00:00:000';
  var day_end = dayStr + ' 23:59:59:999';
  client.query('SELECT channel_id,  COUNT(DISTINCT order_id) AS mo_success_time, SUM(price) AS mo_success_money, COUNT(DISTINCT user_id) AS mo_success_user FROM mo_1' +
      ' WHERE create_time BETWEEN ? AND ? AND type = 1 AND result = 0 GROUP BY channel_id',
      [day_start, day_end],
    function (err, results) {
      if(err) {
        console.log('err : ' + err);
        callback(false, results, dayNum, dayStr);
      }else {
        callback(true, results, dayNum, dayStr);
      }
    }
  );
}

function insertSomeDayMoSuccess(client, items, callback){
  client.query('INSERT INTO report_channel_day(day, channel_id, mo_success_time, mo_success_money, mo_success_user) VALUES ? ' +
      ' ON DUPLICATE KEY UPDATE mo_success_time = VALUES(mo_success_time), mo_success_money = VALUES(mo_success_money), mo_success_user = VALUES(mo_success_user) ',
      [items],
    function (err, results) {
      if(err) {
        console.log('err : ' + err);
        callback(false);
      }else {
        callback(true);
      }
    }
  );
}

/**
 * 查询某日留存用户[某日：今天往前某一天注册的用户，今天来的记录]
 */
function getSomeDayUserNum(client, dayNum, login_day, callback) {
  client.query('SELECT channel_id, COUNT(user_id) AS r_some_u FROM mark_user_login_1 WHERE ' +
      'day = ? AND login_day = ? GROUP BY channel_id',
      [dayNum, login_day],
    function (err, results) {
      if(err) {
        console.log('[getSecondUserNum]err : ' + err);
        callback(false, results, dayNum);
      }else {
        callback(true, results, dayNum);
      }
    }
  );
}

function insertSomeDayUserNum(client, login_day, items, callback){
  var r_some_u = null;
  if(login_day === 1){
    r_some_u = 'r_second_u';
  }else if(login_day >= 2 && login_day <=7){
    r_some_u = 'r_' + login_day + '_u';
  }
  if(r_some_u === null) {
    callback(false);
    return ;
  }
  client.query('INSERT INTO report_channel_day(day, channel_id, ' + r_some_u + ') VALUES ? ' +
      ' ON DUPLICATE KEY UPDATE ' + r_some_u + ' = VALUES(' + r_some_u + ')',
      [items],
    function (err, results) {
      if(err) {
        console.log('[insertSomeDayUserNum]err : ' + err);
        callback(false);
      }else {
        callback(true);
      }
    }
  );
}

exports.getSomeDayUserNum = getSomeDayUserNum;
exports.insertSomeDayUserNum = insertSomeDayUserNum;

/**
 * 查询某一天注册大于30天的留存用户
 */
function getThirtyMUserNum(client, dayNum, callback) {
  client.query('SELECT channel_id, COUNT(user_id) AS r_thirty_m FROM mark_user_login_1 WHERE ' +
      'day = ? AND login_day >= 30 GROUP BY channel_id',
      [dayNum],
    function (err, results) {
      if(err) {
        console.log('[getSecondUserNum]err : ' + err);
        callback(false, results, dayNum);
      }else {
        callback(true, results, dayNum);
      }
    }
  );
}

function insertThirtyMUserNum(client, items, callback){
  client.query('INSERT INTO report_channel_day(day, channel_id, r_thirty_m) VALUES ? ' +
      ' ON DUPLICATE KEY UPDATE r_thirty_m = VALUES(r_thirty_m)',
      [items],
    function (err, results) {
      if(err) {
        console.log('[insertThirtyMUserNum]err : ' + err);
        callback(false);
      }else {
        callback(true);
      }
    }
  );
}

/**
 * 查询N天内来过的用户
 */
function getBeforeX2UserNum(client, dayNum, dayBefore1, dayBeforeX, callback) {
  client.query('SELECT channel_id, SUM(user_count) AS r_beforex_2 FROM ' +
      ' (SELECT channel_id, day_num, COUNT(user_id) AS user_count FROM ' +
      ' (SELECT channel_id, user_id, COUNT(day) AS day_num FROM mark_user_login_1 ' +
      ' WHERE day <= ? AND day >= ? AND user_id IN ' +
      ' (SELECT user_id FROM mark_user_login_1 WHERE day = ?) GROUP BY user_id) AS a ' +
      ' GROUP BY channel_id, day_num) AS b  GROUP BY channel_id',
      [dayBefore1, dayBeforeX, dayNum],
    function (err, results) {
      if(err) {
        console.log('[getBeforeX2UserNum]err : ' + err);
        callback(false, results, dayNum);
      }else {
        callback(true, results, dayNum);
      }
    }
  );
}

function insertSeven2UserNum(client, items, callback){
  client.query('INSERT INTO report_channel_day(day, channel_id, r_seven_2) VALUES ? ' +
      ' ON DUPLICATE KEY UPDATE r_seven_2 = VALUES(r_seven_2)',
      [items],
    function (err, results) {
      if(err) {
        console.log('[insertSeven2UserNum]err : ' + err);
        callback(false);
      }else {
        callback(true);
      }
    }
  );
}

function insertThirty2UserNum(client, items, callback){
  client.query('INSERT INTO report_channel_day(day, channel_id, r_thirty_2) VALUES ? ' +
      ' ON DUPLICATE KEY UPDATE r_thirty_2 = VALUES(r_thirty_2)',
      [items],
    function (err, results) {
      if(err) {
        console.log('[insertThirty2UserNum]err : ' + err);
        callback(false);
      }else {
        callback(true);
      }
    }
  );
}

exports.getSomeDayNewUser = getSomeDayNewUser;
exports.insertSomeDayNewUser = insertSomeDayNewUser;
exports.getSomeDayActiveUser = getSomeDayActiveUser;
exports.insertSomeDayActiveUser = insertSomeDayActiveUser;

exports.getSomeDayMoReq = getSomeDayMoReq;
exports.getSomeDayMoSuccess = getSomeDayMoSuccess;

exports.insertSomeDayMoReq = insertSomeDayMoReq;
exports.insertSomeDayMoSuccess = insertSomeDayMoSuccess;


exports.getThirtyMUserNum = getThirtyMUserNum;
exports.insertThirtyMUserNum = insertThirtyMUserNum;
exports.getBeforeX2UserNum = getBeforeX2UserNum;
exports.insertSeven2UserNum = insertSeven2UserNum;
exports.insertThirty2UserNum = insertThirty2UserNum;
