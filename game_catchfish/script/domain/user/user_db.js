'use strict';
function getGuestStartUserId(vauleStep, client, callback) {
	client.query(' SELECT value FROM id_builder WHERE id = 1',
            function (err, results) {
        if (err) {
            console.log('[ERROR!!]user_dab->getGuestStartUserId, msg : ' + err);
            callback(false, err);
            return;
        }
        if(results != undefined && results != null && results.length > 0) {
        	console.log('user_db->getGuestMaxUserId, result = ' + results[0]['value']);
        	updateGuestStartUserId( (parseInt(results[0]['value'])+vauleStep), vauleStep, client, callback);
        }
    });
}

function updateGuestStartUserId(newValue, vauleStep, client, callback) {
	client.query(' UPDATE id_builder SET value = ? WHERE id = 1',
			[newValue],
            function (err, results) {
        if (err) {
            console.log('[ERROR!!]user_dab->updateGuestStartUserId, msg : ' + err);
            callback(false, err);
            return;
        }
        callback( true, newValue-vauleStep);
    });
}

function addNewMarkLogin(client, user_id, login_id, channel_id, day, login_day, callback) {
	client.query(' INSERT INTO mark_user_login_' + login_id +
			' SET user_id = ?, day = ?, channel_id = ?, login_day = ? ',
			[user_id, day, channel_id, login_day],
            function (err, results) {
        if (err) {
            // console.log('[ERROR!!]user_db->addNewMarkLogin, msg : ' + err);
            callback(false);
            return;
        }
        callback(true);
    });
}

function addNewGuestUser(client, guestDbTablePostfix, user_id, imei, hdType, hdFactory, channel_id,
		name_id, login_id, fortune_id, mo_id, callback) {
	client.query(' INSERT INTO user_guest_' + guestDbTablePostfix +
			' SET user_id = ?, imei = ?, hd_type = ?, hd_factory = ?, channel_id = ?, '+
			' name_id = ?, login_id = ?, fortune_id = ?, mo_id = ?, ' +
			' create_time = ?',
			[user_id, imei, hdType, hdFactory, channel_id,
			 name_id, login_id, fortune_id, mo_id,
			 new Date().Format("yyyy-MM-dd hh:mm:ss:S")],
            function (err, results) {
        if (err) {
            console.log('[ERROR!!]user_db->addNewGuestUser, msg : ' + err);
            callback(false);
            return;
        }
        callback(true, user_id, login_id, channel_id);
    });
}

function isLogin(client, guestDbTablePostfix, user_id, imei, channel_id, callback) {
	client.query(' select user_id, name_id, login_id, fortune_id, mo_id, create_time FROM user_guest_' + guestDbTablePostfix +
			' WHERE user_id = ? AND imei = ? AND channel_id = ?',
			[user_id, imei, channel_id],
            function (err, results) {
        if (err) {
            console.log('[ERROR!!]user_db->isLogin, msg : ' + err);
            callback(201, err);		// DB ERROR
            return;
        }
        if(results != undefined && results != null && results.length > 0) {
					var user_info = {
						user_id : results[0]['user_id'],
						nick_name : 'g_' + results[0]['user_id'],
						name_id : results[0]['name_id'],
						login_id : results[0]['login_id'],
						fortune_id : results[0]['fortune_id'],
						mo_id : results[0]['mo_id'],
						channel_id : channel_id,
						create_time : (results[0]['create_time']).substring(0,10),
						coins : 0,
						diamonds : 0,
						level : 0,
						exp : 0,
						turrent_level : 1,
						mo : 0,
						chest_level : 0

					};
        	callback(0, user_info, channel_id);
        	return ;
        }
        callback(301, 'NO USER', channel_id);		// 没有用户信息
    });
}

/**
 * 注册用户名
 */
function setNickName(client, user_id, name_id, nickname, gender, callback) {
	console.log('user_id = ' + user_id + ';name_id = ' + name_id + 'nickname = ' + nickname + ';gender = ' + gender);
	client.query(' INSERT INTO name_' + name_id + ' SET user_name = ?, gender = ?, user_id = ?',
			[nickname, gender, user_id],
            function (err, results) {
        if (err) {
            console.log('[ERROR!!]user_db->setNickName,nickname :' + nickname + ', err msg : ' + err);
            callback(false);
            return;
        }
        callback(true);
    });
}


exports.getGuestStartUserId = getGuestStartUserId;
exports.addNewGuestUser = addNewGuestUser;
exports.isLogin = isLogin;
exports.addNewMarkLogin =addNewMarkLogin;
exports.setNickName = setNickName;

function register(client, user_id, name_id, nick_name, gender, password, salt, callback) {
	client.query(' INSERT INTO nick_name_' + name_id + ' SET nick_name = ?, gender = ?, user_id = ?, password = ?, salt = ?, create_time = ? ',
			[nick_name, gender, user_id, password, salt, new Date().Format("yyyyMMdd")],
            function (err, results) {
        if (err) {
            console.log('[ERROR!!]user_db->register,nickname :' + nick_name + ', err msg : ' + err);
            callback(false);
            return;
        }
        callback(true);
    });
}

exports.register = register;

function isUserIdExit(client, guestDbTablePostfix, user_id, callback) {
	client.query(' select user_id, name_id, login_id, fortune_id, mo_id, channel_id, create_time FROM user_guest_' + guestDbTablePostfix +
			' WHERE user_id = ?',
			[user_id],
            function (err, results) {
        if (err) {
            console.log('[ERROR!!]user_db->isUserIdExit, msg : ' + err);
            callback(201, err);		// DB ERROR
            return;
        }
        if(results != undefined && results != null && results.length > 0) {
					var user_info = {
						user_id : results[0]['user_id'],
						name_id : results[0]['name_id'],
						nick_name : 'g_'+ results[0]['user_id'],
						login_id : results[0]['login_id'],
						fortune_id : results[0]['fortune_id'],
						mo_id : results[0]['mo_id'],
						channel_id : results[0]['channel_id'],
						create_time : (results[0]['create_time']).substring(0,10),
						coins : 0,
						diamonds : 0,
						level : 0,
						exp : 0,
						turrent_level : 1,
						mo : 0,
						chest_level : 0
					};
        	callback(0, user_info);
        	return ;
        }
        callback(301, 'NO USER');		// 没有用户信息
    });
}

exports.isUserIdExit = isUserIdExit;

function isUser(client, guestDbTablePostfix, nick_name, old_password, callback) {
	client.query(' select user_id, password, salt FROM nick_name_' + guestDbTablePostfix +
			' WHERE nick_name = ?',
			[nick_name],
            function (err, results) {
        if (err) {
            console.log('[ERROR!!]user_db->isUser, msg : ' + err);
            callback(201, err);		// DB ERROR
            return;
        }
        if(results != undefined && results != null && results.length > 0) {
					var user_info = {
						user_id : results[0]['user_id'],
						password : old_password,
						store_password : results[0]['password'],
						salt : results[0]['salt']
					};
					console.log('molo_isUser' + JSON.stringify(user_info));
        	callback(0, user_info);
        	return ;
        }
        callback(301, 'NO USER');		// 没有用户信息
    });
}

exports.isUser = isUser;
