'use strict';
/**
 * 用户进入[user/hello]
 * 用户登陆[user/login]
 * 用户注册[user/register]
 * 第三方登陆(微信)[user/third]
 */

var user_logic = require('./user_logic.js');
var session_manager = require('../../session_manager.js');
var agreement = require('../../agreement.js');

var express = require('express');
var router = express.Router();

/**
 * 用户进入
 * 协议：/user/hello
 * 测试：
 */
router.post( '/hello', function (req, res) {
	if(needUpdate(req.body.game_version)){
		res.end(agreement.needUpdateDesc);
		return ;
	}
	if(!examineDeviceParams(req.body.imei, req.body.hd_type, req.body.hd_factory, req.body.channel_id)) {
		res.end(agreement.reqParamsErrorDesc);
		return ;
	}
	var req_params = {
		imei : req.body.imei,
		hd_type : req.body.hd_type,
		hd_factory : req.body.hd_factory,
		channel_id : req.body.channel_id
	};
	console.log('user_routers->[/hello]' + JSON.stringify(req_params));
	user_logic.getNewUserInfo(req_params, function(result){
		res.end(result);
	});

});

function examineDeviceParams(imei, hd_type, hd_factory, channel_id){
	if(imei === undefined || hd_type === undefined ||
			hd_factory === undefined ||
			channel_id === undefined || channel_id === null ||
			channel_id.length < 2) {
		return false;
	}
	return true;
}

/**
 * 用户登录。玩家在会话失效的时候用于获取session_id
 * 协议：user/login
 * 测试：
 */
router.post( '/login', function (req, res) {
	if(needUpdate(req.body.game_version)){
		res.end(agreement.needUpdateDesc);
		return ;
	}
	if(req.body.imei === undefined || req.body.hd_type === undefined ||
			req.body.hd_factory === undefined || req.body.user_name === undefined ||
			req.body.channel_id === undefined || req.body.channel_id === null) {
		res.end(agreement.reqParamsErrorDesc);
		return ;
	}

	var req_params = {
		user_name : req.body.user_name,
		imei : req.body.imei,
		hd_type : req.body.hd_type,
		hd_factory : req.body.hd_factory,
		channel_id : req.body.channel_id
	};
	console.log('user_routers->[/login]' + JSON.stringify(req_params));

	if(req_params.user_name.substring(0, user_logic.GUEST_USER_NAME_HEAD.length) != user_logic.GUEST_USER_NAME_HEAD || req_params.user_name.length <= user_logic.GUEST_USER_NAME_HEAD.length ) {
		res.end(agreement.errorUserInfoDesc);
		return ;
	}
	var user_id = req_params.user_name.substring(user_logic.GUEST_USER_NAME_HEAD.length, req_params.user_name.length);
	user_logic.isLogin(user_id, req_params.imei, req_params.channel_id, function(result){	// 查询玩家是否登录
		res.end(result);
	});
});

/**
 * 单机用户昵称设定[TODO : 等待移除]
 * 协议：user/nickname
 * 测试：
 */
router.post( '/nickname', function (req, res) {
	if(req.body.session_id === undefined || req.body.nickname === undefined || req.body.gender === undefined) {
		res.end(agreement.reqParamsErrorDesc);
		return ;
	}
	var nickname = req.body.nickname;
	var gender = req.body.gender;
	console.log('nickname length : ' + nickname.length);
	if(nickname === null || nickname.length < 4 || nickname.length > 16) {
		res.end(agreement.reqParamsErrorDesc);
	}
	if(gender === null || (gender != '0' && gender != '1') ) {
		res.end(agreement.reqParamsErrorDesc);
	}
	(function(nickname, gender){
		session_manager.isLogin(req.body.session_id, function(login, data){
			if(!login) {
				res.end(data);
				return ;
			}
			user_logic.setNickName(data.user_id, data.name_id, nickname, gender, function(resultStr){
				console.log('setNickName result : ' + resultStr);
				res.end(resultStr);
			});
		});
	})(nickname, gender);
});

/**
 * 用户昵称绑定-第三方
 * 协议：user/register[POST]
 * 参数：nick_name, password, gender, imei, hd_type, hd_factory, channel_id
 */
router.post( '/register', function (req, res) {
	if(needUpdate(req.body.game_version)){
		res.end(agreement.needUpdateDesc);
		return ;
	}
	if(!examineDeviceParams(req.body.imei, req.body.hd_type, req.body.hd_factory, req.body.channel_id)) {
		res.end(agreement.reqParamsErrorDesc);
		return ;
	}
	var req_params = {
		nick_name : req.body.nick_name,
		password : req.body.password,
		gender : req.body.gender
	};
	var device_params = {
		imei : req.body.imei,
		hd_type : req.body.hd_type,
		hd_factory : req.body.hd_factory,
		channel_id : req.body.channel_id
	};
	user_logic.register(device_params, req_params, function(resultStr){
		console.log('register result : ' + resultStr);
		res.end(resultStr);
	});
});

/**
 * 用户昵称绑定-第三方
 * 协议：user/nickname/bind[POST]
 * 参数：nick_name, password, gender, session_id
 */
router.post( '/nickname/bind', function (req, res) {
	if(needUpdate(req.body.game_version)){
		res.end(agreement.needUpdateDesc);
		return ;
	}
	var req_params = {
		nick_name : req.body.nick_name,
		password : req.body.password,
		gender : req.body.gender
	};

	(function(req_params){
		session_manager.isLogin(req.body.session_id, function(login, data){
			if(!login) {
				res.end(data);
				return ;
			}
			user_logic.bindNickname(data.session_id, data.fortune_id, data.user_id, data.name_id, req_params, function(resultStr){
				console.log('nickname bind result : ' + resultStr);
				res.end(resultStr);
			});
		});
	})(req_params);
});

/**
 * 用户昵称登录。玩家在会话失效的时候用于获取session_id
 * 协议：user/nickname/login[POST]
 * 参数：nick_name, password
 */
router.post( '/nickname/login', function (req, res) {
	if(needUpdate(req.body.game_version)){
		res.end(agreement.needUpdateDesc);
		return ;
	}
	var req_params = {
		nick_name : req.body.nick_name,
		password : req.body.password
	};


	user_logic.isUser(req_params, function(result){	// 查询玩家是否登录
			console.log('user_routers->[nickname/login] result : ' + result);
		res.end(result);
	});
});

/**
 * 用户登录-第三方
 * 协议：user/third
 * 测试：
 */
router.post( '/third', function (req, res) {
	// TODO : 暂不实现
  res.end(agreement.notOpenDesc);
});



function needUpdate(game_version) {
	if(game_version === undefined || game_version === null) {
		return false;
	}
	game_version = parseInt(game_version);
	if(game_version === 1) {
		return true;
	}
	return false;
}


module.exports = router;
