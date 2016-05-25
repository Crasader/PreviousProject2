'use strict';
/**
 * 红包业务[hongbao]
 */

var express = require('express');
var router = express.Router();

var hongbao_logic = require('./hongbao_logic.js');

/**
 * 领取红包口令信息
 * hongbao/get[POST]
 * 参数:session_id, hongbao_id
 */
router.post( '/get', function (req, res) {
  var session_id = req.body.session_id;
  var hongbao_id = req.body.hongbao_id;
  hongbao_logic.get(session_id, hongbao_id, function(result){
    res.end(result);
  });
});

/**
 * 获取分享信息
 * hongbao/shareinfo/get[POST]
 * 参数:session_id
 */
router.post('/shareinfo/get', function (req, res) {
  var session_id = req.body.session_id;
  hongbao_logic.getShareinfo(session_id, function(result){
    res.end(result);
  });
});


module.exports = router;
