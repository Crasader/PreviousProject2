
function getDayreport(client, day, callback) {
  client.query(' SELECT * FROM report_channel_day WHERE day = ?',
      [day],
    function (err, results) {
      if (err) {
        console.log('[ERROR!!]channel_db->getDayreport, msg : ' + err);
        callback( false, err );
        return;
      }
      if(results != undefined && results != null && results.length > 0) {
        callback( true, results);
      }else {
        callback( true, []);
      }
    }
  );
}

exports.getDayreport = getDayreport;

function getOnechannelInfo(client, channel_id, callback) {
  client.query(' SELECT * FROM report_channel_day WHERE channel_id = ? ORDER BY day  DESC LIMIT 0 , 10',
      [channel_id],
    function (err, results) {
      if (err) {
        console.log('[ERROR!!]channel_db->getOnechannelInfo, msg : ' + err);
        callback( false, err );
        return;
      }
      if(results != undefined && results != null && results.length > 0) {
        callback( true, results);
      }else {
        callback( true, []);
      }
    }
  );
}

exports.getOnechannelInfo = getOnechannelInfo;
