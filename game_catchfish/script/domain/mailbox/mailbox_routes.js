'use strict';
/**
 * 活动业务[activity]
 */

var express = require('express');
var router = express.Router();

var mailbox_logic = require('./mailbox_logic.js');

/**
 * 查询玩家的未读邮件
 * mailbox/info/list/get
 * 测试：
 */
router.post( '/info/list/get', function (req, res) {
  var session_id = req.body.session_id;
  mailbox_logic.getPlayerMailInfo(session_id, function(result){
    res.end(result);
  });
});

/**
 * 领取玩家某条信息的奖励
 * mailbox/info/reward/get
 * 测试：
 */
router.post( '/info/reward/get', function (req, res) {
  var session_id = req.body.session_id;
  var mailbox_id = req.body.mailbox_id;
  mailbox_logic.getPlayerMailboxRewardsById(session_id, mailbox_id, function(result){
    res.end(result);
  });
});

/**
 * 批量领取玩家的奖励信息
 * mailbox/info/reward/get/all
 * 测试：
 */
router.post('/info/reward/get/all', function (req, res) {
  var session_id = req.body.session_id;
  mailbox_logic.getPlayerAllMailboxRewardsById(session_id, function(result){
    res.end(result);
  });
});

/**
 * 查询玩家的好友进阶奖励
 * mailbox/info/list/friend/reward/get
 * 测试：
 */
router.post( '/info/list/friend/reward/get', function (req, res) {
  var session_id = req.body.session_id;
  mailbox_logic.getPlayerFriendRewardById(session_id, function(result){
    res.end(result);
  });
});

module.exports = router;
