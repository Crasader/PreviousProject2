/**
 * 获取配置文件
 */

var express = require('express');
var router = express.Router();

/**
 * 获取配置文件
 * 协议：config/get/base
 */
router.post( '/get/base/', function (req, res) {
  var config_version = parseInt(req.body.config_version);
  if(config_version < 1) {
    var test = {
      errorcode : 0,
      errormsg : '',
      config_version : 2,
      catch_per : 1.0,
      bullet_speed : 700,
      bullet_interval : 0.15
    };
    res.end(JSON.stringify(test));
    return ;
  }
  var notNeedUpdate = {
    errorcode : 601,
    errormsg : 'not need update'
  };
  res.end(JSON.stringify(notNeedUpdate));
});

module.exports = router;
