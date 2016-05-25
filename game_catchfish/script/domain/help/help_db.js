
function insertOneFeedBack(client, user_id, info, create_time, callback) {
  client.query(' INSERT INTO feedback SET user_id = ?, feedback_info = ?, create_time = ?',
			[user_id, info, create_time],
            function (err, results) {
        if (err) {
            console.log('[ERROR!!]help_db->insertOneFeedBack,user_id :' + user_id + ', err msg : ' + err);
            callback(false);
            return;
        }
        callback(true);
    });
}

exports.insertOneFeedBack = insertOneFeedBack;
