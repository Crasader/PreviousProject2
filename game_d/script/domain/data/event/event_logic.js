/**
 * 监听路径：'/map'
 */

var dashboard_data = require('../../../data/dashboard/dashboard_data.js');
var gamelogic = require('../../gamelogic/gamelogic.js');

function getFishinfo(day, room_id, callback) {
	dashboard_data.getEventUserInfo('fishinfo', day, function (success, body) {
		var fish_infos = [];
		if(success ) {
			var bodyObj = JSON.parse(body);
			var i = 0;
			for(i=0; i<bodyObj.length;i++) {
				item = {
					id : i+1,
					day : bodyObj[i]["day"],
					room_id : bodyObj[i]["room_id"],
					fish_id : bodyObj[i]["fish_id"],
					create_times : bodyObj[i]["create_times"],
					hit_times : bodyObj[i]["hit_times"],
					hit_moneys : bodyObj[i]["hit_moneys"],
					catch_times : bodyObj[i]["catch_times"],
					catch_times_user : bodyObj[i]["catch_times_user"]
				}
				if (room_id == 0 || room_id != 0 && room_id == bodyObj[i]["room_id"]) {
					fish_infos[i] = item;
				};				
			}
		}
		callback(fish_infos);
	});
}

exports.getFishinfo = getFishinfo;

function getBankrupt(day, callback) {
	dashboard_data.getEventUserInfo('bankrupt', day, function (success, body) {
		var infos = [];
		if(success ) {
			var bodyObj = JSON.parse(body);
			var i = 0;
			for(i=0; i<bodyObj.length;i++) {
				item = {
					id : i+1,
					day : bodyObj[i]["day"],
					seq_id : bodyObj[i]["seq_id"],
					nums : bodyObj[i]["nums"],
					get_nums : bodyObj[i]["get_nums"],
					per : parseInt(bodyObj[i]["nums"]) == 0 ? '0%' :
					 	(parseFloat(bodyObj[i]["get_nums"])*100/parseFloat(bodyObj[i]["nums"])).toFixed(2) + '%',
					new_user : bodyObj[i]["new_nums"],
					new_user_per : parseInt(bodyObj[i]["new_nums"]) == 0 ? '0%' :
					 	(parseFloat(bodyObj[i]["new_nums"])*100/parseFloat(bodyObj[i]["nums"])).toFixed(2) + '%',
					new_get_nums : bodyObj[i]["new_get_nums"],
					new_get_nums_per : parseInt(bodyObj[i]["new_get_nums"]) == 0 ? '0%' :
					 	(parseFloat(bodyObj[i]["new_get_nums"])*100/parseFloat(bodyObj[i]["get_nums"])).toFixed(2) + '%'
				}
				infos[i] = item;
			}
		}
		callback(infos);
	});
}

exports.getBankrupt = getBankrupt;

function getMermaidtask(day, callback) {
	dashboard_data.getEventUserInfo('mermaidask', day, function (success, body) {
		var infos = [];
		if(success ) {
			var bodyObj = JSON.parse(body);
			var i = 0;
			for(i=0; i<bodyObj.length;i++) {
				item = {
					id : i+1,
					day : bodyObj[i]["day"],
					nums : bodyObj[i]["nums"],
					user_nums : bodyObj[i]["user_nums"],
					success_nums : bodyObj[i]["success_nums"],
					success_user_nums : bodyObj[i]["success_user_nums"],
					success_user_times : bodyObj[i]["success_user_times"],
					success_rewards : bodyObj[i]["success_rewards"]
				}
				infos[i] = item;
			}
		}
		callback(infos);
	});
}

exports.getMermaidtask = getMermaidtask;

