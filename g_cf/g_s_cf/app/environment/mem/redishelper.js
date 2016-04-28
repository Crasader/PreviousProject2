var config = require('../config.json');
var redis = require('redis');


var username = config.redis.username;
var password = config.redis.password;
var redis_host = config.redis.redis_host;
var redis_port = config.redis.redis_port;
var redis_db_name =config.redis.redis_db_name;
var redis_options = {"no_ready_check":config.redis.no_ready_check};

var client;

var first_init_success = false;
function firstInit() {
	if(!first_init_success) {
		first_init_success = true;
		init();
	}
}
exports.firstInit = firstInit;

function init() {
	console.log('init redis ... ... ');
	if(config.debug) {
		username = config.redis_debug.username;
		password = config.redis_debug.password;
		redis_host = config.redis_debug.redis_host;
		redis_port = config.redis_debug.redis_port;
		redis_db_name =config.redis_debug.redis_db_name;
		redis_options = {"no_ready_check":config.redis.no_ready_check};
	}
	client = redis.createClient(redis_port, redis_host, redis_options);

	client.on("error", function (err) {
  		console.log("redis meet Error " + err + ';' + redis_host + ';' + redis_port);
  		setTimeout(init, 5*1000);	// 5秒后重连
	});
	client.auth(username + '-' + password + '-' + redis_db_name);
}

function setVaule(key, values) {
	client.set(key, values);

}

function getVaule(key, callback ) {
	client.get(key, function(err, redis_result) {
		callback(err, redis_result);
	});
}

function del(key) {
	client.del(key);
}

/**
 * 设置缓存值，带失效时间
 */
function setValueWithExpire(key, values, expire) {
	client.set(key, values);
	client.expire(key, expire);	// 单位秒
}

exports.init = init;
exports.setVaule = setVaule;
exports.getVaule = getVaule;
exports.del = del;
exports.setValueWithExpire = setValueWithExpire;

function getTillTomorrowDayEndLeftSeconds() {
	var myDate = new Date();
	return ( ( (24+23) - myDate.getHours() )*60 + ( 59 - myDate.getMinutes() ) )*60 +
		59 - myDate.getSeconds();
}

exports.getTillTomorrowDayEndLeftSeconds = getTillTomorrowDayEndLeftSeconds;

function getCurrentDayLeftSeconds() {
	var myDate = new Date();
	return ((23 - myDate.getHours())*60 + (59 - myDate.getMinutes()))*60 +
		59 - myDate.getSeconds();
}

exports.getCurrentDayLeftSeconds = getCurrentDayLeftSeconds;
