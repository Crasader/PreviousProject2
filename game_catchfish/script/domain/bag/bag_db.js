'use strict';

function syncUserInfo(client, user_id, fortune_id, key, value, callback) {
	client.query(' UPDATE user_fortune_' + fortune_id + ' SET ' + key + ' = ?  WHERE user_id = ? ',
					[value, user_id],
          function (err, results) {
        if (err) {
            console.log('[ERROR!!]bag_db->syncUserInfo, msg : ' + err);
            callback(false);
            return;
        }
        callback(true);
    });
}

exports.syncUserInfo = syncUserInfo;

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
