'use strict';

module.exports = function(app) {
	return new Handler(app);
};

var game = require('../../../domain/game/game.js');
var cgsdk = require('../../../domain/cgsdk/cgsdk.js');
var gametask_everyday_manager = require('../../../domain/cgsdk/gametask/gametask_everyday_manager.js');
var gametask_achievement_manager = require('../../../domain/cgsdk/gametask/gametask_achievement_manager.js');
var pay_service = require('../../../domain/cgsdk/pay/pay_service.js');

var mermaid_manager = require('../../../domain/mermaid/mermaid_manager.js');

var Handler = function(app) {
	this.app = app;
	this.channelService = app.get('channelService');
};

var handler = Handler.prototype;

/**
 * 用户同步事件到服务端
 *
 * @param {Object} msg message from client
 * @param {Object} session
 * @param {Function} next next stemp callback
 *
 */
handler.newevents = function(msg, session, next) {
	console.log('newevents coming, msg : ' + JSON.stringify(msg));
	var self = this;
	var uid = session.uid;
	var user_info = game.userMap.get(game.USER_KEY_HEAD + session.uid);
	if(msg.type == 'catch_mermaid') {	// 捕获美人鱼[TODO  :此消息移动到玩家信息同步中]
		// var routeParam = {};
		// var catchMsg = user_info.nick_name + '在300倍房间捕获美人鱼!';
		// console.log('catchMsg  : ' + catchMsg);
		// self.app.rpc.world.worldRemote.addNewMsg(routeParam, 'catch_mermaid', catchMsg, function(){});
	} else if(msg.type == 'cancel_mermaid') {
		// TODO : 取消当前的美人鱼任务
		user_info.mermaid_task_info.success = 1;
		game.userMap.set(game.USER_KEY_HEAD + user_info.uid, user_info);
	}
	next(null);
};

/**
 * 玩家炮台升级请求
 *
 * @param {Object} msg message from client
 * @param {Object} session
 * @param  {Function} next next stemp callback
 *
 */
handler.levelchange = function(msg, session, next) {
	console.log('levelchange coming, msg : ' + JSON.stringify(msg));
	var self = this;
	var user_info = game.userMap.get(game.USER_KEY_HEAD + session.uid);
	console.log(JSON.stringify(user_info));
	var requireDiamonds = game.getLevelUpdateRequireDiamond(user_info.turrent_level);
	console.log('karen_requireDiamonds : ' + requireDiamonds + '; user_info.diamonds' + user_info.diamonds + '; user_info.turrent_level = ' + user_info.turrent_level);
	if(user_info.diamonds >= requireDiamonds) {
		if(user_info.turrent_level === 0) {
			next(null, {
				errorcode: 100,
				errormsg: 'top level'
			});
			return ;
		}
		user_info.turrent_level = game.getNextLevel(user_info.turrent_level);
		var rewards = game.getLevelUpdateRewardCoins(user_info.turrent_level);
		user_info.coins = user_info.coins + rewards;
		user_info.diamonds -= requireDiamonds;
		game.userMap.set(game.USER_KEY_HEAD + session.uid, user_info);

		gametask_achievement_manager.syncMaxTurrentLevel(user_info.user_id, user_info.turrent_level, function(success, result){
			// TODO : 如果完成任务,推送消息
		});


		(function(self, session){
			gametask_everyday_manager.upgradeTurrent(user_info.user_id, user_info.turrent_level, function(success, result){
				if(success) {
					var channelService = self.app.get('channelService');
					var channel = channelService.getChannel(session.get('rid'), false);
					var sid = channel.getMember(session.uid)['sid'];
					var uid = session.uid;

					var marquee = {
						msg : result
					};
					channelService.pushMessageByUids('marquee', marquee, [{
						uid: uid,
						sid: sid
					}]);
				}
			});  // 更新用户的任务信息-升级一次炮台
		})(self, session);


		// 调用远程方法升级
		cgsdk.addPlayerBaseInfoChangeBySessionId(session.uid, user_info.coins, user_info.diamonds, user_info.exps, user_info.turrent_level, function(success, result){
			console.log('gameHandler->updateUserInfo, cgsdk success : ' + success);
			dealSyncInfoResult(session, result);
		});
		var levelUpObj = {
			errorcode: 0,
			diamonds: requireDiamonds,
			coins : rewards,
			turrent_level : user_info.turrent_level
		};
		console.log('levelUpObj : ' + JSON.stringify(levelUpObj));
		next(null, levelUpObj);
	}else {
		next(null, {
			errorcode: 100,
			errormsg: 'need more diamonds'
		});
	}
};

