/**
 * 监听路径：'/data'
 */

var noderice = require('noderice');
var channel_logic = require('./channel/channel_logic.js');
var event_logic = require('./event/event_logic.js');
var pay_logic = require('./pay/pay_logic.js');
var user_logic = require('./user/user_logic.js');

var express = require('express');
var router = express.Router();

router.get( '/channel/dayreport', function(req, res) {
	var day = noderice.GetDateNum(0);
	var key_day = day;
	if(req.query.day != undefined && req.query.day != null && req.query.day.length == 8) {
		day=req.query.day;
		key_day = day;
	}
	channel_logic.getChannelDayreport(day, function(channel_dayreport) {
		res.render('data/channel/dayreport', { key_day : key_day, channel_dayreport : channel_dayreport});
	});
});

router.get( '/channel/dayreport/onechannel/', function(req, res) {
	var channel_id = 'duomeng01';
	var key_channel_id = channel_id;
	if(req.query.channel_id != undefined && req.query.channel_id != null && req.query.channel_id.length > 0) {
		channel_id = req.query.channel_id;
		key_channel_id = channel_id;
	}
	channel_logic.getOneChannel(channel_id, function(channel_dayreport) {
		res.render('data/channel/onechannel', { key_channel_id : key_channel_id, channel_dayreport : channel_dayreport});
	});
});

router.get( '/channel/dayreport/onechanneluserinfo/', function(req, res) {
	var channel_id = 'duomeng01';
	var key_channel_id = channel_id;
	if(req.query.channel_id != undefined && req.query.channel_id != null && req.query.channel_id.length > 0) {
		channel_id = req.query.channel_id;
		key_channel_id = channel_id;
	}
	channel_logic.getOneChannel(channel_id, function(channel_dayreport) {
		res.render('data/channel/onechanneluserinfo', { key_channel_id : key_channel_id, channel_dayreport : channel_dayreport});
	});
});

router.get( '/pay/dayreport', function(req, res) {
	var day = noderice.GetDateNum(0);
	var key_day = day;
	if(req.query.day != undefined && req.query.day != null && req.query.day.length == 8) {
		day=req.query.day;
		key_day = day;
	}
	pay_logic.getPayDayreport(day, function(pay_dayreport) {
		res.render('data/pay/dayreport', { key_day : key_day, pay_dayreport : pay_dayreport});
	});
});

//--------------------------------------------------------------------------------

router.get( '/event/dayreport/fishinfo', function(req, res) {
	var day = noderice.GetDateNum(0);
	var key_day = day;
	var room_id = noderice.GetDateNum(1);
	if(req.query.day != undefined && req.query.day != null && req.query.day.length == 8) {
		day=req.query.day;
		key_day = day;
	}
	(function(key_day){
		event_logic.getFishinfo(day, room_id, function(fishinfo) {
			res.render('data/event/dayreport/fishinfo', { key_day : key_day, fishinfo : fishinfo});
		});
	})(key_day);
});

router.get( '/event/dayreport/bankrupt', function(req, res) {
	var day = noderice.GetDateNum(0);
	var key_day = day;
	if(req.query.day != undefined && req.query.day != null && req.query.day.length == 8) {
		day=req.query.day;
		key_day = day;
	}
	(function(key_day){
		event_logic.getBankrupt(day, function(bankruptinfo) {
			res.render('data/event/dayreport/bankrupt', { key_day : key_day, bankruptinfo : bankruptinfo});
		});
	})(key_day);
});

router.get( '/event/dayreport/mermaidask', function(req, res) {
	var day = noderice.GetDateNum(0);
	var key_day = day;
	if(req.query.day != undefined && req.query.day != null && req.query.day.length == 8) {
		day=req.query.day;
		key_day = day;
	}
	(function(key_day){
		event_logic.getMermaidtask(day, function(mermaidtaskinfo) {
			res.render('data/event/dayreport/mermaidtask', { key_day : key_day, mermaidtaskinfo : mermaidtaskinfo});
		});
	})(key_day);
});

router.get( '/event/dayreport/pagechange', function(req, res) {
	var day = noderice.GetDateNum(0);
	var key_day = day;
	if(req.query.day != undefined && req.query.day != null && req.query.day.length == 8) {
		day=req.query.day;
		key_day = day;
	}
	(function(key_day){
		event_logic.getPagechange(day, function(pagechangeinfo) {
			res.render('data/event/dayreport/pagechange', { key_day : key_day, pagechangeinfo : pagechangeinfo});
		});
	})(key_day);
});

router.get( '/event/dayreport/presented', function(req, res) {
	var day = noderice.GetDateNum(0);
	var key_day = day;
	if(req.query.day != undefined && req.query.day != null && req.query.day.length == 8) {
		day=req.query.day;
		key_day = day;
	}
	(function(key_day){
		event_logic.getPresented(day, function(presentedinfo) {
			res.render('data/event/dayreport/presented', { key_day : key_day, presentedinfo : presentedinfo});
		});
	})(key_day);
});

