
function getMarqueeConfig(client, callback) {
	var current_hour = getCurrentHour();
	var current_day = getCurrentDay();
	client.query(' SELECT content FROM config_marquee WHERE day = ? AND start_hour <= ? AND end_hour > ?',
					[current_day, current_hour, current_hour],
          function (err, results) {
        if (err) {
            console.log('[ERROR!!]marguee_db->getMarqueeConfig, msg : ' + err);
            callback( false, err );
            return;
        }
        if(results != undefined && results != null && results.length > 0) {
        	callback( true, results[0]['content'] );
        }else {
					console.log('marguee_db->getMarqueeConfig, go default config ');
					getMarqueeConfigDefaultDay(client, callback);
				}
    });
}

function getMarqueeConfigDefaultDay(client, callback) {
	var current_hour = getCurrentHour();
	client.query(' SELECT content FROM config_marquee WHERE day = ? AND start_hour <= ? AND end_hour > ?',
					['DAY', current_hour, current_hour],
          function (err, results) {
        if (err) {
            console.log('[ERROR!!]marguee_db->getMarqueeConfig, msg : ' + err);
            callback( false, err );
            return;
        }
        if(results != undefined && results != null && results.length > 0) {
        	callback( true, results[0]['content'] );
        }else {
					callback( false, 'result <= 0');
				}
    });
}

function getCurrentHour() {
	var hour = parseInt( new Date().Format("hh") );
	console.log('hour = ' + hour);
	return hour;
}

function getCurrentDay() {
	return new Date().Format("yyyy-MM-dd");
}

exports.getMarqueeConfig = getMarqueeConfig;
