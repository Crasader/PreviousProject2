module.exports = function(app) {
	return new EnterRemote(app);
};



var EnterRemote = function(app) {
	this.app = app;
	this.channelService = app.get('channelService');
};


/**
 * Kick user out game channel.
 *
 * @param {String} uid unique id for user
 * @param {String} sid server id
 * @param {String} name channel name
 *
 */
EnterRemote.prototype.kick = function(uid, cb) {
	var sessionService = this.app.get('sessionService');	// TODO : 测试踢人
	var callback =function(result){console.log('kick callback' + result);};
	sessionService.kick(uid, callback);
	cb();
};
