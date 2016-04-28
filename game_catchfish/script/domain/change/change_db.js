'use strict';

function insertChangeMark(client, user_id, type, change_state, phone_nums, create_time, callback) {
	client.query(' INSERT INTO user_change_mark SET user_id = ?, type = ?, change_state = ?, phone_nums = ?, create_time = ?',
					[user_id, type, change_state, phone_nums, create_time],
          function (err, results) {
        if (err) {
            console.log('[ERROR!!]change_db->insertChangeMark, msg : ' + err);
            callback(false);
            return;
        }
        callback(true);
    });
}
exports.insertChangeMark = insertChangeMark;

function getChangeMark(client, user_id, callback) {
	client.query(' SELECT * FROM user_change_mark WHERE user_id = ? ORDER BY id DESC LIMIT 30',
					[user_id],
          function (err, results) {
        if (err) {
            console.log('[ERROR!!]change_db->insertChangeMark, msg : ' + err);
            callback(false);
            return;
        }
        callback(true, results);
    });
}
exports.getChangeMark = getChangeMark;
