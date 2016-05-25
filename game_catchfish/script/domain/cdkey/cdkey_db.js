'use strict';

function getCdkeyConfig(client, callback) {
	var current_day_num = getCurrentDayNum();
	client.query(' SELECT * FROM config_cdkey WHERE start_day <= ? AND end_day >= ?',
					[current_day_num, current_day_num],
          function (err, results) {
        if (err) {
            console.log('[ERROR!!]cdkey_db->getCdkeyConfig, msg : ' + err);
            callback( false, err );
            return;
        }
        if(results != undefined && results != null && results.length > 0) {
        	callback( true, results);
        }else {
					callback( false, results);
				}
    });
}

exports.getCdkeyConfig = getCdkeyConfig;

function setCdkeyChannelConfig(client, cdkey, channel_id, callback) {
	console.log('[setCdkeyChannelConfig]cdkey : ' + cdkey + '; channel_id = ' + channel_id);
	client.query(' UPDATE config_cdkey SET spec_channel = ? WHERE cdkey = ? ',
					[channel_id, cdkey],
          function (err, results) {
        if (err) {
            console.log('[ERROR!!]cdkey_db->setCdkeyChannelConfig, msg : ' + err);
            callback(false);
            return;
        }
        callback(true);
    });
}

exports.setCdkeyChannelConfig = setCdkeyChannelConfig;

function getCurrentDayNum() {
	return new Date().Format("yyyyMMdd");
}
