
var request = require('request');
var urlencode=require('urlencode');

function sendWaringEmail(title,msg){
    var options = {
        url:'http://183.131.152.31:1508/sendEmail/'+urlencode(title)+'/'+urlencode(msg)+'/zara/catchfish@tallbigup.com',
        timeout: 8000 };

    request(options, function (error, response, body) {
        if (error) {
            console.log('tbuoutdata->getProcessList, meet error : ' + error);
            return ;
        }
        console.log('tbuoutdata->getProcessList, resulut : ' + body
                + '; response.statusCode = ' + response.statusCode);
    });
}

exports.sendWaringEmail = sendWaringEmail;

function sendWaringEmailForMolo(title,msg){
    var options = {
        url:'http://183.131.152.31:1508/sendEmail/'+urlencode(title)+'/'+urlencode(msg)+'/zara/molo.xiao@tallbigup.com',
        timeout: 8000 };

    request(options, function (error, response, body) {
        if (error) {
            console.log('tbuoutdata->getProcessList, meet error : ' + error);
            return ;
        }
        console.log('tbuoutdata->getProcessList, resulut : ' + body
                + '; response.statusCode = ' + response.statusCode);
    });
}

exports.sendWaringEmailForMolo = sendWaringEmailForMolo;
