
var dbmanager = require('../../db/dbmanager.js');
var player_db = require('./player_db.js');
var session_manager = require('../../session_manager.js');
var redishelper = require('../../mem/redishelper.js');
var config_buy_item = require('../../../config/domain/config_buy_item.json');
var agreement = require('../../agreement.js');
var player_logic = require('./player_logic.js');

/**
 * 批量更新背包信息
 */
function addBagItems(session_id, item_lists, callback) {
  if(item_lists.length <= 0) {
    callback(false);
    return ;
  }
  (function(session_id, item_lists){
    session_manager.isLogin(session_id, function(login, data) {
      if(!login) {
        callback(data);
        return ;
      }
      var user_id = data.user_id;
      (function(user_id){
        redishelper.getVaule('BG_' + session_id, function(err, redis_result) {
      		if(err) {
      			callback(false);
      			return ;
      		}
      		if(redis_result != undefined) {
      			var bagInfoObj = JSON.parse(redis_result);
            for(var j=0; j<item_lists.length;j++) {
              if(item_lists[j].item_id != 1001 && item_lists[j].item_id != 1002 && item_lists[j].item_id != 1000) {
                bagInfoObj = getNewBagInfoObj(user_id, session_id, bagInfoObj, item_lists[j].item_id, item_lists[j].nums);
              }
            }
            callback(true);
      		}else {
            callback(false);
          }
      	});
      })(user_id);

    });
  })(session_id, item_lists);
}

exports.addBagItems = addBagItems;

function getNewBagInfoObj(user_id, session_id, bagInfoObj, item_id, nums) {
  if(nums > 0) {
    for(var i=0;i<bagInfoObj.item_lists.length;i++) {
      if(bagInfoObj.item_lists[i].item_id === item_id) {
        bagInfoObj.item_lists[i].nums = bagInfoObj.item_lists[i].nums === null ? parseInt(nums) : parseInt(bagInfoObj.item_lists[i].nums) + parseInt(nums);
        syncPlayerBagInfoByDB(user_id, session_id, item_id, bagInfoObj.item_lists[i].nums, bagInfoObj);
        return bagInfoObj;
      }
    }
    bagInfoObj.item_lists.push({
      item_id : item_id,
      nums : nums
    });
    syncPlayerBagInfoByDB(user_id, session_id, item_id, nums, bagInfoObj);
    return bagInfoObj;
  }else if(nums < 0) {
    for(var i=0; i<bagInfoObj.item_lists.length; i++) {
      if( bagInfoObj.item_lists[i].item_id === item_id ) {
        if(bagInfoObj.item_lists[i].nums >= Math.abs(nums)) {
          bagInfoObj.item_lists[i].nums = bagInfoObj.item_lists[i].nums + nums;
        }else {
          bagInfoObj.item_lists[i].nums = 0;
        }
        syncPlayerBagInfoByDB(user_id, session_id, item_id, bagInfoObj.item_lists[i].nums, bagInfoObj);
        return bagInfoObj;
      }
    }
  }
  return bagInfoObj;
}

function syncUserBagInfoBySessionId(session_id, item_id, nums, callback) {
  (function(session_id, item_id, nums){
    session_manager.isLogin(session_id, function(login, data) {
      if(!login) {
        callback(data);
        return ;
      }
      var user_id = data.user_id;
      (function(user_id){
        redishelper.getVaule('BG_' + session_id, function(err, redis_result) {
      		if(err) {
      			callback(agreement.redisErrorDesc);
      			return ;
      		}

      		if(redis_result != undefined) {
      			var bgInfoObj = JSON.parse(redis_result);
            if(nums > 0) {
              for(var i=0; i<bgInfoObj.item_lists.length; i++) {
                console.log(JSON.stringify(bgInfoObj.item_lists[i]));
                if(bgInfoObj.item_lists[i].item_id === item_id) {
                  bgInfoObj.item_lists[i].nums = bgInfoObj.item_lists[i].nums === null ? nums : bgInfoObj.item_lists[i].nums + nums;
                  syncPlayerBagInfoByDB(user_id, session_id, item_id, bgInfoObj.item_lists[i].nums, bgInfoObj);
                  callback(agreement.successDesc);
                  return ;
                }
              }
              bgInfoObj.item_lists.push({
                item_id : item_id,
                nums : nums
              });
              syncPlayerBagInfoByDB(user_id, session_id, item_id, nums, bgInfoObj);
              callback(agreement.successDesc);
              return ;
            }else if(nums <= 0) {
              for(var i=0; i<bgInfoObj.item_lists.length; i++) {
                if( bgInfoObj.item_lists[i].item_id === item_id && bgInfoObj.item_lists[i].nums >= Math.abs(nums) ) {
                  bgInfoObj.item_lists[i].nums = bgInfoObj.item_lists[i].nums + nums;
                  syncPlayerBagInfoByDB(user_id, session_id, item_id, bgInfoObj.item_lists[i].nums, bgInfoObj);
                  callback(agreement.successDesc);
                  return ;
                }
              }
              callback(agreement.noEnoughItemsDesc); // 没有足够的道具，不能使用
              return ;
            }
            callback(agreement.noEnoughItemsDesc); // 没有足够的道具，不能使用
            return ;
      		}
      		callback(agreement.invalidSessionIdDesc);
      	});
      })(user_id);

    });
  })(session_id, item_id, nums);
}

