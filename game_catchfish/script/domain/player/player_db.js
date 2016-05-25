

function syncPlayerFortuneInfo(client, sync_info, callback) {
  // TODO  :如果负载大考虑批量更新
  var values = [
    [sync_info.user_id, sync_info.coins, sync_info.diamonds, sync_info.exp,
     sync_info.turrent_level, sync_info.mo, sync_info.nobility_time]
  ];
  client.query(' INSERT INTO user_fortune_' + sync_info.fortune_id + ' (user_id, coins, diamonds, exp, turrent_level, mo, nobility_time) VALUES ? ' +
      ' ON DUPLICATE KEY UPDATE coins = VALUES(coins),' +
      ' diamonds = VALUES(diamonds) , exp = VALUES(exp),' +
      ' turrent_level = VALUES(turrent_level), mo = VALUES(mo), nobility_time = VALUES(nobility_time)',
  	   [values],
    function (err, results) {
        if (err) {
            console.log('[ERROR!!]mo_db->syncPlayerFortuneInfo, msg : ' + err);
            callback(false);
            return;
        }
        callback(true);
    });
}

function syncPlayerBaseFortuneInfo(client, sync_info, callback) {
  // 如果负载大考虑批量更新，没有没有感觉
  var values = [
    [sync_info.user_id, sync_info.coins, sync_info.diamonds, sync_info.exps, sync_info.turrent_level]
  ];
  client.query(' INSERT INTO user_fortune_' + sync_info.fortune_id + ' (user_id, coins, diamonds, exp, turrent_level) VALUES ? ' +
      ' ON DUPLICATE KEY UPDATE coins = VALUES(coins),' +
      ' diamonds = VALUES(diamonds) , exp = VALUES(exp), turrent_level = VALUES(turrent_level)',
  	   [values],
    function (err, results) {
        if (err) {
            console.log('[ERROR!!]mo_db->syncPlayerBaseFortuneInfo, msg : ' + err);
            callback(false);
            return;
        }
        callback(true);
    });
}

exports.syncPlayerBaseFortuneInfo = syncPlayerBaseFortuneInfo;

/**
 * add的方式添加
 */
function addPlayerCoinsAndDiamonds(client, sync_info, callback) {
  // 如果负载大考虑批量更新，没有没有感觉
  var values = [
    [sync_info.user_id, sync_info.coins, sync_info.diamonds]
  ];
  client.query(' INSERT INTO user_fortune_' + sync_info.fortune_id + ' (user_id, coins, diamonds) VALUES ? ' +
      ' ON DUPLICATE KEY UPDATE coins = coins + VALUES(coins), diamonds = diamonds + VALUES(diamonds)',
  	   [values],
    function (err, results) {
        if (err) {
            console.log('[ERROR!!]mo_db->addPlayerCoinsAndDiamonds, msg : ' + err);
            callback(false);
            return;
        }
        console.log('[sign] addPlayerCoinsAndDiamonds success ');
        callback(true);
    });
}

exports.addPlayerCoinsAndDiamonds = addPlayerCoinsAndDiamonds;

function syncPlayerCoinsAndDiamonds(client, sync_info, callback) {
  // 如果负载大考虑批量更新，没有没有感觉
  var values = [
    [sync_info.user_id, sync_info.coins, sync_info.diamonds]
  ];
  client.query(' INSERT INTO user_fortune_' + sync_info.fortune_id + ' (user_id, coins, diamonds) VALUES ? ' +
      ' ON DUPLICATE KEY UPDATE coins = VALUES(coins), diamonds = VALUES(diamonds)',
  	   [values],
    function (err, results) {
        if (err) {
            console.log('[ERROR!!]mo_db->syncPlayerCoinsAndDiamonds, msg : ' + err);
            callback(false);
            return;
        }
        console.log('[sign] syncPlayerCoinsAndDiamonds success ');
        callback(true);
    });
}

exports.syncPlayerCoinsAndDiamonds = syncPlayerCoinsAndDiamonds;

function getCoinRank(client, callback) {
	client.query(' SELECT * FROM rank_coins LIMIT 0 , 30',
          function (err, results) {
        if (err) {
            console.log('[ERROR!!]player_db->getCoinRank, msg : ' + err);
            callback( false, err );
            return;
        }
        if(results != undefined && results != null && results.length > 0) {
        	callback( true, results );
        }else {
          callback(false);
        }
    });
}

function getExpRank(client, callback) {
	client.query(' SELECT * FROM rank_exp LIMIT 0 , 30',
          function (err, results) {
        if (err) {
            console.log('[ERROR!!]player_db->getExpRank, msg : ' + err);
            callback( false, err );
            return;
        }
        if(results != undefined && results != null && results.length > 0) {
        	callback( true, results );
        }else {
          callback(false);
        }
    });
}

function getPlayerInfo(client, user_id, table_id, callback) {
    client.query(' SELECT * FROM user_fortune_' + table_id + ' WHERE user_id = ?',
        [user_id],
      function (err, results) {
        if (err) {
            console.log('[ERROR!!]player_db->getPlayerInfo, msg : ' + err);
            callback( false, err );
            return;
        }
        if(results != undefined && results != null && results.length > 0) {
          var user_info = {
						coins : results[0]['coins'],
						diamonds : results[0]['diamonds'],
						turrent_level : results[0]['turrent_level'],
						exp : results[0]['exp'],
            chest_level : results[0]['chest_level'],
            mo : results[0]['mo'],
            mo_first : results[0]['mo_first'],
            mo_coins : results[0]['mo_coins']
					};
        	callback( true, user_info );
        }else {
          var user_info = {
						coins : 0,
						diamonds : 0,
						turrent_level : 1,
						exp : 0,
            chest_level : 0,
            mo : 0,
            mo_first : 0,
            mo_coins : 0
					};
          callback(true, user_info);
        }
    });
}

exports.syncPlayerFortuneInfo = syncPlayerFortuneInfo;
exports.getCoinRank = getCoinRank;
exports.getExpRank = getExpRank;
exports.getPlayerInfo = getPlayerInfo;

function getUserBgInfo(client, user_id, callback) {
	client.query(' SELECT * FROM user_bg_1 WHERE user_id = ?',
			[user_id],
      function (err, results) {
        if (err) {
            console.log('[ERROR!!]player_db->getUserBgInfo, user_id = ' + user_id + ';msg : ' + err);
            callback(false, err);
            return;
        }
				callback(true, results);
    	}
	);
}

exports.getUserBgInfo = getUserBgInfo;

function syncPlayerBgInfo(client, sync_info, callback) {
  var values = [
    [sync_info.user_id, sync_info.item_id, sync_info.nums]
  ];
  console.log('[DB][syncPlayerBgInfo], values : ' + JSON.stringify(values));
  client.query(' INSERT INTO user_bg_1 (user_id, item_id, nums) VALUES ? ' +
      ' ON DUPLICATE KEY UPDATE item_id = VALUES(item_id), nums = VALUES(nums)',
  	   [values],
    function (err, results) {
        if (err) {
            console.log('[ERROR!!]player_db->syncPlayerBgInfo, msg : ' + err);
            callback(false);
            return;
        }
        callback(true);
    });
}

exports.syncPlayerBgInfo = syncPlayerBgInfo;
