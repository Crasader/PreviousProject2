/**
 * 获取角色信息[player/info/get]
 * 同步角色信息[player/info/sync]
 */

var player_logic = require('./player_logic.js');
var bag_logic = require('./bag_logic.js');
var session_manager = require('../../session_manager.js');
var agreement = require('../../agreement.js');
var redishelper = require('../../mem/redishelper.js');

var express = require('express');
var router = express.Router();

/**
 * 角色背包信息获取
 * 协议：player/info/bag/get/:session_id
 * 测试： 106.75.135.78:1701/player/info/bag/get/TBU_1458284974211
 */
router.get( '/info/bag/get/:session_id', function (req, res) {
    var session_id = req.params.session_id;
    getUserBgInfoBySessionId(session_id, res);
});

/**
 * 角色背包信息获取
 * 协议：player/info/bag/get/
 * 测试： 106.75.135.78:1701/player/info/bag/get/
 */
router.post( '/info/bag/get/', function (req, res) {
    var session_id = req.body.session_id;
    getUserBgInfoBySessionId(session_id, res);
});

function getUserBgInfoBySessionId(session_id, res) {
  session_manager.isLogin(session_id, function(login, data){
    if(!login) {
      res.end(data);
      return ;
    }
    // 获取用户背包信息
    redishelper.getVaule('BG_' + session_id, function(err, redis_result){
  		if(err) {
  			res.end(agreement.redisErrorDesc);
  			return ;
  		}
  		if(redis_result != undefined) {
  			res.end(redis_result);
  			return ;
  		}
  		res.end(agreement.invalidSessionIdDesc);
  	});
  });
}

/**
 * 角色信息获取
 * 协议：player/info/get/:session_id
 * 测试： 106.75.135.78:1701/player/info/get/TBU_1458087981384
 */
router.get( '/info/get/:session_id', function (req, res) {
    var session_id = req.params.session_id;
    getBaseUserInfoBySessionId(session_id, res);
});

/**
 * 角色信息获取
 * 协议：player/info/get
 * 测试： 106.75.135.78:1701/player/info/get[POST][参数：session_id]
 */
router.post( '/info/get/', function (req, res) {
    var session_id = req.body.session_id;
    getBaseUserInfoBySessionId(session_id, res);
});

function getBaseUserInfoBySessionId(session_id, res) {
  session_manager.isLogin(session_id, function(login, data){
    if(!login) {
      res.end(data);
      return ;
    }
    var result = {
      errorcode : 0,
      errormsg : '',
      user_info : {
        coins : data.coins === undefined ? 0 :data.coins,
        diamonds : data.diamonds === undefined ? 0 :data.diamonds,
        exps : data.exps === undefined ? 0 : data.exps,
        turrent_level : data.turrent_level === undefined ? 1 : data.turrent_level,
        mo : data.mo === undefined ? 0 : data.mo,
        mo_first : data.mo_first,
        mo_coins : data.mo_coins,
        chest_level : data.chest_level === undefined ? 0 : data.chest_level
      }
    };
    console.log(data.user_id + ': ' + JSON.stringify(result));
    res.end(JSON.stringify(result));
  });
}


/**
 * 角色信息同步-测试模块 TODO : 可以关闭
 * 协议：player/info/sync/fortuneInfo/base/:session_id/:coins/:diamonds/:exp/:turrent_level
 * 测试：106.75.135.78:1701/player/info/sync/fortuneInfo/add/TBU_1458087981384/200/20/200/10
 */
router.get( '/info/sync/fortuneInfo/add/:session_id/:coins/:diamonds/:exps/:turrent_level', function (req, res) {
  if(req.params.session_id === undefined || req.params.coins === undefined ||
			req.params.diamonds === undefined || req.params.exps === undefined ||
      req.params.turrent_level === undefined) {
		res.end(agreement.reqParamsErrorDesc);
		return ;
	}

  var req_info = {
    session_id : req.params.session_id,
    coins : req.params.coins,
    diamonds : req.params.diamonds,
    exps : req.params.exps,
    turrent_level : req.params.turrent_level
  }
  console.log('fortuneInfo base:'+JSON.stringify(req_info));

  (function(req_info){
    session_manager.isLogin(req.params.session_id, function(login, data){
  		if(!login) {
  			res.end(data);
  			return ;
  		}

      data.coins =  parseInt(data.coins) + parseInt(req_info.coins);
      data.diamonds = parseInt(data.diamonds) + parseInt(req_info.diamonds) ;
      data.exps = parseInt(data.exps) + parseInt(req_info.exps) ;
      data.turrent_level = parseInt(req_info.turrent_level) ;
      redishelper.setValueWithExpire(data.session_id, JSON.stringify(data), session_manager.SESSION_EXPIRE);

      var sync_info = {
        user_id : data.user_id,
        fortune_id : data.fortune_id,
        coins : data.coins,
        diamonds : data.diamonds,
        exps : data.exps,
        turrent_level : data.turrent_level
      };
      console.log('[/info/sync/fortuneInfo base]sync_info:'+ JSON.stringify(sync_info));
      player_logic.syncPlayerBaseFortuneInfo(sync_info);
      res.end(agreement.successDesc);
  	});
  })(req_info);
});

