
var dbmanager_catchfish = require('../../../db/dbmanager_catchfish.js');
var pay_db = require('./pay_db.js');

var express = require('express');
var router = express.Router();

/**
 * 查询单日mo信息
 * 114.119.39.150:1703/data/pay/dayreport/:day
 * http://114.119.39.150:1703/data/pay/dayreport/20160204
 */
router.get( '/dayreport/:day', function (req, res) {
  var day = req.params.day;
    pay_db.getDayreport(dbmanager_catchfish.getClientS(), day, function(success, results){
        if(!success) {
            console.log('/data/pay/dayreport, err ');
            res.end('');
            return ;
        }
        res.end(JSON.stringify(results));
    });
});

/**
 * 增加按照用户id查询mo信息
 * 114.119.39.150:1703/data/pay/dayreport/user/mo/:channel_id
 * http://114.119.39.150:1703/data/pay/dayreport/user/mo/17562
 */
router.get( '/dayreport/user/mo/:user_id', function (req, res) {
  var user_id = req.params.user_id;
    pay_db.getUserMo(dbmanager_catchfish.getClientS(), user_id, function(success, results){
        if(!success) {
            console.log('/data/pay/getUserMo, err');
            res.end('');
            return ;
        }
        res.end(JSON.stringify(results));
    });
});

/**
 * 增加按照用户id查询mr
 * 114.119.39.150:1703/data/pay/dayreport/user/mr/:channel_id
 * http://114.119.39.150:1703/data/pay/dayreport/user/mr/17562
 */
router.get( '/dayreport/user/mr/:user_id', function (req, res) {
  var user_id = req.params.user_id;
    pay_db.getUserMr(dbmanager_catchfish.getClientS(), user_id, function(success, results){
        if(!success) {
            console.log('/data/pay/getUserMr, err');
            res.end('');
            return ;
        }
        res.end(JSON.stringify(results));
    });
});

/**
 * 增加按照用户id查询mr
 * 114.119.39.150:1703/data/pay/dayreport/mr/:day
 * http://114.119.39.150:1703/data/pay/dayreport/mr/2016-02-28
 */
router.get( '/dayreport/mr/:day', function (req, res) {
  var dayStr = req.params.day;
  if(dayStr === undefined || dayStr === null ||
      dayStr.length !== 10 ) {
    res.end('[]');
    return ;
  }
    pay_db.getOneDayMr(dbmanager_catchfish.getClientS(), dayStr, function(success, results){
        if(!success) {
            console.log('/data/pay/getOneDayMr, err');
            res.end('');
            return ;
        }
        res.end(JSON.stringify(results));
    });
});

module.exports = router;
