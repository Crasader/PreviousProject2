var request = require('request');
var crypto = require('crypto');
var p_config = require('../../../private_config/server.json');

var APIKEY = p_config.APIKEY;
var URL_HEAD_TBULOOK = p_config.URL_HEAD_TBULOOK;
var urlencode=require('urlencode');

//========================================
// 用户信息-开始

function getDashboardUserInfo(username, callback) {
    // URL_HEAD_TBULOOK/user/login/guest@tallbigup.com
    var options = {
        url : URL_HEAD_TBULOOK + '/user/login/' + username,
        timeout : 2000,
        headers : { 'apikey': APIKEY }
    };
    request(options, function (error, response, body) {
        if (error) {
            console.log('dashboard_data->getDashboardUserInfo, meet error : ' + error);
            callback(false, error);
            return ;
        }else if(response.statusCode != 200) {
          console.log('dashboard_data->getDashboardUserInfo response.statusCode = ' + response.statusCode);
          callback(false, error);
          return ;
        }

        callback(true, body);
        // console.log('tbulookdata->getDashboardUserInfo, resulut : ' + body
        //         + '; response.statusCode = ' + response.statusCode);
    });
}

function reqDashboardNewUserInfo(username, passwd, salt, reqinfo, callback) {
    // TODO : 注意，reqinfo尚未处理中文编码问题
    var options = {
        url : URL_HEAD_TBULOOK + '/user/register/' + username + '/' +
                passwd + '/' + salt + '/' + reqinfo,
        timeout : 2000,
        headers : { 'apikey': APIKEY }
    };
    request(options, function (error, response, body) {
        if (error) {
            console.log('dashboard_data->getDashboardUserInfo, meet error : ' + error);
            callback(false, error);
            return ;
        }

        callback(true, body);
        // console.log('tbulookdata->getDashboardUserInfo, resulut : ' + body
        //         + '; response.statusCode = ' + response.statusCode);
    });
}

// 用户信息-结束
//========================================


//========================================
// 签到-开始

/**
 * 获取当前签到配置
 * URL_HEAD_TBULOOK/config/sign/current
 * URL_HEAD_TBULOOK/sign/config
 */
function getSignCurrentConfig(callback) {
    var options = {
        url : URL_HEAD_TBULOOK + '/config/sign/current',
        timeout : 2000,
        headers : { 'apikey': APIKEY }
    };
    request(options, function (error, response, body) {
        if (error) {
            console.log('dashboard_data->getSignCurrentConfig, meet error : ' + error);
            callback(false, error);
            return ;
        }

        callback(true, body);
        // console.log('tbulookdata->getSignCurrentConfig, resulut : ' + body
        //         + '; response.statusCode = ' + response.statusCode);
    });
}

/**
 * 更新当前签到配置
 * URL_HEAD_TBULOOK/config/sign/update/:newSignConfig
 * URL_HEAD_TBULOOK/config/sign/update/:newSignConfig
 */
function updateSignConfig(newSignConfig, callback) {
    var options = {
        url : URL_HEAD_TBULOOK + '/config/sign/update/' + newSignConfig,
        timeout : 2000,
        headers : { 'apikey': APIKEY }
    };
    request(options, function (error, response, body) {
        if (error) {
            console.log('dashboard_data->updateSignConfig, meet error : ' + error);
            callback(false, error);
            return ;
        }

        callback(true, body);
        console.log('tbulookdata->updateSignConfig, resulut : ' + body
                + '; response.statusCode = ' + response.statusCode);
    });
}

// 签到-结束
//========================================

//========================================
// 配置计费点、事件点-开始

/**
 * 获取当前签到配置
 * URL_HEAD_TBULOOK/config/mo/paypoint
 * URL_HEAD_TBULOOK/config/mo/paypoint
 */
