'use strict';
/**
 * 任务信息
 */

var express = require('express');
var router = express.Router();

var gametask_everyday_logic = require('./gametask_everyday_logic.js');
var gametask_achievement_logic = require('./gametask_achievement_logic.js');

/**
 * 获取用户的每日任务信息
 * gametask/everyday[POST]
 * 参数：session_id
 */
router.post( '/everyday', function (req, res) {
  var session_id = req.body.session_id;
  gametask_everyday_logic.getEveryday(session_id, function(result){
    res.end(result);
  });
});

/**
 * 领取每日任务奖励
 * gametask/everyday/getreward[POST]
 * 参数：session_id, every_task_id
 */
router.post( '/everyday/getreward', function (req, res) {
  var session_id = req.body.session_id;
  var every_task_id = req.body.every_task_id;
  gametask_everyday_logic.getEverydayReward(session_id, every_task_id, function(result){
    res.end(result);
  });
});

/**
 * 获取用户的成就任务信息
 * gametask/achievement[POST]
 * 参数：session_id
 */
router.post( '/achievement', function (req, res) {
  var session_id = req.body.session_id;
  gametask_achievement_logic.getTasklists(session_id, function(result){
    res.end(result);
  });
});

/**
 * 领取成就任务奖励
 * gametask/achievement/getreward[POST]
 * 参数：session_id, achievement_task_id
 */
router.post( '/achievement/getreward', function (req, res) {
  var session_id = req.body.session_id;
  var achievement_task_id = req.body.achievement_task_id;
  gametask_achievement_logic.getRewards(session_id, achievement_task_id, function(result){
    res.end(result);
  });
});

module.exports = router;
