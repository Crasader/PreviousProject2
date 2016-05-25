'use strict';
var redishelper = require('../../environment/mem/redishelper.js');
var agreement = require('./agreement.js');

var startVaule = 0;
var SESSION_ID_HEAD = 'TBU_';

var SESSION_EXPIRE = 60*60*2;	// 2小时

/**
 * 获取一个会话ID
 */
function getNewSessionId() {
	if(startVaule === 0) {
		startVaule = parseInt(new Date().getTime());
	}
	startVaule++;
	return SESSION_ID_HEAD + startVaule;
}

/**
 * 判断用户是否登录
 */
function isLogin(session_id, callback) {
	redishelper.getVaule(session_id, function(err, redis_result){
		if(err) {
			callback(false, agreement.redisErrorDesc);
			return ;
		}
		if(redis_result != undefined) {
			callback(true, JSON.parse(redis_result));
			return ;
		}
		callback(false, agreement.invalidSessionIdDesc);
	});
}

exports.getNewSessionId = getNewSessionId;
exports.SESSION_ID_HEAD = SESSION_ID_HEAD;
exports.SESSION_EXPIRE = SESSION_EXPIRE;

exports.isLogin = isLogin;
