var dbmanager_bg = require('../../db/dbmanager_bg.js');
var user_db = require('./user_db.js');

var express = require('express');
var router = express.Router();

/**
 * 查询某个用户名下的信息
 * 114.119.39.150:1703/user/login/:username
 */
router.get( '/login/:username', function (req, res) {
    console.log('/user/login/:username, username : ' + req.params.username);
    user_db.getUserInfo(dbmanager_bg.getClientS(), req.params.username, function(err, results){
        if(err) {
            console.log('/user/login/:username, err : ' + err);
            res.end('');
            return ;
        }
        console.log('/user/login/:username, result : ' + JSON.stringify(results));
        res.end(JSON.stringify(results));
    });
});

/**
 * 填写入新的用户名和密码[申请]
 * 114.119.39.150:1703/user/register/:username/:username/:passwd/:salt/:reqinfo
 */
router.get('/register/:username/:passwd/:salt/:reqinfo', function (req,res) {
    user_db.reqNewUserInfo(dbmanager_bg.getClient(), req.params.username, req.params.passwd,
            req.params.salt, req.params.reqinfo, function(err, results){
        if(err) {
            console.log('/user/register/:username, err : ' + err);
            res.end('{result : 1}');
            return ;
        }
        console.log('/user/register/:username, result : ' + JSON.stringify(results));
        res.end('{result : 0}');
    });
});

module.exports = router;
