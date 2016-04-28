
var welcome = {
	errorcode : 0,
	errormsg : 'welcome to game catchfish'			// 根目录
};

var success = {
	errorcode : 0,
	errormsg : 'success update data'			// 成功提交数据
};

var notOpen = {
	errorcode : 100,
	errormsg : 'interface not open'			// 接口未开放
};

var notFound404 = {
	errorcode : 101,
	errormsg : '404'	// 404
};

var reqParamsError = {
	errorcode : 102,
	errormsg : '请求参数错误'	// 参数错误
}

var reqVersionError = {
	errorcode : 103,
	errormsg : 'req game version error'	// 参数游戏版本号
}

var dbError = {
	errorcode : 201,
	errormsg : 'db error'	// 数据库访问异常
};

var redisError = {
	errorcode : 202,
	errormsg : 'redis error'	// 缓存访问异常
};

var noUserInfo = {
	errorcode : 301,
	errormsg : 'no user info'	// 找不到用户信息
};

var errorUserInfo = {
	errorcode : 302,
	errormsg : 'error user info'	// 错误格式的用户名
};

var errorCreateNewUser = {
	errorcode : 303,
	errormsg : 'error cretate new user'	// 分配临时用户错误
};

var invalidSessionId = {
	errorcode : 304,
	errormsg : '登陆过期,请清新登陆.'	// 会话id失效
};

var noOrderInfo = {
	errorcode : 305,
	errormsg : 'no order info'	// 找不到用户信息
};

var successSetNickName = {
	errorcode : 0,
	errormsg : 'success set user name'	// 写入用户名成功
};

var existNickName = {
	errorcode : 306,
	errormsg : 'exist nick name'	// 已经存在的用户名
};

var errorNickNameOrPassword = {
	errorcode : 307,
	errormsg : 'error Nick Name Or Password'	// 错误的用户名或者密码
};

var needUpdate = {
	errorcode : 310,
	errormsg : '版本过低请升级到最新版本',	// 版本过低请升级到最新版本
	url : 'www.baidu.com'
};

var maintenance = {
	errorcode : 311,
	errormsg : '抱歉,服务器正在维护,请稍后再试.',	// 抱歉,服务器正在维护,请稍后再试.
}

exports.maintenanceDesc = JSON.stringify(maintenance);

exports.errorNickNameOrPasswordDesc = JSON.stringify(errorNickNameOrPassword);



exports.welcomeDesc = JSON.stringify(welcome);
exports.successDesc = JSON.stringify(success);
exports.notOpenDesc = JSON.stringify(notOpen);
exports.notFound404Desc = JSON.stringify(notFound404);
exports.reqParamsErrorDesc = JSON.stringify(reqParamsError);
exports.reqVersionErrorDesc = JSON.stringify(reqVersionError);

exports.dbErrorDesc = JSON.stringify(dbError);
exports.redisErrorDesc = JSON.stringify(redisError);

exports.noUserInfoDesc = JSON.stringify(noUserInfo);
exports.errorUserInfoDesc = JSON.stringify(errorUserInfo);
exports.errorCreateNewUserDesc = JSON.stringify(errorCreateNewUser);
exports.invalidSessionIdDesc = JSON.stringify(invalidSessionId);
exports.needUpdateDesc = JSON.stringify(needUpdate);
exports.noOrderInfoDesc = JSON.stringify(noOrderInfo);


exports.successSetNickNameDesc = JSON.stringify(successSetNickName);
exports.existNickNameDesc = JSON.stringify(existNickName);

var errorMoParameter = {
	errorcode : 401,
	errormsg : 'Error Mo Parameter'			// 异常的mo提交参数
};

var errorMrQueryParameter = {
	errorcode : 402,
	errormsg : 'Error Mr Query Parameter'			// 异常的mr查询提交参数
};

var errorMrQueryNoOrderInfo = {
	errorcode : 403,
	errormsg : 'Error Mr Query No Order Info'			// 没有查询到订单的mr信息
};

exports.errorMoParameterDesc = JSON.stringify(errorMoParameter);
exports.errorMrQueryParameterDesc = JSON.stringify(errorMrQueryParameter);
exports.errorMrQueryNoOrderInfoDesc = JSON.stringify(errorMrQueryNoOrderInfo);

var noEnoughItems = {
	errorcode : 510,
	errormsg : 'no enough items'	// 没有足够的道具供使用
};

exports.noEnoughItemsDesc = JSON.stringify(noEnoughItems);

var notAllowBuyItems = {
	errorcode : 511,
	errormsg : 'no allow buy items'	// 没有足够的道具供使用
};

exports.notAllowBuyItemsDesc = JSON.stringify(notAllowBuyItems);

var noEnoughDiamonds = {
	errorcode : 512,
	errormsg : 'no enough diamonds'	// 没有足够的钻石
};

exports.noEnoughDiamondsDesc = JSON.stringify(noEnoughDiamonds);
