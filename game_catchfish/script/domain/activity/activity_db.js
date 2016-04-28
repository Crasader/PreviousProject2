'use strict';

function getActivityConfig(client, callback) {
	// TODO : 查询没有过期的数据
	var current_day_num = getCurrentDayNum();
	client.query(' SELECT * FROM config_activity WHERE invalid_day >= ? ',
					[current_day_num],
          function (err, results) {
        if (err) {
            console.log('[ERROR!!]activity_db->getActivityConfig, msg : ' + err);
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

exports.getActivityConfig = getActivityConfig;

function getCurrentDayNum() {
	return new Date().Format("yyyyMMdd");
}
