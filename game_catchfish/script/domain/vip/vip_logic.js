'use strict';

var redishelper = require('../../mem/redishelper.js');
var session_manager = require('../../session_manager.js');
var player_logic =  require('../player/player_logic.js');
var noderice = require('noderice');

var VIP_REDIS_HEAD = 'VIP_REDIS_HEAD_';

var default_require_more_vip_level_str = JSON.stringify({
  errorcode : 1501,
  errormsg : '需要更高等级的vip才能领取'
});

var default_reward_str = JSON.stringify({
  errorcode : 1502,
  errormsg : '今日已经领取过VIP金币奖励,请明天再来.'
});

/**
 * 获取玩家的VIP奖励信息
 */
function getVipRewards(session_id, callback){
  (function(session_id){
    session_manager.isLogin(session_id, function(login, data){
      if(!login) {
        res.end(data);
        return ;
      }
      var user_info = data;
      if(user_info.mo >= 1000000 ) { // 满足可以领取的条件
        var r_key = VIP_REDIS_HEAD + noderice.GetDateNum(0) + user_info.user_id;
        (function(user_info, r_key){
          redishelper.getVaule(r_key, function(err, redis_result) { // 查询缓存中是否有今天的领取记录
            if(err) {
              var err_to_c = {
                errorcode : 500,
                errormsg : 'read redis error'
              }
              callback(JSON.stringify(err_to_c));
              return ;
            }
            if(redis_result === undefined || redis_result === null) { // 没领过
              redishelper.setValueWithExpire(r_key, 1, redishelper.getCurrentDayLeftSeconds());
              syncUserCoinsAndDiamonds(user_info.session_id, user_info.user_id, user_info.fortune_id, user_info.mo); // 更新用户奖励
              callback(JSON.stringify({
                errorcode : 0,
                coins : getCoinsByMo(user_info.mo)
              }));
              return ;
            } else {  // 领过了
              callback(default_reward_str);
            }
          });
        })(user_info, r_key);
      }else {
        callback(default_require_more_vip_level_str);
      }
    });
  })(session_id);
}

exports.getVipRewards = getVipRewards;

function syncUserCoinsAndDiamonds(session_id, user_id, fortune_id, mo) {
  var sync_info = {
    user_id : user_id,
    fortune_id : fortune_id,
    coins : getCoinsByMo(mo),
    diamonds : 0
  };
  player_logic.syncPlayerCoinsAndDiamonds(session_id, sync_info);
}

function getCoinsByMo(mo) {
  if(mo < 1000000) {
    return 0;
  } else if(mo < 2000000) { // 1W ~ 2W之间。
    return 500000;
  }else if(mo < 5000000) { // 2W ~ 5W之间。
    return 1000000;
  }else { //// 大于5W
    return 2000000;
  }
}
