/**
 * 奖池逻辑
 */

var express = require('express');
var router = express.Router();

var bonuspool_logic = require('./bonuspool_logic.js');

/**
 * 捕获一条黄金鱼，信息更新
 * bonuspool/catchfish/:session_id/:fish_id
 * 测试： 106.75.135.78:1701/bonuspool/catchfish/TBU_1458284974211/40
 */
router.get( '/catchfish/:session_id/:fish_id', function (req, res) {
  var session_id = req.params.session_id;
  var fish_id = req.params.fish_id;
  bonuspool_logic.catchfish(session_id, fish_id, function(result){
    res.end(result);
  });
});

/**
 * 进行一次抽奖活动
 * bonuspool/turntable/:session_id
 * 测试： 106.75.135.78:1701/bonuspool/turntable/TBU_1458284974211
 */
router.get( '/turntable/:session_id/', function (req, res) {
  var session_id = req.params.session_id;
  bonuspool_logic.turntable(session_id, function(result){
    res.end(result);
  });
});

/**
 * 查询奖池状态
 * bonuspool/turntable/:session_id
 * 测试： 106.75.135.78:1701/bonuspool/currentstate/TBU_1458284974211
 */
router.get( '/currentstate/:session_id/', function (req, res) {
  var session_id = req.params.session_id;
  bonuspool_logic.currentstate(session_id, function(result){
    res.end(result);
  });
});

module.exports = router;
