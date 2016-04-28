/**
 * fishNormalManager : 普通鱼群生成算法
 * 2016-03-16
 * 本逻辑灵感来自康俊!!
 */

var config_1 = require('../../../config/domain/config_eight_type1.json');
var config_2 = require('../../../config/domain/config_eight_type2.json');
var config_3 = require('../../../config/domain/config_eight_type3.json');

var MAX_TIME = 300;
var normal_group_data = [];


function createNormalFile(normal_type) {
  for(var i=0;i<15;i++) { // TODO : 15为切分片数
    normal_group_data[i] = [];
  }
  var config_file = getConfigFile(normal_type);
  for( var i=0; i<config_file.launching_points.length; i++ ) {
    var interval_random = parseInt(config_file.launching_points[i].interval_time_end) -
        parseInt(config_file.launching_points[i].interval_time_start);
    var interval_time = parseInt(config_file.launching_points[i].interval_time_start) +
      parseInt(Math.random()*interval_random);
    var start_time = interval_time;
    while(start_time < MAX_TIME) {
      var result_items = getBaseItem(start_time, config_file.launching_points[i].item_list);
      for(var j=0; j<result_items.length; j++) {
        normal_group_data[ parseInt(parseInt(result_items[j].time)/20) ].push(result_items[j]); // TODO : 20为时间片
      }
      start_time += interval_time;
    }
  }
  return normal_group_data;
}

exports.createNormalFile = createNormalFile;

//--------------------------------------------------------------------------------
// --内部方法--

function getBaseItem(start_time, config_item_lists) {
  var results = [];

  for(var j=0; j<config_item_lists.length; j++) {
    var random_waittime = parseInt(config_item_lists[j].wait_time_end) -
        parseInt(config_item_lists[j].wait_time_start)
    var wait_time = start_time + parseInt(config_item_lists[j].wait_time_start) + parseInt(Math.random()*random_waittime);

    var random_fishs = parseInt(Math.random()*(
      parseInt(config_item_lists[j].count_end) - parseInt(config_item_lists[j].count_start)
    ) + 1);
    if(wait_time < MAX_TIME) {
      for( var k=0; k<random_fishs; k++ ) {
        var item = {
          time : wait_time,
          fish_ids : getFishId(config_item_lists[j].fish_id),
          fish_route : getRoute(config_item_lists[j].fishRoute)
        };
        results.push(item);
      }
    }

  }
  return results;
}

function getFishId(fishes) {
  if(fishes.length === 1) {
    return fishes[0];
  }
  return fishes[parseInt(Math.random()*fishes.length)];
}

function getRoute(routes) {
  if(routes === undefined || routes === null) {
    return -1;
  }
  if(routes.length === 1) {
    return routes[0];
  }
  return routes[parseInt(Math.random()*routes.length)];
}

function getConfigFile(normal_type) {
  if(normal_type === 1) {
    return config_1;
  } else if(normal_type === 2) {
    return config_2;
  } else if(normal_type === 3) {
    return config_3;
  }
  return config_1;
}

//--------------------------------------------------------------------------------
// --TEST--
// console.log( JSON.stringify( createNormalFile(config_1) ) );
