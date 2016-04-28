'use strict';
/**
 * 活动业务[activity]
 */

var express = require('express');
var router = express.Router();

var cdkey_logic = require('./cdkey_logic.js');

/**
 * 兑换奖品
 * 协议：cdkey/get[POST]
 * 参数：session_id, cdkey
 */
router.post( '/get', function (req, res) {
  var session_id = req.body.session_id;
  var cdkey = req.body.cdkey;
  cdkey_logic.getRewards(session_id, cdkey, function(result){
    res.end(result);
  });
});

module.exports = router;
