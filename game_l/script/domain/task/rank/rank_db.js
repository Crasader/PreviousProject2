
function getCoinsRank(client, callback) {
  client.query('SELECT IF(b.user_id = a.user_id, a.user_name, b.user_id) as user_name, ' +
      ' IF(b.user_id=a.user_id, a.gender, 0) as gender ,b.coins, b.exp, b.mo ' +
      ' FROM  user_fortune_1 as b ' +
      ' LEFT JOIN ( name_1 as a) ON (b.user_id=a.user_id) ORDER BY b.coins DESC limit 30',
    function (err, results) {
      if(err) {
        console.log('err : ' + err);
        callback(false, results);
      }else {
        callback(true, results);
      }
    }
  );
}

function insertCoinsRank(client, items, callback){
  client.query('INSERT INTO rank_coins(rank, user_name, gender, exp, coins, vip, update_times) VALUES ? ' +
      ' ON DUPLICATE KEY UPDATE user_name = VALUES(user_name), gender = VALUES(gender), ' +
      ' exp = VALUES(exp), coins = VALUES(coins),' +
      ' vip = VALUES(vip), update_times = VALUES(update_times)',
      [items],
    function (err, results) {
      if(err) {
        console.log('[event][insertCoinsRank]err : ' + err);
        callback(false);
      }else {
        callback(true);
      }
    }
  );
}

function getExpRank(client, callback) {
  client.query('SELECT IF(b.user_id = a.user_id, a.user_name, b.user_id) as user_name, ' +
      ' IF(b.user_id=a.user_id, a.gender, 0) as gender ,b.coins, b.exp, b.mo ' +
      ' FROM  user_fortune_1 as b ' +
      ' LEFT JOIN ( name_1 as a) ON (b.user_id=a.user_id) ORDER BY b.exp DESC limit 30',
    function (err, results) {
      if(err) {
        console.log('err : ' + err);
        callback(false, results);
      }else {
        callback(true, results);
      }
    }
  );
}

function insertExpRank(client, items, callback){
  client.query('INSERT INTO rank_exp(rank, user_name, gender, exp, coins, vip, update_times) VALUES ? ' +
      ' ON DUPLICATE KEY UPDATE user_name = VALUES(user_name), gender = VALUES(gender), ' +
      ' exp = VALUES(exp), coins = VALUES(coins),' +
      ' vip = VALUES(vip), update_times = VALUES(update_times)',
      [items],
    function (err, results) {
      if(err) {
        console.log('[event][insertCoinsRank]err : ' + err);
        callback(false);
      }else {
        callback(true);
      }
    }
  );
}

exports.getCoinsRank = getCoinsRank;
exports.insertCoinsRank = insertCoinsRank;
exports.getExpRank = getExpRank;
exports.insertExpRank = insertExpRank;