/**
 * 查询支付订单结果
 *
 * @param {Object} msg message from client
 * @param {Object} session
 * @param  {Function} next next stemp callback
 *
 */
handler.payresult = function(msg, session, next) {
	console.log('payresult coming... ');
	var order_id = msg.order_id;
	var pay_type = msg.pay_type;
	var user_info = game.userMap.get(game.USER_KEY_HEAD + session.uid);
	(function(user_info){
		pay_service.checkPayResult(pay_type, order_id, user_info.user_id, function(success, result) {
			if(success) {
				var reward_lists = result.reward_lists;
				user_info.mo += result.real_price;	// 更新玩家的充值金额
				for(var i=0;i<reward_lists.length;i++) {
					if(reward_lists[i].item_id === 1001) {
						user_info.coins += reward_lists[i].nums;
					}else if(reward_lists[i].item_id === 1002) {
						user_info.diamonds += reward_lists[i].nums;
					}
				}
				game.userMap.set(game.USER_KEY_HEAD + session.uid, user_info);// 更新玩家的金币、钻石信息
				next(null, result);
			}else {
				next(null, result);
			}
		});
	})(user_info);

};

/**
 * 破产领取
 *
 * @param {Object} msg message from client
 * @param {Object} session
 * @param  {Function} next next stemp callback
 *
 */
handler.bankruptRebirth = function(msg, session, next) {
	console.log('bankruptRebirth coming, msg : ' + JSON.stringify(msg));
	var uid = session.uid;
	var user_info = game.userMap.get(game.USER_KEY_HEAD + uid);
	(function(uid, user_info){
		cgsdk.bankruptRebirthBySessionId(uid, user_info.room_id, function(success, result){
			if(success) {
				var resultObj = JSON.parse(result);
				if(parseInt(resultObj.errorcode) === 0 && resultObj.reward_coins > 0) {
					user_info.coins += resultObj.reward_coins;
					game.userMap.set(game.USER_KEY_HEAD + uid, user_info);
				}
				next(null, resultObj);
			}else {
				next(null, {
					errorcode: 500,
					errormsg : 'can not get bankrupt rebirth'
				});
			}
		});
	})(uid, user_info);
};

/**
 * 玩家抽奖
 *
 * @param {Object} msg message from client
 * @param {Object} session
 * @param  {Function} next next stemp callback
 *
 */
handler.bonuspool = function(msg, session, next) {
	console.log('molo_bonuspool coming... ');
	var uid = session.uid;
	cgsdk.turntableForBonuspoolBySessionId(uid, function(success, result){
		if(success) {
			var resultObj = JSON.parse(result);
			var user_info = game.userMap.get(game.USER_KEY_HEAD + uid);
			for(var i=0;i<resultObj.reward_lists.length;i++) {
				if(parseInt(resultObj.reward_lists[i].item_id) === 1001) {
					user_info.coins += parseInt(resultObj.reward_lists[i].nums);
				} else if(parseInt(resultObj.reward_lists[i].item_id) === 1002) {
					user_info.diamonds += parseInt(resultObj.reward_lists[i].nums);
				}else {
					user_info.item_lists = getNewItemInfos(parseInt(resultObj.reward_lists[i].item_id),
							parseInt(resultObj.reward_lists[i].nums), user_info.item_lists);
				}
			}
			game.userMap.set(game.USER_KEY_HEAD + uid, user_info);
			next(null, resultObj);
		}else {
			next(null, {
				errorcode: 500,
				errormsg : 'can not get turntable result'
			});
		}
	});
};

