var dbmanager_catchfish = require('../../../db/dbmanager_catchfish.js');
var sign_db = require('./sign_db.js');

var express = require('express');
var router = express.Router();

/**
 * 查询当前的签到配置信息
 * 114.119.39.150:1703/config/sign/current
 */
router.get( '/current', function (req, res) {
    sign_db.getCurrentSignInfo(dbmanager_catchfish.getClientS(), function(success, results){
        if(!success) {
            console.log('/config/sign/current, err : ' + err);
            res.end('');
            return ;
        }
        var signAgreement = JSON.parse(results);
        signAgreement.today = new Date().Format("yyyy-MM-dd");
        var signAgreementStr = JSON.stringify(signAgreement);
        console.log('/config/sign/current, result : ' + signAgreementStr);
        res.end(signAgreementStr);
    });
});

/**
 * 更新签到记录
 * 114.119.39.150:1703/config/sign/update/:newSignConfig
 */
router.get('/update/:newSignConfig', function (req,res) {
    sign_db.updateSignConfig(dbmanager_catchfish.getClient(), req.params.newSignConfig, function(err, results){
        if(err) {
            console.log('/config/sign/update/:newSignConfig, err : ' + err);
            res.end('{result : 1}');
            return ;
        }
        console.log('/config/sign/update/:newSignConfig, result : ' + JSON.stringify(results));
        res.end('{result : 0}');
    });
});

module.exports = router;
