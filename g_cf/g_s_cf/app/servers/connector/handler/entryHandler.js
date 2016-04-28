module.exports = function(app) {
	return new Handler(app);
};

var Handler = function(app) {
	this.app = app;
	c_app_id = app.getServerId();
	console.log('!!c_app_id = ' + c_app_id);
};

var handler = Handler.prototype;

var roomManager = require('../../../domain/room/roomManager');

var c_app_id;
/**
 * New client entry game server.
 *
 * @param  {Object}   msg     request message
 * @param  {Object}   session current session object
 * @param  {Function} next    next stemp callback
 * @return {Void}
 */
handler.enter = function(msg, session, next) {
	var self = this;
	console.log('enter.msg : ' + JSON.stringify(msg));
	var room_id = msg.room_id;
	if(room_id === undefined || room_id === null) {	// 兼容老版本
		room_id = 1;
	}
	var rid = c_app_id + '_' + room_id + '_' + roomManager.getRoomIdForNewUser();
	var uid = msg.username;
	var sessionService = self.app.get('sessionService');

	// TODO : 增加用户信息格式的效验(uid需要以'TBU_'开头)

	//duplicate log in
	if( !! sessionService.getByUid(uid)) {
		next(null, {
			errorcode: 500,
			errormsg: 'session timeout'
		});
		return;
	}

	session.bind(uid);
	session.set('rid', rid);
	session.push('rid', function(err) {
		if(err) {
			console.error('set rid for session service failed! error is : %j', err.stack);
		}
	});
	session.on('closed', onUserLeave.bind(null, self.app));

	// put user into channel
	self.app.rpc.game.gameRemote.add(session, uid, room_id, self.app.get('serverId'), rid, true, function(result_code, users, fishes, my_info){
		if(result_code === -1) {
			next(null, {
				errorcode: 501,
				errormsg: 'error user id'
			});
			return ;
		}else if(result_code === -2) {
			next(null, {
				errorcode: 502,
				errormsg: 'need more turrent_level'
			});
			return ;
		}else if(result_code === -3) {
			next(null, {
				errorcode: 500,
				errormsg: 'server error'
			});
			return ;
		}

		console.log('[init_add]users : ' + JSON.stringify(users));

		next(null, {
			errorcode: 0,
			users : users,
			fishes : fishes,
			my_info : my_info,
			bullet_speed : 1100,	// TODO : 目前写死的配置
			bullet_interval : 0.2,
			create_time : new Date().getTime()
		});
	});

};

function enterLogic(msg, session, next, rid) {

};

/**
 * User log out handler
 *
 * @param {Object} app current application
 * @param {Object} session current session object
 *
 */
var onUserLeave = function(app, session) {
	if(!session || !session.uid) {
		return;
	}
	roomManager.userLeaveOneRoom(session.get('rid').substring(c_app_id.length + 1));
	app.rpc.game.gameRemote.kick(session, session.uid, app.get('serverId'), session.get('rid'), function(){
		console.log('onUserLeave callback ..........' + session.uid);
	});
};
