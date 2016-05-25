'use strict';
/**
 * 红包业务[hongbao]
 */

var express = require('express');
var router = express.Router();

/**
 * 领取红包口令信息
 * hongbao/get[POST]
 * 参数:session_id, hongbao_id
 */
router.get( '/', function (req, res) {
  var share_key_str = req.query.share_key === undefined ? '8848' : req.query.share_key;
  res.render( 'download', { share_key : share_key_str} );
});



module.exports = router;