/**
 * 玩家信息变更
 *
 * @param {Object} msg message from client
 * @param {Object} session
 * @param  {Function} next next stemp callback
 *
 */
handler.userinfochange = function(msg, session, next) {
	console.log('userinfochange coming, msg : ' + JSON.stringify(msg));
	var self = this;

	var user_info = game.userMap.get(game.USER_KEY_HEAD + session.uid);
	if(user_info === undefined || user_info === null || user_info.coins <= 0) {	// TODO  : 如果已经破产了，不能往下继续
		next(null);
		return ;
	}

	var fishes = msg.fishes;
	var get_coins = msg.get_coins === null ? 0 : parseInt(msg.get_coins);

	var c_coins = 0;
	var c_exps = 0;
	var gold_fish_nums = 0;
	for(var i=0; i<fishes.length; i++) {
		c_coins += fishes[i].turrent_level*game.getCoinsByFishes(fishes[i].fishes) ;
		c_exps += game.getExpsByFishes(fishes[i].fishes);
		gold_fish_nums += game.getGoldFishNums(fishes[i].fishes);
	}

	var exps = msg.get_exps === null ? 0 : parseInt(msg.get_exps);
	var use_coins = msg.use_coins === null ? 0 : parseInt(msg.use_coins);
	var gold_fishes = msg.gold_fishes === null ? [] : msg.gold_fishes;
	var fire_nums =  msg.fire_nums === null ? 0 : parseInt(msg.fire_nums);

	console.log(c_coins + '?===?' + get_coins);
	console.log(c_exps + '?===?' + exps);
	console.log(gold_fish_nums + '?===?' + gold_fishes.length);
	console.log('fire_nums  = ' + fire_nums);

	if( c_coins === get_coins && c_exps === exps && gold_fish_nums === gold_fishes.length
			&& ( exps >= 0) ) {	// 效验金币、经验信息
		// 继续
	}else {
		console.log('MOLO_KICK[2]');
		self.app.rpc.connector.enterRemote.kick(session, session.uid, function(){
			console.log('onUserLeave callback ..........');
		});
		next(null);
		return ;
	}
	var use_coins = msg.use_coins === null ? 0 : parseInt(msg.use_coins);
	var coins = get_coins - use_coins;

	var channelService = self.app.get('channelService');
	var channel = channelService.getChannel(session.get('rid'), false);
	var sid = channel.getMember(session.uid)['sid'];

	var diamonds = 0;

	// 判断是否有BOSS鱼,如果有，要推送奖励
	if(gold_fishes.length > 0) {
		var add_diamonds = 0;
		var boss_nums = 0;
		for(var i=0;i<gold_fishes.length;i++){
			var fish_id = parseInt(gold_fishes[i]);
			if( fish_id === 50 || fish_id === 51) {
				add_diamonds += 20;
				boss_nums++;
			}
		}
		if(add_diamonds > 0) {
			gametask_achievement_manager.addBossfishNums(user_info.user_id, boss_nums, function(success, result){
				// TODO : 如果完成任务,推送消息
			});
			diamonds += add_diamonds;
			var boss_reward = {
				reward_lists : [
					{item_id : 1002, nums : add_diamonds}
				]
			};
			channelService.pushMessageByUids('boss', boss_reward, [{
				uid: session.uid,
				sid: sid
			}]);
		}
	}

	if(fishes.length > 0) {	// 成就任务-捕获鱼数量
		var new_fishes = [];
		for(var i=0;i<fishes.length;i++) {
			for(var j=0;j<fishes[i].fishes.length;j++) {
				new_fishes.push(fishes[i].fishes[j]);
			}
		}
		gametask_achievement_manager.addCatchfishNums(user_info.user_id, new_fishes.length, function(success, result){
			// TODO : 如果完成任务,推送消息
		});

		console.log('m1_mermaid_debug : user_info.room_id = ' + user_info.room_id);
		if(user_info.room_id > 1) {
			var current_task_info = mermaid_manager.getCurrentTaskInfo();
			if(current_task_info !== null ) { // 美人鱼任务正在进行
				user_info.mermaid_task_info.coins += use_coins; // 计算金币数目
				var mermaid_new_fish_ids = mermaid_manager.getMermaidFishIds(new_fishes);
				if(mermaid_new_fish_ids.length > 0) { // 捕获了任务要求的鱼
					// 更新玩家的任务完成信息
					var go_meraid = true;
					if(user_info.mermaid_task_info.task_id !== current_task_info.task_id) {
						user_info.mermaid_task_info = mermaid_manager.createNewUserTask(mermaid_new_fish_ids);
					}else {
						if(user_info.mermaid_task_info.success === 0) { // 未完成任务
							for(var i=0;i<mermaid_new_fish_ids.length; i++) {
									for(j=0;j<user_info.mermaid_task_info.fish_ids.length;j++) {
										if(user_info.mermaid_task_info.fish_ids[j].fish_id === mermaid_new_fish_ids[i]) {
											user_info.mermaid_task_info.fish_ids[j].current_nums += 1;
										}
									}
							}
						}else {
							go_meraid = false;
						}
					}
					if(go_meraid) {
						if( mermaid_manager.isSuccess(user_info.mermaid_task_info) ) { // 计算任务是否完成

							user_info.mermaid_task_info.success = 1;	// 任务完成
							var success = {
								task_id : user_info.mermaid_task_info.task_id,
								reward_coins : user_info.mermaid_task_info.coins
							};
							console.log('md_4_successMermaid, ' + JSON.stringify(success));
							channelService.pushMessageByUids('successMermaid', success, [{
								uid: session.uid,
								sid: sid
							}]);
							coins += success.reward_coins;
						} else {
							console.log('md_4_successMermaid, info = ' + JSON.stringify(user_info.mermaid_task_info));
							console.log('md_4_successMermaid, ' + JSON.stringify({catchfish_ids : mermaid_new_fish_ids}));
							channelService.pushMessageByUids('updateMermaid', {catchfish_ids : mermaid_new_fish_ids}, [{
								uid: session.uid,
								sid: sid
							}]);
						}
					}
				}
			}
		}
	}

	if(gold_fishes.length > 0) {	// 奖池信息同步
		(function(self, session){
			gametask_everyday_manager.catchGoldfish(user_info.user_id, user_info.turrent_level, gold_fishes.length, function(success, result){
				console.log('gametask_everyday_manager, result = ' + result);
				if(success) {
					var channelService = self.app.get('channelService');
					channel = channelService.getChannel(session.get('rid'), false);
					var sid = channel.getMember(session.uid)['sid'];
					var uid = session.uid;

					var marquee = {
						msg : result
					};
					channelService.pushMessageByUids('marquee', marquee, [{
						uid: uid,
						sid: sid
					}]);
				}
			});  // 每日任务-捕获黄金鱼
		})(self, session);

		gametask_achievement_manager.addCatchGoldfishNums(user_info.user_id, gold_fishes.length, function(success, result){});


		for(var i=0;i<gold_fishes.length;i++) {
			var uid = session.uid;
			(function(uid){
				cgsdk.addOneGoldFishForBonuspoolBySessionId(uid, gold_fishes[i], function(success, result){
					if(success) {
						var user_bonuspool_obj = JSON.parse(result);
						console.log('BonuspoolInfo : ' + result);
						// if(user_bonuspool_obj.errorcode == 0 && user_bonuspool_obj.fish_nums > 0) {
							channelService.pushMessageByUids('BonuspoolInfo', user_bonuspool_obj, [{
								uid: uid,
								sid: sid
							}]); // TODO : 感觉通过channel发并不是最好的方式，最好通过notify直接发
						// }
					}
				});
			})(uid);
		}
	}

	game.userMap.set(game.USER_KEY_HEAD + uid, user_info);
	updateUserInfo(session, user_info, channelService, sid, session.uid, coins, diamonds, exps, fire_nums);	// 同步用户信息
	next(null);
};

