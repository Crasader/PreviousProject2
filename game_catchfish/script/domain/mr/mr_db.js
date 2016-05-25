
function addNewMr(client, orderInfo, callback) {
	client.query(' INSERT INTO mr_1 ' +
			' SET order_id = ?, user_id = ?, channel_id = ?, third_type = ?, third_order_id = ?,' +
			' price = ?, real_price = ?, ' +
			' pay_and_event_version = ?, pay_event_id = ?, pay_point_id = ?, ' +
      ' create_time = ?, third_time = ? ',
			[orderInfo.order_id, orderInfo.user_id, orderInfo.channel_id, orderInfo.third_type, orderInfo.third_order_id,
				orderInfo.price, orderInfo.real_price,
				orderInfo.pay_and_event_version, orderInfo.pay_event_id, orderInfo.pay_point_id,
      	orderInfo.create_time, orderInfo.third_time],
            function (err, results) {
        if (err) {
            console.log('[ERROR!!]mr_db->addNewMr, msg : ' + err);
            callback(false);
            return;
        }
        callback(true);
    });
}

exports.addNewMr = addNewMr;

function addNewSkyMr(client, orderInfo, callback) {
	client.query(' INSERT INTO mr_sky ' +
			' SET order_id = ?, user_id = ?, channel_id = ?, ' +
			' price = ?, real_price = ?, sky_type = ?, ' +
			' pay_and_event_version = ?, pay_event_id = ?, pay_point_id = ?, ' +
      ' sky_order_id = ?, sky_error_code = ?, sky_time = ?, create_time = ?',
			[orderInfo.order_id, orderInfo.user_id, orderInfo.channel_id,
				orderInfo.price, orderInfo.real_price, orderInfo.sky_type,
				orderInfo.pay_and_event_version, orderInfo.pay_event_id, orderInfo.pay_point_id,
      orderInfo.third_order_id, orderInfo.sky_error_code, orderInfo.third_time, orderInfo.create_time],
            function (err, results) {
        if (err) {
            console.log('[ERROR!!]mr_db->addNewSkyMr, msg : ' + err);
            callback(false);
            return;
        }
        callback(true);
    });
}

function addNewMrError(client, orderInfo, callback) {
	client.query(' INSERT INTO mr_sky_error ' +
			' SET order_id = ? real_price = ?, sky_type = ?, ' +
      ' sky_order_id = ?, sky_error_code = ?, sky_time = ?, create_time = ?',
			[orderInfo.order_id, orderInfo.real_price, orderInfo.sky_type,
       orderInfo.sky_order_id, orderInfo.sky_error_code, orderInfo.sky_time, orderInfo.create_time],
            function (err, results) {
        if (err) {
            console.log('[ERROR!!]mr_db->addNewMrError, msg : ' + err);
            callback(false);
            return;
        }
        callback(true);
    });
}

exports.addNewSkyMr = addNewSkyMr;
exports.addNewMrError = addNewMrError;

function addNewMrUserInfo(client, order_id, orderInfo, type, callback) {
	client.query(' INSERT INTO mr_user_info ' +
			' SET order_id = ?, coins = ?, diamonds = ?, exp = ?, turrent_level = ?, type = ? ',
			[order_id,
				orderInfo.coins === undefined ? 0 : orderInfo.coins,
				orderInfo.diamonds === undefined ? 0 : orderInfo.diamonds,
				orderInfo.exp === undefined ? 0 : orderInfo.exp,
				orderInfo.level === undefined ? 0 : orderInfo.level,
				type],
            function (err, results) {
        if (err) {
            console.log('[ERROR!!]mr_db->addNewMrUserInfo, msg : ' + err);
            callback(false);
            return;
        }
        callback(true);
    });
}
exports.addNewMrUserInfo = addNewMrUserInfo;
