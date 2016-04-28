/**
 * MO-下单[mo/order/booking]
 */

var express = require('express');
var router = express.Router();

var mo_logic = require('./mo_logic.js');
var session_manager = require('../../session_manager.js');

/**
 * 下单
 * 协议：mo/order/booking
 * 测试：
 */
router.post( '/order/booking', function (req, res) {
  var session_id = req.body.session_id;
	session_manager.isLogin(session_id, function(login, data){
		if(!login) {
			res.end(data);
			return ;
		}

    var req_booking_info = {
      pay_and_event_version : req.body.pay_and_event_version, // 6位,事件点+计费点编号(事件点版本号*1000+计费点版本号)
      pay_event_id : req.body.pay_event_id, // 事件点
      pay_point_id : req.body.pay_point_id, // 计费点
      pay_point_desc : req.body.pay_point_desc, // 计费点描述
      pay_type : parseInt(req.body.pay_type), // 请求类型.0,下单.1,结果
      result : req.body.result === null ? 0 : req.body.result, // 结果。仅在结构有意义。0,成功。非0，错误码。下单填0
      channel_id : req.body.channel_id, // 渠道号
      order_id : req.body.order_id,  // 订单号。下单(type==0)写0，下单结果带上订单号
      price : req.body.price === undefined ? 0 : req.body.price,  // 金额，单位分
      user_id : data.user_id,
      mo_id : data.mo_id,
      session_id : data.session_id,
      third_type : req.body.third_type === undefined ? 0 : parseInt(req.body.third_type), // 1为微信。
      create_time : new Date().Format("yyyy-MM-dd hh:mm:ss:S")
    };
    mo_logic.insertNewBooking(req_booking_info, function(result){
      console.log('booking result : ' + result);
      res.end(result);
    });
	});

});

/**
 * 下单
 * 协议：mo/order/booking
 * 测试：
 */
router.post( '/order/cancel', function (req, res) {
  console.log('cancel mr coming, req.body.order_id = ' + req.body.order_id);
  var session_id = req.body.session_id;
	session_manager.isLogin(session_id, function(login, data) {
		if(!login) {
			res.end(data);
			return ;
		}
    var order_id = req.body.order_id;
    mo_logic.cancelOrder(order_id, function(result){
      res.end(result);
    });
  });
});



module.exports = router;
