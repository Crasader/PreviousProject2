'use strict';
var agreement = require('../../agreement.js');
var load_balancing = require('../../load_balancing.js');
var dbmanager = require('../../db/dbmanager.js');
var user_db = require('./user_db.js');
var user_ids = require('./user_ids.js');
var redishelper = require('../../mem/redishelper.js');
var session_manager = require('../../session_manager.js');

var player_logic =  require('../player/player_logic.js');
var bag_logic = require('../player/bag_logic.js');

var user_manager = require('./user_manager.js');

var GUEST_USER_NAME_HEAD = 'g_';

// TODO : 后期此部分走配置
var name_id = 1;
var login_id = 1;
var fortune_id = 1;
var mo_id = 1;

function addNewGuestUser(user_id, imei, hdType, hdFactory, channel_id) {
	var guestDbTablePostfix = user_ids.getGuestDbTablePostfix(user_id);
	user_db.addNewGuestUser(dbmanager.getClient(), guestDbTablePostfix, user_id, imei, hdType, hdFactory, channel_id,
			name_id, login_id, fortune_id, mo_id, function(success, new_user_id, new_login_id, new_channel_id){
		if(success){
			user_db.addNewMarkLogin(dbmanager.getClient(), new_user_id, new_login_id, new_channel_id, new Date().Format("yyyyMMdd"), 0, function(success){
			});
		}
	});
}

function isLogin(user_id, imei, channel_id, callback) {
	var guestDbTablePostfix = user_ids.getGuestDbTablePostfix(parseInt(user_id));
	user_db.isLogin(dbmanager.getClientS(), guestDbTablePostfix, user_id, imei, channel_id, function(errorcode, result, channel_id) {
		if(errorcode === 0) {
			addLoginMark(result.user_id, result.login_id, channel_id, result.create_time);
			successGetUserLoginInfo(result, callback);
		}else {
			if(errorcode === 201) {
				callback(agreement.dbErrorDesc);
			}else {
				callback(agreement.noUserInfoDesc);
			}
		}
	});
}

function isUser(req_params, callback) {
	if(!examineUserIdParams(req_params.nick_name, req_params.password)) {
		callback(agreement.reqParamsErrorDesc);
	}
	var guestDbTablePostfix = 1;	// TODO  : 目前写死，后续根据id编号自动匹配
	var nick_name = req_params.nick_name;
	(function(nick_name){
		user_db.isUser(dbmanager.getClientS(), guestDbTablePostfix, req_params.nick_name, req_params.password, function(errorcode, result) {
			if(errorcode === 0) {
				if(user_manager.allowLogin(result.password, result.store_password, result.salt)) {
					isUserIdExit(result.user_id, nick_name, callback);
				} else {
					callback(agreement.errorNickNameOrPasswordDesc);	// 错误的用户名或者密码
				}

			}else if(errorcode === 301){
				callback(agreement.noUserInfoDesc);
			}else {
				callback(agreement.dbErrorDesc);
			}
		});
	})(nick_name);

}

function examineUserIdParams(nick_name, password) {
	if( nick_name === undefined || nick_name === null ||
			nick_name.length < 2 ||
			nick_name.substring(0, 2) === 'g_' || nick_name.length >= 16 ) {
		return false;
	}
	if( password === undefined || password === null ||
			password.length < 4 || password.length > 12 ) {
		return false;
	}
	return true;
}

exports.isUser = isUser;

function isUserIdExit(user_id, nick_name, callback) {
	var guestDbTablePostfix = user_ids.getGuestDbTablePostfix(parseInt(user_id));
	(function(nick_name){
		user_db.isUserIdExit(dbmanager.getClientS(), guestDbTablePostfix, user_id, function(errorcode, result) {
			if(errorcode === 0) {
				addLoginMark(result.user_id, result.login_id, result.channel_id, result.create_time);
				result.nick_name = nick_name;
				successGetUserLoginInfo(result,callback);
			}else {
				if(errorcode === 201) {
					callback(agreement.dbErrorDesc);
				}else {
					callback(agreement.noUserInfoDesc);
				}
			}
		});
	})(nick_name);
}

// 查询用户信息并更新缓存
function successGetUserLoginInfo(result, callback) {
	(function(result){
		player_logic.getPlayerInfo(result.user_id, result.fortune_id, function(success, user_result){
			if(success) {
				var session_id = session_manager.getNewSessionId();
				var newResult = createUserSessionInfo(session_id, result, user_result);
				user_manager.resetUserSession(newResult.user_id, newResult.session_id);
				redishelper.setValueWithExpire(newResult.session_id, JSON.stringify(newResult), session_manager.SESSION_EXPIRE);
				initBgInfo(false, newResult.user_id, newResult.session_id);

				var clientResult = getLoginSuccessInfo(newResult.session_id);
				console.log('clientResult : ' + JSON.stringify(clientResult));
				callback(JSON.stringify(clientResult));
				return ;
			} else {
				callback(agreement.dbErrorDesc);
				return ;
			}
		});
	})(result);
}