/**
 * 单机接口：角色信息同步
 * 协议：player/info/sync/fortuneInfo
 * 测试：
 */
router.post( '/info/sync/fortuneInfo', function (req, res) {
  if(req.body.session_id === undefined || req.body.coins === undefined ||
			req.body.diamonds === undefined || req.body.nobility_time === undefined ||
			req.body.exp === undefined || req.body.turrent_level === undefined ||
      req.body.mo === undefined ) {
		res.end(agreement.reqParamsErrorDesc);
		return ;
	}

  var req_info = {
    session_id : req.body.session_id,
    coins : req.body.coins,
    diamonds : req.body.diamonds,
    exp : req.body.exp,
    turrent_level : req.body.turrent_level,
    mo : req.body.mo,
    nobility_time : req.body.nobility_time
  }
  console.log('fortuneInfo:'+JSON.stringify(req_info));


  (function(req_info){
    session_manager.isLogin(req_info.session_id, function(login, data){
  		if(!login) {
  			res.end(data);
  			return ;
  		}
      var sync_info = {
        user_id : data.user_id,
        fortune_id : data.fortune_id,
        coins : req_info.coins,
        diamonds : req_info.diamonds,
        exp : req_info.exp,
        turrent_level : req_info.turrent_level,
        mo : req_info.mo,
        nobility_time : req_info.nobility_time
      };
      player_logic.syncPlayerFortuneInfo(sync_info);
      res.end(agreement.successDesc);
  	});
  })(req_info);
});

/**
 * 经验排行榜
 */
router.get( '/rank/exp', function (req, res) {
    res.end(player_logic.getExpStr());
});

/**
 * 金币排行榜
 */
router.get( '/rank/coin', function (req, res) {
    res.end( player_logic.getCoinStr() );
});

/**
 * 角色背包信息更新,使用或者赠送的时候调用 TODO : 可以关闭
 * 协议 : player/info/bag/sync/:session_id/:item_id/:nums
 * 测试 : 106.75.135.78:1701/player/info/bag/sync/TBU_1458284974211/1004/1
 */
router.get( '/info/bag/sync/:session_id/:item_id/:nums', function (req, res) {
    var session_id = req.params.session_id;
    var nums = parseInt(req.params.nums);
    var item_id = parseInt(req.params.item_id);
    console.log('/info/bag/sync/:session_id/:item_id/:nums, item_id = ' + item_id + ';nums = ' + nums);
    if( !isNaN(nums) && !isNaN(item_id)) {
      bag_logic.syncUserBagInfoBySessionId(session_id, item_id, nums, function(result){
          res.end(result);
      });
    }else {
      res.end(agreement.reqParamsErrorDesc);
    }
});

/**
 * 查询玩家背包信息
 * 协议 : player/info/bag/buy/
 * 测试 : 106.75.135.78:1701/player/info/bag/get/:session_id
 */
router.get( '/info/bag/get/:session_id', function (req, res) {
    var session_id = req.params.session_id;
    bag_logic.getBagInfoBySessionId(session_id, function(result){
      res.end(result);
    });
});

/**
 * 道具购买协议
 * 协议 : player/info/bag/buy/
 * 测试 : 106.75.135.78:1701/player/info/bag/buy
 */
router.post( '/info/bag/buy/', function (req, res) {
    var session_id = req.body.session_id;
    var item_id = parseInt(req.body.item_id);
    if ( !isNaN(item_id) ) {
      bag_logic.buyItemBySessionId(session_id, item_id, function(result){
        res.end(result);
      });
    }else {
      res.end(agreement.reqParamsErrorDesc);
    }
});

module.exports = router;
