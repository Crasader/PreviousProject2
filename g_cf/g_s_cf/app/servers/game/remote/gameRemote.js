'use strict';
module.exports = function(app) {
	return new GameRemote(app);
};



var GameRemote = function(app) {
	this.app = app;
	this.channelService = app.get('channelService');
};

var fishManager = require('../../../domain/fish/fish_manager.js');
var mermaid_manager = require('../../../domain/mermaid/mermaid_manager.js');
var game = require('../../../domain/game/game.js');
var cgsdk = require('../../../domain/cgsdk/cgsdk.js');
var redishelper = require('../../../environment/mem/redishelper.js');
redishelper.firstInit();
var dbmanager = require('../../../environment/db/dbmanager.js');
dbmanager.firstInit();

var ai_manager = require('../domain/ai_manager.js');


var USER_NAME_HEAD = 'g_';

/**
 * Add user into game channel.
 *
 * @param {String} uid unique id for user
 * @param {String} sid server id
 * @param {String} name channel name
 * @param {boolean} flag channel parameter
 *
 */
GameRemote.prototype.add = function(uid, room_id, sid, name, flag, cb) {

	var self = this;
	(function(self, uid, sid, name, flag, cb){
		cgsdk.getPlayerBaseInfoBySessionId(uid, function(success, result){ // 从游戏服务器获取信息
			var catch_per = 1;	// 默认捕获概率
			if(!success) {
				cb(-3, [], {}, {});
				return ;
			}

			var resultObj = result;
			console.log('molo_gameRemote->add, cgsdk result : ' + JSON.stringify(resultObj));
			if(parseInt(resultObj.errorcode) !== 0) {
				cb(-1, [], {}, {});
				return ;
			}

			if( !game.allowEnter(parseInt(room_id), parseInt(resultObj.user_info.turrent_level) ) ) {	// 判断roomid和进入条件
				cb(-2, [], {}, {});
				return ;
			}
			// 计算捕获概率
			if(resultObj.user_info.chest_level === 1) {
				catch_per = 1.03;
			}else if(resultObj.user_info.chest_level === 2) {
				catch_per = 1.06;
			}else if(resultObj.user_info.chest_level === 3) {
				catch_per = 1.1;
			}
			var userInfo = {
				uid : uid,
				user_id : resultObj.user_info.user_id,
				room_id : parseInt(room_id),
				nick_name : resultObj.user_info.nick_name,
				coins : resultObj.user_info.coins,
				diamonds : resultObj.user_info.diamonds,
				exps : resultObj.user_info.exps,
				turrent_level : resultObj.user_info.turrent_level,
				chest_level : resultObj.user_info.chest_level,
				mo : resultObj.user_info.mo,
				mermaid_task_info : {
					task_id : 0,
					coins : 0,
			    success : 0
				},
				max_coins : -1,
				catch_per : catch_per,
				fire_diamonds : 0,	// 用来记录玩家的跑数，决定如何赠送钻石
				fire_items : 0,			// 用来统计玩家的跑数，决定如何赠送道具
				vip_level : 0,
				r_pos : 0,
				room_id : parseInt(room_id),
				item_lists : []
			};
			console.log('gameRemote->add, cgsdk userInfo : ' + JSON.stringify(userInfo));
			game.userMap.set(game.USER_KEY_HEAD + uid, userInfo);	// 本地缓存用户信息

			// 推送美人鱼任务
			var current_task_info = mermaid_manager.getCurrentTaskInfo();
			if(parseInt(room_id) > 1 && current_task_info !== null ) {
				var mermaid_info = {
					task_id : current_task_info.task_id,
		      fish_ids : current_task_info.fish_ids,
		      left_times : mermaid_manager.getTaskLeftTime(current_task_info.start_time)
				};
				self.channelService.pushMessageByUids('mermaidTask', mermaid_info, [{
					uid: uid,
					sid: sid
				}]);
			}

			// 推送奖金池信息
			cgsdk.getPlayerBonuspoolInfoBySessionId(userInfo.uid, function(success, result){
				if(success) {
					var user_bonuspool_obj = JSON.parse(result);
					console.log('BonuspoolInfo : ' + result);
					// if(user_bonuspool_obj.errorcode == 0 && user_bonuspool_obj.fish_nums > 0) {
						self.channelService.pushMessageByUids('BonuspoolInfo', user_bonuspool_obj, [{
							uid: uid,
							sid: sid
						}]); // TODO : 感觉通过channel发并不是最好的方式，最好通过notify直接发
					// }
				}
			});

			var channel = self.channelService.getChannel(name, flag);
			var members = self.get(channel, name, flag); // TODO : 此处只有用户的id信息，没有组装好用户的数据信息
			var userinfos = [];

			var allowPos = [true, true, true, true];
			for(var i=0;i<members.length;i++) {
				userinfos[i] = game.userMap.get(game.USER_KEY_HEAD + members[i]);
				allowPos[userinfos[i].r_pos - 1] = false;
			}
			for(var i=0;i<allowPos.length;i++) {
				if(allowPos[i]) {
					userInfo.r_pos = i + 1;
					break;
				}
			}
			if(userinfos.length < 4) { // 考虑补充机器人
				userinfos = getNewUserInfos( userinfos, parseInt(room_id) );
			}

			(function(self, userInfo){
				cgsdk.getPlayerBagInfoBySessionId(userInfo.uid, function(success, result){
					if(success) {
						userInfo.item_lists = result.item_lists;
						console.log('gameRemote->add, init userinfo : ' + JSON.stringify(userInfo));
						game.userMap.set(game.USER_KEY_HEAD + userInfo.uid, userInfo);
						cb(userInfo.r_pos, userinfos, fishManager.getInitFishGroup(), userInfo);

						if(userInfo.coins <= 0) {	// 判断是否需要同步破产宝箱信息
							cgsdk.bankruptBrokeStateByUserId(userInfo.user_id, function(success, result){
								if(success) {
									self.channelService.pushMessageByUids('bankruptBroke', result, [{
										uid: uid,
										sid: sid
									}]);
								}
							});
						}
					}
				});
			})(self, userInfo);

			if( !! channel) {
				var param = {
					route: 'onAdd',
					user_info : userInfo
				};
				channel.pushMessage(param);
				channel.add(uid, sid);
			}
		});
	})(self, uid, sid, name, flag, cb);

};

