package com.poxiao.smspay.plgin.mark.domain.push;

import java.io.UnsupportedEncodingException;
import java.net.URLEncoder;
import java.text.SimpleDateFormat;
import java.util.Date;

import com.poxiao.smspay.plgin.mark.Mark;
import com.poxiao.smspay.plgin.mark.domain.KeyValue;
import com.poxiao.smspay.plgin.mark.util.MarkUtil;
import com.tbu.androidtools.app.AppInfo;
import com.tbu.androidtools.device.DeviceInfo;

public class PushTable {

	public final static String POST_URL = "4e488421b349ce70be8b0b1ff36b42a49d051e58cb1725182ff8694cf426019672e7eb79b207347a";

	/**
	 * 构造统计数据 - 统计支付会话行为
	 * 
	 * @param markInfo
	 * @return
	 */
	public static String createPayMarkInfo(PushInfo pushInfo) {
		KeyValue keyValue0 = new KeyValue("push_type",
				String.valueOf(pushInfo.push_type));
		KeyValue keyValue1 = new KeyValue("push_game_id",
				String.valueOf(pushInfo.push_game_id));
		KeyValue keyValue2 = new KeyValue("session_id",
				String.valueOf(pushInfo.session_id));
		KeyValue keyValue3 = new KeyValue("req_install_times",
				String.valueOf(pushInfo.req_install_times));
		KeyValue keyValue4 = new KeyValue("result_code",
				String.valueOf(pushInfo.result_code));
		KeyValue keyValue5 = new KeyValue("req_action", pushInfo.req_action);
		KeyValue keyValue6 = new KeyValue("push_game_name",
				pushInfo.push_game_name);

		KeyValue keyValue7 = new KeyValue("package_size",
				String.valueOf(pushInfo.package_size));
		KeyValue keyValue8 = new KeyValue("download_time",
				String.valueOf(pushInfo.download_time));
		KeyValue keyValue9 = new KeyValue("task_seq",
				String.valueOf(pushInfo.task_seq));
		KeyValue keyValue10 = new KeyValue("push_version",
				String.valueOf(pushInfo.push_version));

		KeyValue keyValue18;
		try {
			keyValue18 = new KeyValue("appname", URLEncoder.encode(
					AppInfo.getAppName(), "utf-8"));
		} catch (UnsupportedEncodingException e) {
			keyValue18 = new KeyValue("appname", AppInfo.getAppName());
			e.printStackTrace();
		}

		KeyValue keyValue19 = new KeyValue("accesstype",
				String.valueOf(DeviceInfo.getNewAccessType()));
		KeyValue keyValue20 = new KeyValue("hdfactory", DeviceInfo.getProduct());

		KeyValue keyValue21 = new KeyValue("hdtype", DeviceInfo.getModle());
		KeyValue keyValue22 = new KeyValue("imei", DeviceInfo.getei());
		KeyValue keyValue23 = new KeyValue("imsi", DeviceInfo.getsi());

		Date nowTime = new Date();
		SimpleDateFormat time = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss:SSS");
		KeyValue keyValue24 = new KeyValue("client_create_time",
				time.format(nowTime));

		KeyValue keyValue25 = new KeyValue("markversion", Mark.VERSION);
		KeyValue keyValue26 = new KeyValue("platformversion",
				DeviceInfo.getPlatformVersion());
		KeyValue keyValue27 = new KeyValue("thirdapp",
				DeviceInfo.getSafeAppState()); // 第三方软件安装情况

		return MarkUtil.DoContentJoint(keyValue0, keyValue1, keyValue2,
				keyValue3, keyValue4, keyValue5, keyValue6, keyValue7,
				keyValue8, keyValue9, keyValue10, keyValue18, keyValue19,
				keyValue20, keyValue21, keyValue22, keyValue23, keyValue24,
				keyValue25, keyValue26, keyValue27);
	}
}
