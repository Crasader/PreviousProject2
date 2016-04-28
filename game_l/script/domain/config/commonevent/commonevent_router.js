var dbmanager_bg = require('../../../db/dbmanager_bg.js');
var commonevent_db = require('./commonevent_db.js');

var express = require('express');
var router = express.Router();

/**
 * 查询当前的签到配置信息
 * 114.119.39.150:1703/config/commonevent/current
 */
router.get( '/current', function (req, res) {
    commonevent_db.getCommonevents(dbmanager_bg.getClientS(), function(success, results){
        if(!success) {
            console.log('/config/commonevent/current, err : ');
            res.end('[]');
            return ;
        }
        res.end(JSON.stringify(results));
    });
});

module.exports = router;
