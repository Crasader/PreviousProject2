'use strict';
/**
 * 背包逻辑[bag]
 */

var express = require('express');
var router = express.Router();

var chest_logic = require('./chest_logic.js');

/**
 * 开宝箱
 * bag/chest/get[POST]
 * 参数 : session_id, item_id
 */
router.post( '/chest/get', function (req, res) {
  var session_id = req.body.session_id;
  var item_id = req.body.item_id;
  chest_logic.getChest(session_id, item_id, function(result){
    res.end(result);
  });
});

module.exports = router;
