/**
 * 监听路径：'/map'
 */

var dashboard_data = require('../../../data/dashboard/dashboard_data.js');

function getPayDayreport(day, callback) {
	dashboard_data.getPayDayreport(day, function (success, body) {
		var pay_dayreport = [];
		if(success ) {
			var bodyObj = JSON.parse(body);
			var j = 0;
			var moReqTimesAll = 0;
			for(i=0; i<bodyObj.length;i++) {
				moReqTimesAll = moReqTimesAll + parseInt(bodyObj[i]["mo_req_nums"]);
			}
			for(i=0; i<bodyObj.length;i++) {
				// TODO : mo请求次数占比
				item = {
					id : i+1,
					day : bodyObj[i]["day"],
					pay_point_id : bodyObj[i]["pay_point_id"],
					pay_event_id : bodyObj[i]["pay_event_id"],
					mo_req_nums : bodyObj[i]["mo_req_nums"],
					mo_req_per : (parseFloat(bodyObj[i]["mo_req_nums"])*100/moReqTimesAll).toFixed(2)+'%',
					mo_req_moneys : bodyObj[i]["mo_req_moneys"],
					mo_req_users : bodyObj[i]["mo_req_users"],
					mo_success_nums : bodyObj[i]["mo_success_nums"],
					mo_success_moneys : bodyObj[i]["mo_success_moneys"],
					mo_success_users : bodyObj[i]["mo_success_users"],
					mr_nums : bodyObj[i]["mr_nums"],
					mr_moneys : bodyObj[i]["mr_moneys"],
					mr_users : bodyObj[i]["mr_users"]
				}
				pay_dayreport[i] = item;
			}
		}
		callback(pay_dayreport);
	});
}

exports.getPayDayreport = getPayDayreport;
