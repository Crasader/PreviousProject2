'use strict';
/**
 * 红包逻辑
 */

var dbmanager = require('../../db/dbmanager.js');
var hongbao_db = require('./hongbao_db.js');
var bag_logic = require('../player/bag_logic.js');
var agreement = require('../../agreement.js');
var session_manager = require('../../session_manager.js');
var redishelper = require('../../mem/redishelper.js');

var HONGBAO_S_V = 21854; // 2016-04-20 大家xjb讨论的时候随后说的一个数字，就用了

var default_reward_lists = [
  {item_id : 1013, nums : 50}
];

/**
 * 领取红包奖励
 */
function get(session_id, hongbao_id, callback) {
  if(isNaN(hongbao_id) && parseInt(hongbao_id) > HONGBAO_S_V){
    callback(agreement.reqParamsErrorDesc);
    return ;
  }
  hongbao_id = parseInt(hongbao_id);

  var hongbao_user_id = (hongbao_id - HONGBAO_S_V);
  (function(session_id, hongbao_user_id){
    hongbao_db.isRegisterUser(dbmanager.getClientS(), hongbao_user_id, function(result) { // STEP1 : 查询红包id是否为注册用户
      if(!result) {
        var c_client = {
          errorcode : 2501,
          errormsg : '无效的注册码'
        }
        callback(JSON.stringify(c_client));
        return ;
      }

      session_manager.isLogin(session_id, function(login, data){
        if(!login) {
          callback(data);
          return ;
        }
        var user_info = data;
        (function(user_info){
          hongbao_db.hasGetHongbao(dbmanager.getClientS(), user_info.user_id, function(result){ // STEP2 : 查询玩家是否有过领取记录
            if(result){
              var c_client = {
                errorcode : 2502,
                errormsg : '每位玩家只能领取一次红包奖励,不能重复领取.'
              }
              callback(JSON.stringify(c_client));
              return ;
            }

            var c_client = {
              errorcode : 0,
              reward_lists : default_reward_lists
            }
            callback(JSON.stringify(c_client)); // STEP3 : 领取
            bag_logic.addBagItems(session_id, default_reward_lists, function(result){});// STEP4 : 更新道具数量

            hongbao_db.setUserGetHongbao(dbmanager.getClientS(), hongbao_user_id, user_info.user_id,
                function(result){}); // STEP5 : 记录玩家的领取信息
            // TODO STEP6 : 设置玩家的推荐人为XX[暂未实现]
          });
        })(user_info);

      });
    });
  })(session_id, hongbao_user_id);
}

exports.get = get;

/**
 * 领取红包奖励
 */
function getShareinfo(session_id, callback) {
  session_manager.isLogin(session_id, function(login, data){
    if(!login) {
      callback(data);
      return ;
    }
    var user_info = data;
    var hongbao_key = parseInt(user_info.user_id) + HONGBAO_S_V;
    var c_client = {
      errorcode : 0,
      hongbao_key : hongbao_key,
      title : '赚话费捕鱼 街机千炮新玩法 百万红包等你拿',
      content : user_info.nick_name + '喊你一起来捕鱼,送你5元话费!',
      share_url : 'http://106.75.141.82:1701/share?share_key=' + hongbao_key,
    }
    callback(JSON.stringify(c_client));
  });
}

exports.getShareinfo = getShareinfo;
