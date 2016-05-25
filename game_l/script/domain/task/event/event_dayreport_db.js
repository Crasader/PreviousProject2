

/**
 * 计算分炮台等级的平均用户升级时间。
 */
function getTurrentLevelUpdateInfo(client, dayNum, callback) {
  client.query('SELECT turrent_level, COUNT(user_id) AS user_nums, AVG(update_times) AS avg_update_times ' +
      ' FROM statistics_turrent_change_1 WHERE day = ? GROUP BY turrent_level',
      [dayNum],
    function (err, results) {
      if(err) {
        console.log('[event][getSecondUserNum]err : ' + err);
        callback(false, results, dayNum);
      }else {
        callback(true, results, dayNum);
      }
    }
  );
}

function insertTurrentLevelUpdateInfo(client, items, callback){
  client.query('INSERT INTO report_turrentlevelupdate_day(day, turrent_level, user_nums, avg_update_times) VALUES ? ' +
      ' ON DUPLICATE KEY UPDATE user_nums = VALUES(user_nums), avg_update_times = VALUES(avg_update_times)',
      [items],
    function (err, results) {
      if(err) {
        console.log('[event][insertTurrentLevelUpdateInfo]err : ' + err);
        callback(false);
      }else {
        callback(true);
      }
    }
  );
}

exports.getTurrentLevelUpdateInfo = getTurrentLevelUpdateInfo;
exports.insertTurrentLevelUpdateInfo = insertTurrentLevelUpdateInfo;

/**
 * 计算分炮台等级的平均用户升级时间。
 */
function getSkillUserInfoBase(client, dayNum, callback) {
  client.query('SELECT skill_id, COUNT(user_id) AS user_nums, SUM(nums) AS nums ' +
      ' FROM statistics_skilluser WHERE day = ? GROUP BY skill_id',
      [dayNum],
    function (err, results) {
      if(err) {
        console.log('[event][getSkillUserInfoBase]err : ' + err);
        callback(false, results, dayNum);
      }else {
        callback(true, results, dayNum);
      }
    }
  );
}

function insertSkillUserInfoBase(client, items, callback){
  client.query('INSERT INTO report_skilluse_day(day, skill_id, use_nums, use_users) VALUES ? ' +
      ' ON DUPLICATE KEY UPDATE use_nums = VALUES(use_nums), use_users = VALUES(use_users)',
      [items],
    function (err, results) {
      if(err) {
        console.log('[event][insertSkillUserInfoBase]err : ' + err);
        callback(false);
      }else {
        callback(true);
      }
    }
  );
}

/**
 * type 0,金币;1,钻石;2,触发计费
 */
function getSkillUserInfoType(client, dayNum, type, callback) {
  client.query('SELECT skill_id, COUNT(user_id) AS user_nums, SUM(nums) AS nums ' +
      ' FROM statistics_skilluser WHERE day = ? AND type = ? GROUP BY skill_id',
      [dayNum, type],
    function (err, results) {
      if(err) {
        console.log('[event][getSkillUserInfoType]err : ' + err);
        callback(false, results, dayNum, type);
      }else {
        callback(true, results, dayNum, type);
      }
    }
  );
}

function insertSkillUserInfoType(client, type, items, callback){
  var TYPE_STR_NUMS = 'use_coin_nums';
  var TYPE_STR_USERS = 'use_coin_users';
  if(type === 1) {
    TYPE_STR_NUMS = 'use_diamond_nums';
    TYPE_STR_USERS = 'use_diamond_users';
  }else if(type === 2) {
    TYPE_STR_NUMS = 'use_payreq_nums';
    TYPE_STR_USERS = 'use_payreq_users';
  }
  var queryStr = 'INSERT INTO report_skilluse_day(day, skill_id, ' + TYPE_STR_NUMS +', ' + TYPE_STR_USERS + ') VALUES ? ' +
      ' ON DUPLICATE KEY UPDATE ' + TYPE_STR_NUMS + ' = VALUES(' + TYPE_STR_NUMS + '),' +
      ' ' + TYPE_STR_USERS + ' = VALUES(' + TYPE_STR_USERS + ')';
  client.query(queryStr,
      [items],
    function (err, results) {
      if(err) {
        console.log('[event][insertSkillUserInfoType]err : ' + err);
        callback(false);
      }else {
        callback(true);
      }
    }
  );
}

