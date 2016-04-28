/**
 * 监听端口：1701
 * 部署服务器：106.75.135.78
 * tar -zcvf game_catchfish.tar.gz ./game_catchfish/
 * scp -P 1804  ./game_catchfish.tar.gz ubuntu@106.75.135.78:/home/ubuntu/
 */
var config = require('./script/config.json');
var noderice = require('noderice');
noderice.time_init();

var tbumailservice = require('./script/util/tbumailservice.js');

var dbmanager = require('./script/db/dbmanager.js');
var user_ids = require('./script/domain/user/user_ids.js');
var sign_logic = require('./script/domain/sign/sign_logic.js');
var marquee_logic = require('./script/domain/marquee/marquee_logic.js');
var activity_logic = require('./script/domain/activity/activity_logic.js');
var cdkey_logic = require('./script/domain/cdkey/cdkey_logic.js');
var mo_logic = require('./script/domain/mo/mo_logic.js');
var player_logic = require('./script/domain/player/player_logic.js');

process.on('uncaughtException', function (err) {
  console.log(err);
  console.log(err.stack);
  tbumailservice.sendWaringEmailForMolo('GAME_CG_ERROR', 'err : ' + err + ';' + err.stack);
});

dbmanager.init(function(result) {
    if(result) {
        user_ids.init();
        sign_logic.initConfig();
        marquee_logic.initConfig();
        mo_logic.init();
        player_logic.configRank();
        activity_logic.initConfig();
        cdkey_logic.initConfig();
    }else {
        console.log('[ERROR!!]app->init, db init error');
        tbumailservice.sendWaringEmailForMolo('GAME_CG_ERROR', '[DB]init fail...');
    }
});

var redishelper = require('./script/mem/redishelper.js');
redishelper.init();

var agreement = require('./script/agreement.js');

var express = require('express');
var app = express();

var handlebars = require('express3-handlebars')
        .create( {defaultLayout:'main'} );
app.engine('handlebars', handlebars.engine);
app.set('view engine', 'handlebars');
app.use(express.static(__dirname + '/public'));

var bodyParser = require('body-parser');
app.use(bodyParser.urlencoded({extended: true}));
app.set('port', config.app);

app.get( '/', function(req, res) {
    res.type('text/plain');
    res.status(200);
    res.send(agreement.welcomeDesc);
});

var user_routes = require('./script/domain/user/user_routes.js');      // 账号(用户)管理
app.use('/user', user_routes);
var player_routes = require('./script/domain/player/player_routes.js');      // 角色管理
app.use('/player', player_routes);
var mo_routes = require('./script/domain/mo/mo_routes.js');      // mo
app.use('/mo', mo_routes);
var mr_routes = require('./script/domain/mr/mr_routes.js');      // mr
app.use('/mr', mr_routes);
var gameevent_routes = require('./script/domain/gameevent/gameevent_routes.js');      // 游戏事件
app.use('/gameevent', gameevent_routes);
var config_routes = require('./script/domain/config/config_routes.js');      // 配置
app.use('/config', config_routes);
var sign_routes = require('./script/domain/sign/sign_routes.js');      // 配置
app.use('/sign', sign_routes);
var marquee_routes = require('./script/domain/marquee/marquee_routes.js');      // 跑马灯
app.use('/marquee', marquee_routes);
var help_routes = require('./script/domain/help/help_routes.js');      // 信息反馈
app.use('/help', help_routes);
var statistics_routes = require('./script/domain/statistics/statistics_routes.js');      // 信息反馈
app.use('/statistics', statistics_routes);  // 增加统计模块
var bankrupt_routes = require('./script/domain/bankrupt/bankrupt_routes.js');
app.use('/bankrupt', bankrupt_routes);  // 增加破产模块
var nobility_routes = require('./script/domain/nobility/nobility_routes.js');
app.use('/nobility', nobility_routes);  // 增加贵族模块

var bonuspool_routes = require('./script/domain/bonuspool/bonuspool_routes.js');
app.use('/bonuspool', bonuspool_routes);  // 抽奖
var activity_routes = require('./script/domain/activity/activity_routes.js');
app.use('/activity', activity_routes);  // 活动
var cdkey_routes = require('./script/domain/cdkey/cdkey_routes.js');
app.use('/cdkey', cdkey_routes);  // 兑换
var bag_routes = require('./script/domain/bag/bag_routes.js');
app.use('/bag', bag_routes);  // 背包
var gametask_routes = require('./script/domain/gametask/gametask_routes.js');
app.use('/gametask', gametask_routes);  // 任务
var room_routes = require('./script/domain/room/room_routes.js');
app.use('/room', room_routes);  // 房间信息
var vip_routes = require('./script/domain/vip/vip_routes.js');
app.use('/vip', vip_routes);  // vip信息
var change_routes = require('./script/domain/change/change_routes.js');
app.use('/change', change_routes);  // 对话控制
var mailbox_routes = require('./script/domain/mailbox/mailbox_routes.js');
app.use('/mailbox', mailbox_routes);  // 站内信
var present_routes = require('./script/domain/present/present_routes.js');
app.use('/present', present_routes);  // 赠送
var hongbao_routes = require('./script/domain/hongbao/hongbao_routes.js');
app.use('/hongbao', hongbao_routes);  // 红包
var share_routes = require('./script/domain/share/share_routes.js');
app.use('/share', share_routes);  // 分享

app.use ( function (req, res) {
    res.type('text/plain');
    res.status(404);
    res.send(agreement.notFound404Desc);
});

app.listen(app.get('port'), function() {
    var nowDate = new Date();
    console.log('express started on port :' + app.get('port'));
    tbumailservice.sendWaringEmailForMolo('GAME_CG_START', 'start time : ' + nowDate);
});
