
var dbmanager_catchfish = require('../../../db/dbmanager_catchfish.js');
var event_db = require('./event_db.js');

var express = require('express');
var router = express.Router();

/**
 * 逻辑查询
 * 114.119.39.150:1703/data/event/dayreport/:type/:day
 * 114.119.39.150:1703/data/event/dayreport/turrentlevel/20160129 [炮台][v]
 * 114.119.39.150:1703/data/event/dayreport/skilluse/20160129 [技能使用][v]
 * 114.119.39.150:1703/data/event/dayreport/presented/20160129 [赠送][v]
 * 114.119.39.150:1703/data/event/dayreport/pagechange/20160129 [页面跳转][v]
 * 114.119.39.150:1703/data/event/dayreport/mermaidask/20160129 [美人鱼][v]
 * 114.119.39.150:1703/data/event/dayreport/bankrupt/20160129 [破产][v]
 * 114.119.39.150:1703/data/event/dayreport/fishinfo/20160129 [鱼群][v]
 * 114.119.39.150:1703/data/event/dayreport/turntable/20160129 [抽奖][v]
 * 114.119.39.150:1703/data/event/dayreport/expend/20160129 [消耗][v]
 * 114.119.39.150:1703/data/event/dayreport/turrentlevelgroup/20160129 [消耗][v]
 */
router.get( '/dayreport/:type/:day', function (req, res) {
  var type = req.params.type;
  var day = req.params.day;
  if(type === undefined || day === undefined ||
      type === null || day === null ||
      day.length != 8){
    res.end('[]');
    return ;
  }
  var table_name = '';
  var groupinfo = '';
  if(type === 'turrentlevel') {
    table_name = 'report_turrentlevelupdate_day';
  }else if(type === 'skilluse' ) {
    table_name = 'report_skilluse_day';
  }else if(type === 'presented') {
    table_name = 'report_presented_day';
  }else if(type === 'pagechange') {
    table_name = 'report_pagechange_day';
    groupinfo = ' ORDER BY nums DESC ';
  }else if(type === 'mermaidask') {
    table_name = 'report_mermaidtask_day';
  }else if(type === 'bankrupt') {
    table_name = 'report_bankrupt_day';
  }else if(type === 'fishinfo') {
    table_name = 'report_fishinfo_day';
  }else if(type === 'turntable') {
    table_name = 'report_turntable_day';
  }else if(type === 'expend') {
    table_name = 'report_expend_day';
  }else if(type === 'turrentlevelgroup'){
    table_name = 'report_turrent_group_day';
  }else {
    res.end('[]');
    return ;
  }
  event_db.getSomeInfoByDay(dbmanager_catchfish.getClientS(), day, groupinfo, table_name, function(success, results){
      if(!success) {
          res.end('[]');
          return ;
      }
      res.end(JSON.stringify(results));
  });
});

/**
 * 逻辑查询
 * 114.119.39.150:1703/data/event/dayreport/user/pagechange/:user_id
 *
 */
router.get( '/dayreport/user/pagechange/:user_id', function (req, res) {
  var user_id = req.params.user_id;
  if(user_id === undefined  || user_id === null ||
      user_id.length < 3){
    res.end('[]');
    return ;
  }

  event_db.getUSerPageInfo(dbmanager_catchfish.getClientS(), user_id, function(success, results){
      if(!success) {
          res.end('[]');
          return ;
      }
      res.end(JSON.stringify(results));
  });
});

/**
 * 用户游戏信息查询
 * 114.119.39.150:1703/data/event/dayreport/user/gameinfo/:user_id
 *
 */
router.get( '/dayreport/user/gameinfo/:user_id', function (req, res) {
  var user_id = req.params.user_id;
  if(user_id === undefined  || user_id === null ||
      user_id.length < 3){
    res.end('[]');
    return ;
  }

  event_db.getUserGameInfo(dbmanager_catchfish.getClientS(), user_id, function(success, results){
      if(!success) {
          res.end('[]');
          return ;
      }
      res.end(JSON.stringify(results));
  });
});

/**
 * 用户游戏信息查询
 * 114.119.39.150:1703/data/event/dayreport/user/register/:user_id
 *
 */
router.get( '/dayreport/user/register/:user_id', function (req, res) {
  var user_id = req.params.user_id;
  if(user_id === undefined  || user_id === null ||
      user_id.length < 3 || isNaN(user_id) ){
    res.end('[]');
    return ;
  }

  event_db.getUserRegisterInfo(dbmanager_catchfish.getClientS(), user_id, function(success, results){
      if(!success) {
          res.end('[]');
          return ;
      }
      res.end(JSON.stringify(results));
  });
});

/**
 * 逻辑查询
 * 114.119.39.150:1703/data/event/dayreport/exp_distribution/:day
 *
 */
router.get( '/dayreport/exp/distribution/:day', function (req, res) {
  var day = req.params.day;
  console.log('[/dayreport/exp_distribution/:day]day : ' + day + ', length = ' + day.length);
  if(day === undefined  || day === null ||
      day.length !== 8){
    res.end('[]');
    return ;
  }

  event_db.getExpInfo(dbmanager_catchfish.getClientS(), day, function(success, results){
      if(!success) {
          res.end('[]');
          return ;
      }
      res.end(JSON.stringify(results));
  });
});

module.exports = router;
