'use strict';

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
            console.log('[ERROR!!]player_db->syncPlayerBaseFortuneInfo, msg : ' + err);
            callback(false);
            return;
        }
        callback(true);
    });
}

exports.syncPlayerBaseFortuneInfo = syncPlayerBaseFortuneInfo;

function syncbagInfo(client, user_id, item_id, nums, callback) {
	client.query(' UPDATE user_bg_1 SET nums = ?  WHERE user_id = ? AND item_id = ?',
					[nums, user_id, item_id],
          function (err, results) {
        if (err) {
            console.log('[ERROR!!]bag_db->syncbagInfo, msg : ' + err);
            callback(false);
            return;
        }
        callback(true);
    });
}

exports.syncbagInfo = syncbagInfo;
