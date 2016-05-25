'use strict';
// TODO : 后期改到数据库中配置

var task_lists = [
  {
    every_task_id : 1,
    task_content : '捕获10条黄金鱼',
    content_pic_url : '',
    reward_lists : [
      {item_id : 1002, nums : 10}
    ],
    to_page : 2,  // 进入页面.1-大厅;2-游戏, 14-分享
    level_direction : 0, // 0， 要求小于， 1，要求大于
    level_require : 0,
    task_require_nums : 10, // 任务要求的数目
    current_nums : 12, // 当前数目[TODO : 默认给0]
    user_get : 0  // 是否已经领取
  },
  {
    every_task_id : 2,
    task_content : '使用5次道具',
    content_pic_url : '',
    reward_lists : [
      {item_id : 1004, nums : 1} // 锁定
    ],
    to_page : 2,  // 进入页面.1-大厅;2-游戏, 14-分享
    level_direction : 0, // 0， 要求小于， 1，要求大于
    level_require : 0,
    task_require_nums : 5, // 任务要求的数目
    current_nums : 5, // 当前数目[TODO : 测试，默认为0]
    user_get : 0  // 是否已经领取
  },
  {
    every_task_id : 3,
    task_content : '升级2次炮塔',
    content_pic_url : '',
    reward_lists : [
      {item_id : 1001, nums : 1000}
    ],
    to_page : 2,  // 进入页面.1-大厅;2-游戏, 14-分享
    level_direction : 0, // 0， 要求小于， 1，要求大于
    level_require : 300,
    task_require_nums : 2, // 任务要求的数目
    current_nums : 2, // [TODO ]当前数目
    user_get : 0  // 是否已经领取
  },
  {
    every_task_id : 4,
    task_content : '分享内容',
    content_pic_url : '',
    reward_lists : [
      {item_id : 1003, nums : 1} //冰冻
    ],
    to_page : 14,  // 进入页面.1-大厅;2-游戏, 14-分享
    level_direction : 1, // 0， 要求小于， 1，要求大于
    level_require : 300,
    task_require_nums : 1, // 任务要求的数目
    current_nums : 0, // 当前数目
    user_get : 0  // 是否已经领取
  }
];

function getEveryTask(turrent_level) {
  console.log('getEveryTask : turrent_level = ' + turrent_level);
  var turrent_level = parseInt(turrent_level);
  var everyday_task_config = {
    errorcode : 0,
    task_lists : []
  };
  for(var i=0; i<task_lists.length;i++) {
    if(task_lists[i].level_require === 0 ||
        ( task_lists[i].level_direction === 0 && turrent_level < task_lists[i].level_require ) ||
        ( task_lists[i].level_direction === 1 && turrent_level >= task_lists[i].level_require ) ) {
      everyday_task_config.task_lists.push(task_lists[i]);
    }
  }
  console.log('getEveryTask : everyday_task_config = ' + JSON.stringify(everyday_task_config));
  return everyday_task_config;
}

exports.getEveryTask = getEveryTask;



var achievement_lists = [
  {
    achievement_task_id : 1,
    title_desc : '钢铁护甲',
    title_pic_url : '',
    icon_pic_url : '',
    to_page : 15,  // 进入页面.1-大厅;2-游戏, 14-分享;15-绑定手机号
    tasks : [
      {
        task_content : '账号绑定手机号码',
        task_require_nums : 1, // 任务要求的数目
        reward_lists : [
          {item_id : 1002, nums : 20}
        ]
      }
    ]
  },
  {
    achievement_task_id : 2,
    title_desc : '闲海信步',
    title_pic_url : '',
    icon_pic_url : '',
    to_page : 15,
    tasks : [
      {
        task_content : '使用自动发射功能',
        task_require_nums : 1,
        reward_lists : [
          {item_id : 1001, nums : 5000}
        ]
      }
    ]
  },
  {
    achievement_task_id : 3,
    title_desc : '辛勤渔夫',
    icon_pic_url : '',
    title_pic_url : '',
    to_page : 15,
    tasks : [
      {
        task_content : '累计捕获300条鱼',
        task_require_nums : 300,
        reward_lists : [
          {item_id : 1002, nums : 10}
        ]
      },
      {
        task_content : '累计捕获3000条鱼',
        task_require_nums : 3000,
        reward_lists : [
          {item_id : 1002, nums : 50}
        ]
      },
      {
        task_content : '累计捕获10000条鱼',
        task_require_nums : 10000,
        reward_lists : [
          {item_id : 1002, nums : 150}
        ]
      },
      {
        task_content : '累计捕获50000条鱼',
        task_require_nums : 50000,
        reward_lists : [
          {item_id : 1002, nums : 300}
        ]
      }
    ]
  }
];

var default_task_lists = null;

function getDefaultTask() {
  if(default_task_lists === null) {
    default_task_lists = createDefaultTaskLists();
  }
  return default_task_lists;
}

exports.getDefaultTask = getDefaultTask;

