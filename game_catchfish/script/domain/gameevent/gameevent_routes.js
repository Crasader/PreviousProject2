/**
 * 记录一次游戏事件[gameevent/mark]
 */

var express = require('express');
var router = express.Router();

/**
 * 记录一次游戏事件
 * 协议：gameevent/mark
 * 测试：
 */
router.get( '/mark', function (req, res) {
    res.end('');
});


module.exports = router;
