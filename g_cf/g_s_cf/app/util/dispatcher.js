var crc = require('crc');

// select an item from list based on key
module.exports.dispatch = function(key, list) {

	if(key === undefined || key === null || key.length === undefined) {
		console.log('dispatch_error_key = ' + key);
		return list[0];
	}
	var index = Math.abs(crc.crc32(key)) % list.length;
	return list[index];
};
