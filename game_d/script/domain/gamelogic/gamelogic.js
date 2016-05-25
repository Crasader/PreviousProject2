
function getPropNameById(prop_id) {
	if(prop_id === 1001) {
		return '金币';
	} else if(prop_id === 1002) {
		return '钻石';
	} else if(prop_id === 1003) {
		return '冰冻';
	} else if(prop_id === 1004) {
		return '锁定';
	} else if(prop_id === 1005) {
		return '召唤';
	} else if(prop_id === 1006) {
		return '核弹';
	} else if(prop_id === 1007) {
		return '激光';
	} else if(prop_id === 1008) {
		return '金币宝箱';
	} else if(prop_id === 1009) {
		return '青铜宝箱';
	} else if(prop_id === 1010) {
		return '白银宝箱';
	} else if(prop_id === 1011) {
		return '黄金宝箱';
	} else if(prop_id === 1012) {
		return '升级礼包';
	} else if(prop_id === 1013) {
		return '勋章';
	}

	return '编号:'+prop_id;
}

exports.getPropNameById = getPropNameById;


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

exports.getSkillNameById = getSkillNameById;

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

exports.getPageName = getPageName;
