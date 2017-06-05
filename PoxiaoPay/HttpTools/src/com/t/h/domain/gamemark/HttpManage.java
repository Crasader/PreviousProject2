package com.t.h.domain.gamemark;

import com.t.h.HttpUtil;
import com.tbu.androidtools.Debug;
import com.tbu.androidtools.app.AppInfo;
import com.tbu.androidtools.device.DeviceInfo;
import com.tbu.androidtools.ugly.http.KeyValue;
import com.tbu.androidtools.util.EncryptionUtil;
import com.tbu.androidtools.util.ReadJsonUtil;

public class HttpManage {
	public static final String POST_MARK_URL = "95bee0b7fa5b1872a03813228da0211e71934454cdc074498ff65d22c611745e8bd1ac91f296e90e";

	/**
	 * 上传游戏数据
	 * 
	 * @param eventPayVersion
	 * @param event
	 * @param eventExtend
	 * @param sessionTime
	 */
	public static void uploadData(String eventPayVersion, String event, String eventExtend, String sessionTime,
			String markVersion) {
		final String info = createPayInfo(eventPayVersion, event, eventExtend, sessionTime, markVersion);
		final String strUrl = ReadJsonUtil.decoderByDES(POST_MARK_URL, "p_k");
		Debug.i("HttpManage HttpManage uploadData strUrl=" + strUrl);
		new Thread(new Runnable() {
			public void run() {
				try {
					String conent = EncryptionUtil.getNewParameter(EncryptionUtil.cbcEncrypt(info,
							EncryptionUtil.KeyString, EncryptionUtil.IvString.getBytes("UTF-8")));
					HttpUtil.doPost(strUrl, conent);
				} catch (Exception e) {
					e.printStackTrace();
				}

			}
		}).start();
	}

	private static String createPayInfo(String eventPayVersion, String event, String eventExtend, String sessionTime,
			String markVersion) {

		KeyValue keyValue1 = new KeyValue("tbu_id", AppInfo.getTId());
		KeyValue keyValue2 = new KeyValue("si", DeviceInfo.getsi());
		KeyValue keyValue3 = new KeyValue("event_pay_version", eventPayVersion);
		KeyValue keyValue4 = new KeyValue("event", event);
		KeyValue keyValue5 = new KeyValue("event_extend", eventExtend);
		KeyValue keyValue6 = new KeyValue("session_time", sessionTime);
		KeyValue keyValue7 = new KeyValue("channel_id", AppInfo.getEntrance());
		KeyValue keyValue8 = new KeyValue("mark_version", markVersion);

		// KeyValue keyValue1 = new KeyValue("tbu_id", "201531");
		// KeyValue keyValue2 = new KeyValue("imsi", "46012345678");
		// KeyValue keyValue3 = new KeyValue("event_pay_version",
		// eventPayVersion);
		// KeyValue keyValue4 = new KeyValue("event", event);
		// KeyValue keyValue5 = new KeyValue("event_extend", eventExtend);
		// KeyValue keyValue6 = new KeyValue("session_time", sessionTime);
		// KeyValue keyValue7 = new KeyValue("channel_id", "test");
		// KeyValue keyValue8 = new KeyValue("mark_version", markVersion);

		return HttpUtil.DoContentJoint(keyValue1, keyValue2, keyValue3, keyValue4, keyValue5, keyValue6, keyValue7,
				keyValue8);
	}
}
