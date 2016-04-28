/**
 * 签贵族业务[nobility]
 */

var express = require('express');
var router = express.Router();

var session_manager = require('../../session_manager.js');
var nobility_logic = require('./nobility_logic.js');

/**
 * 查询贵族剩余天数
 * nobility/surplus[POST]
 * 参数：session_id
 */
router.post( '/surplus', function (req, res) {
  var session_id = req.body.session_id;
  session_manager.isLogin(session_id, function(login, data){
    if(!login) {
      res.end(data);
      return ;
    }

    nobility_logic.getSurplusDay(data.user_id, function(result){
      res.end(result);
    });
  });
});

/**
 * 查询贵族可领取奖励
 * nobility/today/reward[POST]
 * 参数：session_id
 */
router.post( '/today/reward', function (req, res) {
  var session_id = req.body.session_id;

  (function(session_id){
    session_manager.isLogin(session_id, function(login, data){
      if(!login) {
        res.end(data);
        return ;
      }
      nobility_logic.getRewardDay(session_id, data.user_id, data.fortune_id ,function(result){
        res.end(result);
      });
    });
  })(session_id);

});


module.exports = router;