function getPaypoint(callback) {
    var options = {
        url : URL_HEAD_TBULOOK + '/config/mo/paypoint',
        timeout : 2000,
        headers : { 'apikey': APIKEY }
    };
    request(options, function (error, response, body) {
        if (error) {
            console.log('dashboard_data->getPaypoint, meet error : ' + error);
            callback(false, error);
            return ;
        }

        callback(true, body);
        // console.log('tbulookdata->getPaypoint, resulut : ' + body
        //         + '; response.statusCode = ' + response.statusCode);
    });
}

/**
 * 获取当前签到配置
 * URL_HEAD_TBULOOK/config/mo/payevent
 * URL_HEAD_TBULOOK/config/mo/payevent
 */
function getPayevent(callback) {
    var options = {
        url : URL_HEAD_TBULOOK + '/config/mo/payevent',
        timeout : 2000,
        headers : { 'apikey': APIKEY }
    };
    request(options, function (error, response, body) {
        if (error) {
            console.log('dashboard_data->getPayevent, meet error : ' + error);
            callback(false, error);
            return ;
        }

        callback(true, body);
        // console.log('tbulookdata->getPayevent, resulut : ' + body
        //         + '; response.statusCode = ' + response.statusCode);
    });
}

/**
 * 获取普通事件点统计信息
 * URL_HEAD_TBULOOK/config/commonevent/current
 * URL_HEAD_TBULOOK/config/commonevent/current
 * URL_HEAD_TBULOOK/config/commonevent/current
 */
function getCommonevent(callback) {
    var options = {
        url : URL_HEAD_TBULOOK + '/config/commonevent/current',
        timeout : 2000,
        headers : { 'apikey': APIKEY }
    };
    request(options, function (error, response, body) {
        if (error) {
            console.log('dashboard_data->getCommonevent, meet error : ' + error);
            callback(false, error);
            return ;
        }
        // console.log('dashboard_data->getCommonevent, resulut : ' + body
        //         + '; response.statusCode = ' + response.statusCode);
        callback(true, body);

    });
}

exports.getPaypoint = getPaypoint;
exports.getPayevent = getPayevent;
exports.getCommonevent = getCommonevent;

// 配置计费点、事件点-结束
//========================================

//========================================
// 数据报表-开始

/**
 * 获取渠道日报
 * URL_HEAD_TBULOOK/data/channel/dayreport/:day
 * URL_HEAD_TBULOOK/data/channel/dayreport/20160120
 */
function getChannelDayreport(day, callback) {
    var options = {
        url : URL_HEAD_TBULOOK + '/data/channel/dayreport/' + day,
        timeout : 2000,
        headers : { 'apikey': APIKEY }
    };
    request(options, function (error, response, body) {
        if (error) {
            console.log('dashboard_data->getChannelDayreport, meet error : ' + error);
            callback(false, error);
            return ;
        }
        if(response.statusCode === 200) {
          callback(true, body);
        }else {
          callback(false, body);
          // console.log('data->getChannelDayreport, resulut : ' + body
          //         + '; response.statusCode = ' + response.statusCode);
        }


    });
}

exports.getChannelDayreport = getChannelDayreport;

/**
 * 获取渠道日报
 * URL_HEAD_TBULOOK/data/channel/dayreport/onechannel/:channel_id
 * URL_HEAD_TBULOOK/data/channel/dayreport/onechannel/tad_ma_1
 */
function getOneChannel(channel_id, callback) {
    var options = {
        url : URL_HEAD_TBULOOK + '/data/channel/dayreport/onechannel/' + channel_id,
        timeout : 2000,
        headers : { 'apikey': APIKEY }
    };
    request(options, function (error, response, body) {
        if (error) {
            console.log('dashboard_data->getChannelDayreport, meet error : ' + error);
            callback(false, error);
            return ;
        }
        if(response.statusCode === 200) {
          callback(true, body);
        }else {
          callback(false, body);
          // console.log('data->getChannelDayreport, resulut : ' + body
          //         + '; response.statusCode = ' + response.statusCode);
        }
    });
}

exports.getOneChannel = getOneChannel;

// 数据报表-结束
//========================================

//========================================
// 帮助系统-开始