function updateUserInfo(session, user_info, channelService, sid, uid, coins, diamonds, exps, fire_nums) {
	console.log('old user info : ' + JSON.stringify(user_info));
	console.log('[' + uid + ']' +  coins + ';' + diamonds);
	if(fire_nums > 0) {

		gametask_achievement_manager.fire(user_info.user_id, fire_nums, function(success, result){});


		user_info.fire_diamonds += fire_nums;
		user_info.fire_items += fire_nums;

		var magnate_diamonds = 0;
		if(user_info.fire_diamonds >= 90) {
			magnate_diamonds = 1;
			user_info.fire_diamonds -= 90;
		}
		var magnate_items = 0;
		if(user_info.fire_items >= 250) {
			magnate_items = 1;
			user_info.fire_items -= 250;
		}

		if(magnate_diamonds > 0 || magnate_items > 0) {
			var magnate = {
				diamonds : 0,
				item_ids : []
			};
			if(magnate_diamonds > 0) {
				diamonds += 1;	// 同步信息钻石数目+1
				console.log('[' + uid + '][diamonds]' +  coins + ';' + diamonds);
				magnate.diamonds = 1;
			}

			if(magnate_items > 0) {
				var item_id = game.getMagnateItem();
				magnate.item_ids.push(item_id);
				var item_change_lists = [
					{item_id : item_id, nums : 1}
				];
				user_info.item_lists = getNewItemInfos(item_id, 1, user_info.item_lists);
				(function(session){
					cgsdk.updatePlayerBagInfoBySessionId(uid, user_info.user_id, item_change_lists, function(result){
						dealSyncInfoResult(session, result);
					});
				})(session);

			}
			channelService.pushMessageByUids('magnate', magnate, [{
				uid: uid,
				sid: sid
			}]); // TODO : 感觉通过channel发并不是最好的方式，最好通过notify直接发
		}
	}

	user_info.coins = parseInt(user_info.coins) + coins;
	user_info.diamonds = parseInt(user_info.diamonds) + diamonds;
	var old_exps = user_info.exps;
	user_info.exps = parseInt(user_info.exps) + exps;

	var expRewards = game.expUpdate(old_exps, user_info.exps);

	if(expRewards.user_level_up_infos.length > 0) {	//广播用户升级奖励
		console.log( 'EXP_UPDATE : ' + JSON.stringify(expRewards) );
		channelService.pushMessageByUids('expUpdate', expRewards, [{
			uid: uid,
			sid: sid
		}]); // TODO : 感觉通过channel发并不是最好的方式，最好通过notify直接发

		var item_change_lists = [];
		for(var i=0;i<expRewards.user_level_up_infos.length;i++) {
			for(var j=0;j<expRewards.user_level_up_infos[i].rewards.length;j++) {
				if( parseInt(expRewards.user_level_up_infos[i].rewards[j].item_id) === 1001) {
					coins += parseInt(expRewards.user_level_up_infos[i].rewards[j].num);
					console.log('[' + uid + ']1001' +  coins + ';' + diamonds);
					user_info.coins += parseInt(expRewards.user_level_up_infos[i].rewards[j].num);
				}else if( parseInt(expRewards.user_level_up_infos[i].rewards[j].item_id) === 1002) {
					diamonds += parseInt(expRewards.user_level_up_infos[i].rewards[j].num);
					console.log('[' + uid + ']1002' +  coins + ';' + diamonds);
					user_info.diamonds += parseInt(expRewards.user_level_up_infos[i].rewards[j].num);
				}else {
					//	背包信息同步[可能获得了道具]
					user_info.item_lists = getNewItemInfos(expRewards.user_level_up_infos[i].rewards[j].item_id,
						 	expRewards.user_level_up_infos[i].rewards[j].num, user_info.item_lists);

					item_change_lists.push({
						item_id : expRewards.user_level_up_infos[i].rewards[j].item_id,
						nums : expRewards.user_level_up_infos[i].rewards[j].num
					});
				}
			}
		}
		if(item_change_lists.length > 0){
			(function(session){
				cgsdk.updatePlayerBagInfoBySessionId(uid, user_info.user_id, item_change_lists, function(result){
					dealSyncInfoResult(session, result);
				});
			})(session);

		}

	}

	if(user_info.coins <= 0) {	// TODO : 如果金币数为0，则破产
		cgsdk.bankruptBrokeBySessionId(uid, user_info.room_id, function(success, result) {
			if(success) {
				channelService.pushMessageByUids('bankruptBroke', JSON.parse(result), [{
					uid: uid,
					sid: sid
				}]);
			}
		});
	}
	if(user_info.max_coins !== -1){
		if(user_info.coins > user_info.max_coins) {
			gametask_achievement_manager.newMaxCoins(user_info.user_id, user_info.coins, function(success, result){});
			user_info.max_coins = user_info.coins;
		}
	}else {
		// 获取玩家的最大金币数目并更新成就任务
		(function(uid){
			gametask_achievement_manager.getMaxCoins(user_info.user_id, function(success, result){
				if(success){
					var user_info = game.userMap.get(game.USER_KEY_HEAD + uid);
					if(user_info !== undefined && user_info !== null) {
						user_info.max_coins = parseInt(result);
						if(user_info.coins > user_info.max_coins) {
							gametask_achievement_manager.newMaxCoins(user_info.user_id, user_info.coins, function(success, result){});
							user_info.max_coins = user_info.coins;
						}
						game.userMap.set(game.USER_KEY_HEAD + uid, user_info);
					}
				}
			});
		})(uid);
	}

	game.userMap.set(game.USER_KEY_HEAD + uid, user_info);
	console.log('new user info : ' + JSON.stringify(user_info));

	// 更新玩家金币钻石信息
	cgsdk.addPlayerBaseInfoChangeBySessionId(uid, user_info.coins, user_info.diamonds, user_info.exps, user_info.turrent_level, function(success, result){
		console.log('gameHandler->updateUserInfo, cgsdk success : ' + success);
		dealSyncInfoResult(session, result);
	});
}


