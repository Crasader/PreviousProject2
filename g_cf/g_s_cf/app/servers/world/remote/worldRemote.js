module.exports = {};

// var roomManager = require('../../../domain/room/roomManager');

var msgs = [];
var MIN_MSG_LENGTH = 5; // 最小允许的消息长度
var MAX_MSG_COUNT_ON_ONETIME = 5; // 单次最大缓存消息数量

/**
 * 记录全局消息
 */
module.exports.addNewMsg = function (type, msg, cb) {
  console.log('[worldaddNewMsg]type : ' + type + 'msg : ' + msg);
  if(msg !== undefined && msg !== null && msg.length > MIN_MSG_LENGTH) {
    msgs.push(msg);
    if(msgs.length > MAX_MSG_COUNT_ON_ONETIME) { // 最多一次带下5条消息
      msgs.shift();
    }
  }
  cb();
};

var count = 0;
module.exports.getNewMsgs = function (cb) {
  if(msgs.length > 0) {
    cb(msgs);
    msgs = [];
  }else {
    count++;
    if(count === 3) {
      count = 0;
      cb(getRandomMsg());
    }else {
      cb([]);
    }

  }
};

function getRandomMsg() {
  var testEvent = [];
  var randomnum = parseInt(60*Math.random());
  var random_name = 'g_' + parseInt(1000000*Math.random());
  if(randomnum < 20){
    testEvent.push(random_name + '在300倍房间捕获美人鱼,获得黄金宝箱!');
  }else if(randomnum < 40) {
    var random_nums = 20 + parseInt(30*Math.random());
    testEvent.push(random_name + '在赚话费中获得' + random_nums + '勋章,可兑换话费!捕获黄金鱼可获得免费赚话费抽奖机会.');
  }else {
    testEvent.push(random_name + '在赚话费中获得黄金宝箱,提升捕鱼概率!捕获黄金鱼可获得免费赚话费抽奖机会.');
  }
  return testEvent;
}
