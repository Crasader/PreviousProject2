'use strict';
var crypto = require('crypto');
var redishelper = require('../../mem/redishelper.js');
var session_manager = require('../../session_manager.js');

var SALT_HEAD = 'T';
var REDIS_HEAD_USER_ID = "USERID_";

function createNewUserNameAndPasswd(passwd, callback) {
	// 用户名和密码效验
	// 验证用户名和密码
	var sha256 = crypto.createHash('sha256');
	sha256.update(passwd);
	var step1 = sha256.digest('hex');

	var sha256_2 = crypto.createHash('sha256');
	sha256_2.update(step1);
	var salt = ( SALT_HEAD + Math.random() ).substring(0, 10);
	sha256_2.update(salt);
	var storePasswd = sha256_2.digest('hex');
	callback(storePasswd, salt);
}

exports.createNewUserNameAndPasswd = createNewUserNameAndPasswd;

/**
 * 验证用户名和密码是否一致
 */
function allowLogin(passwd, storePasswd, salt) {
	var sha256 = crypto.createHash('sha256');
	sha256.update(passwd);
	var step1 = sha256.digest('hex');

	var sha256_2 = crypto.createHash('sha256');
	sha256_2.update(step1);
	sha256_2.update(salt);
	var bufferPasswd = sha256_2.digest('hex');
	console.log('allowLogin, passwd = ' + passwd + '; storePasswd = ' + storePasswd + ';salt = ' + salt +
			';bufferPasswd = ' + bufferPasswd);
	if(bufferPasswd == storePasswd) {
		return true;
	}else {
		return false;
	}
}

exports.allowLogin = allowLogin;

function resetUserSession(user_id, session_id) {

	(function(user_id, session_id){
		redishelper.getVaule(REDIS_HEAD_USER_ID+user_id, function(err, redis_result){	// 查询缓存中是否存在此user_id的session_id,如果存在则删除
			if(err) {
				return ;
			}
			if(redis_result != undefined && redis_result != null) {
				var old_session_id = redis_result;
				redishelper.del(old_session_id);// TODO : 清理
			}
			redishelper.setValueWithExpire(REDIS_HEAD_USER_ID+user_id,
				session_id, session_manager.SESSION_EXPIRE);	// 写入新的session_id到user_id下
		});


	})(user_id, session_id);

}

exports.resetUserSession = resetUserSession;
