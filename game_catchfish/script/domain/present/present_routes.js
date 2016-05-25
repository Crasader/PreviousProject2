'use strict';
/**
 * 赠送业务[present]
 */

var express = require('express');
var router = express.Router();

var present_logic = require('./present_logic.js');

/**
 * 查询玩家的未读邮件
 * present/give
 * 测试：
 */
router.post( '/give', function (req, res) {
  var session_id = req.body.session_id;
  var item_id = req.body.item_id;
  var nick_name = req.body.nick_name;
  present_logic.give(session_id, nick_name, item_id, function(result){
    res.end(result);
  });
});


module.exports = router;