/**
 * 使用技能请求
 *
 * @param {Object} msg message from client
 * @param {Object} session
 * @param  {Function} next next stemp callback
 *
 */
handler.useskill = function(msg, session, next) {
	var self = this;
	console.log('useskill coming, msg : ' + JSON.stringify(msg));
	if(isNaN(msg.item_id)) {
		next(null, {
			errorcode: 301,	// 参数错误
			errormsg : '不存在的道具.无法使用.'
		});
		return ;
	}
	var item_id = parseInt(msg.item_id);
	if(item_id >= 1003 && item_id <= 1007) {
		var user_info_bag = game.userMap.get(game.USER_KEY_HEAD + session.uid);
		var item_id_nums = getItemIdNums(item_id, user_info_bag.item_lists);
		if(item_id_nums > 0) {	//判断玩家的道具数量
			next(null, {
				errorcode: 0,
				item_id : item_id,
				use_type : 0,	// 0,次数; 1钻石
				price : 1,
				current_nums : item_id_nums - 1
			});

			gametask_achievement_manager.useSkill(user_info_bag.user_id, item_id, function(success, result){});

			(function(self, session){
				gametask_everyday_manager.useSkill(user_info_bag.user_id, user_info_bag.turrent_level, item_id, function(success, result){
					if(success) {
						var channelService = self.app.get('channelService');
						var channel = channelService.getChannel(session.get('rid'), false);
						var sid = channel.getMember(session.uid)['sid'];
						var uid = session.uid;

						var marquee = {
							msg : result
						};
						channelService.pushMessageByUids('marquee', marquee, [{
							uid: uid,
							sid: sid
						}]);
					}
				});  // 更新用户的任务信息-升级一次炮台
			})(self, session);

			user_info_bag.item_lists = getNewItemInfos(item_id, -1, user_info_bag.item_lists);
			game.userMap.set(game.USER_KEY_HEAD + session.uid, user_info_bag);
			var item_change_lists = [
				{item_id : item_id, nums : -1}
			];
			cgsdk.updatePlayerBagInfoBySessionId(session.uid, user_info_bag.user_id, item_change_lists, function(result){});
		} else {	// 道具数量不够判断钻石数量
			if( (item_id === 1006) && user_info_bag.mo < 50000) {	// 需要vip3才能使用,500元
				next(null, {
					errorcode: 303,	// 需要vip等级
					errormsg : '需要VIP3才能购买.'
				});
				return ;
			}
			if( (item_id === 1007) && user_info_bag.mo < 20000) {	//需要vip2才能使用,200元
				next(null, {
					errorcode: 303,	// 需要vip等级
					errormsg : '需要VIP2才能购买.'
				});
				return ;
			}
			if( (item_id === 1005) && user_info_bag.turrent_level < 10) {	//需要更高的炮台等级
				next(null, {
					errorcode: 304,	// 需要vip等级
					errormsg : '需要10级以上炮台才能购买.'
				});
				return ;
			}
			if( (item_id === 1003 || item_id === 1004) && user_info_bag.turrent_level < 30) {	//需要更高的炮台等级
				next(null, {
					errorcode: 304,	// 需要vip等级
					errormsg : '需要30级以上炮台才能购买.'
				});
				return ;
			}
			var itemDiamondsPrice = getSkillUsePriceByItemId(item_id);
			if(user_info_bag.diamonds >= itemDiamondsPrice ) {
				user_info_bag.diamonds = user_info_bag.diamonds - itemDiamondsPrice;
				game.userMap.set(game.USER_KEY_HEAD + session.uid, user_info_bag);
				cgsdk.addPlayerBaseInfoChangeBySessionId(session.uid, user_info.coins, user_info.diamonds, user_info.exps, user_info.turrent_level, function(success, result){
					console.log('gameHandler->sync userinfo for uses skills, cgsdk success : ' + success);
					dealSyncInfoResult(session, result);
				});
				next(null, {
					errorcode: 0,
					item_id : item_id,
					use_type : 1,	// 0,次数; 1钻石
					price : itemDiamondsPrice,
					current_nums : user_info_bag.diamonds
				});
			}else {
				next(null, {
					errorcode: 302,	// 钻石不足
					errormsg : '钻石不足.无法使用.'
				});
			}

		}

	}else {
		next(null, {
			errorcode: 301,	// 参数错误
			errormsg : '不存在的道具.无法使用.'
		});
	}
};


