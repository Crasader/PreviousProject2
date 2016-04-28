/**
 * 监听路径：'/map'
 */

var dashboard_data = require('../../../data/dashboard/dashboard_data.js');

var express = require('express');
var router = express.Router();

router.get( '/paypoint', function(req, res) {
	dashboard_data.getPaypoint(function (success, body) {
		if(success) {
			var bodyObj = JSON.parse(body);
			var paypoints = [];
			// {"id":1,"pay_point_version":100,"pay_point_id":1,"price":800,"pay_point_desc":"8元4万金币","create_time":"2015-01-19"}
			for(var i=0; i<bodyObj.length;i++) {
				paypoint = {
					id : i+1,
					pay_point_version : bodyObj[i]["pay_point_version"],
					pay_point_id : bodyObj[i]["pay_point_id"],
					price : bodyObj[i]["price"],
					pay_point_desc : bodyObj[i]["pay_point_desc"],
					create_time : bodyObj[i]["create_time"]
				}
				paypoints[i] = paypoint;
			}

			res.render('config/mo/paypoint', { paypoints : paypoints});
		}else {
			res.render('config/mo/paypoint');
		}
	});

});

router.get( '/payevent', function(req, res) {
	dashboard_data.getPayevent(function (success, body) {
		if(success) {
			var bodyObj = JSON.parse(body);
			var payevents = [];
			for(var i=0; i<bodyObj.length;i++) {
				payevent = {
					id : i+1,
					pay_event_version : bodyObj[i]["pay_event_version"],
					event_id : bodyObj[i]["event_id"],
					event_desc : bodyObj[i]["event_desc"],
					create_time : bodyObj[i]["create_time"]
				}
				payevents[i] = payevent;
			}

			res.render('config/mo/payevent', {payevents : payevents});
		}else {
			res.render('config/mo/payevent');
		}
	});

});

module.exports = router;
