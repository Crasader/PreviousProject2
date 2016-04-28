
var MAX_ONEROOM_USERS = 4;  // 一个房间最大的用户数

var hasIdleRoom = new Map();  // 还有座位的房间列表
var fullRoom = new Map(); // 满座的房间列表

/**
 * 为新用户分配房间
 *
 */
function getRoomIdForNewUser() {
  var roomInfo;
  if(hasIdleRoom.size > 0) {
    roomInfo = getIdleRoomId();
    console.log('[getRoomIdForNewUser][hasIdleRoom]roomInfo : ' + JSON.stringify(roomInfo));
    if(roomInfo.value >= MAX_ONEROOM_USERS) {
      hasIdleRoom.delete(roomInfo.key);
      fullRoom.set(roomInfo.key, roomInfo.value);
    } else {
      hasIdleRoom.set(roomInfo.key, roomInfo.value);
    }
  } else {
    roomInfo = {
      key : getNewRoomId(),
      value : 1
    };
    console.log('[getRoomIdForNewUser][noIdleRoom]roomInfo : ' + JSON.stringify(roomInfo));
    hasIdleRoom.set(roomInfo.key, roomInfo.value);
  }
  return roomInfo.key;
}

/**
 * 取出一个空闲的房间id
 *
 * @param {String} roomId 房间编号
 */
function userLeaveOneRoom(roomId) {
  console.log('userLeaveOneRoom roomId : ' + roomId);
  if( fullRoom.size > 0 && fullRoom.has(roomId) ) {
    var value = fullRoom.get(roomId);
    // console.log('----userLeaveOneRoom [fullRoom]fullRoom.size = ' + fullRoom.size);
    fullRoom.delete(roomId);
    // console.log('----userLeaveOneRoom [fullRoom]fullRoom.size = ' + fullRoom.size);
    // console.log('----userLeaveOneRoom [fullRoom]hasIdleRoom.size = ' + hasIdleRoom.size);
    hasIdleRoom.set(roomId, (value - 1) );
    // console.log('----userLeaveOneRoom [fullRoom]hasIdleRoom.size = ' + hasIdleRoom.size);
    // console.log('--userLeaveOneRoom [fullRoom]roomId = ' + roomId);
  } else if( hasIdleRoom.size > 0 && hasIdleRoom.has(roomId) ) {
    var value = hasIdleRoom.get(roomId);
    if(value <= 1) {
      hasIdleRoom.delete(roomId);
      addRoomId(roomId);
    } else {
      hasIdleRoom.set(roomId, (value - 1) );
    }
    // console.log('--userLeaveOneRoom [hasIdleRoom]roomId = ' + roomId);
  }
}

exports.getRoomIdForNewUser = getRoomIdForNewUser;
exports.userLeaveOneRoom = userLeaveOneRoom;

var freeRoomIdPos = 1;
var freeRoomIds = new Array();

/**
 * 产生一个新的房间号
 *
 */
function getNewRoomId() {
  var roomId = freeRoomIdPos;
  if(freeRoomIds.length > 0) {
    roomId = freeRoomIds.shift();
  } else {
    freeRoomIdPos++;
  }
  return roomId;
}

/**
 * 添加一个可用的空房间
 *
 */
function addRoomId(roomId) {
  freeRoomIds.push(roomId);
}

/**
 * 取出一个空闲的房间id
 *
 */
function getIdleRoomId() {
  var BreakException= {};
  var roomInfo;

  try{
    hasIdleRoom.forEach(function(value, key) {
      roomInfo = {
        key : key,
        value : parseInt(value) + 1
      };
      throw BreakException;
    }, hasIdleRoom);
  }catch(e) {
    if (e!==BreakException) throw e;
  }

  return roomInfo;

}

// function test() {
//   for(var i=0;i<24;i++) {
//     getRoomIdForNewUser();
//   }
//   console.log('[step1]freeRoomIds.length = ' + freeRoomIds.length);
//   console.log('--------------------------------------------------');
//   for(var i=3;i<5;i++) {
//     for(var j=0;j<4;j++) {
//       userLeaveOneRoom(i);
//     }
//   }
//   console.log('[step2]freeRoomIds.length = ' + freeRoomIds.length);
//   console.log('--------------------------------------------------');
//   for(var i=0;i<8;i++) {
//     getRoomIdForNewUser();
//   }
//   console.log('[step3]freeRoomIds.length = ' + freeRoomIds.length);
// }

// function test() {
//   getRoomIdForNewUser();
//   getRoomIdForNewUser();
//   getRoomIdForNewUser();
//   getRoomIdForNewUser();
//   console.log('--test fullRoom.size = ' + fullRoom.size);
//   console.log('--test hasIdleRoom.size = ' + hasIdleRoom.size);
//   getRoomIdForNewUser();
//   userLeaveOneRoom(1);
//   getRoomIdForNewUser();
//   getRoomIdForNewUser();
//   getRoomIdForNewUser();
//   getRoomIdForNewUser();
//   console.log('--test fullRoom.size = ' + fullRoom.size);
//   console.log('--test hasIdleRoom.size = ' + hasIdleRoom.size);
//   getRoomIdForNewUser();
// }
//
// test();
