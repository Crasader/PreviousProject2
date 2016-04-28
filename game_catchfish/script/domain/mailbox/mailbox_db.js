'use strict';
/**
 * 站内信数据库工具接口
 */

//------------------------------------------------------------------------------
// 公开方法

/**
 * 查询玩家的邮箱信息-只查询未读信息
 */
function getPlayerMailInfo(client, user_id, callback) {
  client.query('SELECT * FROM mailbox WHERE user_id = ? AND msg_state = 0',// [msg_state = 0]代表未读
	   [user_id],
     function (err, results) {
       if (err) {
            console.log('[ERROR!!]mailbox_db->getPlayerMailInfo, msg : ' + err);
            callback(false, err);
            return;
        }
        if(results != undefined && results != null && results.length > 0) {
        	callback(true, results);
        }else {
					callback(false, results);
				}
    });
}

exports.getPlayerMailInfo = getPlayerMailInfo;

/**
 * 查询玩家的邮箱信息-单条[未读]
 */
function getPlayerMailboxRewardsById(client, user_id, mailbox_id, callback) {
  client.query('SELECT * FROM mailbox WHERE user_id = ? AND id = ? AND msg_state = 0',// [msg_state = 0]代表未读
	   [user_id, mailbox_id],
     function (err, results) {
       if (err) {
            console.log('[ERROR!!]mailbox_db->getPlayerMailInfo, msg : ' + err);
            callback(false, err);
            return;
        }
        if(results != undefined && results != null && results.length > 0) {
        	callback(true, results);
        }else {
					callback(false, results);
				}
    });
}

exports.getPlayerMailboxRewardsById = getPlayerMailboxRewardsById;

/**
 * 更新玩家的邮箱信息状态为已读
 */
function updatePlayerMailboxStateById(client, mailbox_id, callback) {
  client.query('UPDATE mailbox SET msg_state = 1 WHERE id = ?',
	   [mailbox_id],
     function (err, results) {
       if (err) {
            console.log('[ERROR!!]mailbox_db->updatePlayerMailboxStateById, msg : ' + err);
            callback(false, err);
            return;
        }
        callback(true, results);
    });
}

exports.updatePlayerMailboxStateById = updatePlayerMailboxStateById;

/**
 * 查询玩家的好友进阶奖励
 */
function getPlayerFriendRewardById(client, user_id, callback) {
  client.query('SELECT * FROM mailbox WHERE user_id = ? AND msg_type = 1',// [msg_type = 1]代表好友进阶奖励
	   [user_id],
     function (err, results) {
       if (err) {
            console.log('[ERROR!!]mailbox_db->getPlayerFriendRewardById, msg : ' + err);
            callback(false, err);
            return;
        }
        if(results != undefined && results != null && results.length > 0) {
          callback(true, results);
        }else {
          callback(false, results);
        }
      }
  );
}

exports.getPlayerFriendRewardById = getPlayerFriendRewardById;

//------------------------------------------------------------------------------
// 内部方法


//--------------------------------------------------------------------------------
// 工具方法
