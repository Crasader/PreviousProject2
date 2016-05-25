

function getSomeInfoByDay(client, day, groupinfo, table_name,  callback) {
  client.query(' SELECT * FROM ' + table_name + ' WHERE day = ? ' + groupinfo,
      [day],
    function (err, results) {
      if (err) {
        console.log('[ERROR!!]event_db->getSomeInfoByDay, msg : ' + err);
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


exports.getSomeInfoByDay = getSomeInfoByDay;

function getUSerPageInfo(client, user_id, callback) {
  client.query('SELECT * FROM statistics_page_change WHERE user_id = ?',
      [user_id],
    function (err, results) {
      if (err) {
        console.log('[ERROR!!]event_db->getUSerPageInfo, msg : ' + err);
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

exports.getUSerPageInfo = getUSerPageInfo;

function getUserGameInfo(client, user_id, callback) {
  client.query('SELECT * FROM user_fortune_1 WHERE user_id = ?',
      [user_id],
    function (err, results) {
      if (err) {
        console.log('[ERROR!!]event_db->getUserGameInfo, msg : ' + err);
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

exports.getUserGameInfo = getUserGameInfo;

function getUserRegisterInfo(client, user_id, callback) {
  var user_id_num = parseInt(user_id)%10;
  client.query('SELECT * FROM user_guest_' + user_id_num + ' WHERE user_id = ?',
      [user_id],
    function (err, results) {
      if (err) {
        console.log('[ERROR!!]event_db->getUserRegisterInfo, msg : ' + err);
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
exports.getUserRegisterInfo = getUserRegisterInfo;

function getExpInfo(client, day, callback) {
  client.query('SELECT * FROM report_exp_day WHERE day = ?',
      [day],
    function (err, results) {
      if (err) {
        console.log('[ERROR!!]event_db->getExpInfo, msg : ' + err);
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

exports.getExpInfo = getExpInfo;
