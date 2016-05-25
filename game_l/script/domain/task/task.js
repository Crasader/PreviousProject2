/**
 * 定时任务入口
 */
var schedule = require('node-schedule');
var noderice = require('noderice');
var channel_dayreport = require('./channel/channel_dayreport.js');
var event_dayreport = require('./event/event_dayreport.js');
var rank = require('./rank/rank.js');
var pay_dayreport = require('./pay/pay_dayreport.js');


function init() {
  dayTaskConfig();
}

function dayTaskConfig() {
  // 执行每日任务
  var rule1 = new schedule.RecurrenceRule();
  rule1.dayOfWeek = [0, new schedule.Range(1, 6)];
  rule1.hour = 3;
  rule1.minute = 44;
  schedule.scheduleJob(rule1, function() { // 执行基础日报
    console.log('rule1 working ...');
    channel_dayreport.startOneDayTask(noderice.GetDateNum(-1), noderice.GetDateStr(-1),
        noderice.GetDateNum(-2), noderice.GetDateNum(-8), noderice.GetDateNum(-31) );
    event_dayreport.startOneDayTask(noderice.GetDateNum(-1));
    pay_dayreport.startOneDayTask(noderice.GetDateNum(-1), noderice.GetDateStr(-1));
  });

  // 执行每小时的任务-1
  var rule2 = new schedule.RecurrenceRule();
  rule2.dayOfWeek = [0, new schedule.Range(1, 6)];
  var minutes = [];
  // for(var i=0;i<60;i++) {
  //   minutes.push(i);
  // }
  minutes.push(1);
  minutes.push(11);
  minutes.push(21);
  minutes.push(31);
  minutes.push(41);
  minutes.push(51);
  rule2.minute = minutes;
  schedule.scheduleJob(rule2, function() { // 执行小时报表
    console.log('rule2 working ... ');
    channel_dayreport.startOneDayTask(noderice.GetDateNum(0), noderice.GetDateStr(0),
        noderice.GetDateNum(-1), noderice.GetDateNum(-7), noderice.GetDateNum(-30));
    event_dayreport.startOneDayTask(noderice.GetDateNum(0));
    pay_dayreport.startOneDayTask(noderice.GetDateNum(0), noderice.GetDateStr(0));
    rank.startTask();
  });

  // 执行每小时的任务-2
  var rule3 = new schedule.RecurrenceRule();
  rule3.dayOfWeek = [0, new schedule.Range(1, 6)];
  rule3.minute = 4;
  schedule.scheduleJob(rule3, function() { // 执行小时报表
    console.log('rule3 working ... ');
    rank.startTask();
  });
}

exports.init = init;

// setTimeout(updateReqMoney,3*10*1000);
