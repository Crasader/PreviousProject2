/**
 * 签到业务[sign]
 */

var express = require('express');
var router = express.Router();

var sign_logic = require('./sign_logic.js');
var session_manager = require('../../session_manager.js');

/**
 * 签到
 * sign/result
 * 测试：
 */
router.get( '/config', function (req, res) {
  res.end(sign_logic.getSignAgreementStr());
});

/**
 * 用户签到
 * 协议：sign/today
 * 测试： [POST]106.75.135.78:1701/sign/today
 */
router.post( '/today', function (req, res) {
  var session_id = req.body.session_id;
  (function(session_id){
    session_manager.isLogin(session_id, function(login, data){
      if(!login) {
        res.end(data);
        return ;
      }
      sign_logic.getSignInfo(session_id, data.user_id, data.fortune_id, function(result){
        res.end(result);
      });
    });
  })(session_id);


});

module.exports = router;
