/**
 * 监听路径：'/map'
 */

var dashboard_data = require('../../../data/dashboard/dashboard_data.js');
var gamelogic = require('../../gamelogic/gamelogic.js');

function getUserInfo(user_id, key_q_type, callback) {
	if(key_q_type === 'mo') {
		dashboard_data.getUserMoInfo(user_id, function (success, body) {
			var pay_dayreport = [];
			if(success ) {
				var bodyObj = JSON.parse(body);
				var i = 0;
				for(i=0; i<bodyObj.length;i++) {
					item = {
						id : i+1,
						pay_and_event_version : bodyObj[i]["pay_and_event_version"],
						pay_event_id : bodyObj[i]["pay_event_id"],
						pay_point_id : bodyObj[i]["pay_point_id"],
						price : bodyObj[i]["price"],
						type : parseInt(bodyObj[i]["type"]) == 0 ? '请求' : '结果',
						order_id : bodyObj[i]["order_id"],
						result : parseInt(bodyObj[i]["result"]) == 0 ? '成功' : bodyObj[i]["result"],
						channel_id : bodyObj[i]["channel_id"],
						create_time : bodyObj[i]["create_time"]
					}
					pay_dayreport[i] = item;
				}
			}
			callback(pay_dayreport);
		});
	}else if(key_q_type === 'mr'){
		dashboard_data.getUserMrInfo(user_id, function (success, body) {
			var pay_dayreport = [];
			if(success ) {
				var bodyObj = JSON.parse(body);
				var i = 0;
				for(i=0; i<bodyObj.length;i++) {
					item = {
						id : i+1,
						pay_and_event_version : bodyObj[i]["pay_and_event_version"],
						pay_event_id : bodyObj[i]["pay_event_id"],
						pay_point_id : bodyObj[i]["pay_point_id"],
						price : bodyObj[i]["price"],
						real_price : bodyObj[i]["real_price"],
						order_id : bodyObj[i]["order_id"],
						third_order_id : bodyObj[i]["third_order_id"],
						third_type : parseInt(bodyObj[i]["third_type"]) == 1 ? '微信' : '斯凯',
						channel_id : bodyObj[i]["channel_id"],
						create_time : bodyObj[i]["create_time"],
						third_time : bodyObj[i]["third_time"]
					}
					pay_dayreport[i] = item;
				}
			}
			callback(pay_dayreport);
		});
	} else if(key_q_type === 'pagechange') {
		dashboard_data.getUserPagechangeInfo(user_id, function (success, body) {
			var pay_dayreport = [];
			if(success ) {
				console.log('getUserPagechangeInfo bodyObj :' + bodyObj);
				var bodyObj = JSON.parse(body);
				var i = 0;
				for(i=0; i<bodyObj.length;i++) {
					item = {
						id : i+1,
						day : bodyObj[i]["day"],
						user_id : bodyObj[i]["user_id"],
						from_page : gamelogic.getPageName(parseInt(bodyObj[i]["from_page"])),
						to_page : gamelogic.getPageName(parseInt(bodyObj[i]["to_page"])),
						channel : bodyObj[i]["channel"],
						nums : bodyObj[i]["nums"]
					}
					pay_dayreport[i] = item;
				}
			}
			callback(pay_dayreport);
		});
	} else if(key_q_type === 'gameinfo') {
		dashboard_data.getUserGameInfo(user_id, function (success, body) {
			var pay_dayreport = [];
			if(success ) {
				console.log('getUserGameInfo bodyObj :' + bodyObj);
				var bodyObj = JSON.parse(body);
				var i = 0;
				for(i=0; i<bodyObj.length;i++) {
					item = {
						user_id : bodyObj[i]["user_id"],
						coins : bodyObj[i]["coins"],
						diamonds : bodyObj[i]["diamonds"],
						exp : bodyObj[i]["exp"],
						turrent_level : bodyObj[i]["turrent_level"],
						mo : bodyObj[i]["mo"],
						nobility_time : bodyObj[i]["nobility_time"]
					}
					pay_dayreport[i] = item;
				}
			}
			callback(pay_dayreport);
		});
	}  else if(key_q_type === 'register') {
		dashboard_data.getUserRegisterInfo(user_id, function (success, body) {
			var pay_dayreport = [];
			if(success ) {
				console.log('getUserRegisterInfo bodyObj :' + bodyObj);
				var bodyObj = JSON.parse(body);
				var i = 0;
				for(i=0; i<bodyObj.length;i++) {
					item = {
						user_id : bodyObj[i]["user_id"],
						create_time : bodyObj[i]["create_time"],
						imei : bodyObj[i]["imei"],
						channel_id : bodyObj[i]["channel_id"],
						hd_type : bodyObj[i]["hd_type"],
						hd_factory : bodyObj[i]["hd_factory"]
					}
					pay_dayreport[i] = item;
				}
			}
			callback(pay_dayreport);
		});
	} else {
		callback(null);
	}

}

exports.getUserInfo = getUserInfo;
