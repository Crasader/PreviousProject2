

function getCommonevents(client, callback) {
        client.query(' SELECT event_id, event_desc, user_desc FROM commons_event_definition ORDER BY event_id ASC',
          function (err, results) {
        if (err) {
            console.log('[ERROR!!]commonevent_db->getCommonevents, msg : ' + err);
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


exports.getCommonevents = getCommonevents;