function addLoginMark(user_id, login_id, channel_id, create_time) {
	var day = parseInt(new Date().Format("yyyyMMdd"));
	var logs = create_time.split('-');
	var login_day = parseInt( Math.abs( new Date() - new Date(logs[0],parseInt(logs[1])-1,logs[2]) ) / 1000 / 60 / 60 / 24);
	user_db.addNewMarkLogin(dbmanager.getClient(), user_id, login_id, channel_id,
			day, login_day, function(success){
	});
}

function getLoginSuccessInfo(session_id) {
	return {
		errorcode : 0,
		errormsg : '',
		session_id : session_id,
		app_address : load_balancing.getAppServerIp(),
		app_port : load_balancing.getAppServerPort(),
		game_address : load_balancing.getGameServerIp(),
		game_port : load_balancing.getGameServerPort()
	};
}

function createUserSessionInfo(p_session_id, result, user_result) {

	var user_info =  {
		user_id : result.user_id,
		nick_name : result.nick_name,
		channel_id : result.channel_id,
		session_id : p_session_id,
		name_id : result.name_id,
		login_id : result.login_id,
		fortune_id : result.fortune_id,
		mo_id : result.mo_id,
		create_time : result.create_time,
		coins : user_result.coins,
		diamonds : user_result.diamonds,
		exps : user_result.exp,
		turrent_level : user_result.turrent_level,
		chest_level : user_result.chest_level,
		mo : user_result.mo,
		mo_first : user_result.mo_first,
		mo_coins : user_result.mo_coins
	};
	return user_info;
}


var initRewards = [];	// TODO : 目前写死，后期读等级1的配置文件
initRewards.push({
	item_id : 1013,
	nums : 100
});
initRewards.push({
	item_id : 1001,
	nums : 200
});
initRewards.push({
	item_id : 1004,
	nums : 2
});

function getNewUserInfo(req_params, callback) {
	(function(req_params){
		user_ids.getGuestIds(function(success, id){	// 获取一个分配的id
			if(success && id > user_ids.MAX_CURSOR_POSITION) {
				initNewUser(id, req_params, callback);
			}else {
				callback(agreement.errorCreateNewUser);
			}
		});
	})(req_params);
}

function initNewUser(id, req_params, callback) {
	addNewGuestUser(id, req_params.imei, req_params.hd_type, req_params.hd_factory, req_params.channel_id);	// 入库
	var session_id = session_manager.getNewSessionId();
	// 生成sessionid并写入缓存
	var clientResult = {
		errorcode : 0,
		user_name : GUEST_USER_NAME_HEAD + id,
		session_id : session_id,
		app_address : load_balancing.getAppServerIp(),
		app_port : load_balancing.getAppServerPort(),
		game_address : load_balancing.getGameServerIp(),
		game_port : load_balancing.getGameServerPort(),
		login_rewards : initRewards
	};
	callback(JSON.stringify(clientResult));
	var user_info = { 	// 玩家的基础信息：金币、钻石、等级和经验，当前为写入初始化默认信息。
		user_id : id,
		nick_name : 'g_' + id,
		channel_id : req_params.channel_id,
		session_id : session_id,
		name_id : name_id,
		login_id : login_id,
		fortune_id : fortune_id,
		mo_id : mo_id,
		create_time : new Date().Format("yyyy-MM-dd"),
		coins : 200,
		diamonds : 0,
		turrent_level : 1,
		exps : 0,
		chest_level : 0,
		mo : 0,
		mo_first : 0,
		mo_coins : 0
	};
	var sync_info = {
		user_id : user_info.user_id,
		fortune_id : user_info.fortune_id,
		coins : user_info.coins,
		diamonds : user_info.diamonds
	};
	player_logic.addPlayerCoinsAndDiamondsWithoutRedis(sync_info);	// 写入用户信息
	redishelper.setValueWithExpire(user_info.session_id, JSON.stringify(user_info), session_manager.SESSION_EXPIRE);

	var user_bag_result = {
		errorcode : 0,
		item_lists : []
	};
	var sync_info = {	// TODO : 目前没有走配置
		user_id : user_info.user_id,
		item_id : 1013,
		nums : 100
	};
	user_bag_result.item_lists.push(sync_info);
	bag_logic.syncPlayerBgInfo(sync_info);
	sync_info = {
		user_id : user_info.user_id,
		item_id : 1004,
		nums : 2
	};
	user_bag_result.item_lists.push(sync_info);
	bag_logic.syncPlayerBgInfo(sync_info);

	redishelper.setValueWithExpire('BG_' + user_info.session_id, JSON.stringify(user_bag_result), session_manager.SESSION_EXPIRE);
}

