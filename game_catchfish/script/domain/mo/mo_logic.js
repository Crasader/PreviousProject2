
var agreement = require('../../agreement.js');
var dbmanager = require('../../db/dbmanager.js');
var mo_db = require('./mo_db.js');
var redishelper = require('../../mem/redishelper.js');
var order_id = 0;
var paypoint_manager = require('./paypoint_manager.js');

var ctp = require('../../plugin/ctp/ctp.js');

var SESSION_EXPIRE = 60*60*2;	// 2小时

function insertNewBooking(reqreq_booking_info, callback) {
  if(reqreq_booking_info.pay_type === 0) { // 下单
    if(parseInt(reqreq_booking_info.price) <= 0 || ( parseInt(reqreq_booking_info.price) !==
        paypoint_manager.getPrice(reqreq_booking_info.pay_point_id) ) ) { // 参数效验
        var error_result = {
            errorcode : 3304,
            errormsg : '检测到您存在作弊行为!'
        };
        callback(JSON.stringify(error_result));
        return ;
    }
    order_id = order_id + 1;
    var result = {
      errorcode : 0,
      errormsg : 'success update data',
      order_id : ''+order_id
    };
    reqreq_booking_info.order_id = result.order_id;
    console.log('[/order/booking]reqreq_booking_info:'+JSON.stringify(reqreq_booking_info));
    if(reqreq_booking_info.third_type === 1) { // 1,为微信支付
      (function(order_id){  // 201602 为tbu_id
        ctp.reqWxOrder(order_id, '201602', reqreq_booking_info.pay_point_id,
            reqreq_booking_info.pay_point_desc, reqreq_booking_info.price, function(success, result){
          if(success === 0) {
            var resultObj = JSON.parse(result);
            if(parseInt(resultObj.result) === 0) {
              var wx_result = {
                errorcode : 0,
                errormsg : '下单成功',
                order_id : ''+order_id,
                wx_nonce_str : resultObj.wx_nonce_str,
                wx_prepayid : resultObj.wx_prepayid,
                wx_sign : resultObj.wx_sign,
                wx_timestamp : '' + resultObj.wx_timestamp,
                wx_order_id : resultObj.wx_order_id // 微信的out_trade_no
              };
              redishelper.setValueWithExpire('wxp_'+req_booking_session.order_id,
                  JSON.stringify(wx_result), SESSION_EXPIRE);
              callback(JSON.stringify(wx_result));
              return ;
            } else {
              var error_result = {
                errorcode : 3003,
                errormsg : '微信支付错误'+resultObj.result
              };
              callback(JSON.stringify(error_result));
              return ;
            }
          }else if(success === 1){
            var error_result = {
              errorcode : 3001,
              errormsg : '支付服务器忙,请稍后再试'
            };
            callback(JSON.stringify(error_result));
            return ;
          }else if(success === 2) {
            var error_result = {
              errorcode : 3002,
              errormsg : '微信服务器忙,请稍后再试'
            };
            callback(JSON.stringify(error_result));
            return ;
          }
          var error_result = {
            errorcode : 500,
            errormsg : '支付服务器正在维护' + result
          };
          callback(JSON.stringify(error_result));
        });
      })(order_id);

    }else {
      callback(JSON.stringify(result));
    }


    // 缓存中写入一条记录[有效期2天]
    var req_booking_session = {
      pay_and_event_version : reqreq_booking_info.pay_and_event_version,
      pay_event_id : reqreq_booking_info.pay_event_id ,
      pay_point_id : reqreq_booking_info.pay_point_id ,
      channel_id : reqreq_booking_info.channel_id ,
      order_id : reqreq_booking_info.order_id ,
      price : reqreq_booking_info.price ,
      user_id : reqreq_booking_info.user_id,
      session_id : reqreq_booking_info.session_id,
      mo_id : reqreq_booking_info.mo_id,
      create_time : reqreq_booking_info.create_time
    };
    redishelper.setValueWithExpire('o_'+req_booking_session.order_id,
        JSON.stringify(req_booking_session), SESSION_EXPIRE);

  }else if(reqreq_booking_info.pay_type === 1 && reqreq_booking_info.order_id != null) { // 结果
    var result = {
      errorcode : 0,
      errormsg : 'success update data',
      order_id : reqreq_booking_info.order_id
    };
    callback(JSON.stringify(result));
  }else {
    callback(agreement.errorMoParameterDesc);
    return ;
  }
  // callback(JSON.stringify(reqreq_booking_info));
  mo_db.addNewMo(dbmanager.getClient(), reqreq_booking_info, function(result) {
    if(!result) {
      console.log('insert mo error');
    }
  });
}

exports.insertNewBooking = insertNewBooking;

function cancelOrder(order_id, callback) {
  (function(order_id){
    redishelper.getVaule('wxp_'+ order_id, function(err, redis_result){
      if(err || redis_result === undefined || redis_result === null) {
        callback(agreement.noOrderInfoDesc);  // 305，没有查询到订单信息
        return ;
      }

      var obj = JSON.parse(redis_result);
      if(obj.wx_order_id === null) {
        callback(agreement.noOrderInfoDesc);  // 305，没有查询到订单信息
        return ;
      }
      ctp.reqWxOrderCancel(order_id, obj.wx_order_id, function(success, result){
        if(success) {
          var successMsg = {
            errorcode : 0,
            errormsg : 'success cancel'
          };
          callback(JSON.stringify(successMsg));
          return ;
        }
        var error_result = {
          errorcode : 500,
          errormsg : 'cancel order error, code : ' + result
        };
        callback(JSON.stringify(error_result));
      });
    });
  })(order_id);

}

exports.cancelOrder = cancelOrder;

function init() {
  order_id = parseInt(new Date().Format("yyyyMMddhhmmss"));
  console.log('init order_id : ' + order_id);
}

exports.init = init;

function markMoResult(orderInfo) {
  var req_booking_info = {
    pay_and_event_version : orderInfo.pay_and_event_version,
    pay_event_id : orderInfo.pay_event_id ,
    pay_point_id : orderInfo.pay_point_id ,
    channel_id : orderInfo.channel_id ,
    order_id : orderInfo.order_id ,
    price : orderInfo.price ,
    user_id : orderInfo.user_id,
    third_type : orderInfo.third_type,
    pay_type : 1, // 0,请求，1结果
    result : 0,
    mo_id : orderInfo.mo_id,
    create_time : new Date().Format("yyyy-MM-dd hh:mm:ss:S")
  };
  mo_db.addNewMo(dbmanager.getClient(), req_booking_info, function(result) {
    if(!result) {
      console.log('insert mo error');
    }
  });
}

exports.markMoResult = markMoResult;
