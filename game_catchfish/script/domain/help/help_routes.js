
var express = require('express');
var router = express.Router();

var session_manager = require('../../session_manager.js');
var help_logic = require('./help_logic.js');

/**
 * 记录一次用户反馈信息
 * 协议：help/feedback
 * 测试：
 */
router.post('/feedback', function (req, res) {
  if(req.body.session_id === undefined || req.body.info === undefined ||
      req.body.info.length > 140) {
		res.end(agreement.reqParamsErrorDesc);
		return ;
	}
  var session_id = req.body.session_id;
  var info = req.body.info;
  (function(info){
    session_manager.isLogin(session_id, function(login, data){
      help_logic.insertOneFeedBack(data.user_id, info, new Date().Format("yyyy-MM-dd hh:mm:ss:S"), function(result){
        res.end(result);
      });
    });
  })(info);


});


module.exports = router;
