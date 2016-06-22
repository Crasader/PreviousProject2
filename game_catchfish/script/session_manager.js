
var redishelper = require('./mem/redishelper.js');
var agreement = require('./agreement.js');

var startVaule = 0;
var SESSION_ID_HEAD = 'TBU_';

var SESSION_EXPIRE = 60*60*2;	// 2小时

var maintenance = false;	// 服务器是否在维护 TODO : 等待实现逻辑，默认为false

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
	// if(maintenance) {	// TODO : 后期上线后打开
	// 	callback(false, agreement.maintenanceDesc);
	// 	return ;
	// }
	(function(session_id){
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
	})(session_id);

}

exports.getNewSessionId = getNewSessionId;
exports.SESSION_ID_HEAD = SESSION_ID_HEAD;
exports.SESSION_EXPIRE = SESSION_EXPIRE;

exports.isLogin = isLogin;