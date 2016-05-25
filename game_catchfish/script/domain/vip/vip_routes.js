'use strict';
/**
 * 房间信息获取
 */

var express = require('express');
var router = express.Router();

var vip_logic = require('./vip_logic.js');

/**
 * 获取vip的登陆奖励信息
 * vip/getrewards[POST]
 * 参数：session_id
 */
router.post( '/getrewards', function (req, res) {
  console.log('[vip/getrewards]coming , ' + req.body.session_id);
  var session_id = req.body.session_id;
  vip_logic.getVipRewards(session_id, function(result){
    console.log('vip result : ' + result);
    res.end(result);
  });

});

module.exports = router;
