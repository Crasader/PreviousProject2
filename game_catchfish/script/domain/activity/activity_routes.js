'use strict';
/**
 * 活动业务[activity]
 */

var express = require('express');
var router = express.Router();

var activity_logic = require('./activity_logic.js');

/**
 * 下单-结果
 * activity/config
 * 测试：
 */
router.get( '/config', function (req, res) {
  res.end(activity_logic.getActivityAgreementStr());
});

module.exports = router;
