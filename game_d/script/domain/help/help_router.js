/**
 * 监听路径：'/data'
 */

var express = require('express');
var router = express.Router();

var dashboard_data = require('../../data/dashboard/dashboard_data.js');

router.get( '/feedback/lastinfo', function(req, res) {
	dashboard_data.getLastFeedback(function(success, body) {
		var lastinfos = [];
		if(success) {
			var bodyObj = JSON.parse(body);
			var i = 0;
			for(i=0; i<bodyObj.length;i++) {
				item = {
					id : i+1,
					create_time : bodyObj[i]["create_time"],
					user_id : bodyObj[i]["user_id"],
					info : bodyObj[i]["feedback_info"]
				}
				lastinfos[i] = item;
			}
		}
		res.render('help/feedback/lastinfo', { lastinfos : lastinfos});
	});

});



module.exports = router;
