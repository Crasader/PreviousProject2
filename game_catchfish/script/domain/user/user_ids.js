'use strict';
/**
 * 用户ID生成器
 *
 */

var dbmanager = require('../../db/dbmanager.js');
var user_db = require('./user_db.js');
var config = require('../../config.json');

var cursor = 0;
var startValue = 0;
var nextStartValue = 0;
var readyNextSync = false;
var MAX_CURSOR_POSITION = 100;	// default 100
var NEXT_CHECK_STEP = 10;		// default 10
var START_VALUE_STEP = 120;		// default 120

function init() {
	if(config.debug){
		return ;
	}
	getNewGuestIdValues(function(result, value) {
		if(result) {
			cursor = 0;	// 重置游标
			startValue = value;
			readyNextSync = false;
			console.log('user_ids new startValue = ' + startValue);
		}else {
			// TODO : 需要做异常处理，监控报警
			console.log('[ERROR!!]init user_ids, value = ' + value);
		}
	});
}

/**
 * 取出id缓存值
 */
function getNewGuestIdValues(callback) {
	// 取出临时用户表第一张表的最大值
	user_db.getGuestStartUserId(START_VALUE_STEP, dbmanager.getClientS(), function(success, data) {
		if(success) {
			callback(true, data);
		}else {
			callback(false, 'db error');
		}
	});
}

/**
 * 返回值>100，可用。<100，不可用，服务异常。
 */
function getGuestIds(callback) {
	if(config.debug){
		callback(true, 101);	// TODO : db里面增加一个批量删除101相关信息的接口
		return ;
	}
	if( ( cursor >= (MAX_CURSOR_POSITION-NEXT_CHECK_STEP) ) && !readyNextSync) {
		readyNextSync = true;
		getNewGuestIdValues(function(result, value){
			if(result) {
				nextStartValue = value;
				console.log('user_ids->getGuestIds, user_ids new startValue = ' + nextStartValue);
			}else {
				// TODO : 需要做异常处理，监控报警
				console.log('[ERROR!!]user_ids->getGuestIds,update user_ids, value = ' + value);
			}
		});
	}

	if(cursor >= MAX_CURSOR_POSITION) {
		startValue = nextStartValue;
		cursor = 0;	// 重置游标
		nextStartValue = 0;
		readyNextSync = false;
	}
	cursor++;
	callback(true, startValue+cursor);

}

/**
 * 获取db表后缀，取值范围:[1, 10]
 */
function getGuestDbTablePostfix(ids) {
	var result = ids%10;
	if(result === 0) {
		result = 10;
	}
	return result;
}

exports.init = init;
exports.getGuestIds = getGuestIds;
exports.getGuestDbTablePostfix = getGuestDbTablePostfix;
exports.MAX_CURSOR_POSITION = MAX_CURSOR_POSITION;
