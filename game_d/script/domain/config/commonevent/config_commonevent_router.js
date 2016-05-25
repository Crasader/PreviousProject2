/**
 * 监听路径：'/map'
 */

var dashboard_data = require('../../../data/dashboard/dashboard_data.js');

var express = require('express');
var router = express.Router();

router.get( '/', function(req, res) {
	dashboard_data.getCommonevent(function (success, body) {
		if(success) {
			var bodyObj = JSON.parse(body);
			var commonevents = [];
			// {"id":1,"event_id":1,"event_desc":0,"user_desc":"点击昵称设置的玩家数和次数"}
			for(var i=0; i<bodyObj.length;i++) {
				commonevent = {
					id : i+1,
					event_id : bodyObj[i]["event_id"],
					event_desc : bodyObj[i]["event_desc"],
					user_desc : bodyObj[i]["user_desc"]
				}
				commonevents[i] = commonevent;
			}
			res.render('config/commonevent/commonevent', { commonevents : commonevents});
		}else {
			res.render('config/commonevent/commonevent');
		}
	});

});

module.exports = router;
