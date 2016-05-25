var config = require('../config.json');
var noderice = require('noderice');
var mysql = require('mysql');

var client;
var requestConnectMySqlTime = 0;
var clientS;
var requestConnectMySqlTimeS = 0;

var option = {
    host : config.mysql_catchfish.host,
    port :  config.mysql_catchfish.port,
    user :  config.mysql_catchfish.user,
    password :  config.mysql_catchfish.password,
    database :  config.mysql_catchfish.database
}

var options = {
    host : config.mysql_catchfish_s.host,
    port :  config.mysql_catchfish_s.port,
    user :  config.mysql_catchfish_s.user,
    password :  config.mysql_catchfish_s.password,
    database :  config.mysql_catchfish_s.database
}

function init(callback) {
  initM(callback);
  initS();
}

function initM(callback)  {
  console.log('[dbmanager_catchfish_m]option.host = ' + option.host);
  client = mysql.createConnection(option);
  //connect error，retry on 5 seconds
  client.connect(function (err) {
     if (err) {
      console.log('[dbmanager_catchfish_m]error when connecting to db:requestConnectMySqlTime = ' + requestConnectMySqlTime + ';err = ', err);
      requestConnectMySqlTime++;
      setTimeout(initM(callback), 5*1000);
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
        initM(callback);
      } else {
        console.log('db error70', err);
      }
    });
}

function initS()  {
  console.log('[dbmanager_catchfish_s]options.host = ' + options.host);
  clientS = mysql.createConnection(options);
  //connect error，retry on 5 seconds
  clientS.connect(function (err) {
     if (err) {
      console.log('[dbmanager_catchfish_s]error when connecting to db:requestConnectMySqlTime = ' + requestConnectMySqlTimeS + ';err = ', err);
      requestConnectMySqlTimeS++;
      setTimeout(initS(), 5*1000);
      // TODO :  if retry time over 3, need send mail
     }else {
      requestConnectMySqlTimeS = 0;
     }
  });
  clientS.on('error', function (err) {
    console.log('db error', err);
      // 如果是连接断开，自动重新连接
      if (err.code === 'PROTOCOL_CONNECTION_LOST') {
        initS();
      } else {
        console.log('db error70', err);
      }
    });
}

function getClient() {
    return client;
}

function getClientS() {
    return clientS;
}

exports.init = init;
exports.getClient = getClient;
exports.getClientS = getClientS;
