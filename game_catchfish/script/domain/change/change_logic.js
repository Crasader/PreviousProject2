'use strict';

var redishelper = require('../../mem/redishelper.js');
var dbmanager = require('../../db/dbmanager.js');
var session_manager = require('../../session_manager.js');

var bag_db = require('../bag/bag_db.js');
var bag_service = require('../bag/bag_service.js');
var change_db = require('./change_db.js');

var default_require_more_1013_str = JSON.stringify({
  errorcode : 1601,
  errormsg : '您的话费劵数目不足.'
});

var error_params_str = JSON.stringify({
  errorcode : 1602,
  errormsg : '不存在的领取类型.'
});

/**
 * 申请领取话费卷奖励
 */
function getRewards(session_id, change_type, phone_nums, callback){
  change_type = parseInt(change_type);
  if( !(change_type >= 1 && change_type <= 3) ) {
    callback(error_params_str);
    return ;
  }
  (function(session_id, change_type, phone_nums){
    session_manager.isLogin(session_id, function(login, data){
      if(!login) {
        res.end(data);
        return ;
      }
      (function(data){
        redishelper.getVaule('BG_' + session_id, function(err, redis_result) {
      		if(err) {
      			callback(agreement.redisErrorDesc);
      			return ;
      		}
      		if(redis_result != undefined) {
      			var bag_info = JSON.parse(redis_result);
            var nums1013 = getItem1013Nums(bag_info);
            if(nums1013 < 300) { // 查询玩家的背包信息,1013话费卷的数量要大于300
              callback(default_require_more_1013_str);
              return ;
            } else {
              for(var i=0;i<bag_info.item_lists.length;i++) {
                if(bag_info.item_lists[i].item_id === 1013) {
                  bag_info.item_lists[i].nums -= 300;
                  break;
                }
              }
              if(change_type === 1) { // 1,话费
                bag_db.syncbagInfo(dbmanager.getClient(), data.user_id, 1013, (nums1013 - 300), function(result){});
                change_db.insertChangeMark(dbmanager.getClient(), data.user_id, 1, 0, phone_nums, new Date().Format("yyyyMMdd"), function(result){});
              } else if(change_type === 2) { // 2 钻石
                // TODO : 添加领取记录
                data.diamonds += 500;
                redishelper.setValueWithExpire(session_manager.SESSION_ID_HEAD + session_id, JSON.stringify(data),
                    session_manager.SESSION_EXPIRE);
                bag_service.syncUserInfoDb(data.user_id, data.fortune_id, 1002, data.diamonds, function(result){});
                change_db.insertChangeMark(dbmanager.getClient(), data.user_id, 2, 1, phone_nums, new Date().Format("yyyyMMdd"), function(result){});
              } else if(change_type === 3) { // 3 核弹
                var end_nums = 3;
                for(var i=0;i<bag_info.item_lists.length;i++) {
                  var set = false;
                  if(bag_info.item_lists[i].item_id === 1006) {
                    bag_info.item_lists[i].nums += 3; // TODO : 领取的核弹数目客户端写死的
                    end_nums = bag_info.item_lists[i].nums;
                    set = true;
                    break;
                  }
                }
                if(!set) {
                  bag_info.item_lists.push({
                    item_id : 1006,
                    nums : 3
                  });
                }
                bag_db.syncbagInfo(dbmanager.getClient(), data.user_id, 1006, end_nums, function(result){});
                change_db.insertChangeMark(dbmanager.getClient(), data.user_id, 3, 1, phone_nums, new Date().Format("yyyyMMdd"), function(result){});
              }


              redishelper.setValueWithExpire('BG_' + session_id, JSON.stringify(bag_info),
                  session_manager.SESSION_EXPIRE);


              callback(JSON.stringify({
                errorcode : 0,
                errormsg : '兑换申请已提交,2~3个工作日到账'
              }));
            }
      			return ;
      		}
      		callback(default_require_more_1013_str);
      	});
      })(data);

    });
  })(session_id, change_type, phone_nums);
}

exports.getRewards = getRewards;


function getRecord(session_id, callback) {
  session_manager.isLogin(session_id, function(login, data){
    if(!login) {
      res.end(data);
      return ;
    }
    change_db.getChangeMark(dbmanager.getClientS(), data.user_id, function(success, result){
      var client_result = {
        errorcode : 0,
        info_lists : []
      };
      if(success) {
        for(var i=0;i<result.length;i++) {
          var item = {
            date : result[i]['create_time'],
            reward_desc : getTypeDesc( parseInt(result[i]['type']) ),
            change_state : parseInt(result[i]['change_state']) === 0 ? '已申请' : '已完成'
          }
          client_result.info_lists.push(item);
        }
      }
      callback(JSON.stringify(client_result));
    });

  });
}

exports.getRecord = getRecord;


function getTypeDesc(type) {
  type = parseInt(type); // 1,话费;2 钻石; 3核弹
  if(type === 1) {
    return '话费';
  }else if(type === 2) {
    return '钻石';
  }else if(type === 3) {
    return '核弹';
  }else {
    return '未知';
  }
}

function getItem1013Nums(bag_info) {
  for(var i=0;i<bag_info.item_lists.length;i++) {
    if(bag_info.item_lists[i].item_id === 1013) {
      return bag_info.item_lists[i].nums;
    }
  }
  return 0;
}
