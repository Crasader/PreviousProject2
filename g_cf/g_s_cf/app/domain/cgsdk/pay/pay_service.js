'use strict';
var redishelper = require('../../../environment/mem/redishelper.js');
var agreement = require('../agreement.js');
var paypoint_manager = require('./paypoint_manager.js');

var ORDER_RESULT_HEAD  = 'ORDER_R_';

function checkPayResult(pay_type, order_id, user_id, callback){
  if(pay_type === 1){ // 微信支付
    var r_key = ORDER_RESULT_HEAD + order_id + user_id;
    (function(r_key){
      redishelper.getVaule(r_key, function(err, redis_result){
        if(err) {
          callback(false, JSON.parse(greement.redisErrorDesc)); // 返回服务器错误
          return ;
        }
        if ( redis_result != undefined ) { // 返回订单实际金额
          var resultObj = JSON.parse(redis_result);
          var result = {
            errorcode : 0,
            realprice : parseInt(resultObj.real_price),
            reward_lists : paypoint_manager.getRewardsByPayPointId(resultObj.pay_point_id)
          };
          redishelper.del(r_key); // 订单不能一直查询,查询成功后删除缓存记录
          console.log('checkPayResult success : ' + JSON.stringify(result));
          callback(true, result);
          return ;
        }
        callback(false, JSON.parse(agreement.errorMrQueryNoOrderInfoDesc));  // 返回没有查询到订单
      });
    })(r_key);

  }else {
    var result = {
      errorcode : 3104,
      errormsg : '未知支付类型'
    };
    callback(JSON.stringify(result));
  }
}

exports.checkPayResult = checkPayResult;