function createDefaultTaskLists() {
  var task_lists = [];
  for(var i=0;i<achievement_lists.length;i++) {
    if(achievement_lists[i].tasks.length > 0) {
      var item = {
        achievement_task_id : achievement_lists[i].achievement_task_id,
        title_desc : achievement_lists[i].title_desc,
        title_pic_url : achievement_lists[i].title_pic_url,
        icon_pic_url : achievement_lists[i].icon_pic_url,
        task_content : achievement_lists[i].tasks[0].task_content,
        reward_lists : achievement_lists[i].tasks[0].reward_lists,
        to_page : achievement_lists[i].to_page,
        max_level : achievement_lists[i].tasks.length,
        current_level : 1,  // 当前等级
        task_require_nums : achievement_lists[i].tasks[0].task_require_nums,
        current_nums : 0, // 当前数目
        user_get : 0  // 是否已经领取.0未领取。1，领取
      };
      task_lists.push(item);
    }
  }
  return task_lists;
}

function getPlayerTask(player_taskinfos) {
  return createPlayerTaskLists(player_taskinfos);
}

exports.getPlayerTask = getPlayerTask;

function createPlayerTaskLists(player_taskinfos) {
  var task_lists = [];
  for(var i=0;i<achievement_lists.length;i++) {
    if(achievement_lists[i].tasks.length > 0) {
      var item = null;
      for(j=0;j<player_taskinfos.length;j++){
        if(parseInt(player_taskinfos[j]['task_id']) === achievement_lists[i].achievement_task_id) {
          var pos = parseInt(player_taskinfos[j]['current_level']) > 0 ?
              parseInt(player_taskinfos[j]['current_level']) - 1 : 0;
          item = {
            achievement_task_id : achievement_lists[i].achievement_task_id,
            title_desc : achievement_lists[i].title_desc,
            title_pic_url : achievement_lists[i].title_pic_url,
            icon_pic_url : achievement_lists[i].icon_pic_url,
            task_content : achievement_lists[i].tasks[pos].task_content,
            reward_lists : achievement_lists[i].tasks[pos].reward_lists,
            to_page : achievement_lists[i].to_page,
            max_level : achievement_lists[i].tasks.length,
            current_level : parseInt(player_taskinfos[j]['current_level']),  // 当前等级
            task_require_nums : achievement_lists[i].tasks[pos].task_require_nums,
            current_nums : parseInt(player_taskinfos[j]['current_nums']), // 当前数目
            user_get : parseInt(player_taskinfos[j]['user_get'])  // 是否已经领取.0未领取。1，领取
          };
          break;
        }

      }
      if(item === null) {
        item = {
          achievement_task_id : achievement_lists[i].achievement_task_id,
          title_desc : achievement_lists[i].title_desc,
          title_pic_url : achievement_lists[i].title_pic_url,
          icon_pic_url : achievement_lists[i].icon_pic_url,
          task_content : achievement_lists[i].tasks[0].task_content,
          reward_lists : achievement_lists[i].tasks[0].reward_lists,
          to_page : achievement_lists[i].to_page,
          max_level : achievement_lists[i].tasks.length,
          current_level : 1,  // 当前等级
          task_require_nums : achievement_lists[i].tasks[0].task_require_nums,
          current_nums : 0, // 当前数目
          user_get : 0  // 是否已经领取.0未领取。1，领取
        };
      }
      task_lists.push(item);
    }
  }
  return task_lists;
}

function getAchievementRequireNums(task_id, current_level) {
  for(var i=0; i<achievement_lists.length;i++) {
    if(achievement_lists[i].achievement_task_id === task_id) {
      for(var j=0;j<achievement_lists[i].tasks.length;j++) {
        if(j === current_level){
          return achievement_lists[i].tasks[j].task_require_nums;
        }
      }
      return 0;
    }
  }
  return 0;
}

exports.getAchievementRequireNums = getAchievementRequireNums;

function getAchievementRewards(task_id, current_level){
  for(var i=0; i<achievement_lists.length;i++) {
    if(achievement_lists[i].achievement_task_id === task_id) {
      for(var j=0;j<achievement_lists[i].tasks.length;j++) {
        if( (j+1) === current_level ){
          return achievement_lists[i].tasks[j].reward_lists;
        }
      }
      return [];
    }
  }
  return [];
}

exports.getAchievementRewards = getAchievementRewards;

function getNextLevelInfo(task_id, current_level) {
  for(var i=0; i<achievement_lists.length;i++) {
    if(achievement_lists[i].achievement_task_id === task_id) {
      for(var j=0;j<achievement_lists[i].tasks.length;j++) {
        if( j === current_level){
          return {
            achievement_task_id : achievement_lists[i].achievement_task_id,
            title_desc : achievement_lists[i].title_desc,
            title_pic_url : achievement_lists[i].title_pic_url,
            icon_pic_url : achievement_lists[i].icon_pic_url,
            task_content : achievement_lists[i].tasks[j].task_content,
            reward_lists : achievement_lists[i].tasks[j].reward_lists,
            to_page : achievement_lists[i].to_page,
            max_level : achievement_lists[i].tasks.length,
            current_level : j+1,  // 当前等级
            task_require_nums : achievement_lists[i].tasks[j].task_require_nums,
            current_nums : 0, // 当前数目
            user_get : 0  // 是否已经领取.0未领取。1，领取
          };
        }
      }
      return null;
    }
  }
  return null;
}

exports.getNextLevelInfo = getNextLevelInfo;
