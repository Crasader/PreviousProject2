'use strict';
/**
 * 活动逻辑
 */

var dbmanager = require('../../db/dbmanager.js');
var session_manager = require('../../session_manager.js');
var mailbox_db = require('./mailbox_db.js');
var player_info_service = require('../player/player_info_service.js');


/**
 * 查询用户的站内信信息
 */
function getPlayerMailInfo(session_id, callback) {
  session_manager.isLogin(session_id, function(login, data){
    if(!login) {
      callback(data);
      return ;
    }
    var user_info = data;
    mailbox_db.getPlayerMailInfo(dbmanager.getClientS(), user_info.user_id, function(success, result){
      var c_result = {
        errorcode : 0,
        mail_lists : []
      }
      if(success && result.length > 0) {
        for(var i=0;i<result.length;i++) {
          var item = {
            mailbox_id : result[i]['id'],
            title : result[i]['title'],
            content_desc : result[i]['content_desc'],
            reward_lists : JSON.parse(result[i]['reward_lists']),
            create_time : result[i]['create_time']
          }
          c_result.mail_lists.push(item);
        }
      }
      callback(JSON.stringify(c_result));
    });

  });
}

exports.getPlayerMailInfo = getPlayerMailInfo;

/**
 * 领取用户站内信的奖励
 */
function getPlayerMailboxRewardsById(session_id, mailbox_id, callback) {
  session_manager.isLogin(session_id, function(login, data){
    if(!login) {
      callback(data);
      return ;
    }
    var user_info = data;
    mailbox_db.getPlayerMailboxRewardsById(dbmanager.getClientS(), user_info.user_id, mailbox_id, function(success, result){
      if(success && result.length > 0) {
        var reward_lists = JSON.parse(result[0]['reward_lists']);
        if(reward_lists.length > 0) { // 计算是否有可领取的物品信息
          console.log('reward_lists : ' + result[0]['reward_lists']);
          mailbox_db.updatePlayerMailboxStateById(dbmanager.getClient(), mailbox_id, function(success, result){});// 删除记录
          player_info_service.syncRewardsInfo(reward_lists, user_info);// 根据奖励列表,同步信息
          var c_result = {
            errorcode : 0,
            reward_lists : reward_lists
          }
          callback(JSON.stringify(c_result));
        } else {
          mailbox_db.updatePlayerMailboxStateById(dbmanager.getClient(), mailbox_id, function(success, result){});// 删除记录
          var c_result = {
            errorcode : 0,
            reward_lists : []
          }
          callback(JSON.stringify(c_result));
        }
      } else {
        var c_result = {
          errorcode : 2301,
          errormsg : '没有可领取的物品信息'
        }
        callback(JSON.stringify(c_result));
      }
    });
  });
}

exports.getPlayerMailboxRewardsById = getPlayerMailboxRewardsById;

/**
 * 批量领取用户站内信的奖励
 */
function getPlayerAllMailboxRewardsById(session_id, callback) {
  session_manager.isLogin(session_id, function(login, data){
    if(!login) {
      callback(data);
      return ;
    }
    var user_info = data;
    (function(user_info){
      mailbox_db.getPlayerMailInfo(dbmanager.getClientS(), user_info.user_id, function(success, result){
        if(success && result.length > 0) {
          var reward_lists = [];
          if(result.length > 0) { // 计算是否有可领取的物品信息
            for(var i=0;i<result.length;i++) {
              var item = JSON.parse(result[i]['reward_lists']);
              for(var j=0;j<item.length;j++) {
                reward_lists.push(item[j]);
              }

              mailbox_db.updatePlayerMailboxStateById(dbmanager.getClient(), result[i]['id'], function(success, result){});// 删除记录
            }
            player_info_service.syncRewardsInfo(reward_lists, user_info); //根据奖励列表,同步信息
            var c_result = {
              errorcode : 0,
              reward_lists : reward_lists
            }
            callback(JSON.stringify(c_result));
          } else {
            var c_result = {
              errorcode : 2301,
              errormsg : '没有可领取的物品信息'
            }
            callback(JSON.stringify(c_result));
          }
        } else {
          var c_result = {
            errorcode : 2301,
            errormsg : '没有可领取的物品信息'
          }
          callback(JSON.stringify(c_result));
        }
      });
    })(user_info);

  });
}

exports.getPlayerAllMailboxRewardsById = getPlayerAllMailboxRewardsById;

/**
 * 查询玩家的好友进阶奖励
 */
function getPlayerFriendRewardById(session_id, callback) {
  session_manager.isLogin(session_id, function(login, data){
    if(!login) {
      callback(data);
      return ;
    }
    var user_info = data;
    mailbox_db.getPlayerFriendRewardById(dbmanager.getClientS(), user_info.user_id, function(success, result){
      var c_result = {
        errorcode : 0,
        mail_lists : []
      }
      if(success && result.length > 0) {
        for(var i=0;i<result.length;i++) {
          var item = {
            mailbox_id : result[i]['id'],
            title : result[i]['title'],
            content_desc : result[i]['content_desc'],
            reward_lists : JSON.parse(result[i]['reward_lists']),
            create_time : result[i]['create_time']
          }
          c_result.mail_lists.push(item);
        }
      }
      callback(JSON.stringify(c_result));
    });

  });
}

exports.getPlayerFriendRewardById = getPlayerFriendRewardById;
