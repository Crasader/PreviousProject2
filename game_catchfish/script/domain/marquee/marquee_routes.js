/**
 * 签到业务[sign]
 */

var express = require('express');
var router = express.Router();

var marquee_logic = require('./marquee_logic.js');

/**
 * 跑马灯展示-大厅
 * 协议：marquee/config
 * 测试：
 */
router.get( '/config', function (req, res) {
  res.end(marquee_logic.getMarqueeAgreementStr());
});

module.exports = router;
