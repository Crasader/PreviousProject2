
function getDayreport(client, day, callback) {
  client.query(' SELECT * FROM report_pay_day WHERE day = ? ORDER BY mo_req_moneys DESC',
      [day],
    function (err, results) {
      if (err) {
        console.log('[ERROR!!]pay_db->getDayreport, msg : ' + err);
        callback( false, err );
        return;
      }
      if(results != undefined && results != null && results.length > 0) {
        callback( true, results);
      }else {
        callback( true, []);
      }
    }
  );
}

exports.getDayreport = getDayreport;

function getUserMo(client, user_id, callback) {
  client.query(' SELECT * FROM mo_1 WHERE user_id = ? ORDER BY create_time DESC',
      [user_id],
    function (err, results) {
      if (err) {
        console.log('[ERROR!!]pay_db->getUserMo, msg : ' + err);
        callback( false, err );
        return;
      }
      if(results != undefined && results != null && results.length > 0) {
        callback( true, results);
      }else {
        callback( true, []);
      }
    }
  );
}

exports.getUserMo = getUserMo;

function getUserMr(client, user_id, callback) {
  client.query(' SELECT * FROM mr_1 WHERE user_id = ? ORDER BY create_time DESC',
      [user_id],
    function (err, results) {
      if (err) {
        console.log('[ERROR!!]pay_db->getUserMr, msg : ' + err);
        callback( false, err );
        return;
      }
      if(results != undefined && results != null && results.length > 0) {
        callback( true, results);
      }else {
        callback( true, []);
      }
    }
  );
}
exports.getUserMr = getUserMr;

function getOneDayMr(client, dayStr, callback) {
  var day_start = dayStr + ' 00:00:00:000';
  var day_end = dayStr + ' 23:59:59:999';
  client.query(' SELECT * FROM mr_1 WHERE create_time BETWEEN ? AND ?',
      [day_start, day_end],
    function (err, results) {
      if (err) {
        console.log('[ERROR!!]pay_db->getUserMr, msg : ' + err);
        callback( false, err );
        return;
      }
      if(results != undefined && results != null && results.length > 0) {
        callback( true, results);
      }else {
        callback( true, []);
      }
    }
  );
}

exports.getOneDayMr = getOneDayMr;
