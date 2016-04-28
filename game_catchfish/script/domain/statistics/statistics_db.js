

function insertOneUserFishData(client, user_id, data, day, callback) {
  if(data.fishes.length <= 0) {
    callback(false);
    return ;
  }
  var values = [];
  for(var i=0; i<data.fishes.length; i++) {
    var value = [day, user_id, data.fishes[i].fish_id, data.fishes[i].create_times,
        data.fishes[i].hit_times, data.fishes[i].hit_moneys, data.fishes[i].catch_times, data.fishes[i].catch_times_user];
    values[i] = value;
  }
  client.query(' INSERT INTO statistics_fish_' + data.room_id + ' (day, user_id, fish_id, create_times, hit_times, hit_moneys, catch_times, catch_times_user) VALUES ? ' +
      ' ON DUPLICATE KEY UPDATE create_times = create_times + VALUES(create_times), ' +
      ' hit_times = hit_times + VALUES(hit_times), hit_moneys = hit_moneys + VALUES(hit_moneys), catch_times = catch_times + VALUES(catch_times), ' +
      ' catch_times_user = catch_times_user + VALUES(catch_times_user)',
  	   [values],
    function (err, results) {
        if (err) {
            console.log('[ERROR!!]statistics_db->insertOneUserFishData, msg : ' + err);
            callback(false);
            return;
        }
        callback(true);
    });
}

/**
 * 美人鱼任务
 */
function insertOneMermaidTaskData(client, user_id, data, day, callback) {
  client.query(' INSERT INTO statistics_mermaid_task SET ' +
      ' user_id = ?, day = ?, result = ?, rewards = ?, room_id = ?',
  	   [user_id, day, data.result, data.rewards, data.room_id],
    function (err, results) {
        if (err) {
            console.log('[ERROR!!]statistics_db->insertOneMermaidTaskData, msg : ' + err);
            callback(false);
            return;
        }
        callback(true);
    });
}

/**
 * 奖励存储
 */
function insertOnePresentedData(client, user_id, data, day, callback) {
  if(data.presenteds.length <= 0) {
    callback(false);
    return ;
  }
  var values = [];
  for(var i=0; i<data.presenteds.length; i++) {
    var value = [day, user_id, data.presenteds[i].prop_id, data.presenteds[i].nums];
    values[i] = value;
  }
  console.log('insertOnePresentedData : ' + values);
  client.query(' INSERT INTO statistics_presented (day, user_id, prop_id, nums) VALUES ? ' +
      ' ON DUPLICATE KEY UPDATE nums = nums + VALUES(nums)',
  	   [values],
    function (err, results) {
        if (err) {
            console.log('[ERROR!!]statistics_db->insertOnePresentedData, msg : ' + err);
            callback(false);
            return;
        }
        callback(true);
    });
}

/**
 * 破产
 */
function insertOneBankruptData(client, user_id, data, day, callback) {
  client.query('INSERT INTO statistics_bankrupt SET user_id = ?, day = ?, type = ?, nums = ?, room_id = ?',
  	   [user_id, day, data.type, data.nums, data.room_id],
    function (err, results) {
        if (err) {
            console.log('[ERROR!!]statistics_db->insertOneBankruptData, msg : ' + err);
            callback(false);
            return;
        }
        callback(true);
    });
}

function insertOneSkillUseData(client, user_id, data, day, callback) {
  if(data.skills.length <= 0) {
    callback(false);
    return ;
  }
  var values = [];
  for(var i=0; i<data.skills.length; i++) {
    var value = [day, user_id, data.skills[i].skill_id, data.skills[i].type,
        data.skills[i].price, data.skills[i].nums];
    values[i] = value;
  }
  // console.log('insertOneSkillUseData : ' + JSON.stringify(values));
  client.query(' INSERT INTO statistics_skilluser (day, user_id, skill_id, type, price, nums) VALUES ? ' +
      '  ON DUPLICATE KEY UPDATE nums = nums + VALUES(nums), price = price + VALUES(price) ',
  	   [values],
    function (err, results) {
        if (err) {
            console.log('[ERROR!!]statistics_db->insertOnePropUserData, msg : ' + err);
            callback(false);
            return;
        }
        callback(true);
    });
}

/**
 * 写入页面跳转数据
 */
function insertOneUserPageChangeData(client, user_id, data, day, callback) {
  if(data.pagechanges.length <= 0) {
    callback(false);
    return ;
  }
  var values = [];
  for(var i=0; i<data.pagechanges.length; i++) {
    var value = [day, user_id, data.pagechanges[i].from_page, data.pagechanges[i].to_page,
        data.pagechanges[i].channel, data.pagechanges[i].nums];
    values[i] = value;
  }
  // console.log('insertOneSkillUseData : ' + JSON.stringify(values));
  client.query(' INSERT INTO statistics_page_change (day, user_id, from_page, to_page, channel, nums) VALUES ? ' +
      '  ON DUPLICATE KEY UPDATE nums = nums + VALUES(nums)',
  	   [values],
    function (err, results) {
        if (err) {
            console.log('[ERROR!!]statistics_db->insertOneUserPageChangeData, msg : ' + err);
            callback(false);
            return;
        }
        callback(true);
    });
}

