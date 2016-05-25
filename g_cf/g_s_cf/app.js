var pomelo = require('pomelo');
var dispatcher = require('./app/util/dispatcher');
var httpconfig = require('./config/httpconfig.json');

var express_req = require('express');
var express = express_req();
var bodyParser = require('body-parser');
express.use(bodyParser.urlencoded({extended: true}));

express.set('port', httpconfig.app);

// route definition for game server
var gameRoute = function(session, msg, app, cb) {
  var gameServers = app.getServersByType('game');

	if(!gameServers || !(gameServers.length > 0) ) {
		cb(new Error('can not find game servers.'));
		return;
	}
	var res = dispatcher.dispatch(session.get('rid'), gameServers);
  console.log('dispatcher->gameRoute, res = ' + JSON.stringify(res));
	cb(null, res.id);
};

/**
 * Init app for client.
 */
var app = pomelo.createApp();
app.set('name', 'chatofpomelo-websocket');

// app configuration
app.configure('production|development', 'connector', function(){
	app.set('connectorConfig',
		{
			connector : pomelo.connectors.hybridconnector,
			heartbeat : 3,
		});
});

app.configure('production|development', 'gate', function(){
	app.set('connectorConfig',
		{
			connector : pomelo.connectors.hybridconnector,
			useProtobuf : true
		});
});

// app configure
app.configure('production|development', function() {
	// route configures
	app.route('game', gameRoute);

	// filter configures
	// app.filter(pomelo.timeout());
});

express.get( '/gate/:user_id', function(req, res) {
    res.type('text/plain');
    res.status(200);
    var user_id = req.params.user_id;
    if(user_id === undefined || user_id === null ||
        user_id.length < 3) {
      var error =  {
      		errorcode: 100,
      		msg  : 'params error'
      };
      res.end(JSON.stringify(error));
      return;
    }


    var connectors = app.getServersByType('connector');
    if(!connectors || connectors.length === 0) {
  		var error =  {
  			errorcode: 500,
  			msg  : 'error connectors'
  		};
      res.end(JSON.stringify(error));
  		return;
  	}
  	// select connector, because more than one connector existed.
  	var result_info = dispatcher.dispatch(user_id, connectors);
  	var result =  {
  		errorcode: 0,
      msg : 'success',
  		host: result_info.host,
  		port: result_info.clientPort
  	};
    res.end(JSON.stringify(result));
});

express.use ( function (req, res) {
    res.type('text/plain');
    res.status(404);
    res.send('404 - NOT FOUND');
});

// start app
app.start();

process.on('uncaughtException', function(err) {
	console.error(' Caught exception: ' + err.stack);
});

var initExpressState = false;
function initExpress() {
  if(initExpressState) {
    console.log('[express] inited !!');
    return ;
  }
  initExpressState = true;
  express.listen(express.get('port'), function() {
      var nowDate = new Date();
      console.log('[express]' + nowDate.toLocaleDateString() + ' ' +
          nowDate.toLocaleTimeString() );
      console.log('[express]game gate server(http) started on port :' + express.get('port'));
  });
}

// initExpress();
