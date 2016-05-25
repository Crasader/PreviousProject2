
function addNewMo(client, reqreq_booking_info, callback) {
	client.query(' INSERT INTO mo_'+ reqreq_booking_info.mo_id +
			' SET pay_and_event_version = ?, pay_event_id = ?, pay_point_id = ?,' +
      ' type = ?, order_id = ?, user_id = ?, third_type = ?, ' +
      ' result = ?, channel_id = ?, price = ?, create_time = ?',
			[reqreq_booking_info.pay_and_event_version, reqreq_booking_info.pay_event_id, reqreq_booking_info.pay_point_id,
      reqreq_booking_info.pay_type, reqreq_booking_info.order_id, reqreq_booking_info.user_id, reqreq_booking_info.third_type,
      reqreq_booking_info.result, reqreq_booking_info.channel_id, reqreq_booking_info.price, reqreq_booking_info.create_time],
            function (err, results) {
        if (err) {
            console.log('[ERROR!!]mo_db->addNewMo, msg : ' + err);
            callback(false);
            return;
        }
        callback(true);
    });	// TODO : 增加第三方支付类型入库
}
exports.addNewMo = addNewMo;