exports.getSkillUserInfoBase = getSkillUserInfoBase;
exports.insertSkillUserInfoBase = insertSkillUserInfoBase;
exports.getSkillUserInfoType = getSkillUserInfoType;
exports.insertSkillUserInfoType = insertSkillUserInfoType;

/**
 * 计算赠送任务
 */
function getPresentedUserInfo(client, dayNum, callback) {
  client.query('SELECT prop_id, COUNT(user_id) AS user_nums, SUM(nums) AS nums FROM statistics_presented ' +
      ' WHERE day = ? GROUP BY prop_id',
      [dayNum],
    function (err, results) {
      if(err) {
        console.log('[event][getPresentedUserInfo]err : ' + err);
        callback(false, results, dayNum);
      }else {
        callback(true, results, dayNum);
      }
    }
  );
}

function insertPresentedUserInfo(client, items, callback){
  client.query('INSERT INTO report_presented_day(day, prop_id, nums, user_nums) VALUES ? ' +
      ' ON DUPLICATE KEY UPDATE user_nums = VALUES(user_nums), nums = VALUES(nums)',
      [items],
    function (err, results) {
      if(err) {
        console.log('[event][insertPresentedUserInfo]err : ' + err);
        callback(false);
      }else {
        callback(true);
      }
    }
  );
}

exports.getPresentedUserInfo = getPresentedUserInfo;
exports.insertPresentedUserInfo = insertPresentedUserInfo;

/**
 * 计算页面跳转任务
 */
function getPageChangeInfo(client, dayNum, callback) {
  client.query('SELECT to_page, from_page, SUM(nums) AS nums, COUNT(nums) AS user_nums FROM statistics_page_change ' +
      ' WHERE day = ? GROUP BY to_page, from_page',
      [dayNum],
    function (err, results) {
      if(err) {
        console.log('[event][getPresentedUserInfo]err : ' + err);
        callback(false, results, dayNum);
      }else {
        callback(true, results, dayNum);
      }
    }
  );
}

function insertPageChangeInfo(client, items, callback){
  client.query('INSERT INTO report_pagechange_day(day, to_page, from_page, nums, user_nums) VALUES ? ' +
      ' ON DUPLICATE KEY UPDATE nums = VALUES(nums), user_nums = VALUES(user_nums)',
      [items],
    function (err, results) {
      if(err) {
        console.log('[event][insertPresentedUserInfo]err : ' + err);
        callback(false);
      }else {
        callback(true);
      }
    }
  );
}


exports.getPageChangeInfo = getPageChangeInfo;
exports.insertPageChangeInfo = insertPageChangeInfo;

/**
 * 计算单一房间的鱼群信息
 */
function getFishInfoByRoomId(client, dayNum, room_id, callback) {
  client.query('SELECT fish_id, SUM(create_times) AS create_times, SUM(hit_times) AS hit_times, SUM(hit_moneys) AS hit_moneys, SUM(catch_times) AS catch_times, SUM(catch_times_user) AS catch_times_user ' +
      ' FROM statistics_fish_' + room_id + ' WHERE day = ? GROUP BY fish_id',
      [dayNum],
    function (err, results) {
      if(err) {
        console.log('[event][getFishInfoByRoomId]err : ' + err);
        callback(false, results, dayNum, room_id);
      }else {
        callback(true, results, dayNum, room_id);
      }
    }
  );
}

function insertFishInfoByRoomId(client, items, callback){
  client.query('INSERT INTO report_fishinfo_day(day, room_id, fish_id, create_times, hit_times, hit_moneys, catch_times, catch_times_user) VALUES ? ' +
      ' ON DUPLICATE KEY UPDATE create_times = VALUES(create_times), hit_times = VALUES(hit_times), hit_moneys = VALUES(hit_moneys), ' +
      ' catch_times = VALUES(catch_times), catch_times_user = VALUES(catch_times_user)',
      [items],
    function (err, results) {
      if(err) {
        console.log('[event][insertFishInfoByRoomId]err : ' + err);
        callback(false);
      }else {
        callback(true);
      }
    }
  );
}