/**
 * 获取最近30条 用户反馈
 * URL_HEAD_TBULOOK/help/feedback
 * URL_HEAD_TBULOOK/help/feedback
 */
function getLastFeedback(callback) {
    var options = {
        url : URL_HEAD_TBULOOK + '/help/feedback',
        timeout : 2000,
        headers : { 'apikey': APIKEY }
    };
    request(options, function (error, response, body) {
        if (error) {
            console.log('dashboard_data->getLastFeedback, meet error : ' + error);
            callback(false, error);
            return ;
        }
        if(response.statusCode === 200) {
          callback(true, body);
        }else {
          callback(false, body);
          // console.log('data->getChannelDayreport, resulut : ' + body
          //         + '; response.statusCode = ' + response.statusCode);
        }


    });
}

exports.getLastFeedback = getLastFeedback;

// 帮助系统-结束
//========================================

//========================================
// 统计数据-开始

/**
 * 逻辑查询
 * URL_HEAD_TBULOOK/data/event/dayreport/:type/:day
 * URL_HEAD_TBULOOK/data/event/dayreport/turrentlevel/20160129 [炮台][v]
 * URL_HEAD_TBULOOK/data/event/dayreport/skilluse/20160129 [技能使用][v]
 * URL_HEAD_TBULOOK/data/event/dayreport/presented/20160129 [赠送][v]
 * URL_HEAD_TBULOOK/data/event/dayreport/pagechange/20160129 [页面跳转][v]
 * URL_HEAD_TBULOOK/data/event/dayreport/mermaidask/20160129 [美人鱼][v]
 * URL_HEAD_TBULOOK/data/event/dayreport/bankrupt/20160129 [破产][v]
 * URL_HEAD_TBULOOK/data/event/dayreport/fishinfo/20160129 [鱼群][v]
 * URL_HEAD_TBULOOK/data/event/dayreport/exp/distribution/20160314 [人物等级][v]
 * URL_HEAD_TBULOOK/data/event/dayreport/turntable/20160315 [转盘抽奖][v]
 */
 function getEventUserInfo(typeStr, dayStr, callback) {
     var options = {
         url : URL_HEAD_TBULOOK + '/data/event/dayreport/' + typeStr + '/' + dayStr,
         timeout : 2000,
         headers : { 'apikey': APIKEY }
     };
     request(options, function (error, response, body) {
         if (error) {
             console.log('dashboard_data->getEventUserInfo, meet error : ' + error);
             callback(false, error);
             return ;
         }

         callback(true, body);
        //  console.log('data->getEventUserInfo, resulut : ' + body
        //          + '; response.statusCode = ' + response.statusCode);
     });
 }

 exports.getEventUserInfo = getEventUserInfo;

 // 统计数据-结束
 //========================================

exports.getDashboardUserInfo = getDashboardUserInfo;
exports.reqDashboardNewUserInfo = reqDashboardNewUserInfo;
exports.getSignCurrentConfig = getSignCurrentConfig;
exports.updateSignConfig = updateSignConfig;

/**
 * 获取最近30条 用户反馈
 * http://URL_HEAD_TBULOOK/data/pay/dayreport/:day
 * http://URL_HEAD_TBULOOK/data/pay/dayreport/20160204
 */
function getPayDayreport(dayStr, callback) {
    var options = {
        url : URL_HEAD_TBULOOK + '/data/pay/dayreport/' + dayStr,
        timeout : 2000,
        headers : { 'apikey': APIKEY }
    };
    request(options, function (error, response, body) {
        if (error) {
            console.log('dashboard_data->getPayDayreport, meet error : ' + error);
            callback(false, error);
            return ;
        }
        if(response.statusCode === 200) {
          callback(true, body);
        }else {
          callback(false, body);
        }
    });
}

exports.getPayDayreport = getPayDayreport;

/**
 * 查询某个用户的mo信息
 * http://URL_HEAD_TBULOOK/data/pay/dayreport/user/mo/user_id
 * http://URL_HEAD_TBULOOK/data/pay/dayreport/user/mo/17562
 */
