'use strict';
/**
 * 对话
 */

var express = require('express');
var router = express.Router();

var change_logic = require('./change_logic.js');

/**
 * 兑换奖励
 * change/getrewards[POST]
 * 参数：session_id, change_type[1,话费;2 钻石; 3核弹], phone_nums
 */
router.post( '/getrewards', function (req, res) {
  console.log('[change/getrewards]coming , ' + req.body.session_id);
  var session_id = req.body.session_id;
  var change_type = req.body.change_type; // 1,话费;2 钻石; 3核弹
  var phone_nums = req.body.phone_nums;   // 用户手机号码
  change_logic.getRewards(session_id, change_type, phone_nums, function(result){
    console.log('change result : ' + result);
    res.end(result);
  });

});


/**
 * 兑换奖励
 * change/getrecord[POST]
 * 参数：session_id
 */
router.post( '/getrecord', function (req, res) {
  console.log('[change/getrecord]coming , ' + req.body.session_id);
  var session_id = req.body.session_id;
  change_logic.getRecord(session_id, function(result){
    console.log('getrecord result : ' + result);
    res.end(result);
  });

});

module.exports = router;
