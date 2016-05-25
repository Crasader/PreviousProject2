'use strict';
/**
 * 成就任务数据库查询
 */

//--------------------------------------------------------------------------------
// 公开方法

/**
 * 查询任务数据库中的用户信息
 */
function getAchievementTasklists(client, user_id, callback) {
  var table_index_id = 1; // TODO : 后期走配置
  client.query('SELECT * FROM gametask_achievement_' + table_index_id + ' WHERE user_id = ? ',
					[user_id],
          function (err, results) {
        if (err) {
            console.log('[ERROR!!]gametask_achievement_db->getAchievementTasklists, msg : ' + err);
            callback(false, err );
            return;
        }
        if(results != undefined && results != null && results.length > 0) {
        	callback(true, results);
        }else {
					callback(false, results);
				}
    });
}

exports.getAchievementTasklists = getAchievementTasklists;

/**
 * 查询用户单个任务信息
 */
function getAchievementTaskInfoById(client, user_id, task_id, callback) {
  var table_index_id = 1; // TODO : 后期走配置
  client.query('SELECT * FROM gametask_achievement_' + table_index_id + ' WHERE user_id = ? AND task_id = ? ',
         [user_id, task_id],
          function (err, results) {
        if (err) {
            console.log('[ERROR!!]gametask_achievement_db->getAchievementTaskInfoById, msg : ' + err);
            callback(false, err);
            return;
        }
        if(results != undefined && results != null && results.length > 0) {
          var result = {
            user_id : results[0]['user_id'],
            task_id : parseInt(results[0]['task_id']),
            current_level : parseInt(results[0]['current_level']),
            current_nums : parseInt(results[0]['current_nums']),
            user_get : parseInt(results[0]['user_get'])
          };
         callback(true, result);
        }else {
         callback(false, results);
       }
    });
}

exports.getAchievementTaskInfoById = getAchievementTaskInfoById;

/**
 * 更新用户单个任务信息[主要在领取的时候调用][如果存在就更新，不存在就写入]
 */
 function updateAchievementTaskInfoById(client, user_id, task_id, current_level, current_nums, user_get, callback) {
   var table_index_id = 1; // TODO : 后期走配置
   var values = [[user_id, task_id, current_level, current_nums, user_get]];
   client.query(' INSERT INTO gametask_achievement_' + table_index_id +
      ' (user_id, task_id, current_level, current_nums, user_get) VALUES ? ' +
      ' ON DUPLICATE KEY UPDATE current_level = VALUES(current_level),' +
      ' current_nums = VALUES(current_nums), user_get = VALUES(user_get) ',
     [values],
     function (err, results) {
         if (err) {
             console.log('[ERROR!!]gametask_achievement_db->updateAchievementTaskInfoById, msg : ' + err);
             callback(false);
             return;
         }
         callback(true);
    });
 }

exports.updateAchievementTaskInfoById = updateAchievementTaskInfoById;

/**
 * 更新用户任务获取信息
 */
 function addAchievementTaskCurrentNumsById(client, user_id, task_id, current_nums, callback) {
   var table_index_id = 1; // TODO : 后期走配置
   client.query(' INSERT INTO gametask_achievement_' + table_index_id +
      ' (user_id, task_id, current_level, current_nums, user_get) VALUES ? ' +
      ' ON DUPLICATE KEY UPDATE current_nums = current_nums + VALUES(current_nums)',
     [user_id, task_id, current_nums],
     function (err, results) {
         if (err) {
             console.log('[ERROR!!]gametask_achievement_db->addAchievementTasCurrentNumsById, msg : ' + err);
             callback(false);
             return;
         }
         callback(true);
    });
 }

exports.addAchievementTaskCurrentNumsById = addAchievementTaskCurrentNumsById;


//--------------------------------------------------------------------------------
// 内部方法


//--------------------------------------------------------------------------------
// 工具方法
