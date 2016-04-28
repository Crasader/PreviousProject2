

function getPaypoint(client, callback) {
    client.query(' SELECT * FROM paypoint',
          function (err, results) {
        if (err) {
            console.log('[ERROR!!]mo_db->getPaypoint, msg : ' + err);
            callback( false, err );
            return;
        }
        if(results != undefined && results != null && results.length > 0) {
            callback( true, results );
        }else {
          callback( false, 'no data');
        }
    });
}

function getPayevent(client, callback) {
        client.query(' SELECT * FROM event',
          function (err, results) {
        if (err) {
            console.log('[ERROR!!]mo_db->getPayevent, msg : ' + err);
            callback( false, err );
            return;
        }
        if(results != undefined && results != null && results.length > 0) {
            callback( true, results );
        }else {
          callback( false, 'no data');
        }
    });
}

exports.getPaypoint = getPaypoint;
exports.getPayevent = getPayevent;