function getUserMoInfo(user_id, callback) {
    var options = {
        url : URL_HEAD_TBULOOK + '/data/pay/dayreport/user/mo/' + user_id,
        timeout : 2000,
        headers : { 'apikey': APIKEY }
    };
    request(options, function (error, response, body) {
        if (error) {
            console.log('dashboard_data->getPayDayreport, meet error : ' + error);
            callback(false, error);
            return ;
        }
        if(response.statusCode === 200) {
          callback(true, body);
        }else {
          callback(false, body);
        }
    });
}

exports.getUserMoInfo = getUserMoInfo;

/**
 * 查询某个用户的mr信息
 * http://URL_HEAD_TBULOOK/data/pay/dayreport/user/mr/user_id
 * http://URL_HEAD_TBULOOK/data/pay/dayreport/user/mr/17562
 */
function getUserMrInfo(user_id, callback) {
    var options = {
        url : URL_HEAD_TBULOOK + '/data/pay/dayreport/user/mr/' + user_id,
        timeout : 2000,
        headers : { 'apikey': APIKEY }
    };
    request(options, function (error, response, body) {
        if (error) {
            console.log('dashboard_data->getPayDayreport, meet error : ' + error);
            callback(false, error);
            return ;
        }
        if(response.statusCode === 200) {
          callback(true, body);
        }else {
          callback(false, body);
        }
    });
}

exports.getUserMrInfo = getUserMrInfo;

//
/**
 * 查询某个用户的页面跳转信息
 * http://URL_HEAD_TBULOOK/data/event/dayreport/user/pagechange/:user_id
 * http://URL_HEAD_TBULOOK/data/event/dayreport/user/pagechange/17569
 */
function getUserPagechangeInfo(user_id, callback) {
    var options = {
        url : URL_HEAD_TBULOOK + '/data/event/dayreport/user/pagechange/' + user_id,
        timeout : 2000,
        headers : { 'apikey': APIKEY }
    };
    request(options, function (error, response, body) {
        if (error) {
            console.log('dashboard_data->getUserMrInfo, meet error : ' + error);
            callback(false, error);
            return ;
        }
        if(response.statusCode === 200) {
          callback(true, body);
        }else {
          callback(false, body);
        }
    });
}

exports.getUserPagechangeInfo = getUserPagechangeInfo;

/**
 * 查询某个用户的游戏信息
 * http://URL_HEAD_TBULOOK/data/event/dayreport/user/gameinfo/:user_id
 * http://URL_HEAD_TBULOOK/data/event/dayreport/user/gameinfo/17569
 */
function getUserGameInfo(user_id, callback) {
    var options = {
        url : URL_HEAD_TBULOOK + '/data/event/dayreport/user/gameinfo/' + user_id,
        timeout : 2000,
        headers : { 'apikey': APIKEY }
    };
    request(options, function (error, response, body) {
        if (error) {
            console.log('dashboard_data->getUserGameInfo, meet error : ' + error);
            callback(false, error);
            return ;
        }
        if(response.statusCode === 200) {
          callback(true, body);
        }else {
          callback(false, body);
        }
    });
}
exports.getUserGameInfo = getUserGameInfo;

/**
 * 查询某个用户的游戏信息
 * http://URL_HEAD_TBULOOK/data/event/dayreport/user/register/user_id
 * http://URL_HEAD_TBULOOK/data/event/dayreport/user/register/19023
 */
function getUserRegisterInfo(user_id, callback) {
    var options = {
        url : URL_HEAD_TBULOOK + '/data/event/dayreport/user/register/' + user_id,
        timeout : 2000,
        headers : { 'apikey': APIKEY }
    };
    request(options, function (error, response, body) {
        if (error) {
            console.log('dashboard_data->getUserRegisterInfo, meet error : ' + error);
            callback(false, error);
            return ;
        }
        if(response.statusCode === 200) {
          callback(true, body);
        }else {
          callback(false, body);
        }
    });
}
exports.getUserRegisterInfo = getUserRegisterInfo;
