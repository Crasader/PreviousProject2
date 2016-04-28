'use strict';

var get_info_count = 0;
var NEED_RELOAD_TIMES = 20; // 多少个玩家请求过数据后重新产生信息
var room_player_info;
var room_player_info_str;

/**
 * 获取房间人数协议
 * TODO : 当前没有判断游戏版本。后期根据不同的版本响应不同的信息
 */
function getRoomPlayerInfoStr(game_version){
  if(get_info_count === 0) {
    room_player_info = getRoomPlayerInfo();
    room_player_info_str = JSON.stringify(room_player_info);
  }
  get_info_count++;
  if(get_info_count >= NEED_RELOAD_TIMES) {
    get_info_count = 0;
  }
  return room_player_info_str;
}

exports.getRoomPlayerInfoStr = getRoomPlayerInfoStr;

function getRoomPlayerInfo() {
  var currentHour = ( 1+ new Date().getHours() );
  var room_player_info = {
    errorcode : 0,
    room_lists : [
      {room_id : 1, player_nums : getPlayerCounts(currentHour, 1), require_turrent_level : 1},
      {room_id : 2, player_nums : getPlayerCounts(currentHour, 2), require_turrent_level : 30},
      {room_id : 3, player_nums : getPlayerCounts(currentHour, 3), require_turrent_level : 100},
      {room_id : 4, player_nums : getPlayerCounts(currentHour, 4), require_turrent_level : 300}
    ]
  };
  return room_player_info;
}


var room1Players = 0;
var room2Players = 0;
var room3Players = 0;
var room4Players = 0;

function getPlayerCounts(currentHour, roomId) {
    if(roomId < 1 || roomId > 4) {
        roomId = 4;
    }
    var base = 0;
    if(currentHour <= 8) {
        base = -0.8;
    }else if(currentHour <= 18) {
        base = -0.4;
    }else if(currentHour <= 22) {
        base = 0;
    }else {
        base = -0.4;
    }
    if(roomId == 1) {
        if(room1Players == 0) {
            room1Players = parseInt((1+base)*12000) + parseInt(4000*Math.random()) ;
        }else {
            room1Players = room1Players - parseInt(room1Players/20) + parseInt( (room1Players/10+1)*Math.random() ) ;
        }
        if(room1Players <= 3000) {
            room1Players = 3000 +  parseInt(2000*Math.random());
        }
        return  room1Players;
    }else if(roomId == 2) {
        if(room2Players == 0) {
            room2Players = parseInt((1+base)*6000) + parseInt(4000*Math.random()); //6000-10000
        }else {
            room2Players = room2Players - parseInt(room2Players/20) + parseInt( (room2Players/10+1)*Math.random() );
        }
        if(room2Players <= 1000) {
            room2Players = 1000 + parseInt(1000*Math.random());
        }
        return  room2Players;
    }else if(roomId == 3) {
        if(room3Players == 0) {
            room3Players = parseInt((1+base)*4000) + parseInt(4000*Math.random()); //4000-8000
        }else {
			room3Players = room3Players-parseInt(room3Players / 20) + parseInt( (room3Players/10+1)*Math.random() );
        }
        if(room3Players <= 500) {
            room3Players = 500 + parseInt(500*Math.random());
        }
        return room3Players;
    }else if(roomId == 4) {
        if(room4Players == 0) {
            room4Players = parseInt((1+base)*500) + parseInt(1000*Math.random()); //500-1500
        }else {
			room4Players = room4Players-parseInt(room4Players / 20) + parseInt( (room4Players/10+1)*Math.random() );
        }
        if(room4Players <= 50) {
            room4Players =  50 + parseInt(50*Math.random());
        }
        return room4Players;
    }

    return 2357 + parseInt(300*Math.random());
}