function getPagechange(day, callback) {
	dashboard_data.getEventUserInfo('pagechange', day, function (success, body) {
		var infos = [];
		if(success ) {
			var bodyObj = JSON.parse(body);
			var i = 0;
			for(i=0; i<bodyObj.length;i++) {
				item = {
					id : i+1,
					day : bodyObj[i]["day"],
					to_page : isNaN(bodyObj[i]["to_page"]) ? bodyObj[i]["to_page"] : getPageName(parseInt(bodyObj[i]["to_page"])),
					from_page : isNaN(bodyObj[i]["from_page"]) ? bodyObj[i]["from_page"] : getPageName(parseInt(bodyObj[i]["from_page"])),
					nums : bodyObj[i]["nums"],
					user_nums : bodyObj[i]["user_nums"]
				}
				infos[i] = item;
			}
		}
		callback(infos);
	});
}

function getPageName(pageId) {
	if(pageId === 0) {
		return '加载';
	}else if(pageId === 1) {
		return '大厅';
	}else if(pageId === 2) {
		return '游戏';
	}else if(pageId === 3) {
		return '背包';
	}else if(pageId === 4) {
		return '奖品';
	}else if(pageId === 5) {
		return '排行';
	}else if(pageId === 6) {
		return '客服';
	}else if(pageId === 7) {
		return 'VIP';
	}else if(pageId === 8) {
		return '贵族';
	}else if(pageId === 9) {
		return '首充';
	}else if(pageId === 10) {
		return '抽奖';
	}else if(pageId === 11) {
		return '昵称';
	}else if(pageId === 12) {
		return '金币充值';
	}else if(pageId === 13) {
		return '钻石充值';
	}
		return '页面:' + pageId;
}

exports.getPagechange = getPagechange;

function getPresented(day, callback) {
	dashboard_data.getEventUserInfo('presented', day, function (success, body) {
		var infos = [];
		if(success ) {
			var bodyObj = JSON.parse(body);
			var i = 0;
			for(i=0; i<bodyObj.length;i++) {
				item = {
					id : i+1,
					day : bodyObj[i]["day"],
					prop_id : gamelogic.getPropNameById(bodyObj[i]["prop_id"]),
					nums : bodyObj[i]["nums"],
					user_nums : bodyObj[i]["user_nums"],
					user_nums_per : parseInt(bodyObj[i]["user_nums"]) == 0 ? 0 : (parseFloat(bodyObj[i]["nums"])/parseInt(bodyObj[i]["user_nums"])).toFixed(2)
				}
				infos[i] = item;
			}
		}
		callback(infos);
	});
}

exports.getPresented = getPresented;

function getSkilluse(day, callback) {
	dashboard_data.getEventUserInfo('skilluse', day, function (success, body) {
		var infos = [];
		if(success ) {
			var bodyObj = JSON.parse(body);
			var i = 0;
			for(i=0; i<bodyObj.length;i++) {
				item = {
					id : i+1,
					day : bodyObj[i]["day"],
					skill_id : isNaN(bodyObj[i]["skill_id"]) ? bodyObj[i]["skill_id"] : getSkillNameById(parseInt(bodyObj[i]["skill_id"])),
					use_nums : bodyObj[i]["use_nums"],
					use_users : bodyObj[i]["use_users"],
					use_coin_nums : bodyObj[i]["use_coin_nums"],
					use_coin_users : bodyObj[i]["use_coin_users"],
					use_diamond_nums : bodyObj[i]["use_diamond_nums"],
					use_diamond_users : bodyObj[i]["use_diamond_users"],
					use_payreq_nums : bodyObj[i]["use_payreq_nums"],
					use_payreq_users : bodyObj[i]["use_payreq_users"]
				}
				infos[i] = item;
			}
		}
		callback(infos);
	});
}

function getSkillNameById(skillId) {
	if(skillId === 1) {
		return '冰冻';
	} else if(skillId === 2) {
		return '锁定';
	} else if(skillId === 3) {
		return '召唤';
	} else if(skillId === 4) {
		return '核弹';
	} else if(skillId === 5) {
		return '激光炮';
	}

	return '编号:'+skillId;
}

exports.getSkilluse = getSkilluse;