function getSkillUsePriceByItemId(item_id) {	// TODO : 后续走配置
	if(item_id === 1003) {
		return 5;
	}else if(item_id === 1004) {
		return 2;
	}if(item_id === 1005) {
		return 2;
	}if(item_id === 1006) {
		return 200;
	}if(item_id === 1007) {
		return 10;
	}
	return 2;
}

function getNewItemInfos(item_id, num_changes, item_lists) {
	for(var i=0; i<item_lists.length;i++) {
		if(item_lists[i].item_id === item_id) {
			item_lists[i].nums = item_lists[i].nums + num_changes;
			return item_lists;
		}
	}
	return item_lists;
}

function getItemIdNums(item_id, item_lists) {
	for(var i=0; i<item_lists.length;i++) {
		if(item_lists[i].item_id === item_id) {
			return item_lists[i].nums;
		}
	}
	return 0;
}

/**
 * 保留的聊天测试接口
 *
 * @param {Object} msg message from client
 * @param {Object} session
 * @param  {Function} next next stemp callback
 *
 */
handler.send = function(msg, session, next) {
	var rid = session.get('rid');
	var username = session.uid;
	var channelService = this.app.get('channelService');
	var param = {
		msg: msg.content,
		from: username,
		target: msg.target
	};
	var channel = channelService.getChannel(rid, false);

	//the target is all users
	if(msg.target == '*') { //the target is specific user
		channel.pushMessage('onChat', param);
	} else {
		var tuid = msg.target.substring(2);
		console.log('tuid : ' + tuid + '; member' + channel.getMember(tuid));
		var tsid = channel.getMember(tuid)['sid'];

		channelService.pushMessageByUids('onChat', param, [{
			uid: tuid,
			sid: tsid
		}]);
	}
	next(null, {
		route: msg.route
	});
};

function dealSyncInfoResult(session, result) {
	if(!result) {
		self.app.rpc.connector.enterRemote.kick(session, session.uid, function(){
			console.log('onUserLeave callback ..........');
		});
	}

}
