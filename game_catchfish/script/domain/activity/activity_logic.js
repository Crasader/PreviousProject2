'use strict';
/**
 * 活动逻辑
 */

var dbmanager = require('../../db/dbmanager.js');
var schedule = require('node-schedule');
var activity_db = require('./activity_db.js');

var activityAgreement = {
   errorcode : 0,
   item_lists : [
     {
       title : '万劫不复',
       start_day : 20160401,
       end_day : 20160405,
       invalid_day : 20160407,
       desc_info : '让逝者气哭的力度，清明假期所有墓地2折促销，不可错过！',
       pic_url : 'http://img.hb.aicdn.com/edbcaed536dbca4e1c258f6c32d18f2e368500ab40fa-unkKoo_fw658'
     }
   ]
};

var activityAgreementStr = JSON.stringify(activityAgreement);

function initConfig() {
  updateActivityConfig();
  initTask();
}

exports.initConfig = initConfig;

function initTask() {
	var rule = new schedule.RecurrenceRule();
	var times = [];
	times.push(0);
	rule.minute = times;
　　 schedule.scheduleJob(rule, function(){
		console.log(' strat task for activity config at ' + new Date().Format("yyyy-MM-dd hh:mm:ss:S"));
		updateActivityConfig();
	});
}

function updateActivityConfig() {
  activity_db.getActivityConfig(dbmanager.getClientS(), function(success, results){
    if(success) {
      // TODO : 组装数据
      activityAgreement.item_lists = [];
      for(var i=0;i<results.length;i++){
        var item = {
          title : results[i]['title'],
          start_day : results[i]['start_day'],
          end_day : results[i]['end_day'],
          invalid_day : results[i]['invalid_day'],
          desc_info : results[i]['desc_info'],
          pic_url : results[i]['pic_url']
        };
        activityAgreement.item_lists.push(item);
      }
      activityAgreementStr = JSON.stringify(activityAgreement);
      console.log('update activity config : ' + activityAgreementStr);
    }else {
      console.log('marguee_logic->updateActivityConfig, fail : ' + activityAgreementStr);
    }
  });
}

function getActivityAgreementStr() {
  return activityAgreementStr;
}

exports.getActivityAgreementStr = getActivityAgreementStr;