function getTurrentlevel(day, callback) {
	dashboard_data.getEventUserInfo('turrentlevel', day, function (success, body) {
		var infos = [];
		if(success ) {
			var bodyObj = JSON.parse(body);
			var j = 0;
			for(i=0; i<bodyObj.length;i++) {
				item = {
					id : i+1,
					day : bodyObj[i]["day"],
					turrent_level : bodyObj[i]["turrent_level"],
					user_nums : bodyObj[i]["user_nums"],
					avg_update_times : bodyObj[i]["avg_update_times"],
					avg_update_times_mins : (parseFloat(bodyObj[i]["avg_update_times"])/60).toFixed(2),
					current_level_update_times : i <= 0 ? (parseFloat(bodyObj[i]["avg_update_times"])/60).toFixed(2) :
							( ( parseFloat(bodyObj[i]["avg_update_times"]) - parseFloat(bodyObj[i-1]["avg_update_times"]) ) /60).toFixed(2)
				}
				infos[j] = item;
				j++;
				if(j%10===0) {
					var itemTitle = {
						id : '序号',
						day : '日期',
						turrent_level : '炮台等级',
						user_nums : '升级用户数',
						avg_update_times : '平均升级用时/秒',
						avg_update_times_mins : '平均升级用时/分钟',
						current_level_update_times : '单级平均升级用时/分钟'
					};
					infos[j] = itemTitle;
					j++;
				}
			}
		}
		callback(infos);
	});
}

exports.getTurrentlevel = getTurrentlevel;

function getTurntable(day, callback) {
	dashboard_data.getEventUserInfo('turntable', day, function (success, body) {
		var infos = [];
		if(success ) {
			var bodyObj = JSON.parse(body);
			var i = 0;
			for(i=0; i<bodyObj.length;i++) {
				item = {
					id : i+1,
					day : bodyObj[i]["day"],
					t_type : getTurnTableTypeDesc(parseInt(bodyObj[i]["t_type"])),
					statistics_type : parseInt(bodyObj[i]["t_type"]) == 11 ? "新增用户抽奖" : "活跃用户抽奖",
					times : bodyObj[i]["times"],
					user_times : bodyObj[i]["user_times"],
					p_type_1_counts : bodyObj[i]["p_type_1_counts"],
					p_type_2_counts : bodyObj[i]["p_type_2_counts"],
					p_type_3_counts : bodyObj[i]["p_type_3_counts"],
					p_type_4_counts : bodyObj[i]["p_type_4_counts"],
					p_type_5_counts : bodyObj[i]["p_type_5_counts"],
					p_type_6_counts : bodyObj[i]["p_type_6_counts"]
				}
				infos[i] = item;
			}
		}
		callback(infos);
	});
}

function getTurnTableTypeDesc(t_type) {
	if(t_type === 1) {
		return '[0, 19999]';
	}else if(t_type === 2) {
		return '[2W, 99999]';
	}if(t_type === 3) {
		return '[10W, 199999]';
	}if(t_type === 4) {
		return '[20w, 399999]';
	}if(t_type === 5) {
		return '[40w, 1199999]';
	}if(t_type === 6) {
		return '[120W+]';
	}
	return '[' + t_type + ']';
}

exports.getTurntable = getTurntable;

function getExpendinfo(day, callback) {
	dashboard_data.getEventUserInfo('expend', day, function (success, body) {
		var infos = [];
		if(success ) {
			var bodyObj = JSON.parse(body);
			var i = 0;
			for(i=0; i<bodyObj.length;i++) {
				item = { // TODO : 增加人均计算显示
					id : i+1,
					day : bodyObj[i]["day"],
					coin_get_user : bodyObj[i]["coin_get_user"],
					coin_gets : bodyObj[i]["coin_gets"],
					coin_get_per : parseInt(bodyObj[i]["coin_get_user"]) == 0 ? 0 : (parseFloat(bodyObj[i]["coin_gets"])/parseFloat(bodyObj[i]["coin_get_user"])).toFixed(2),
					coin_use_user : bodyObj[i]["coin_use_user"],
					coin_uses : bodyObj[i]["coin_uses"],
					coin_user_per : parseInt(bodyObj[i]["coin_use_user"]) == 0 ? 0 : (parseFloat(bodyObj[i]["coin_uses"])/parseFloat(bodyObj[i]["coin_use_user"])).toFixed(2),
					diamond_get_user : bodyObj[i]["diamond_get_user"],
					diamond_gets : bodyObj[i]["diamond_gets"],
					diamond_get_per : parseInt(bodyObj[i]["diamond_get_user"]) == 0 ? 0 : (parseFloat(bodyObj[i]["diamond_gets"])/parseFloat(bodyObj[i]["diamond_get_user"])).toFixed(2),
					diamond_use_user : bodyObj[i]["diamond_use_user"],
					diamond_uses : bodyObj[i]["diamond_uses"],
					diamond_use_per : parseInt(bodyObj[i]["diamond_use_user"]) == 0 ? 0 : (parseFloat(bodyObj[i]["diamond_uses"])/parseFloat(bodyObj[i]["diamond_use_user"])).toFixed(2)
				}
				infos[i] = item;
			}
		}
		callback(infos);
	});
}

