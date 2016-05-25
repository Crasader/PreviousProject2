

var dbmanager = require('../../db/dbmanager.js');
var player_db = require('./player_db.js');
var schedule = require('node-schedule');
var user_logic = require('../user/user_logic.js');
var redishelper = require('../../mem/redishelper.js');
var session_manager = require('../../session_manager.js');

var coinStr;
var expStr;

function initTask() {
	var rule = new schedule.RecurrenceRule();
	var times = [];
	times.push(5);
	rule.minute = times;
　　 schedule.scheduleJob(rule, function(){
		configRank();
	});
}

function syncPlayerFortuneInfo(sync_info) {
  player_db.syncPlayerFortuneInfo(dbmanager.getClient(), sync_info, function(result) {
    if(!result) {
      console.log('fail sync player fortune info');
    }
  });
}

function syncPlayerBaseFortuneInfo(sync_info) {
  player_db.syncPlayerBaseFortuneInfo(dbmanager.getClient(), sync_info, function(result) {
    if(!result) {
      console.log('fail sync player base fortune info');
    }
  });
}

exports.syncPlayerBaseFortuneInfo = syncPlayerBaseFortuneInfo;

function syncPlayerCoinsAndDiamonds(session_id, sync_info) {
	redishelper.getVaule(session_id, function(err, redis_result){
		if(err) {
			return ;
		}
		if(redis_result != undefined) {
			var resultObj = JSON.parse(redis_result);
			resultObj.coins += sync_info.coins;
			resultObj.diamonds += sync_info.diamonds;
			redishelper.setValueWithExpire(resultObj.session_id, JSON.stringify(resultObj), session_manager.SESSION_EXPIRE);
			return ;
		}
	});
	player_db.addPlayerCoinsAndDiamonds(dbmanager.getClient(), sync_info, function(result) {
		if(!result) {
			console.log('fail add player coins and diamonds fortune info[0]');
		}
	});
}

exports.syncPlayerCoinsAndDiamonds = syncPlayerCoinsAndDiamonds;

function addPlayerCoinsAndDiamondsWithoutRedis(sync_info) {
	console.log('[addPlayerCoinsAndDiamondsWithoutRedis] : ' + JSON.stringify(sync_info));
	player_db.addPlayerCoinsAndDiamonds(dbmanager.getClient(), sync_info, function(result) {
    if(!result) {
      console.log('fail add player coins and diamonds fortune info[1]');
    }
  });
}

exports.addPlayerCoinsAndDiamondsWithoutRedis = addPlayerCoinsAndDiamondsWithoutRedis;


/**
 * 查询玩家的信息
 */
function getPlayerInfo(user_id, table_id, callback) {
	player_db.getPlayerInfo(dbmanager.getClientS(), user_id, table_id, function(success, result) {
    if(!success) {
      console.log('fail getPlayerInfo fortune info');
			callback(false, result);
			return ;
    }

		callback(true, result);
  });
};


var expObj = {
  ranklist : [],
  rankrule : []
};
var coinObj = {
  ranklist : [],
  rankrule : []
};

function init() {
  initTask();
  // 排名算法 [coinrank  100-1000     1000-10000   10000 -30000]
  var rulecoin1 = {
  	coin_start : 0,
  	coin_end : 10000,
  	rank_start : 10000,
  	rank_end : 30000
  };
  coinObj.rankrule[0] = rulecoin1;
  var rulecoin2 = {
  	coin_start : 10000,
  	coin_end : 1000000,
  	rank_start : 1000,
  	rank_end : 10000
  };
  coinObj.rankrule[1] = rulecoin2;
  var rulecoin3 = {
  	coin_start : 1000000,
  	coin_end : 10000000,
  	rank_start : 30,
  	rank_end : 1000
  };
  coinObj.rankrule[2] = rulecoin3;

  // 排名算法
  var rulecoin1 = {
  	coin_start : 0,
  	coin_end : 10000,
  	rank_start : 10000,
  	rank_end : 30000
  };
  expObj.rankrule[0] = rulecoin1;
  var rulecoin2 = {
  	coin_start : 10000,
  	coin_end : 1000000,
  	rank_start : 1000,
  	rank_end : 10000
  };
  expObj.rankrule[1] = rulecoin2;
  var rulecoin3 = {
  	coin_start : 1000000,
  	coin_end : 10000000,
  	rank_start : 30,
  	rank_end : 1000
  };
  expObj.rankrule[2] = rulecoin3;
}

function configRank() {
  ConfigCoin();
  ConfigExp();
}

function ConfigCoin() {

  player_db.getCoinRank(dbmanager.getClientS(), function(success, results){
    if(success && results.length > 0) {
      for(var i=0;i<results.length;i++) {
        var player = {
        	name : isNaN(results[i]['user_name']) ? results[i]['user_name'] : user_logic.GUEST_USER_NAME_HEAD + results[i]['user_name'],
          gender : results[i]['gender'],
        	vip : results[i]['vip'],
        	exp : results[i]['exp'],
        	coins : results[i]['coins']
        };
        coinObj.ranklist[i] = player;
      }
    } else {
			console.log('fail config rank coins');
		}
    coinStr = JSON.stringify(coinObj);
  });
}

function ConfigExp() {

  player_db.getExpRank(dbmanager.getClientS(), function(success, results){
    if(success && results.length > 0) {
      for(var i=0;i<results.length;i++) {
        var player = {
        	name : isNaN(results[i]['user_name']) ? results[i]['user_name'] : user_logic.GUEST_USER_NAME_HEAD + results[i]['user_name'],
          gender : results[i]['gender'],
        	vip : results[i]['vip'],
        	exp : results[i]['exp'],
        	coins : results[i]['coins']
        };
        expObj.ranklist[i] = player;
      }
    }else {
			console.log('fail config rank exps');
		}
    expStr = JSON.stringify(expObj);
  });
}

/**
 * 获取金币排名信息
 */
function getCoinStr() {
  return coinStr;
}

/**
 * 获取经验排名信息
 */
function getExpStr() {
  return expStr;
}

init();

exports.configRank = configRank;
exports.getCoinStr = getCoinStr;
exports.getExpStr = getExpStr;
exports.syncPlayerFortuneInfo = syncPlayerFortuneInfo;
exports.getPlayerInfo = getPlayerInfo;

function getUserBgInfo(user_id, callback) {
	player_db.getUserBgInfo(dbmanager.getClientS(), user_id, function(success, result) {
    if(!success) {
      console.log('fail getPlayerInfo fortune info');
			callback(false, result);
			return ;
    }

		callback(true, result);
  });
}

exports.getUserBgInfo = getUserBgInfo;
