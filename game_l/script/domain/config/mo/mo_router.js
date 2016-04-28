var dbmanager_bg = require('../../../db/dbmanager_bg.js');
var mo_db = require('./mo_db.js');

var express = require('express');
var router = express.Router();

/**
 * 查询当前的签到配置信息
 * 114.119.39.150:1703/config/mo/paypoint
 */
router.get( '/paypoint', function (req, res) {
    mo_db.getPaypoint(dbmanager_bg.getClientS(), function(success, results){
        if(!success) {
            console.log('/config/mo/paypoint, err : ');
            res.end('');
            return ;
        }
        res.end(JSON.stringify(results));
    });
});

/**
 * 查询当前的签到配置信息
 * 114.119.39.150:1703/config/mo/payevent
 */
router.get( '/payevent', function (req, res) {
    mo_db.getPayevent(dbmanager_bg.getClientS(), function(success, results){
        if(!success) {
            console.log('/config/mo/paypoint, err : ' + err);
            res.end('');
            return ;
        }
        res.end(JSON.stringify(results));
    });
});



module.exports = router;