router.get( '/event/dayreport/skilluse', function(req, res) {
	var day = noderice.GetDateNum(0);
	var key_day = day;
	if(req.query.day != undefined && req.query.day != null && req.query.day.length == 8) {
		day=req.query.day;
		key_day = day;
	}
	(function(key_day){
		event_logic.getSkilluse(day, function(skilluseinfo) {
			res.render('data/event/dayreport/skilluse', { key_day : key_day, skilluseinfo : skilluseinfo});
		});
	})(key_day);
});

router.get( '/event/dayreport/turrentlevel', function(req, res) {
	var day = noderice.GetDateNum(0);
	var key_day = day;
	if(req.query.day != undefined && req.query.day != null && req.query.day.length == 8) {
		day=req.query.day;
		key_day = day;
	}
	(function(key_day){
		event_logic.getTurrentlevel(day, function(turrentlevelinfo) {
			res.render('data/event/dayreport/turrentlevel', { key_day : key_day, turrentlevelinfo : turrentlevelinfo});
		});
	})(key_day);
});

router.get( '/event/dayreport/turntable', function(req, res) {
	var day = noderice.GetDateNum(0);
	var key_day = day;
	if(req.query.day != undefined && req.query.day != null && req.query.day.length == 8) {
		day=req.query.day;
		key_day = day;
	}
	(function(key_day){
		event_logic.getTurntable(day, function(turntableInfo) {
			res.render('data/event/dayreport/turntable', { key_day : key_day, turntableInfo : turntableInfo});
		});
	})(key_day);
});

router.get( '/event/dayreport/expend', function(req, res) {
	var day = noderice.GetDateNum(0);
	var key_day = day;
	if(req.query.day != undefined && req.query.day != null && req.query.day.length == 8) {
		day=req.query.day;
		key_day = day;
	}
	(function(key_day){
		event_logic.getExpendinfo(day, function(expendInfo) {
			res.render('data/event/dayreport/expend', { key_day : key_day, expendInfo : expendInfo});
		});
	})(key_day);
});


router.get( '/event/dayreport/turrentlevelgroup', function(req, res) {
	var day = noderice.GetDateNum(0);
	var key_day = day;
	if(req.query.day != undefined && req.query.day != null && req.query.day.length == 8) {
		day=req.query.day;
		key_day = day;
	}
	(function(key_day){
		event_logic.getTurrentlevelgroup(day, function(turrentlevelgroupInfo) {
			res.render('data/event/dayreport/turrentlevelgroup', { key_day : key_day, turrentlevelgroupInfo : turrentlevelgroupInfo});
		});
	})(key_day);
});

router.get( '/event/dayreport/userlevelgroup', function(req, res) {
	var day = noderice.GetDateNum(0);
	var key_day = day;
	if(req.query.day != undefined && req.query.day != null && req.query.day.length == 8) {
		day=req.query.day;
		key_day = day;
	}
	(function(key_day){
		event_logic.getUserlevelgroup(day, function(userlevelgroupInfo) {
			res.render('data/event/dayreport/userlevelgroup', { key_day : key_day, userlevelgroupInfo : userlevelgroupInfo});
		});
	})(key_day);
});

router.get( '/userinfo/query', function(req, res) {
	var key_user_id = '201';
	var key_q_type = 'mo';
	if(req.query.user_id != undefined && req.query.user_id != null && req.query.user_id.length > 0 ) {
		user_id=req.query.user_id;
		key_user_id = user_id;
		key_q_type = req.query.q_type ;
		(function(key_user_id, key_q_type){
			user_logic.getUserInfo(key_user_id, key_q_type, function(userInfo) {
				if(key_q_type == 'mo') {
					res.render('data/user/query', { key_user_id : key_user_id, key_q_type : key_q_type, userMo : userInfo});
				}else if(key_q_type == 'mr') {
					res.render('data/user/query', { key_user_id : key_user_id, key_q_type : key_q_type, userMr : userInfo});
				} else if(key_q_type === 'pagechange'){
					res.render('data/user/query', { key_user_id : key_user_id, key_q_type : key_q_type, userPagechange : userInfo});
				} else if(key_q_type === 'gameinfo'){
					res.render('data/user/query', { key_user_id : key_user_id, key_q_type : key_q_type, gameinfo : userInfo});
				} else if(key_q_type === 'register'){
					res.render('data/user/query', { key_user_id : key_user_id, key_q_type : key_q_type, registerinfo : userInfo});
				}  else {
					res.render('data/user/query', { key_user_id : key_user_id, key_q_type : key_q_type, userMo : null});
				}

			});
		})(key_user_id, key_q_type);
	}else {
		res.render('data/user/query', { key_user_id : key_user_id, key_q_type : key_q_type, userMo : null});
	}

});


module.exports = router;
