
var config = require('../config.json');
var mysql = require('mysql');

var client;
var client_s;
var requestConnectMySqlTime = 0;

var option = {
    host : config.mysql_catchfish.host,
    port :  config.mysql_catchfish.port,
    user :  config.mysql_catchfish.user,
    password :  config.mysql_catchfish.password,
    database :  config.mysql_catchfish.database
};

var option_s = {
    host : config.mysql_catchfish_s.host,
    port :  config.mysql_catchfish_s.port,
    user :  config.mysql_catchfish_s.user,
    password :  config.mysql_catchfish_s.password,
    database :  config.mysql_catchfish_s.database
};

var first_init_success = false;
function firstInit() {
	if(!first_init_success) {
		first_init_success = true;
		init(function(result){
      console.log('init db result : ' + result);
    });
	}
}
exports.firstInit = firstInit;

function init(callback)  {
  console.log('init db');
  if(config.debug){
    option = {
        host : config.mysql_catchfish_debug.host,
        port :  config.mysql_catchfish_debug.port,
        user :  config.mysql_catchfish_debug.user,
        password :  config.mysql_catchfish_debug.password,
        database :  config.mysql_catchfish_debug.database
    };
    option_s = {
        host : config.mysql_catchfish_s_debug.host,
        port :  config.mysql_catchfish_s_debug.port,
        user :  config.mysql_catchfish_s_debug.user,
        password :  config.mysql_catchfish_s_debug.password,
        database :  config.mysql_catchfish_s_debug.database
    }
  }
	initClient(callback);
  initClientS();
}

function initClient(callback) {
    console.log('initClient [mysql db]option.host = ' + option.host);
    client = mysql.createConnection(option);
    client.connect(function (err) {
       if (err) {
            console.log('initClient [[mysql db]]error when connecting to db:requestConnectMySqlTime = ' + requestConnectMySqlTime + ';err = ', err);
            requestConnectMySqlTime++;
            setTimeout(initClient, 5*1000);// TODO :  if retry time over 3, need send mail
            callback(false);
       }else {
            requestConnectMySqlTime = 0;
            callback(true);
        }
    });

    client.on('error', function (err) {
        console.log('initClient db error', err);
        if (err.code === 'PROTOCOL_CONNECTION_LOST') { // 如果是连接断开，自动重新连接
            initClient(function(result){
                console.log('reconnect db result : ' + result);
            });
        }
    });
}

function initClientS() {
    console.log('initClientS [mysql db]option_s.host = ' + option_s.host);
    client_s = mysql.createConnection(option_s);
    client_s.connect(function (err) {
       if (err) {
            console.log('initClientS [[mysql db]]error when connecting to db:requestConnectMySqlTime = ' + requestConnectMySqlTime + ';err = ', err);
            requestConnectMySqlTime++;
            setTimeout(initClientS, 5*1000);// TODO :  if retry time over 3, need send mail
       }else {
            requestConnectMySqlTime = 0;
           }
    });

    client_s.on('error', function (err) {
        console.log('initClientS db error', err);
        if (err.code === 'PROTOCOL_CONNECTION_LOST') { // 如果是连接断开，自动重新连接
            initClientS();
        }
    });
}

function getClient() {
    return client;
}

function getClientS() {
    return client_s;
}

exports.init = init;
exports.getClient = getClient;
exports.getClientS = getClientS;
