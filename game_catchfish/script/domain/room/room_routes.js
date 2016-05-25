'use strict';
/**
 * 房间信息获取
 */

var express = require('express');
var router = express.Router();

var room_logic = require('./room_logic.js');

/**
 * 获取配置文件
 * 协议：room/roominfo
 * 参数：game_version
 */
router.post( '/roominfo', function (req, res) {
  var game_version = req.body.game_version;
  res.end(room_logic.getRoomPlayerInfoStr(game_version));
});

module.exports = router;
