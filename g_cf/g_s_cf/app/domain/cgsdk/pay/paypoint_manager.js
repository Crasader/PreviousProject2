'use strict';

var paypoint = require('../../../../config/domain/paypoint.json');
paypoint = paypoint.paypoint;

function getRewardsByPayPointId(pay_point_id){
  pay_point_id = parseInt(pay_point_id);
  for(var i=0;i<paypoint.length;i++){
    if(pay_point_id === paypoint[i].id) {
      return paypoint[i].reward_lists;
    }
  }
  return [];
}

exports.getRewardsByPayPointId = getRewardsByPayPointId;


function getPrice(pay_point_id){
  pay_point_id = parseInt(pay_point_id);
  for(var i=0;i<paypoint.length;i++){
    if(pay_point_id === paypoint[i].id) {
      return paypoint[i].price;
    }
  }
  return 0;
}
exports.getPrice = getPrice;
