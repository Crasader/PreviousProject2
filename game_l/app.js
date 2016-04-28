/**
 * http://114.119.39.150:1703
 */
var config = require('./script/config.json');
var noderice = require('noderice');
noderice.time_init();

var task = require('./script/domain/task/task.js');

var dbmanager_bg = require('./script/db/dbmanager_bg.js');
dbmanager_bg.init(function(success){
    if(success) {
        // TODO : 数据库初始化成功回调
    }
});
var dbmanager_catchfish = require('./script/db/dbmanager_catchfish.js');
dbmanager_catchfish.init(function(success){
  console.log('dbmanager_catchfish init result : ' + success);
    if(success) {
        setTimeout(task.init(), 3*1000);
    }
});

var express = require('express');
var app = express();
var bodyParser = require('body-parser');
app.use(bodyParser.urlencoded({extended: true}));
app.set('port', config.app);

app.get( '/', function(req, res) {
    res.type('text/plain');
    res.status(200);
    res.send('Welcome To game bg ... ...');
});

var user_router = require('./script/domain/user/user_router.js');    // 用户登陆注册
app.use('/user', user_router);
var sign_router = require('./script/domain/config/sign/sign_router.js');    // 签到配置
app.use('/config/sign', sign_router);
var commonevent_router = require('./script/domain/config/commonevent/commonevent_router.js');    // 普通事件点统计配置
app.use('/config/commonevent', commonevent_router);

var mo_router = require('./script/domain/config/mo/mo_router.js');    // 签到配置
app.use('/config/mo', mo_router);
var data_channel_router = require('./script/domain/data/channel/channel_router.js');    // 数据查看-渠道
app.use('/data/channel', data_channel_router);
var data_event_router = require('./script/domain/data/event/event_router.js');    // 数据查看-事件统计
app.use('/data/event', data_event_router);
var data_pay_router = require('./script/domain/data/pay/pay_router.js');    // 数据查看-事件统计
app.use('/data/pay', data_pay_router);


var help_router = require('./script/domain/help/help_router.js');    // 用户反馈
app.use('/help', help_router);

app.use ( function (req, res) {
    res.type('text/plain');
    res.status(404);
    res.send('404 - NOT FOUND');
});



app.listen(app.get('port'), function() {
    var nowDate = new Date();
    console.log(nowDate.toLocaleDateString() + ' ' +
        nowDate.toLocaleTimeString() );
    console.log('express started on port :' + app.get('port'));
});
