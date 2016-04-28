'use strict';
/**
 * 赠送数据库工具接口
 */

//------------------------------------------------------------------------------
// 公开方法

/**
 * 查询某个用户是否有设置过昵称
 */
function isRegisterUser(client, hongbao_user_id, callback) {
  client.query('SELECT nick_name FROM nick_name_1 WHERE user_id = ? ',
	   [hongbao_user_id],
     function (err, results) {
       if (err) {
            console.log('[ERROR!!]hongbao_db->isRegisterUser, msg : ' + err);
            callback(false);
            return;
        }
        if(results != undefined && results != null && results.length > 0) {
        	callback(true, results[0]['nick_name']);
        }else {
					callback(false);
				}
    });
}

exports.isRegisterUser = isRegisterUser;

/**
 * 查询某个用户是否有过红包领取记录
 */
function hasGetHongbao(client, user_id, callback) {
  client.query('SELECT create_time FROM hongbao_mark WHERE user_id = ? ',
	   [user_id],
     function (err, results) {
       if (err) {
            console.log('[ERROR!!]hongbao_db->hasGetHongbao, msg : ' + err);
            callback(false);
            return;
        }
        if(results != undefined && results != null && results.length > 0) {
        	callback(true, results[0]['create_time']);
        }else {
					callback(false);
				}
    });
}

exports.hasGetHongbao = hasGetHongbao;




function setUserGetHongbao(client, hongbao_user_id, user_id, callback) {
  client.query('INSERT INTO hongbao_mark SET user_id = ?, hongbao_user_id = ?, create_time = ? ',
	   [user_id, hongbao_user_id, new Date().Format("yyyyMMdd")],
     function (err, results) {
       if (err) {
         console.log('[ERROR!!]hongbao_db->setUserGetHongbao, msg : ' + err);
         callback(false);
         return;
        }
        callback(true);
    });
}

exports.setUserGetHongbao = setUserGetHongbao;

//------------------------------------------------------------------------------
// 内部方法


//--------------------------------------------------------------------------------
// 工具方法
