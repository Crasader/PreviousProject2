
function getLastFeedback(client, callback) {
  client.query(' SELECT * FROM feedback ORDER BY create_time DESC LIMIT 30',
      function (err, results) {
    if (err) {
      console.log('[ERROR!!]help_db->getLastFeedback, msg : ' + err);
      callback( false, err );
      return;
    }
    if(results != undefined && results != null && results.length > 0) {
      callback(true, results );
    }else {
      callback(false, '[]' );
    }
  });
}

exports.getLastFeedback = getLastFeedback;
