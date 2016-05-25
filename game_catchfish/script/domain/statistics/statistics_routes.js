/**
 * 签到业务[sign]
 */

var express = require('express');
var router = express.Router();

var session_manager = require('../../session_manager.js');

var statistics_logic = require('./statistics_logic.js');

var agreement = require('../../agreement.js');

// TODO : 调试接口
router.get( '/test', function (req, res) {
  // type = 10,消耗统计
  // data.turrent_level, data.update_times
  var dataObj = {
    data_type : 10,
    lists : []
  };

  dataObj.lists[0] = {
    coin_get : 100,
    coin_use : 50,
    diamond_get : 2,
    diamond_use : 1
  };

  // dataObj.lists[1] = {
  //   t_type : 2,
  //   p_type_1 : 0,
  //   p_type_2 : 1,
  //   p_type_3 : 0,
  //   p_type_4 : 0,
  //   p_type_5 : 0,
  //   p_type_6 : 0
  // };
  // console.log('JSON.stringify(dataObj) : ' + JSON.stringify(dataObj));
  statistics_logic.insertOneUserData('201', JSON.stringify(dataObj), function(result){
    res.end(result);
  });
});

var MARK_GAME_VERSION = 7;  // TODO  :后期最好改为全局配置

/**
 * 测试入库一笔订单记录
 * 协议：statistics/data
 * 测试：
 */
router.post( '/data', function (req, res) {
  var data_str = req.body.data_str;
  var session_id = req.body.session_id;
  var game_version = req.body.game_version;
  if(game_version === undefined || game_version === null ||
      parseInt(game_version) != MARK_GAME_VERSION) {
    res.end(agreement.reqVersionErrorDesc);
  }

  (function(data_str){
    session_manager.isLogin(session_id, function(login, user_info){
  		if(!login) {
  			res.end(user_info);
  			return ;
  		}
      // console.log('data_str : ' + data_str);
      statistics_logic.insertOneUserData(user_info.user_id, data_str, function(result){
        res.end(result);
      });
    });
  })(data_str);
});

module.exports = router;
