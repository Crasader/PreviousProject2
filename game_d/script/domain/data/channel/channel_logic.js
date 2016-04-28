/**
 * 监听路径：'/map'
 */

var dashboard_data = require('../../../data/dashboard/dashboard_data.js');

function getChannelDayreport(day, callback) {
	dashboard_data.getChannelDayreport(day, function (success, body) {
		var channel_dayreport = [];
		if(success ) {
			var bodyObj = JSON.parse(body);
			var i = 0;
			for(i=0; i<bodyObj.length;i++) {
				item = {
					id : i+1,
					day : bodyObj[i]["day"],
					channel_id : bodyObj[i]["channel_id"],
					user_new : bodyObj[i]["user_new"],
					user_active : bodyObj[i]["user_active"],
					r_second_u : bodyObj[i]["r_second_u"],
					mo_req_time : bodyObj[i]["mo_req_time"],
					mo_req_money : bodyObj[i]["mo_req_money"],
					mo_req_user : bodyObj[i]["mo_req_user"],
					mo_req_user_per : (parseFloat(bodyObj[i]["mo_req_user"])*100/parseFloat(bodyObj[i]["user_active"])).toFixed(2)+'%',
					mo_success_time : bodyObj[i]["mo_success_time"],
					mo_success_money : bodyObj[i]["mo_success_money"],
					mo_success_user : bodyObj[i]["mo_success_user"],
					mr_time : bodyObj[i]["mr_time"],
					mr_money : bodyObj[i]["mr_money"],
					mr_user : bodyObj[i]["mr_user"],
					new_mr_money : (parseFloat(bodyObj[i]["mr_money"])/parseFloat(bodyObj[i]["user_new"])).toFixed(2)+'%',
					r_seven_2 : bodyObj[i]["r_seven_2"],
					r_thirty_2 : bodyObj[i]["r_thirty_2"],
					r_thirty_m : bodyObj[i]["r_thirty_m"]
				}
				channel_dayreport[i] = item;
			}
		}
		// TODO : 增加全部渠道叠加数据
		callback(channel_dayreport);
	});
}

exports.getChannelDayreport = getChannelDayreport;



function getOneChannel(channel_id, callback) {
	dashboard_data.getOneChannel(channel_id, function (success, body) {
		var channel_dayreport = [];
		if(success ) {
			var bodyObj = JSON.parse(body);
			var i = 0;
			for(i=0; i<bodyObj.length;i++) {
				item = {
					id : i+1,
					day : bodyObj[i]["day"],
					channel_id : bodyObj[i]["channel_id"],
					user_new : bodyObj[i]["user_new"],
					user_active : bodyObj[i]["user_active"],
					r_second_u : bodyObj[i]["r_second_u"],
					r_second_u_per : i == (bodyObj.length-1) ? 'NA' : (parseFloat(bodyObj[i]["r_second_u"])*100/parseFloat(bodyObj[i+1]["user_new"])).toFixed(2)+'%',
					r_2_u : bodyObj[i]["r_2_u"],
					r_3_u : bodyObj[i]["r_3_u"],
					r_4_u : bodyObj[i]["r_4_u"],
					r_5_u : bodyObj[i]["r_5_u"],
					r_6_u : bodyObj[i]["r_6_u"],
					r_7_u : bodyObj[i]["r_7_u"],
					mo_req_time : bodyObj[i]["mo_req_time"],
					mo_req_money : bodyObj[i]["mo_req_money"],
					mo_req_user : bodyObj[i]["mo_req_user"],
					mo_success_time : bodyObj[i]["mo_success_time"],
					mo_success_money : bodyObj[i]["mo_success_money"],
					mo_success_user : bodyObj[i]["mo_success_user"],
					mr_time : bodyObj[i]["mr_time"],
					new_mr_money : bodyObj[i]["new_mr_money"],
					mr_money : bodyObj[i]["mr_money"],
					mr_user : bodyObj[i]["mr_user"],
					new_mr_money : (parseFloat(bodyObj[i]["mr_money"])/parseFloat(bodyObj[i]["user_new"])).toFixed(2)+'%',
					r_seven_2 : bodyObj[i]["r_seven_2"],
					r_thirty_2 : bodyObj[i]["r_thirty_2"],
					r_thirty_m : bodyObj[i]["r_thirty_m"]
				}
				channel_dayreport[i] = item;
			}
		}
		// TODO : 增加全部渠道叠加数据
		callback(channel_dayreport);
	});
}

exports.getOneChannel = getOneChannel;