/**
 * 写入普通事件统计
 */
function insertOneUserCommonEventData(client, user_id, data, day, callback) {
  if(data.events.length <= 0) {
    callback(false);
    return ;
  }
  var values = [];
  for(var i=0; i<data.events.length; i++) {
    var value = [day, user_id, data.events[i].event_id, data.events[i].event_desc,
        data.events[i].nums];
    values[i] = value;
  }
  // console.log('insertOneSkillUseData : ' + JSON.stringify(values));
  client.query(' INSERT INTO statistics_commons_event (day, user_id, event_id, event_desc, nums) VALUES ? ' +
      '  ON DUPLICATE KEY UPDATE nums = nums + VALUES(nums)',
  	   [values],
    function (err, results) {
        if (err) {
            console.log('[ERROR!!]statistics_db->insertOneUserCommonEventData, msg : ' + err);
            callback(false);
            return;
        }
        callback(true);
    });
}

/**
 * 写入炮台升级用时统计事件统计
 */
function insertOneUserTurrentLevelChangeData(client, user_id, data, day, callback) {
  // console.log('insertOneSkillUseData : ' + JSON.stringify(values));
  // '20160127', '201', 2, 325' at line 1
  client.query(' INSERT INTO statistics_turrent_change_1 SET day = ?, ' +
      'user_id = ?, turrent_level = ?, update_times = ? ',
  	  [day, user_id, data.turrent_level, data.update_times],
    function (err, results) {
        if (err) {
            console.log('[ERROR!!]statistics_db->insertOneUserTurrentLevelChangeData, msg : ' + err);
            callback(false);
            return;
        }
        callback(true);
    });
}



exports.insertOneUserFishData = insertOneUserFishData;
exports.insertOneMermaidTaskData = insertOneMermaidTaskData;
exports.insertOnePresentedData = insertOnePresentedData;
exports.insertOneBankruptData = insertOneBankruptData;
exports.insertOneSkillUseData = insertOneSkillUseData;

exports.insertOneUserPageChangeData = insertOneUserPageChangeData;
exports.insertOneUserCommonEventData = insertOneUserCommonEventData;
exports.insertOneUserTurrentLevelChangeData = insertOneUserTurrentLevelChangeData;


/**
 * 写入抽奖统计
 */
function insertOneUserTurnTableData(client, user_id, data, day, callback) {
  if(data.lists.length <= 0) {
    callback(false);
    return ;
  }
  var values = [];
  for(var i=0; i<data.lists.length; i++) {
    var value = [day, user_id, data.lists[i].t_type, data.lists[i].p_type_1,
        data.lists[i].p_type_2, data.lists[i].p_type_3, data.lists[i].p_type_4,
        data.lists[i].p_type_5, data.lists[i].p_type_6];
    values[i] = value;
  }
  // console.log('insertOneSkillUseData : ' + JSON.stringify(values));
  client.query(' INSERT INTO statistics_turntable (day, user_id, t_type, p_type_1, p_type_2, p_type_3, p_type_4, p_type_5, p_type_6) VALUES ? ' +
      ' ON DUPLICATE KEY UPDATE p_type_1 = p_type_1 + VALUES(p_type_1), p_type_2 = p_type_2 + VALUES(p_type_2), ' +
      ' p_type_3 = p_type_3 + VALUES(p_type_3), p_type_4 = p_type_4 + VALUES(p_type_4), ' +
      ' p_type_5 = p_type_5 + VALUES(p_type_5), p_type_6 = p_type_6 + VALUES(p_type_6) ',
  	   [values],
    function (err, results) {
        if (err) {
            console.log('[ERROR!!]statistics_db->insertOneUserTurnTableData, msg : ' + err);
            callback(false);
            return;
        }
        callback(true);
    });
}

exports.insertOneUserTurnTableData = insertOneUserTurnTableData;

/**
 * 写入消耗统计信息
 */
function insertOneUserExpendData(client, user_id, data, day, callback) {
  if(data.lists.length <= 0) {
    callback(false);
    return ;
  }
  var values = [];
  for(var i=0; i<data.lists.length; i++) {
    var value = [day, user_id, data.lists[i].coin_get, data.lists[i].coin_use,
        data.lists[i].diamond_get, data.lists[i].diamond_use];
    values[i] = value;
  }
  client.query(' INSERT INTO statistics_expend (day, user_id, coin_get, coin_use, diamond_get, diamond_use) VALUES ? ' +
      ' ON DUPLICATE KEY UPDATE coin_get = coin_get + VALUES(coin_get), coin_use = coin_use + VALUES(coin_use), ' +
      ' diamond_get = diamond_get + VALUES(diamond_get), diamond_use = diamond_use + VALUES(diamond_use) ',
  	   [values],
    function (err, results) {
        if (err) {
            console.log('[ERROR!!]statistics_db->insertOneUserExpendData, msg : ' + err);
            callback(false);
            return;
        }
        callback(true);
    });
}

exports.insertOneUserExpendData = insertOneUserExpendData;
