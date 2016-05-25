'use strict';
// TODO : 当前的逻辑下，只能开单个的游戏服务器实例
module.exports = function(app) {
  return new Cron(app);
};

var fishManager = require('../../../domain/fish/fish_manager.js');
var mermaid_manager = require('../../../domain/mermaid/mermaid_manager.js');

var Cron = function(app) {
  fishManager.init();
  this.app = app;
  this.channelService = this.app.get('channelService');

};
var cron = Cron.prototype;

var count = 1;

cron.updatePer20Sec = function() {
  fishManager.oneStepWorking();
  this.sendFishGroupInfo();
  var new_task_info = mermaid_manager.nextStep(20); // 更新美人鱼任务时间往前走20秒
  if(new_task_info !== null) {
    var mermaid_info = {
      task_id : new_task_info.task_id,
      fish_ids : new_task_info.fish_ids,
      left_times : new_task_info.task_time
    };
    this.sendMermaidInfo(mermaid_info);
  }
};

cron.sendMermaidInfo = function(mermaid_info) {
  // 获取数据要从远程方法里面去调用，保证在同一个实例中
  // 后期mo类型游戏的时候这个问题就会变得更为简单，因为每一个房间要维持唯一的实例
  var self = this;
  self.channelService.broadcast('connector' ,'mermaidTask', mermaid_info, {binded: true}, function(err){
     if(err){
         console.log(err);
     }
  });
};

cron.sendFishGroupInfo = function() {
  // 获取数据要从远程方法里面去调用，保证在同一个实例中
  // 后期mo类型游戏的时候这个问题就会变得更为简单，因为每一个房间要维持唯一的实例
  var self = this;
  (function(self) {
    var routeParam = {};
    self.app.rpc.world.worldRemote.getNewMsgs(routeParam, function(events_msg){
      var paramNew = {
        msg     : fishManager.getOnceFishGroup(),
        events  : events_msg
      };
      self.channelService.broadcast('connector' ,'onFishes', paramNew, {binded: true}, function(err){
         if(err){
             console.log(err);
         }
      });
    });
  })(self);
};
