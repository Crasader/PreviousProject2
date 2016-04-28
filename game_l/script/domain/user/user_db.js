

function getUserInfo(client, username, callback) {
        console.log('getUserInfo, username : ' + username);
        client.query('select name, passwd, salt, role, authentication, username'+
            ' from user where name =?',
        [username],
        function (err, results) {
            callback(err, results);
        });
}

function reqNewUserInfo(client, username, passwd, salt, reqinfo, callback) {
    // TODO : 未添加基本的参数效验
    var create_time = new Date().Format("yyyy-MM-dd");
    client.query('INSERT INTO user SET name = ?, passwd = ?, salt = ?, req_info = ?, create_time = ?',
        [username, passwd, salt, reqinfo, create_time],
        function (err, results) {
            if(err) {
               console.log('reqNewUserInfo meet err : ' + err); 
            }
            callback(err, results);
        }
    );
}

exports.getUserInfo = getUserInfo;
exports.reqNewUserInfo = reqNewUserInfo;