/**
 * Get user from game channel.
 *
 * @param {Object} opts parameters for request
 * @param {String} name channel name
 * @param {boolean} flag channel parameter
 * @return {Array} users uids in channel
 *
 */
GameRemote.prototype.get = function(channel, name, flag) {
	if( !! channel) {
		var result = channel.getMembers();
	}
	return result;
};

/**
 * Kick user out game channel.
 *
 * @param {String} uid unique id for user
 * @param {String} sid server id
 * @param {String} name channel name
 *
 */
GameRemote.prototype.kick = function(uid, sid, name, cb) {
	var channel = this.channelService.getChannel(name, false);

	var userinfo = game.userMap.get(game.USER_KEY_HEAD + uid);
	var user_r_pos = userinfo == undefined ?  0 : userinfo.r_pos;
	var param = {
		r_pos: user_r_pos
	};

	if( !! channel) {	// leave channel
		channel.leave(uid, sid);
		channel.pushMessage('onLeave', param);
	}

	game.userMap.delete(game.USER_KEY_HEAD + uid);	// 清除用户缓存信息
	cb();
};

function getNewUserInfos( userinfos, room_id ) {
	var random = parseInt(Math.random()*100);
	var require_nums = 4;

	if(random <= 10) {	// TODO : 后期根据房间号产生不同的数值
		require_nums = 2;
	} else if(random <= 40) {
		require_nums = 3;
	}

	if(userinfos.length >= require_nums) {
		return userinfos;
	}
	var need_add = require_nums - userinfos.length;
	console.log('need_add ai is : ' + need_add);
	for(var i=0; i<need_add; i++) {
		var turrent_level = ai_manager.getTurrentLevel(room_id);
		var item = {
			nick_name : '' + parseInt(Math.random()*100000),
			turrent_level : turrent_level,
			coins : ai_manager.getCoins(turrent_level),
			diamonds : ai_manager.getDiamonds(turrent_level),
			exps : ai_manager.getExps(turrent_level),
			chest_level : ai_manager.getCheskLevel(turrent_level),
			vip_level : 0,	// TODO  :通过mo产生
			mo : 0,
			catch_per : 1,
			r_pos : 0
		};
		userinfos.push(item);
	}
	return userinfos;
}
