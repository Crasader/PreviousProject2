var config = require('../config.json');
var noderice = require('noderice');
var mysql = require('mysql');

var client;
var requestConnectMySqlTime = 0;

var option = {
    host : config.mysql_game_bg.host,
    port :  config.mysql_game_bg.port, 
    user :  config.mysql_game_bg.user, 
    password :  config.mysql_game_bg.password,
    database :  config.mysql_game_bg.database
}

function init(callback)  {
		console.log('[dbmanager_bg]option.host = ' + option.host);
		client = mysql.createConnection(option);

    	//connect error，retry on 5 seconds
    	client.connect(function (err) {
    	   if (err) {
    			console.log('[dbmanager_bg]error when connecting to db:requestConnectMySqlTime = ' + requestConnectMySqlTime + ';err = ', err);
    			requestConnectMySqlTime++;
    			setTimeout(init(callback), 5*1000);
    			// TODO :  if retry time over 3, need send mail
    	   }else {
    			requestConnectMySqlTime = 0;
                callback(true);
    	   }
    	});

    	client.on('error', function (err) {
    		console.log('db error', err);
        	// 如果是连接断开，自动重新连接
        	if (err.code === 'PROTOCOL_CONNECTION_LOST') {
        		init(callback);
        	} else {
        		console.log('db error70', err);
        	}
        });
}

function getClient() {
    return client;
}

function getClientS() {
    return client;  // TODO : 从库添加后获取从库实例
}

exports.init = init;
exports.getClient = getClient;
exports.getClientS = getClientS;