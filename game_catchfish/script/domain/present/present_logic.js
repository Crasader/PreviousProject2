'use strict';
/**
 * 赠送逻辑
 */

var dbmanager = require('../../db/dbmanager.js');
var present_db = require('./present_db.js');
var player_info_service = require('../player/player_info_service.js');
var bag_logic = require('../player/bag_logic.js');
var agreement = require('../../agreement.js');
var session_manager = require('../../session_manager.js');
var config_buy_item = require('../../../config/domain/config_buy_item.json');
var redishelper = require('../../mem/redishelper.js');


/**
 * 赠送逻辑
 */
function give(session_id, nick_name, item_id, callback) {
  var item_id = parseInt(item_id);
  if(!isAllowItemId(item_id)){ // 判断item_id是否为允许的
    callback(agreement.reqParamsErrorDesc);
    return ;
  }
  // TODO  :判断nick_name是否合法[暂时不判断不影响业务逻辑正确性]
  (function(session_id, item_id, nick_name){
    present_db.isNickNameExist(dbmanager.getClientS(), nick_name, function(success, user_id){ // 判断对方昵称是否存在
      if(!success) {
        var c_result = {
          errorcode : 2402,
          errormsg : '您输入的好友不存在,无法赠送'
        }
        callback(JSON.stringify(c_result));
        return ;
      }
      var send_user_id = user_id;
      (function(send_user_id){
        session_manager.isLogin(session_id, function(login, data) {
          if(!login) {
            callback(data);
            return ;
          }
          var user_info = data;
          if(user_info.user_id === send_user_id) {
            var c_result = {
              errorcode : 2403,
              errormsg : '不能向自己赠送礼物!'
            }
            callback(JSON.stringify(c_result));
            return ;
          }
          (function(user_info){
            redishelper.getVaule('BG_' + session_id, function(err, redis_result) { // 查询背包数量是否足够
              if(err) {
                callback(agreement.redisErrorDesc);
                return ;
              }
              if(redis_result != undefined) { // 获取用户背包中宝箱的数目
                var bagInfoObj = JSON.parse(redis_result);
                var requireNums = getRequireNums(item_id);
                for(var i=0; i<bagInfoObj.item_lists.length; i++) {
                  if(item_id === parseInt(bagInfoObj.item_lists[i].item_id)) {
                    if( requireNums <= parseInt(bagInfoObj.item_lists[i].nums) ) {
                      var reward_lists = [{
                        item_id : item_id,
                        nums : -1*requireNums
                      }];
                      bag_logic.addBagItems(session_id, reward_lists, function(result){});// 更新道具数量
                      var send_reward_lists = [{
                        item_id : item_id,
                        nums : requireNums
                      }];
                      var title = '玩家赠送';
                      var content_desc = '您的好友' + user_info.nick_name + '赠送给您' + getItemName(item_id) + '道具' + requireNums + '个.';
                      present_db.addNewPresent(dbmanager.getClient(), send_user_id,
                        title, content_desc, JSON.stringify(send_reward_lists), function(success){}); // 添加赠送记录[db]

                      var c_result = {
                        errorcode : 0,
                        item_id : item_id,
                        nums : requireNums
                      }
                      callback(JSON.stringify(c_result));
                      return ;
                    }else {
                      var c_result = {
                        errorcode : 2401,
                        errormsg : '道具数量不足,不能赠送'
                      }
                      callback(JSON.stringify(c_result));
                      return ;
                    }
                  }
                }
              }
              var c_result = {
                errorcode : 2401,
                errormsg : '道具数量不足,不能赠送'
              }
              callback(JSON.stringify(c_result));
            });
          })(user_info);
        });

      })(send_user_id);


    });

  })(session_id, item_id, nick_name);

}

exports.give = give;

function isAllowItemId(item_id){
  if(item_id >= 1003 && item_id <= 1007){
    return true;
  }
  if(item_id >= 1009 && item_id <= 1011){
    return true;
  }
  return false;
}

/**
 * 读取赠送数量(同时也为赠送的要求最低数目)
 */
function getRequireNums(item_id){
  if(item_id >= 1003 && item_id <= 1007){
    for(var i=0;i<config_buy_item.item_list.length;i++) {
      if(item_id === config_buy_item.item_list[i].item_id) {
        return config_buy_item.item_list[i].buy_nums;
      }
    }
  }
  return 1;
}

function getItemName(item_id) {
  if(item_id === 1003) {
    return '冰冻';
  } else if(item_id === 1004) {
    return '锁定';
  }else if(item_id === 1005) {
    return '召唤';
  }else if(item_id === 1006) {
    return '核弹';
  }else if(item_id === 1007) {
    return '激光';
  }else if(item_id === 1009) {
    return '青铜宝箱';
  }else if(item_id === 1010) {
    return '白银宝箱';
  }else if(item_id === 1011) {
    return '黄金宝箱';
  }
  return item_id;
}
