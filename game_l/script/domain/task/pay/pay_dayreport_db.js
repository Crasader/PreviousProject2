
var PAYANDEVENTVERSION = 102100;

/**
 * 查询某一天的分渠道mo请求金额和用户
 */
function getMoReq(client, dayNum, dayStr, callback) {
  var day_start = dayStr + ' 00:00:00:000';
  var day_end = dayStr + ' 23:59:59:999';
  client.query('SELECT pay_point_id, pay_event_id, price, ' +
      ' COUNT(DISTINCT order_id) AS mo_req_nums, SUM(price) AS mo_req_moneys, COUNT(DISTINCT user_id) AS mo_req_users ' +
      'FROM mo_1 WHERE type = 0 AND pay_and_event_version = ? AND (create_time BETWEEN ? AND ?) GROUP BY pay_point_id, pay_event_id',
      [PAYANDEVENTVERSION, day_start, day_end],
    function (err, results) {
      if(err) {
        console.log('[getMoReq]err : ' + err);
        callback(false, results, dayNum, dayStr);
      }else {
        callback(true, results, dayNum, dayStr);
      }
    }
  );
}

function insertMoReq(client, items, callback){
  client.query('INSERT INTO report_pay_day(day, pay_point_id, pay_event_id, mo_req_nums, mo_req_users, mo_req_moneys) VALUES ? ' +
      ' ON DUPLICATE KEY UPDATE mo_req_nums = VALUES(mo_req_nums), mo_req_users = VALUES(mo_req_users), mo_req_moneys = VALUES(mo_req_moneys) ',
      [items],
    function (err, results) {
      if(err) {
        console.log('[insertMoReq]err : ' + err);
        callback(false);
      }else {
        callback(true);
      }
    }
  );
}

exports.getMoReq = getMoReq;
exports.insertMoReq = insertMoReq;

/**
 * 查询某一天的分渠道mo成功金额和用户
 */
function getMoSuccess(client, dayNum, dayStr, callback) {
  var day_start = dayStr + ' 00:00:00:000';
  var day_end = dayStr + ' 23:59:59:999';
  client.query('SELECT pay_point_id, pay_event_id, price, ' +
      ' COUNT(DISTINCT order_id) AS mo_success_nums, SUM(price) AS mo_success_moneys, COUNT(DISTINCT user_id) AS mo_success_users ' +
      'FROM mo_1 WHERE type = 1 AND result = 0 AND pay_and_event_version = ? AND (create_time BETWEEN ? AND ?) GROUP BY pay_point_id, pay_event_id',
      [PAYANDEVENTVERSION, day_start, day_end],
    function (err, results) {
      if(err) {
        console.log('[getMoSuccess]err : ' + err);
        callback(false, results, dayNum);
      }else {
        callback(true, results, dayNum);
      }
    }
  );
}

function insertMoSuccess(client, items, callback){
  client.query('INSERT INTO report_pay_day(day, pay_point_id, pay_event_id, mo_success_nums, mo_success_users, mo_success_moneys) VALUES ? ' +
      ' ON DUPLICATE KEY UPDATE mo_success_nums = VALUES(mo_success_nums), mo_success_users = VALUES(mo_success_users), mo_success_moneys = VALUES(mo_success_moneys) ',
      [items],
    function (err, results) {
      if(err) {
        console.log('[insertMoSuccess]err : ' + err);
        callback(false);
      }else {
        callback(true);
      }
    }
  );
}

exports.getMoSuccess = getMoSuccess;
exports.insertMoSuccess = insertMoSuccess;

/**
 * 查询某一天的分渠道mr金额和用户
 */
function getMr(client, dayNum, dayStr, callback) {
  var day_start = dayStr + ' 00:00:00:000';
  var day_end = dayStr + ' 23:59:59:999';
  client.query('SELECT pay_point_id, pay_event_id, price, ' +
      ' COUNT(DISTINCT order_id) AS mr_nums, SUM(real_price) AS mr_moneys, COUNT(DISTINCT user_id) AS mr_users ' +
      'FROM mr_1 WHERE (create_time BETWEEN ? AND ?) GROUP BY pay_point_id, pay_event_id',
      [day_start, day_end],
    function (err, results) {
      if(err) {
        console.log('[getMr]err : ' + err);
        callback(false, results, dayNum);
      }else {
        callback(true, results, dayNum);
      }
    }
  );
}

function insertMr(client, items, callback){
  client.query('INSERT INTO report_pay_day(day, pay_point_id, pay_event_id, mr_nums, mr_users, mr_moneys) VALUES ? ' +
      ' ON DUPLICATE KEY UPDATE mr_nums = VALUES(mr_nums), mr_users = VALUES(mr_users), mr_moneys = VALUES(mr_moneys) ',
      [items],
    function (err, results) {
      if(err) {
        console.log('[insertMr]err : ' + err);
        callback(false);
      }else {
        callback(true);
      }
    }
  );
}


exports.getMr = getMr;
exports.insertMr = insertMr;
