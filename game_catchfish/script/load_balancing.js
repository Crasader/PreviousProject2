/**
 * 应用服务器负载均衡服务器
 */


/**
 * 获取应用服务器的配置信息-IP
 */
function getAppServerIp() {
  return '106.75.135.78';
}

/**
 * 获取应用服务器的配置信息-端口号
 */
function getAppServerPort() {
  return 1701;
}

exports.getAppServerIp = getAppServerIp;
exports.getAppServerPort = getAppServerPort;

/**
 * 获取游戏-服务器的配置信息-IP
 */
function getGameServerIp() {
  return '106.75.141.82';
}

/**
 * 获取游戏-服务器的配置信息-端口号
 */
function getGameServerPort() {
  return 3050;
}

exports.getGameServerIp = getGameServerIp;
exports.getGameServerPort = getGameServerPort;
