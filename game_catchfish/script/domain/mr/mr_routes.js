/**
 * MR-结果[mr/result]
 */

var express = require('express');
var router = express.Router();

var redishelper = require('../../mem/redishelper.js');
var dbmanager = require('../../db/dbmanager.js');
var agreement = require('../../agreement.js');
var session_manager = require('../../session_manager.js');
var mr_db = require('./mr_db.js');
var mo_logic = require('../mo/mo_logic.js');
var tbumailservice = require('../../util/tbumailservice.js');
var nobility_logic = require('../nobility/nobility_logic.js');

var player_info_service = require('../player/player_info_service.js');
var paypoint_manager = require('../mo/paypoint_manager.js');

var SESSION_EXPIRE = 60*60*2;	// 2小时
var ORDER_RESULT_HEAD  = 'ORDER_R_';

/**
 * 下单-结果[SKY第三方支付]
 * 协议：mr/sky/result
 * 测试：
 */
router.get( '/sky/result', function (req, res) {

  var order_id = req.query.order_id;
  (function(req, res){
    redishelper.getVaule('o_'+ order_id, function(err, redis_result){
  		if(err) {
  			res.end('ok');
  			return ;
  		}
  		if(redis_result != undefined) {
        var orderInfo = JSON.parse(redis_result);
        orderInfo.third_order_id = req.query.sky_order_id;
        orderInfo.real_price = req.query.real_price;
        orderInfo.sky_error_code = req.query.sky_error_code;
        orderInfo.third_time = req.query.sky_time;
        orderInfo.sky_type = req.query.sky_type;
        orderInfo.third_type = 0;
        mr_db.addNewSkyMr(dbmanager.getClient(), orderInfo, function(success){
        });
        mr_db.addNewMr(dbmanager.getClient(), orderInfo, function(success){
        });
        console.log('[mr][sky] callback [addNewMr]: ' + JSON.stringify(orderInfo));
        dealMrByOrderInfo(orderInfo);

        var r_s_o = {
          real_price : orderInfo.real_price,
          pay_point_id : orderInfo.pay_point_id
        };
        redishelper.setValueWithExpire(ORDER_RESULT_HEAD + orderInfo.order_id + orderInfo.user_id,
            JSON.stringify(r_s_o), SESSION_EXPIRE); // 向缓存记录一笔mr记录，供客户端查询

        tbumailservice.sendWaringEmail('GAME_CG_MR[SKY]=' + orderInfo.real_price,
            '订单信息:' + orderInfo.order_id + '[' +orderInfo.user_id + '], channel[' + orderInfo.channel_id + ']' +
            ', sky_error_code[' + orderInfo.sky_error_code + '], sky_type[' + orderInfo.sky_type + ']');

        // 记录角色充值时的用户信息
        var order_id = orderInfo.order_id;
        (function(order_id){
          redishelper.getVaule(orderInfo.session_id, function(err, redis_result){
            if(err || redis_result === undefined) {
        			return ;
        		}
            var userinfo = JSON.parse(redis_result);
            // TODO : 更新用户信息中的充值金额
            console.log('mr_userinfo : ' + redis_result);
            if(userinfo !== undefined && userinfo !== null) {
              mr_db.addNewMrUserInfo(dbmanager.getClient(), order_id, userinfo, 1, function(success){
              });
            }
          });
        })(order_id);

  		}else {
        var orderInfo = {
          order_id : req.query.order_id,
          sky_order_id : req.query.sky_order_id,
          real_price : req.query.real_price,
          sky_error_code : req.query.sky_error_code,
          sky_type : req.query.sky_type,
          sky_time : req.query.sky_time,
          create_time : new Date().Format("yyyy-MM-dd hh:mm:ss:S")
        };
        console.log('[mr][sky] callback [addNewMrError]: ' + JSON.stringify(orderInfo));
        mr_db.addNewMrError(dbmanager.getClient(), orderInfo, function(success){
        });
      }
  		res.end('ok');
  	});
  })(req, res);
});


/**
 * 下单-结果[微信支付]
 * 协议：HEAD/mr/wx/result
 * 测试：
 */