exports.getFishInfoByRoomId = getFishInfoByRoomId;
exports.insertFishInfoByRoomId = insertFishInfoByRoomId;

/**
 * 计算美人鱼任务-基础
 */
function getMermaidTaskInfoBase(client, dayNum, callback) {
  client.query('SELECT COUNT(DISTINCT user_id) AS user_nums, COUNT(user_id) AS nums ' +
      ' FROM statistics_mermaid_task WHERE day = ?',
      [dayNum],
    function (err, results) {
      if(err) {
        console.log('[event][mermaidTaskInfoBase]err : ' + err);
        callback(false, results, dayNum);
      }else {
        callback(true, results, dayNum);
      }
    }
  );
}

function insertMermaidTaskInfoBase(client, items, callback){
  client.query('INSERT INTO report_mermaidtask_day(day, nums, user_nums) VALUES ? ' +
      ' ON DUPLICATE KEY UPDATE nums = VALUES(nums), user_nums = VALUES(user_nums)',
      [items],
    function (err, results) {
      if(err) {
        console.log('[event][insertTurrentLevelUpdateInfo]err : ' + err);
        callback(false);
      }else {
        callback(true);
      }
    }
  );
}

/**
 * 计算美人鱼任务-成功
 */
function getMermaidTaskInfoSuccess(client, dayNum, callback) {
  client.query('SELECT ' +
      ' COUNT(DISTINCT user_id) AS user_nums, COUNT(user_id) AS nums, AVG(result) AS user_times, AVG(rewards) AS rewards ' +
      ' FROM statistics_mermaid_task WHERE day = ? AND result != 0',
      [dayNum],
    function (err, results) {
      if(err) {
        console.log('[event][mermaidTaskInfoBase]err : ' + err);
        callback(false, results, dayNum);
      }else {
        callback(true, results, dayNum);
      }
    }
  );
}

function insertMermaidTaskInfoSuccess(client, items, callback){
  client.query('INSERT INTO report_mermaidtask_day(day, success_nums, success_user_nums, success_user_times, success_rewards) VALUES ? ' +
      ' ON DUPLICATE KEY UPDATE success_nums = VALUES(success_nums), success_user_nums = VALUES(success_user_nums), ' +
      ' success_user_times = VALUES(success_user_times), success_rewards = VALUES(success_rewards)',
      [items],
    function (err, results) {
      if(err) {
        console.log('[event][insertMermaidTaskInfoSuccess]err : ' + err);
        callback(false);
      }else {
        callback(true);
      }
    }
  );
}


exports.getMermaidTaskInfoBase = getMermaidTaskInfoBase;
exports.insertMermaidTaskInfoBase = insertMermaidTaskInfoBase;
exports.getMermaidTaskInfoSuccess = getMermaidTaskInfoSuccess;
exports.insertMermaidTaskInfoSuccess = insertMermaidTaskInfoSuccess;

/**
 * 计算破产-基础
 */
function getBankruptInfo(client, dayNum, type, callback) {
  client.query('SELECT nums, COUNT(DISTINCT user_id) AS counts  FROM statistics_bankrupt WHERE day = ? AND type = ? GROUP BY nums',
      [dayNum, type],
    function (err, results) {
      if(err) {
        console.log('[event][getBankruptInfo]err : ' + err);
        callback(false, results, dayNum, type);
      }else {
        callback(true, results, dayNum, type);
      }
    }
  );
}

function insertBankruptInfo(client, type, items, callback){
  var TYPE_STR = 'nums';
  if(type === 1) {
    TYPE_STR  = 'get_nums';
  }
  client.query('INSERT INTO report_bankrupt_day(day, seq_id, ' + TYPE_STR + ') VALUES ? ' +
      ' ON DUPLICATE KEY UPDATE ' + TYPE_STR + ' = VALUES(' + TYPE_STR + ')',
      [items],
    function (err, results) {
      if(err) {
        console.log('[event][insertBankruptInfo]err : ' + err);
        callback(false);
      }else {
        callback(true);
      }
    }
  );
}

