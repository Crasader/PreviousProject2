/**
 * 渠道日报的一天统计任务
 */
var dbmanager_catchfish = require('../../../db/dbmanager_catchfish.js');
var rank_db = require('./rank_db.js');

/**
 * 进行一次排名计算
 */
function startTask() {
  console.log('[rank]startTask ...');
  coinsRank(); // 进行一次金币排名计算
  expRank(); // 进行一次经验排名计算
}

function coinsRank() {
  rank_db.getCoinsRank(dbmanager_catchfish.getClientS(),
      function(success, results) {
    if(success && results.length > 0) {
      var items = [];
      var update_time = new Date().Format("yyyy-MM-dd hh:mm:ss:S");
      for(var i=0;i<results.length; i++) {
        var item = [i+1, results[i]['user_name'], results[i]['gender'],
            results[i]['exp'], results[i]['coins'],  getVipLevel(parseInt(results[i]['mo'])), update_time ];
        items[i] = item;
      }
      rank_db.insertCoinsRank(dbmanager_catchfish.getClient(), items, function(success) {
      });
    }
  });
}

function expRank() {
  rank_db.getExpRank(dbmanager_catchfish.getClientS(),
      function(success, results) {
    if(success && results.length > 0) {
      var items = [];
      var update_time = new Date().Format("yyyy-MM-dd hh:mm:ss:S");
      for(var i=0;i<results.length; i++) {
        var item = [i+1, results[i]['user_name'], results[i]['gender'],
            results[i]['exp'], results[i]['coins'],  getVipLevel(parseInt(results[i]['mo'])), update_time ];
        items[i] = item;
      }
      rank_db.insertExpRank(dbmanager_catchfish.getClient(), items, function(success) {
      });
    }
  });
}

function getVipLevel(mo) {
  if(mo < 20) {
    return 0;
  }else if(mo < 200) {
    return 1;
  }else if(mo < 500) {
    return 2;
  }else if(mo < 1000) {
    return 3;
  }else if(mo < 2000) {
    return 4;
  }else if(mo < 5000) {
    return 5;
  }else if(mo < 10000) {
    return 6;
  }else if(mo < 20000) {
    return 7;
  }else if(mo < 50000) {
    return 8;
  }else if(mo >= 50000) {
    return 9;
  }
  return 0;
}

exports.startTask = startTask;
