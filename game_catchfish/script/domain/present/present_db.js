'use strict';
/**
 * 红包数据库工具接口
 */

//------------------------------------------------------------------------------
// 公开方法

/**
 * 查询某个用户昵称是否存在
 */
function isNickNameExist(client, nick_name, callback) {
  client.query('SELECT user_id FROM nick_name_1 WHERE nick_name = ? ',
	   [nick_name],
     function (err, results) {
       if (err) {
            console.log('[ERROR!!]present_db->isNickNameExist, msg : ' + err);
            callback(false);
            return;
        }
        if(results != undefined && results != null && results.length > 0) {
        	callback(true, results[0]['user_id']);
        }else {
					callback(false);
				}
    });
}

exports.isNickNameExist = isNickNameExist;

function addNewPresent(client, send_user_id, title, content_desc, reward_lists, callback) {
  client.query('INSERT INTO mailbox SET user_id = ?, title = ?, content_desc = ?, reward_lists = ?, create_time = ? ',
	   [send_user_id, title, content_desc, reward_lists, new Date().Format("yyyyMMdd")],
     function (err, results) {
       if (err) {
            console.log('[ERROR!!]present_db->addNewPresent, msg : ' + err);
            callback(false);
            return;
        }
        callback(true);
    });
}

exports.addNewPresent = addNewPresent;

//------------------------------------------------------------------------------
// 内部方法


//--------------------------------------------------------------------------------
// 工具方法