router.get( '/wx/result', function (req, res) {

  if(req.query.result !== undefined && parseInt(req.query.result) === 0) {
    (function(req, res){
      var order_id = req.query.order_id;
      redishelper.getVaule('o_'+ order_id, function(err, redis_result){
    		if(err) {
    			res.end('ok');
    			return ;
    		}
    		if(redis_result != undefined) {
          var orderInfo = JSON.parse(redis_result);

          orderInfo.third_order_id = req.query.wx_order_id;
          orderInfo.real_price = isNaN(req.query.price) === false ? parseInt(req.query.price) : 0;
          orderInfo.third_time = req.query.time_end;
          orderInfo.third_type = 1;
          mr_db.addNewMr(dbmanager.getClient(), orderInfo, function(success){
          });
          console.log('[mr][wx] callback [addNewMr]: ' + JSON.stringify(orderInfo));
          dealMrByOrderInfo(orderInfo);
          mo_logic.markMoResult(orderInfo);

          tbumailservice.sendWaringEmail('GAME_CG_MR[WX]=' + orderInfo.real_price,
              '订单信息:' + orderInfo.order_id + '[' + orderInfo.user_id +
              '], channel[' + orderInfo.channel_id + ']');

          (function(orderInfo){
            redishelper.getVaule(orderInfo.session_id, function(err, redis_result){
              if(err || redis_result === undefined) {
          			return ;
          		}
              console.log('mr_old_userinfo : ' + redis_result);
              var userinfo = JSON.parse(redis_result);
              if(orderInfo.real_price > 0) {
                var reward_lists = getRewardByVip(userinfo.mo,
                    paypoint_manager.getRewardsByPayPointId(orderInfo.pay_point_id) );//根据VIP等级判断应该给多少

                if(userinfo.mo_coins === 0 && parseInt(orderInfo.pay_point_id)>= 1 && parseInt(orderInfo.pay_point_id) <= 7) {
                  userinfo.mo += orderInfo.real_price;
                  userinfo.mo_coins = 1;
                  player_info_service.syncMoInfo(userinfo, 997);  // 更新用户信息中的充值金额+金币首充
                  reward_lists = getNewRewardsByFirstPayForCoins(reward_lists);// 奖励信息需要更新
                }else if(userinfo.mo_first === 0 && parseInt(orderInfo.pay_point_id) === 15) {
                  userinfo.mo += orderInfo.real_price;
                  userinfo.mo_first = 1;
                  player_info_service.syncMoInfo(userinfo, 998);  // 更新用户信息中的充值金额+首充礼包
                }else {
                  userinfo.mo += orderInfo.real_price;
                  player_info_service.syncMoInfo(userinfo, 999);  // 更新用户信息中的充值金额
                }

                var r_s_o = {
                  real_price : parseInt(orderInfo.real_price),
                  pay_point_id : parseInt(orderInfo.pay_point_id),
                  reward_lists : reward_lists
                };
                redishelper.setValueWithExpire(ORDER_RESULT_HEAD + orderInfo.order_id + orderInfo.user_id,
                    JSON.stringify(r_s_o), SESSION_EXPIRE);   // 向缓存记录一笔mr记录，供客户端查询

                console.log(orderInfo.pay_point_id + '_mr_reward_lists : ' + JSON.stringify(reward_lists));
                player_info_service.syncRewardsInfo(reward_lists, userinfo); // 同步用户信息
              }

              console.log('mr_new_userinfo : ' + JSON.stringify(userinfo));
              if(userinfo !== undefined && userinfo !== null) {
                redishelper.setValueWithExpire(userinfo.session_id, JSON.stringify(userinfo), SESSION_EXPIRE);
                mr_db.addNewMrUserInfo(dbmanager.getClient(), orderInfo.order_id, userinfo, 0, function(success){
                });// 记录角色充值时的用户信息
              }
            });
          })(orderInfo);

    		}
    		res.end('ok');
    	});
    })(req, res);
  }
  res.end('error');
});

function dealMrByOrderInfo(orderInfo) {
  if(parseInt(orderInfo.pay_point_id) === 13) {   // 如果计费点编号是13(贵族充值，需要写入贵族信息)
    nobility_logic.addNewNobilityInfo(orderInfo.user_id);
  }
}

/**
 * client查询订单信息.仅查询缓存中最近2小时的订单
 * [POST]114.119.39.150:1701/mr/order/result/
 * 114.119.39.150:1701/mr/order/result/
 *
 */
router.post( '/order/result/', function (req, res) {
  var session_id = req.body.session_id;
  var order_id = req.body.order_id;
  console.log('[/order/result/][mr]order_id : ' + order_id);
  (function(order_id){
    session_manager.isLogin(session_id, function(login, data){
      if(!login) {
        res.end(data);
        return ;
      }
      var r_key = ORDER_RESULT_HEAD + order_id + data.user_id;
      (function(r_key){
        redishelper.getVaule(r_key, function(err, redis_result){
          if(err) {
            res.end(agreement.redisErrorDesc); // 返回服务器错误
            return ;
          }
          if ( redis_result != undefined ) { // 返回订单实际金额
            var resultObj = JSON.parse(redis_result);
            var result = {
              errorcode : 0,
              errormsg : 'success',
              realprice : resultObj.real_price,
              reward_lists : resultObj.reward_lists
            };
            console.log('[/order/result/][mr] success : ' + JSON.stringify(result));
            redishelper.del(r_key); // 查询成功后再次查询不能够查询到
            res.end(JSON.stringify(result));
            return ;
          }
          res.end(agreement.errorMrQueryNoOrderInfoDesc);  // 返回没有查询到订单
        });
      })(r_key);
    });
  })(order_id);
});


module.exports = router;

/**
 * 根据VIP等级判断应该给多少
 */
function getRewardByVip(mo, reward_lists) {
  mo = parseInt(mo);
  var new_reward_lists = [];
  var per = 1.0;
  if(mo < 1000) {
    return reward_lists;
  } else if(mo < 5000) {
    per = 1.1;
  } else {
    per = 1.2;
  }
  for(var i=0;i<reward_lists.length;i++){
    var item = {
      item_id : reward_lists[i].item_id,
      nums : parseInt(reward_lists[i].nums*per)
    }
    new_reward_lists.push(item);
  }
  return new_reward_lists;
}

/**
 * 额外送100个钻石
 */
function getNewRewardsByFirstPayForCoins(reward_lists){
  var new_reward_lists = [];
  var success_update = false;
  for(var i=0;i<reward_lists.length;i++){
    var item = {
      item_id : reward_lists[i].item_id,
      nums : parseInt(reward_lists[i].nums)
    }
    if(item.item_id === 1002) {
      item.nums += 100;
      success_update = true;
    }
    new_reward_lists.push(item);
  }
  if(!success_update) {
    new_reward_lists.push({
      item_id : 1002,
      nums : 100
    });
  }
  return new_reward_lists;
}
