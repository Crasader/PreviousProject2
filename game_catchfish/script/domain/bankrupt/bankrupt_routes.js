/**
 * 破产逻辑
 */

var express = require('express');
var router = express.Router();

var noderice = require('noderice');
var session_manager = require('../../session_manager.js');
var redishelper = require('../../mem/redishelper.js');
var statistics_gametask_logic = require('../statistics/statistics_gametask_logic.js');
var player_logic = require('../player/player_logic.js');

var MAX_BROKE_NUM = 3;

/**
 * 破产
 * bankrupt/broke
 * 测试：
 */
router.post( '/broke', function (req, res) {
  var session_id = req.body.session_id;
  var room_id = req.body.room_id;
  broke(session_id, room_id, res);
});

/**
 * 破产
 * bankrupt/broke
 * 测试：
 */
router.get( '/broke/:session_id/:room_id', function (req, res) {
  var session_id = req.params.session_id;
  var room_id = req.params.room_id;
  broke(session_id, room_id, res);
});

function broke(session_id, room_id, res) {
  session_manager.isLogin(session_id, function(login, data){
    if(!login) {
      res.end(data);
      return ;
    }
    var r_key = noderice.GetDateNum(0) + '_' + data.user_id;
    var user_id = data.user_id;

    (function(r_key, room_id, user_id){
      redishelper.getVaule(r_key, function(err, redis_result){
    		if(err) {
          var err_to_c = {
            errorcode : 500,
            errormsg : 'read redis error'
          }
    			res.end(JSON.stringify(err_to_c));
    			return ;
    		}
        if(redis_result === undefined || redis_result === null) { // 今日还没有领取过
          var key_info = {
            broke_num : 1,
            rebirth_num : 0
          };
          redishelper.setValueWithExpire(r_key, JSON.stringify(key_info), getCurrentDayLeftSeconds());
          var test = {
            errorcode : 0,
            errormsg : '',
            times : 1,      // 第几次破产
            coins : 1000, // 如果领取的金额
            wait_time : 0,  // 破产等待时间 : 秒
            left_times : 3  // 剩余可领取次数(包括本次)
          };
          var mark_data = {
            type : 2, // 1领取，2，破产
            nums : 1,
            room_id : room_id
          };
          statistics_gametask_logic.insertOneBankruptData(user_id,  mark_data, function(result){
          });
          res.end(JSON.stringify(test));
          return ;
        }
        console.log(r_key + '; result  : ' + redis_result);
        var bankruptObj = JSON.parse(redis_result);
        if(bankruptObj.broke_num < MAX_BROKE_NUM) {
          bankruptObj.broke_num = bankruptObj.broke_num + 1;
          var test = {
            errorcode : 0,
            times : bankruptObj.broke_num,      // 第几次破产
            coins : (bankruptObj.rebirth_num + 1)*1000, // 如果领取的金额
            wait_time : 0,  // 破产等待时间 : 秒
            left_times : MAX_BROKE_NUM + 1 - bankruptObj.broke_num  // 剩余可领取次数(包括本次)
          };
          var mark_data = {
            type : 2, // 1领取，2，破产
            nums : bankruptObj.broke_num,
            room_id : room_id
          };
          statistics_gametask_logic.insertOneBankruptData(user_id,  mark_data, function(result){
          });
          redishelper.setValueWithExpire(r_key, JSON.stringify(bankruptObj), getCurrentDayLeftSeconds());
          res.end(JSON.stringify(test));
          console.log('broke [bankruptObj]: ' + JSON.stringify(bankruptObj));
          console.log('broke [client]: ' + JSON.stringify(test));
          return ;
        }else {
          var test = {
            errorcode : 0,
            times : 100,      // 第几次破产
            wait_time : 0,  // 破产等待时间 : 秒
            left_times : 0  // 剩余可领取次数(包括本次)
          };
          res.end(JSON.stringify(test));
          console.log('broke [client]: ' + JSON.stringify(test));
        }
      });
    })(r_key, room_id, user_id);
  });
}

