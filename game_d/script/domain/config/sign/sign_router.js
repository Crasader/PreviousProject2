/**
 * 监听路径：'/map'
 */

var dashboard_data = require('../../../data/dashboard/dashboard_data.js');

var express = require('express');
var router = express.Router();

router.get( '/current', function(req, res) {
	dashboard_data.getSignCurrentConfig(function (success, body) {
		if(success) {
			var bodyObj = JSON.parse(body);
			var sign_info = [];
			for(var i=0; i<bodyObj["item_lists"].length;i++) {
				item = {
					id : i+1,
					item_id : bodyObj["item_lists"][i]['item_id'],
					num : bodyObj["item_lists"][i]['num'],
					probability : bodyObj["item_lists"][i]['probability']
					// content : JSON.stringify( bodyObj["item_lists"][i] )
				}
				sign_info[i] = item;
			}

			var version = '当前版本' + bodyObj["version"];
			res.render('config/sign/current', {version : version, sign_info : sign_info});
		}else {
			res.render('config/sign/current');
		}
	});

});

router.get( '/update', function(req, res) {
	if(req.query.new_config != undefined && req.query.new_config.length > 0) {
		console.log('req.query.new_config :' + req.query.new_config);
		dashboard_data.updateSignConfig(req.query.new_config, function (success, body) {
			res.redirect('current');
		});
	}else {
		res.render('config/sign/update');
	}

});



module.exports = router;