exports.getBankruptInfo = getBankruptInfo;
exports.insertBankruptInfo = insertBankruptInfo;

/**
 * 计算新增用户破产-基础
 */
function getBankruptInfoForNew(client, dayNum, type, callback) {
  client.query('SELECT nums, COUNT(DISTINCT user_id) AS counts  FROM statistics_bankrupt WHERE day = ? AND type = ? ' +
      ' AND user_id IN (SELECT user_id FROM mark_user_login_1 WHERE day = ? AND login_day = 0) GROUP BY nums',
      [dayNum, type, dayNum],
    function (err, results) {
      if(err) {
        console.log('[event][getBankruptInfo]err : ' + err);
        callback(false, results, dayNum, type);
      }else {
        callback(true, results, dayNum, type);
      }
    }
  );
}

function insertBankruptInfoForNew(client, type, items, callback){
  var TYPE_STR = 'new_nums';
  if(type === 1) {
    TYPE_STR  = 'new_get_nums';
  }
  client.query('INSERT INTO report_bankrupt_day(day, seq_id, ' + TYPE_STR + ') VALUES ? ' +
      ' ON DUPLICATE KEY UPDATE ' + TYPE_STR + ' = VALUES(' + TYPE_STR + ')',
      [items],
    function (err, results) {
      if(err) {
        console.log('[event][insertBankruptInfo]err : ' + err);
        callback(false);
      }else {
        callback(true);
      }
    }
  );
}

exports.getBankruptInfoForNew = getBankruptInfoForNew;
exports.insertBankruptInfoForNew = insertBankruptInfoForNew;

function getTurntableInfo(client, dayNum, callback) {
  client.query('SELECT t_type, COUNT(t_type) AS times, COUNT(user_id) AS user_times, ' +
      ' SUM(p_type_1) AS p_type_1_counts, SUM(p_type_2) AS p_type_2_counts, SUM(p_type_3) AS p_type_3_counts, ' +
      ' SUM(p_type_4) AS p_type_4_counts, SUM(p_type_5) AS p_type_5_counts, SUM(p_type_6) AS p_type_6_counts ' +
      ' FROM statistics_turntable WHERE day = ? GROUP BY t_type',
      [dayNum],
    function (err, results) {
      if(err) {
        console.log('[event][getTurntableInfo]err : ' + err);
        callback(false, results, dayNum);
      }else {
        callback(true, results, dayNum);
      }
    }
  );
}

function insertTurntableInfo(client, items, callback){
  client.query('INSERT INTO report_turntable_day(day, t_type, times, user_times, p_type_1_counts, ' +
      ' p_type_2_counts, 	p_type_3_counts, 	p_type_4_counts, 	p_type_5_counts, 	p_type_6_counts) VALUES ? ' +
      ' ON DUPLICATE KEY UPDATE times = VALUES(times), user_times = VALUES(user_times), ' +
      ' p_type_1_counts = VALUES(p_type_1_counts), p_type_2_counts = VALUES(p_type_2_counts), ' +
      ' p_type_3_counts = VALUES(p_type_3_counts), p_type_4_counts = VALUES(p_type_4_counts),' +
      ' p_type_5_counts = VALUES(p_type_5_counts), p_type_6_counts = VALUES(p_type_6_counts)',
      [items],
    function (err, results) {
      if(err) {
        console.log('[event][insertTurntableInfo]err : ' + err);
        callback(false);
      }else {
        callback(true);
      }
    }
  );
}

exports.getTurntableInfo = getTurntableInfo;
exports.insertTurntableInfo = insertTurntableInfo;

