

function getCurrentSignInfo(client, callback) {
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
        }else {
          callback( false, '[]' );
        }
    });
}

function updateSignConfig(client, info_value, callback) {
    // TODO : 未添加基本的参数效验
    var create_time = new Date().Format("yyyy-MM-dd hh:ss:S");
    client.query('UPDATE config_domain SET info_value = ?, update_time = ? WHERE info_key = ?',
        [info_value, create_time, 'sign'],
        function (err, results) {
            if(err) {
               console.log('updateSignConfig meet err : ' + err);
            }
            callback(err, results);
        }
    );
}

exports.getCurrentSignInfo = getCurrentSignInfo;
exports.updateSignConfig = updateSignConfig;
