/**
 * 签到逻辑
 */

var dbmanager = require('../../db/dbmanager.js');
var schedule = require('node-schedule');
var marquee_db = require('./marquee_db.js');

 var marqueeAgreement = {
   version        : 1,
   play_interval  : 60, // 建议播放间隔，单位秒
   req_interval   : 60*60,  // 建议请求间隔单位秒
   item_list : [
     {
       msg : '每日登陆送金币,天数越多送的越多.'
     }
   ]
};

var marqueeAgreementStr = JSON.stringify(marqueeAgreement);

function initConfig() {
  updateMarqueeConfig();
  initTask();
}

function initTask() {
	var rule = new schedule.RecurrenceRule();
	var times = [];
	times.push(0);
	rule.minute = times;
　　 schedule.scheduleJob(rule, function(){
		console.log(' strat task for marguee config at ' + new Date().Format("yyyy-MM-dd hh:mm:ss:S"));
		updateMarqueeConfig();
	});
}

function updateMarqueeConfig() {
  marquee_db.getMarqueeConfig(dbmanager.getClientS(), function(success, configMarqueeAgreementStr){
    if(success) {
      marqueeAgreement = JSON.parse(configMarqueeAgreementStr);
      marqueeAgreementStr = JSON.stringify(marqueeAgreement);
      console.log('update marguee config : ' + marqueeAgreementStr);
    }else {
      console.log('marguee_logic->updateMargueeConfig, fail : ' + marqueeAgreementStr);
    }
  });
}

function getMarqueeAgreementStr() {
  return marqueeAgreementStr;
}

exports.initConfig = initConfig;
exports.getMarqueeAgreementStr = getMarqueeAgreementStr;