var bg_result = {
	errorcode : 0,
	item_lists : []
}; // 初始化背包信息
var bg_result_str = JSON.stringify(bg_result);

function initBgInfo(newUser, user_id, session_id) {
	redishelper.setValueWithExpire('BG_' + session_id, bg_result_str, session_manager.SESSION_EXPIRE);
	if( !newUser ) {	// 如果不是新用户，查询并更新角色背包信息
		player_logic.getUserBgInfo(user_id, function(success, results) {
			if(success && results != undefined && results != null && results.length > 0) {
				var user_bg_result = {
					errorcode : 0,
					item_lists : []
				};
				for(var i=0; i<results.length; i++) {
					user_bg_result.item_lists.push({
						item_id : results[i]['item_id'],
				    nums : results[i]['nums']
					});
				}
				redishelper.setValueWithExpire('BG_' + session_id, JSON.stringify(user_bg_result), session_manager.SESSION_EXPIRE);
			}
		});
	}
}

/**
 * [TODO][即将作废] 注册用户名
 */
function setNickName(user_id, name_id, nickname, gender, callback) {
	user_db.setNickName(dbmanager.getClient(), user_id, name_id, nickname, gender, function(success){
		if(success) {
			callback(agreement.successSetNickNameDesc);
		}else {
			callback(agreement.existNickNameDesc);
		}
	});
}

exports.GUEST_USER_NAME_HEAD = GUEST_USER_NAME_HEAD;
exports.addNewGuestUser = addNewGuestUser;
exports.isLogin = isLogin;
exports.getNewUserInfo = getNewUserInfo;
exports.setNickName = setNickName;

/**
 * 注册
 */
function bindNickname(session_id, fortune_id, user_id, name_id, req_params, callback) {
	if( !examineRegisterParams(req_params) ) {
		callback(agreement.reqParamsErrorDesc);
		return ;
	}
	(function(session_id, fortune_id, user_id, req_params) {
		user_manager.createNewUserNameAndPasswd(req_params.password, function(storePasswd, salt){
			user_db.register( dbmanager.getClient(), user_id, name_id, req_params.nick_name, req_params.gender, storePasswd, salt, function(success) {
				if (success) {
					var result = {
						errorcode : 0,
						presented_diamonds : 20	// TODO : 目前写死，绑定账号赠送的钻石
					};


					presentedForRegister(session_id, user_id, fortune_id);
					callback(JSON.stringify(result));
				} else {
					callback(agreement.existNickNameDesc);
				}
			} );
		});
	} )(session_id, fortune_id, user_id, req_params);
}

exports.bindNickname = bindNickname;

/**
 * 注册
 */
function register(device_params, req_params, callback) {
	if( !examineRegisterParams(req_params) ) {
		callback(agreement.reqParamsErrorDesc);
		return ;
	}
	(function(device_params, req_params){
		user_ids.getGuestIds(function(success, user_id){	// 获取一个分配的id
			(function(user_id){
				user_manager.createNewUserNameAndPasswd(req_params.password, function(storePasswd, salt){
					user_db.register( dbmanager.getClient(), user_id, name_id, req_params.nick_name, req_params.gender, storePasswd, salt, function(success) {
						if (success) {
							initNewUser(user_id, device_params, callback);
						} else {
							callback(agreement.existNickNameDesc);
						}
					} );
				});
			})(user_id);
		});
	})(device_params, req_params);
}

exports.register = register;

function presentedForRegister(session_id, user_id, fortune_id) {
	var sync_info = {
		user_id : user_id,
		fortune_id : fortune_id === undefined ? 1 : fortune_id,
		coins : 0,
		diamonds : 20
	};
	player_logic.syncPlayerCoinsAndDiamonds(session_id, sync_info);
}

function examineRegisterParams(req_params) {
	console.log('examineRegisterParams req_params :' + JSON.stringify(req_params));
	if( req_params.nick_name === undefined || req_params.nick_name === null ||
			req_params.nick_name.length < 2 ||
			req_params.nick_name.substring(0, 2) === 'g_' || req_params.nick_name.length >= 16 ) {
		console.log('examineRegisterParams nickname ... ');
		return false;
	}
	// if( ( parseInt(req_params.gender) != 0 && parseInt(req_params.gender) != 1) ) {
	// 	console.log('examineRegisterParams gender ... ');
	// 	return false;
	// }
	if( req_params.password === undefined || req_params.password === null ||
			req_params.password.length < 6 || req_params.password.length > 12 ) {
		console.log('examineRegisterParams password ... ');
		return false;
	}
	// TODO : 增加检查，包含数字并且包含字母
	return true;
}
