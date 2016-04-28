
function getSignConfig(client, callback) {
	client.query(' SELECT info_value FROM config_domain WHERE info_key = ? ORDER BY version  DESC LIMIT 1',
					['sign'],
          function (err, results) {
        if (err) {
            console.log('[ERROR!!]sign_db->getSignConfig, msg : ' + err);
            callback( false, err );
            return;
        }
        if(results != undefined && results != null && results.length > 0) {
        	callback( true, results[0]['info_value'] );
        }
    });
}

exports.getSignConfig = getSignConfig;
