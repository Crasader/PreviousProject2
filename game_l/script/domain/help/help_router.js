var express = require('express');
var router = express.Router();

var dbmanager_catchfish = require('../../db/dbmanager_catchfish.js');
var help_db = require('./help_db.js');

/**
 * 查询最新的30条用户意见反馈
 * 114.119.39.150:1703/help/feedback
 */
router.get( '/feedback', function (req, res) {
    help_db.getLastFeedback(dbmanager_catchfish.getClientS(), function(success, results){
        if(!success) {
            console.log('/help/feedback, err : ' + err);
            res.end('[]');
            return ;
        }
        res.end(JSON.stringify(results));
    });
});

module.exports = router;
