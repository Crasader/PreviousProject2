
var request = require('request');
var urlencode=require('urlencode');

/**
 *
 *  url   : http://106.75.135.78:1801/weixin/pay/req
 *  参数   : order_id tbu_id, product_id, product_name, price
 */
function reqWxOrder(order_id, tbu_id, product_id, product_name, price, callback){

    var param = 'order_id=' + order_id + '&tbu_id=' + tbu_id + '&product_id=' + product_id +
        '&product_name=' + urlencode(product_name) + '&price=' + price;
    //var sign = getMd5(order_id + tbu_id + product_id + product_name + price);
    var url='http://106.75.135.78:1801/weixin/pay/order?'+param;//+'&sign='+sign;
    var options = {
        url: url,
        timeout: 8000,
        method:'GET'
        };

    request(options, function (error, response, body) {
        if (error) {
            console.log('reqWxOrder-> meet error : ' + error);
            callback(1, 'timeout');
            return ;
        }


        if(response.statusCode=='200'){
            console.log('ctp[reqWxOrder]->body=' + body);
            callback(0, body);
            return ;
        }
        console.log('reqWxOrder->response.statusCode = ' + response.statusCode);
        callback(2, response.statusCode);
    });
}

function reqWxOrderCancel(order_id, wx_order_id, callback) {
  var param = 'order_id=' + order_id + '&wx_order_id=' + wx_order_id;
  //var sign = getMd5(order_id + tbu_id + product_id + product_name + price);
  var url='http://106.75.135.78:1801/weixin/pay/close?'+param;//+'&sign='+sign;
  var options = {
      url: url,
      timeout: 8000,
      method:'GET'
  };

  request(options, function (error, response, body) {
      if (error) {
          console.log('reqWxOrderCancel-> meet error : ' + error);
          callback(false, 'timeout');
          return ;
      }

      if(response.statusCode=='200'){
          console.log('ctp[reqWxOrderCancel]->body=' + body);
          callback(true, body);
          return ;
      }
      console.log('reqWxOrderCancel->response.statusCode = ' + response.statusCode);
      callback(false, response.statusCode);
  });
}

exports.reqWxOrder = reqWxOrder;
exports.reqWxOrderCancel = reqWxOrderCancel;
