var config = require('./script/config.json');

var dashboard_data = require('./script/data/dashboard/dashboard_data.js');

var noderice = require('noderice');
noderice.time_init();

var authmanager = require('./script/authmanager.js');

var map = new Map();
var express = require('express');
var app = express();

var cookieParser = require('cookie-parser');
app.use(cookieParser());

var handlebars = require('express3-handlebars')
        .create( {defaultLayout:'main'} );
app.engine('handlebars', handlebars.engine);
app.set('view engine', 'handlebars');

app.use(express.static(__dirname + '/public'));
var bodyParser = require('body-parser');
app.use(bodyParser.json({limit: '1mb'}));  //body-parser 解析json格式数据
app.use(bodyParser.urlencoded({extended: true}))
app.set('port', config.app);

var map_router = require('./script/domain/map/map_router.js');
app.use( '/map', authmanager.checkLogin, map_router);  // 导航页面
var sign_router = require('./script/domain/config/sign/sign_router.js');
app.use( '/config/sign', authmanager.checkLogin, sign_router);  // 签到页面
var config_mo_router = require('./script/domain/config/mo/config_mo_router.js');
app.use( '/config/mo', authmanager.checkLogin, config_mo_router);  // 签到页面
var config_commonevent_router = require('./script/domain/config/commonevent/config_commonevent_router.js');
app.use( '/config/commonevent', authmanager.checkLogin, config_commonevent_router);  // 普通事件统计页面
var data_router = require('./script/domain/data/data_router.js');
app.use( '/data', authmanager.checkLogin, data_router);  // 数据部分
var help_router = require('./script/domain/help/help_router.js');
app.use( '/help', authmanager.checkLogin, help_router);  // 帮助系统

app.get( '/', authmanager.checkLogin, function(req, res) {
    res.render('home');
});

app.get('/listener', function(req, res) {
    res.type('text/plain');
    res.status(200);
    res.send('Welcome To tbu bgp look ... ...');
});

app.get( '/index', function(req, res) {
    res.render('index');
});

app.get( '/thanks', function(req, res) {
    res.render('thanks');
});

app.get( '/register', function(req, res) {
    var username = req.query.username;
    var passwd = req.query.passwd;
    var reqinfo = req.query.reqinfo == undefined ? 'NA' : req.query.reqinfo;
    // 没有做参数效验
    if (username == null || username == undefined ||
            passwd == null || passwd == undefined) {
        res.render('register');
    }else {
        // TODO : 等待处理注册业务
        (function(reqinfo){
            authmanager.createNewUserNameAndPasswd(username, passwd, function(success, username, storePasswd, salt){
                if(success) {
                    dashboard_data.reqDashboardNewUserInfo(username, storePasswd, salt, reqinfo, function(){
                        res.redirect('/thanks');
                    });
                }
            });
        })(reqinfo);
    }
});

app.get( '/switchuser', authmanager.checkLogin, function(req, res) {
    authmanager.logout(req);
    res.redirect('/login');
});

app.get( '/login', function(req, res) {
    var username = req.query.username;
    var passwd = req.query.passwd;
    // console.log('/login->username = ' + username + ';passwd = ' + passwd);
    if (username == null || username == undefined) {
        res.render('login');
    }else {
        (function(passwd){
            dashboard_data.getDashboardUserInfo(username, function(success, result){
                if(!success) {
                    res.render('login');
                    return ;
                }
                // console.log('login info, result = ' + result);
                var resultObj = JSON.parse(result);
                if(resultObj != null && resultObj[0] != undefined && parseInt(resultObj[0]["authentication"])==1) {
                    if(authmanager.allowLogin(passwd, resultObj[0]["passwd"], resultObj[0]["salt"])) {
                        var cookieId = authmanager.createCookieId();
                        authmanager.setNewUser(
                                cookieId,
                                parseInt(resultObj[0]["role"]),
                                resultObj[0]["name"]);
                        res.cookie(authmanager.getCookieKey(), cookieId, {maxAge: authmanager.getCookieTime()});
                        res.redirect('/');
                    } else {
                        res.render('login');
                    }
                }else {
                    res.render('login');
                }
            });
        })(passwd);
    }
});

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