/**
 * 领取
 * bankrupt/rebirth
 * 测试：
 */
router.post( '/rebirth', function (req, res) {
  var session_id = req.body.session_id;
  var room_id = req.body.room_id;
  rebirth(session_id, room_id, res);
});

/**
 * 领取
 * bankrupt/rebirth
 * 测试：
 */
router.get( '/rebirth/:session_id/:room_id', function (req, res) {
  var session_id = req.params.session_id;
  var room_id = req.params.room_id;
  rebirth(session_id, room_id, res);
});

function rebirth(session_id, room_id, res) {
  session_manager.isLogin(session_id, function(login, data){
    if(!login) {
      res.end(data);
      return ;
    }
    var r_key = noderice.GetDateNum(0) + '_' + data.user_id;
    var user_id = data.user_id;
    var fortune_id = data.fortune_id;
    console.log('[rebirth_fortune_id] : ' + fortune_id);
    (function(r_key, room_id, user_id, fortune_id){
      redishelper.getVaule(r_key, function(err, redis_result){
    		if(err) {
          var err_to_c = {
            errorcode : 500,
            errormsg : 'read redis error'
          }
    			res.end(JSON.stringify(err_to_c));
    			return ;
    		}
        if(redis_result === undefined || redis_result === null) { // 今日还没有领取过
          redishelper.setValueWithExpire(r_key, JSON.stringify(key_info), getCurrentDayLeftSeconds());
          var test = {
            errorcode : 701,
            errormsg : 'expire or no broke info'
          };
          res.end(JSON.stringify(test));
          return ;
        }
        var bankruptObj = JSON.parse(redis_result);
        if(bankruptObj.rebirth_num < MAX_BROKE_NUM) {
          bankruptObj.rebirth_num = bankruptObj.rebirth_num + 1;
          var test = {
            errorcode : 0,
            errormsg : '',
            reward_coins : 1000*bankruptObj.rebirth_num
          };
          updateUserCoinsOrDiamonds(session_id, user_id, fortune_id,
              test.reward_coins, 0);// 同步用户信息，增加金币数

          var mark_data = {
            type : 1, // 1领取，2，破产
            nums : bankruptObj.rebirth_num,
            room_id : room_id
          };
          statistics_gametask_logic.insertOneBankruptData(user_id,  mark_data, function(result){
          });
          redishelper.setValueWithExpire(r_key, JSON.stringify(bankruptObj), getCurrentDayLeftSeconds());
          console.log('rebirth [bankruptObj]: ' + JSON.stringify(bankruptObj));
          console.log('rebirth [client]: ' + JSON.stringify(test));
          res.end(JSON.stringify(test));
          return ;
        }else {
          var test = {
            errorcode : 0,
            errormsg : '',
            reward_coins : 1
          };
          res.end(JSON.stringify(test));
          console.log('rebirth [client]: ' + JSON.stringify(test));
        }
      });
    })(r_key, room_id, user_id);
  });
}

function getCurrentDayLeftSeconds() {
	var myDate = new Date();
	return ((23 - myDate.getHours())*60 + (59 - myDate.getMinutes()))*60 +
		59 - myDate.getSeconds();
}

function updateUserCoinsOrDiamonds(session_id, user_id, fortune_id, coins, diamonds) {
  var sync_info = {
    user_id : user_id,
    fortune_id : fortune_id === undefined ? 1 : fortune_id,
    coins : coins,
    diamonds : diamonds
  };
  // [bankrupt] sync_info : {"user_id":43837,"coins":3000,"diamonds":0}
  console.log('[bankrupt] sync_info : ' + JSON.stringify(sync_info));
  player_logic.syncPlayerCoinsAndDiamonds(session_id, sync_info);
}

module.exports = router;
