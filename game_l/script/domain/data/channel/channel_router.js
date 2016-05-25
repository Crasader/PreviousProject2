
var dbmanager_catchfish = require('../../../db/dbmanager_catchfish.js');
var channel_db = require('./channel_db.js');

var express = require('express');
var router = express.Router();

/**
 * 查询当前的签到配置信息
 * 114.119.39.150:1703/data/channel/dayreport/:day
 */
router.get( '/dayreport/:day', function (req, res) {
  var day = req.params.day;
    channel_db.getDayreport(dbmanager_catchfish.getClientS(), day, function(success, results){
        if(!success) {
            console.log('/data/channel/dayreport, err ');
            res.end('');
            return ;
        }
        res.end(JSON.stringify(results));
    });
});

/**
 * 查询当前的签到配置信息
 * 114.119.39.150:1703/data/channel/dayreport/onechannel/:channel_id
 */
router.get( '/dayreport/onechannel/:channel_id', function (req, res) {
  var channel_id = req.params.channel_id;
  channel_db.getOnechannelInfo(dbmanager_catchfish.getClientS(), channel_id, function(success, results){
    if(!success) {
      console.log('/data/channel/dayreport/onechannel , err ');
      res.end('');
      return ;
    }
    res.end(JSON.stringify(results));
  });
});

module.exports = router;
