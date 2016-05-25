/**
 * 定义角色
 *
 *
 */

var U_ADIMN = 10;
var U_NORMAL = 20;

var crypto = require('crypto');
var map = new Map();

function checkLogin(req, res, next){
	if(!isLogin(req)) {
        res.redirect('/index');
        return ;
    }
   	next();
}

function isLogin(req) {
	var userId = req.cookies.user_id != undefined ? req.cookies.user_id : null;
	if(userId != null) {
		var sessions = getUser(userId);
		if(sessions == undefined) {
			return false;
		}
		var currentTime = (new Date()).getTime();
		if(currentTime >= sessions.expire) {
			return false;
		}

		return allowRoleAccessModel(sessions.roleType, req.baseUrl);
    }else {
        return false;
    }
}


function allowRoleAccessModel(roleType, modelStr) {
	modelStr = modelStr == ''?'/' : modelStr;
	if (roleType == U_ADIMN) {
		return true;
	}
	if (modelStr == '/') {
		return true;
	}

	return false;
}

function changeMerchantId(req, merchant_id) {
	var userId = req.cookies.user_id != undefined ? req.cookies.user_id : null;
	var sessions = getUser(userId);

	console.log('changeMerchantId, delete = ' + sessions.merchant_id + ';new = ' + merchant_id );
	sessions.merchant_id = merchant_id;
	map.delete(sessions.cookieId);
	map.set(sessions.cookieId, sessions);
}

function getUserMerchant(req) {
	var userId = req.cookies.user_id != undefined ? req.cookies.user_id : null;
	var sessions = getUser(userId);
	return sessions.merchant_id;
}

function getUserMerchantType(req) {
	var userId = req.cookies.user_id != undefined ? req.cookies.user_id : null;
	var sessions = getUser(userId);
	return sessions.merchant_type;
}

function getUserRoleType(req) {
	var userId = req.cookies.user_id != undefined ? req.cookies.user_id : null;
	var sessions = getUser(userId);
	return sessions.roleType;
}

//----------------------------------------
// 添加会话认证

function setNewUser(cookieId, roleType, userName) {
	map.delete(cookieId);
	var sessions = {};
	sessions.cookieId = cookieId;
	sessions.roleType = roleType;
	sessions.userName = userName;
	sessions.expire = (new Date()).getTime() + getCookieTime();
	map.set(cookieId, sessions);
	console.log('new login : ' + JSON.stringify(sessions));
	// TODO : 目前没有添加session中定时删除过期数据的功能
}

function getUser(cookieId) {
	return map.get(cookieId);
}

/**
 * 定时更新session过期数据
 */
function updateUserState() {
	var bufferMap = new Map();
	for (var value of map) {
    	var currentTime = (new Date()).getTime();
		if ( currentTime >= value.expire ) {
			bufferMap.set(value.cookieId, value);
		}
	}
	for (var value of bufferMap) {
    	map.delete(value.cookieId);
	}
	setTimeout(updateUserState, 60*60*1000);
}

function logout(req) {
	var userId = req.cookies.user_id != undefined ? req.cookies.user_id : null;
	var sessions = getUser(userId);
	var cookieId = sessions.cookieId;
	map.delete(cookieId);
}

//----------------------------------------
// 工具方法

function getCookieKey() {
	return 'user_id';
}

function getCookieTime() {
	return 60*60*1000;	 // 当前设置为20分钟一次
}

function createCookieId() {
	return 'TBU' + (new Date()).getTime()+ Math.random();
}

function createNewUserNameAndPasswd(username, passwd, callback) {
	// 用户名和密码效验
	// 验证用户名和密码
	var sha256 = crypto.createHash('sha256');
	sha256.update(passwd);
	var step1 = sha256.digest('hex');

	var sha256_2 = crypto.createHash('sha256');
	sha256_2.update(step1);
	var salt = ('T' + Math.random()).substring(0, 10);
	sha256_2.update(salt);
	var storePasswd = sha256_2.digest('hex');
	callback(true, username, storePasswd, salt);
}

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
	if(bufferPasswd == storePasswd) {
		return true;
	}else {
		return false;
	}
}

setTimeout(updateUserState, 60*60*1000);

exports.checkLogin = checkLogin;

exports.isLogin = isLogin;
exports.getCookieTime = getCookieTime;
exports.createCookieId = createCookieId;
exports.getCookieKey = getCookieKey;

exports.setNewUser = setNewUser;
exports.getUser = getUser;

exports.createNewUserNameAndPasswd = createNewUserNameAndPasswd;
exports.allowLogin = allowLogin;

exports.getUserMerchant = getUserMerchant;
exports.getUserMerchantType = getUserMerchantType;
exports.getUserRoleType = getUserRoleType;
exports.changeMerchantId = changeMerchantId;

exports.logout = logout;