function getTurntableInfoForNew(client, dayNum, callback) {
  client.query('SELECT t_type, COUNT(t_type) AS times, COUNT(user_id) AS user_times, ' +
      ' SUM(p_type_1) AS p_type_1_counts, SUM(p_type_2) AS p_type_2_counts, SUM(p_type_3) AS p_type_3_counts, ' +
      ' SUM(p_type_4) AS p_type_4_counts, SUM(p_type_5) AS p_type_5_counts, SUM(p_type_6) AS p_type_6_counts ' +
      ' FROM statistics_turntable WHERE day = ? AND ' +
      ' user_id IN (SELECT user_id FROM mark_user_login_1 WHERE day = ? AND login_day = 0) ' +
      ' GROUP BY t_type',
      [dayNum, dayNum],
    function (err, results) {
      if(err) {
        console.log('[event][getTurntableInfoForNew]err : ' + err);
        callback(false, results, dayNum);
      }else {
        callback(true, results, dayNum);
      }
    }
  );
}

function insertTurntableInfoForNew(client, items, callback){
  client.query('INSERT INTO report_turntable_day(day, t_type, times, user_times, p_type_1_counts, ' +
      ' p_type_2_counts, 	p_type_3_counts, 	p_type_4_counts, 	p_type_5_counts, 	p_type_6_counts) VALUES ? ' +
      ' ON DUPLICATE KEY UPDATE times = VALUES(times), user_times = VALUES(user_times), ' +
      ' p_type_1_counts = VALUES(p_type_1_counts), p_type_2_counts = VALUES(p_type_2_counts), ' +
      ' p_type_3_counts = VALUES(p_type_3_counts), p_type_4_counts = VALUES(p_type_4_counts),' +
      ' p_type_5_counts = VALUES(p_type_5_counts), p_type_6_counts = VALUES(p_type_6_counts)',
      [items],
    function (err, results) {
      if(err) {
        console.log('[event][insertTurntableInfoForNew]err : ' + err);
        callback(false);
      }else {
        callback(true);
      }
    }
  );
}

exports.getTurntableInfoForNew = getTurntableInfoForNew;
exports.insertTurntableInfoForNew = insertTurntableInfoForNew;

function turrentLevelGroupActiveInfo(client, dayNum, callback) {
  client.query('SELECT turrent_level, COUNT(user_id) AS active_user FROM user_fortune_1 ' +
    ' WHERE user_id IN (SELECT user_id FROM mark_user_login_1 WHERE day = ? ) GROUP BY turrent_level',
      [dayNum],
    function (err, results) {
      if(err) {
        console.log('[event][turrentLevelGroupActiveInfo]err : ' + err);
        callback(false, results, dayNum);
      }else {
        callback(true, results, dayNum);
      }
    }
  );
}

function insertTurrentLevelGroupActiveInfo(client, items, callback){
  client.query('INSERT INTO report_turrent_group_day(day, turrent_level, active_user) VALUES ? ' +
      ' ON DUPLICATE KEY UPDATE active_user = VALUES(active_user)',
      [items],
    function (err, results) {
      if(err) {
        console.log('[event][insertTurrentLevelGroupActiveInfo]err : ' + err);
        callback(false);
      }else {
        callback(true);
      }
    }
  );
}

exports.turrentLevelGroupActiveInfo = turrentLevelGroupActiveInfo;
exports.insertTurrentLevelGroupActiveInfo = insertTurrentLevelGroupActiveInfo;

function turrentLevelGroupNewInfo(client, dayNum, callback) {
  client.query('SELECT turrent_level, COUNT(user_id) AS new_user FROM user_fortune_1 ' +
    ' WHERE user_id IN (SELECT user_id FROM mark_user_login_1 WHERE day = ? AND login_day = 0 ) GROUP BY turrent_level',
      [dayNum],
    function (err, results) {
      if(err) {
        console.log('[event][turrentLevelGroupNewInfo]err : ' + err);
        callback(false, results, dayNum);
      }else {
        callback(true, results, dayNum);
      }
    }
  );
}

function insertTurrentLevelGroupNewInfo(client, items, callback){
  client.query('INSERT INTO report_turrent_group_day(day, turrent_level, new_user) VALUES ? ' +
      ' ON DUPLICATE KEY UPDATE new_user = VALUES(new_user)',
      [items],
    function (err, results) {
      if(err) {
        console.log('[event][insertTurrentLevelGroupNewInfo]err : ' + err);
        callback(false);
      }else {
        callback(true);
      }
    }
  );
}

