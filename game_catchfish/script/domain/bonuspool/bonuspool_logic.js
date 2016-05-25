
var session_manager = require('../../session_manager.js');
var redishelper = require('../../mem/redishelper.js');

var config_bonuspool = require('../../../config/domain/config_bonuspool.json');
var config_gold_fish = require('../../../config/domain/config_gold_fish.json');

var SESSION_HEAD_BONUSPOOL = 'BONUSPOOL_';
var SESSION_EXPIRE_BONUSPOOL =  60*60*24*7;	// TODO : 目前写7天，上线后改为30天

var player_logic =  require('../player/player_logic.js');
var bag_logic = require('../player/bag_logic.js');

function currentstate(session_id, callback) {
  session_manager.isLogin(session_id, function(login, data) { // 查询用户是否登陆
    if(!login) {
      callback(data);
      return ;
    }
    var user_id = data.user_id;
    redishelper.getVaule(SESSION_HEAD_BONUSPOOL + user_id, function(err, redis_result) {
      if(err) {
        callback(agreement.redisErrorDesc);
        return ;
      }
      if(redis_result !== undefined && redis_result !== null ) {
        callback(redis_result);
      } else {
        var bonuspoolObj = {
          errorcode : 0,
          fish_nums : 0,
          fish_coins : 0,
          user_nums : 0
        };
        callback(JSON.stringify(bonuspoolObj));
      }
    });

  });
}

exports.currentstate = currentstate;

function catchfish(session_id, fish_id, callback) {
  (function(fish_id){
    session_manager.isLogin(session_id, function(login, data) { // 查询用户是否登陆
      if(!login) {
        callback(data);
        return ;
      }
      var fish_coins = getFishCoins(parseInt(fish_id));  // 获取鱼的奖金池价格
      if(fish_coins <= 0) { // 判断参数有效性
        var result = {
          errorcode : 860,
          errormsg : 'fish_id not gold fish!!'
        };
        callback(JSON.stringify(result));
        return ;
      }
      var user_id = data.user_id;
      ( function( fish_coins, user_id ) {
        redishelper.getVaule(SESSION_HEAD_BONUSPOOL + user_id, function(err, redis_result) {
          if(err) {
            callback(agreement.redisErrorDesc);
            return ;
          }
          if(redis_result !== undefined && redis_result !== null ) {
            var bonuspoolObj = JSON.parse(redis_result);
            bonuspoolObj.fish_nums = bonuspoolObj.fish_nums + 1;
            bonuspoolObj.fish_coins = bonuspoolObj.fish_coins + fish_coins;
          } else {
            var bonuspoolObj = {
              errorcode : 0,
              fish_nums : 1,
              fish_coins : fish_coins,
              user_nums : 0
            };
          }
          redishelper.setValueWithExpire(SESSION_HEAD_BONUSPOOL + user_id,
              JSON.stringify(bonuspoolObj), SESSION_EXPIRE_BONUSPOOL);
          callback(JSON.stringify(bonuspoolObj));
        });
      } )( fish_coins, user_id );

    });
  })(fish_id);
}

exports.catchfish = catchfish;

function turntable(session_id, callback) {
  session_manager.isLogin(session_id, function(login, data) { // 查询用户是否登陆
    if(!login) {
      callback(data);
      return ;
    }
    var user_id = data.user_id;
    var fortune_id = data.fortune_id;
    ( function( session_id, user_id, fortune_id ) {
      redishelper.getVaule(SESSION_HEAD_BONUSPOOL + user_id, function(err, redis_result) {
        if(err) {
          callback(agreement.redisErrorDesc);
          return ;
        }
        if(redis_result !== undefined && redis_result !== null) {
          var bonuspoolObj = JSON.parse(redis_result);
          if(bonuspoolObj.fish_nums >= config_bonuspool.turntable_fish_nums) {
            var resultObj = {
              errorcode : 0,
              reward_lists : getTurntableRewards(bonuspoolObj.user_nums, bonuspoolObj.fish_coins),
              user_nums : bonuspoolObj.user_nums
            };
            bonuspoolObj.fish_nums = 0;
            bonuspoolObj.fish_coins = 0;
            bonuspoolObj.user_nums = bonuspoolObj.user_nums + 1;
            redishelper.setValueWithExpire(SESSION_HEAD_BONUSPOOL + user_id,
                JSON.stringify(bonuspoolObj), SESSION_EXPIRE_BONUSPOOL);
            for(var i=0;i<resultObj.reward_lists.length;i++){
              if(resultObj.reward_lists[i].item_id === 1001) {
                syncUserCoinsAndDiamonds(session_id, user_id, fortune_id, resultObj.reward_lists[i].nums, 0);
              } else if(resultObj.reward_lists[i].item_id === 1002) {
                syncUserCoinsAndDiamonds(session_id, user_id, fortune_id, 0, resultObj.reward_lists[i].nums);
              }else {
                syncUserBagInfo(session_id, resultObj.reward_lists[i].item_id, resultObj.reward_lists[i].nums);
              }
            }
            callback(JSON.stringify(resultObj));
          }else {
            var resultObj = {
              errorcode : 862,
              errormsg : 'not enough fish nums. need more than five.'
            };
            callback(JSON.stringify(resultObj));
          }
        } else {
          var resultObj = {
            errorcode : 861,
            errormsg : 'no bonuspool info'
          };
          callback(JSON.stringify(resultObj));
        }

      });
    } )( session_id, user_id, fortune_id );
  });
}

exports.turntable = turntable;

function getFishCoins(fish_id) {
  for(var i=0;i<config_gold_fish.item_lists.length;i++) {
    if(config_gold_fish.item_lists[i].fish_id === fish_id) {
      return config_gold_fish.item_lists[i].bonus_pool_reward;
    }
  }
  return 0;
}

function getTurntableRewards(user_nums, fish_coins) {
  var reward_lists = [];
  for(var i=config_bonuspool.item_lists.length-1;i >=0;i--) {
    if(fish_coins >= config_bonuspool.item_lists[i].require_coins) {
      if( user_nums === 0 && config_bonuspool.item_lists[i].first_reward !== undefined ) {
        return config_bonuspool.item_lists[i].first_reward;
      }
      var randomnum = parseInt(100*Math.random());
      var currentNum = 0;
      for(var j=0;j<config_bonuspool.item_lists[i].reward_list.length;j++) {
        currentNum += config_bonuspool.item_lists[i].reward_list[j].per;
        if(currentNum >= randomnum) {
          var reward = {
            item_id : config_bonuspool.item_lists[i].reward_list[j].item_id,
            nums : config_bonuspool.item_lists[i].reward_list[j].num
          };
          reward_lists.push(reward);
          return reward_lists;
        }
      }
    }
  }
  return reward_lists;
}


function syncUserCoinsAndDiamonds(session_id, user_id, fortune_id, coins, diamonds) {
  var sync_info = {
    user_id : user_id,
    fortune_id : fortune_id,
    coins : coins,
    diamonds : diamonds
  };
  player_logic.syncPlayerCoinsAndDiamonds(session_id, sync_info);
}

function syncUserBagInfo(session_id, item_id, item_id) {
  bag_logic.syncUserBagInfoBySessionId(session_id, item_id, item_id, function(result){});
}