exports.syncUserBagInfoBySessionId = syncUserBagInfoBySessionId;

function syncPlayerBagInfoByDB(user_id, session_id, item_id, nums, bgInfoObj) {
  redishelper.setValueWithExpire('BG_' + session_id, JSON.stringify(bgInfoObj), session_manager.SESSION_EXPIRE);
  var sync_info = {
    user_id : user_id,
    item_id : item_id,
    nums : nums
  };
  console.log('[syncPlayerBagInfoByDB] sync_info : ' + JSON.stringify(sync_info));
  syncPlayerBgInfo(sync_info);
}

function syncPlayerBgInfo(sync_info) {
  player_db.syncPlayerBgInfo(dbmanager.getClient(), sync_info, function(result) {
    if(!result) {
      console.log('fail sync player bag fortune info');
    }
  });
}

exports.syncPlayerBgInfo = syncPlayerBgInfo;

function buyItemBySessionId(session_id, item_id, callback) {


  if(!allowByItemId(item_id)) { // 判断item_id是否可以购买
    callback(agreement.notAllowBuyItemsDesc);
    return ;
  }

  (function(session_id, item_id){
    session_manager.isLogin(session_id, function(login, data) { // 查询用户是否登陆
      if(!login) {
        callback(data);
        return ;
      }
      var buyInfo = getItemBuyInfo(item_id);
      if(buyInfo === null) {
        callback(agreement.notAllowBuyItemsDesc);
        return ;
      }
      if( data.diamonds >= buyInfo.buy_price ) {
        data.diamonds = data.diamonds - buyInfo.buy_price;  // 扣钻石
        syncUserInfo(data); // 同步用户信息
        syncUserBagInfoBySessionId(session_id, item_id, buyInfo.nums, function(result){}); // 同步背包信息

        var client_result = {
          errorcode : 0,
          diamonds_price : buyInfo.buy_price,
          buy_nums : buyInfo.nums

        };
        callback(JSON.stringify(client_result));
      }else {
        callback(agreement.noEnoughDiamondsDesc); // 钻石不足
        return ;
      }

    });
  })(session_id, item_id);
}

exports.buyItemBySessionId = buyItemBySessionId;

function syncUserInfo(data) {
  redishelper.setValueWithExpire(data.session_id, JSON.stringify(data), session_manager.SESSION_EXPIRE);

  var sync_info = {
    user_id : data.user_id,
    fortune_id : data.fortune_id,
    coins : data.coins,
    diamonds : data.diamonds,
    exp : data.exp,
    turrent_level : data.turrent_level
  };
  player_logic.syncPlayerBaseFortuneInfo(sync_info);
}

function allowByItemId(item_id) {
  var item_num = parseInt(item_id);
  if( item_id >= 1003 && item_id <= 1007 ) {  // TODO : 目前没有走配置
    return true;
  }
  return false;
}

function getItemBuyInfo(ietm_id) {
  for(var i=0; i<config_buy_item.item_list.length; i++) {
    if(config_buy_item.item_list[i].item_id === ietm_id) {
      var buyInfo = {
        buy_price : config_buy_item.item_list[i].buy_price,
        nums : config_buy_item.item_list[i].buy_nums
      };
      return buyInfo;
    }
  }
  return null;
}

function getBagInfoBySessionId(session_id) {
  redishelper.getVaule('BG_' + session_id, function(err, redis_result) {
    if(err) {
      callback(agreement.redisErrorDesc);
      return ;
    }
    if(redis_result !== undefined) {
      callback(redis_result);
    } else {
      var clientResult = {
        errorcode : 0,
        item_lists : []
      };
      callback(JSON.stringify(redis_result));
    }
  });
}

exports.getBagInfoBySessionId = getBagInfoBySessionId;