exports.turrentLevelGroupNewInfo = turrentLevelGroupNewInfo;
exports.insertTurrentLevelGroupNewInfo = insertTurrentLevelGroupNewInfo;

function sqlWithParam(client, sqlStr, params, callback){
  client.query(sqlStr,
      [params],
    function (err, results) {
      if(err) {
        console.log('[event][sqlWithParam]err : ' + err);
        callback(false);
      }else {
        callback(true);
      }
    }
  );
}

exports.sqlWithParam = sqlWithParam;

function getUserExpInfo(client, dayNum, callback) {
  client.query('SELECT ELT(interval(d.exp, 0, 378, 998, 1388, 3188, 5588, 6888, 9500, 19000, 25000, 35000, 50000, 60500, 77000, 99500, 117500, 144500, 182000, 207500, 249500, 300500, 339500, 396500, 494000, 567500, 684500, 818000, 941000, 1088000, 1275500, 1440500, 9999999), ' +
      ' 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32) AS exp_level, COUNT(d.user_id) AS nums FROM user_fortune_1 AS d  ' +
      ' GROUP BY elt(interval(d.exp, 0, 378, 998, 1388, 3188, 5588, 6888, 9500, 19000, 25000, 35000, 50000, 60500, 77000, 99500, 117500, 144500, 182000, 207500, 249500, 300500, 339500, 396500, 494000, 567500, 684500, 818000, 941000, 1088000, 1275500, 1440500, 9999999), 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32)',
    function (err, results) {
      if(err) {
        console.log('[event][getUserExpInfo]err : ' + err);
        callback(false, results, dayNum);
      }else {
        callback(true, results, dayNum);
      }
    }
  );
}

function insertUserExpInfo(client, items, callback){
  client.query('INSERT INTO report_exp_day(day, exp_level, nums) VALUES ? ' +
      ' ON DUPLICATE KEY UPDATE nums = VALUES(nums)',
      [items],
    function (err, results) {
      if(err) {
        console.log('[event][insertUserExpInfo]err : ' + err);
        callback(false);
      }else {
        callback(true);
      }
    }
  );
}

exports.getUserExpInfo = getUserExpInfo;
exports.insertUserExpInfo = insertUserExpInfo;

function getUserExpInfoForNew(client, dayNum, callback) {
  client.query('SELECT ELT(interval(d.exp, 0, 378, 998, 1388, 3188, 5588, 6888, 9500, 19000, 25000, 35000, 50000, 60500, 77000, 99500, 117500, 144500, 182000, 207500, 249500, 300500, 339500, 396500, 494000, 567500, 684500, 818000, 941000, 1088000, 1275500, 1440500, 9999999), ' +
      ' 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32) AS exp_level, COUNT(d.user_id) AS nums FROM user_fortune_1 AS d  ' +
      ' WHERE user_id IN (SELECT user_id FROM mark_user_login_1 WHERE day = ? AND login_day = 0)' +
      ' GROUP BY elt(interval(d.exp, 0, 378, 998, 1388, 3188, 5588, 6888, 9500, 19000, 25000, 35000, 50000, 60500, 77000, 99500, 117500, 144500, 182000, 207500, 249500, 300500, 339500, 396500, 494000, 567500, 684500, 818000, 941000, 1088000, 1275500, 1440500, 9999999), 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32)',
      [dayNum],
    function (err, results) {
      if(err) {
        console.log('[event][getUserExpInfo]err : ' + err);
        callback(false, results, dayNum);
      }else {
        callback(true, results, dayNum);
      }
    }
  );
}

function insertUserExpInfoForNew(client, items, callback){
  client.query('INSERT INTO report_exp_day(day, exp_level, new_nums) VALUES ? ' +
      ' ON DUPLICATE KEY UPDATE new_nums = VALUES(new_nums)',
      [items],
    function (err, results) {
      if(err) {
        console.log('[event][insertUserExpInfo]err : ' + err);
        callback(false);
      }else {
        callback(true);
      }
    }
  );
}

exports.getUserExpInfoForNew = getUserExpInfoForNew;
exports.insertUserExpInfoForNew = insertUserExpInfoForNew;