exports.getExpendinfo = getExpendinfo;

function getTurrentlevelgroup(day, callback) {
	dashboard_data.getEventUserInfo('turrentlevelgroup', day, function (success, body) {
		var infos = [];
		if(success ) {
			var bodyObj = JSON.parse(body);
			var i = 0;
			var allActivieUser = 0;
			var allNewUsers = 0;
			for(i=0; i<bodyObj.length;i++) {
				allActivieUser = allActivieUser + parseInt(bodyObj[i]["active_user"]);
				allNewUsers = allNewUsers + parseInt(bodyObj[i]["new_user"]);
			}
			var levelActivieUsers = 0;
			var levelNewUsers = 0;
			for(i=0; i<bodyObj.length;i++) {
				levelActivieUsers = levelActivieUsers + parseInt(bodyObj[i]["active_user"]);
				levelNewUsers = levelNewUsers + parseInt(bodyObj[i]["new_user"]);

				var active_user_per = (parseFloat(bodyObj[i]["active_user"])*100/allActivieUser);
				var new_user_per = parseFloat(bodyObj[i]["new_user"])*100/allNewUsers;
				item = {
					id : i+1,
					day : bodyObj[i]["day"],
					turrent_level : bodyObj[i]["turrent_level"],
					active_user : bodyObj[i]["active_user"],
					active_user_per : active_user_per.toFixed(4) + '%',
					active_user_all_per : levelActivieUsers == 0 ? 0 : (parseFloat(levelActivieUsers)*100/allActivieUser).toFixed(2) + '%',
					new_user : bodyObj[i]["new_user"],
					new_user_per : new_user_per.toFixed(4) + '%',
					new_user_all_per : levelNewUsers == 0 ? 0 : (parseFloat(levelNewUsers)*100/allNewUsers).toFixed(2) + '%'
				}
				infos[i] = item;
			}
		}
		callback(infos);
	});
}

exports.getTurrentlevelgroup = getTurrentlevelgroup;

function getUserlevelgroup(day, callback) {
	dashboard_data.getEventUserInfo('exp/distribution', day, function (success, body) {
		var infos = [];
		if(success ) {
			var bodyObj = JSON.parse(body);
			var allNewUsers = 0;
			for(i=0; i<bodyObj.length;i++) {
				allNewUsers = allNewUsers + parseInt(bodyObj[i]["new_nums"]);
			}
			var i = 0;
			var levelNewUsers = 0;
			for(i=0; i<bodyObj.length;i++) {
				var new_user_per = parseFloat(bodyObj[i]["new_nums"])*100/allNewUsers;
				levelNewUsers = levelNewUsers + parseInt(bodyObj[i]["new_nums"]);
				item = {
					id : i+1,
					day : bodyObj[i]["day"],
					exp_level : bodyObj[i]["exp_level"],
					active_user : bodyObj[i]["nums"],
					new_user : bodyObj[i]["new_nums"],
					new_user_per : new_user_per.toFixed(2) + '%',
					new_user_all_per : levelNewUsers == 0 ? 0 : (parseFloat(levelNewUsers)*100/allNewUsers).toFixed(2) + '%' 
				}
				infos[i] = item;
			}
		}
		callback(infos);
	});
}

exports.getUserlevelgroup = getUserlevelgroup;