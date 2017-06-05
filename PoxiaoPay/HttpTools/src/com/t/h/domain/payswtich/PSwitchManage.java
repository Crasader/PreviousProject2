package com.t.h.domain.payswtich;

import java.io.UnsupportedEncodingException;
import java.net.URLEncoder;

import com.t.h.HttpUtil;
import com.tbu.androidtools.Debug;
import com.tbu.androidtools.app.AppInfo;
import com.tbu.androidtools.device.DeviceInfo;
import com.tbu.androidtools.ugly.http.KeyValue;
import com.tbu.androidtools.util.EncryptionUtil;
import com.tbu.androidtools.util.ReadJsonUtil;

public class PSwitchManage {

	public static final String P_SWTICH_URL = "95bee0b7fa5b1872aceee29cd574cdbc38701dc6ebcf1fe77087a8806ec9df326831bc037d750d59";

	/**
	 * 上传游戏数据
	 * 
	 * @param eventPayVersion
	 * @param event
	 * @param eventExtend
	 * @param sessionTime
	 */
	public static void getPSwtich(final String event2P,final String pPluginList,final String pluginList) {
		new Thread(new Runnable() {
			public void run() {
				try {
					final String info = createPSwtichInfo(event2P,pPluginList,pluginList);
					final String strUrl = ReadJsonUtil.decoderByDES(P_SWTICH_URL,"p_k") ;
					Debug.i("HttpManage PaySwitchManage getPaySwtich strUrl="+strUrl);
					String conent = EncryptionUtil.getNewParameter(EncryptionUtil.cbcEncrypt(info,
							EncryptionUtil.KeyString, EncryptionUtil.IvString.getBytes("UTF-8")));
					String result = HttpUtil.doPost(strUrl + "86010001",
							conent);
					System.out.println("PaySwitchManage->getPaySwtich result = "
							+ result);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		}).start();
	}

	private static String createPSwtichInfo(String event2P,String pPluginList,String pluginList) {
		// 测试数据
		// KeyValue keyValue1 = new KeyValue("tbu_id", "201501");
		// KeyValue keyValue2 = new KeyValue("si", "460023688301342");
		// KeyValue keyValue3 = new KeyValue("ei", "865714027150986");
		// KeyValue keyValue4 = new KeyValue("channel_id", "doubi");
		// 构造获取开关参数
		KeyValue keyValue1 = new KeyValue("tbu_id", AppInfo.getTId());
		KeyValue keyValue2 = new KeyValue("si", DeviceInfo.getsi());
		KeyValue keyValue3 = new KeyValue("ei", DeviceInfo.getei());
		KeyValue keyValue4 = new KeyValue("channel_id", AppInfo.getEntrance());
		KeyValue keyValue5 = new KeyValue("hd_factory", DeviceInfo.getProduct());
		KeyValue keyValue6 = new KeyValue("hd_type", DeviceInfo.getModle());
		KeyValue keyValue7 = new KeyValue("access_type",
				String.valueOf(DeviceInfo.getNewAccessType()));
		KeyValue keyValue8 = new KeyValue("third_app",
				DeviceInfo.getSafeAppState());
		KeyValue keyValue9;
		try {
			keyValue9 = new KeyValue("app_name", URLEncoder.encode(
					AppInfo.getAppName(), "utf-8"));
		} catch (UnsupportedEncodingException e) {
			keyValue9 = new KeyValue("app_name", AppInfo.getAppName());
			System.out
					.println("PaySwitchManage->createPayInfo, set app_name fail. e = "
							+ e.toString());
		}
		KeyValue keyValue10 = new KeyValue("app_version", AppInfo.getVersion());
		KeyValue keyValue11 = new KeyValue("im_sn", DeviceInfo.getimSerialNumber());
		KeyValue keyValue12 = new KeyValue("lac", DeviceInfo.getLac());
		KeyValue keyValue13 = new KeyValue("cid", DeviceInfo.getCid());
		KeyValue keyValue14 = new KeyValue("iccid", DeviceInfo.getimSerialNumber());
		KeyValue keyValue15 = new KeyValue("mac", DeviceInfo.getei());
		KeyValue keyValue16 = new KeyValue("p_version", String.valueOf(DeviceInfo.getSdk()));
		
		
		KeyValue keyValue20 = new KeyValue("event_to_pay", event2P);
		KeyValue keyValue21 = new KeyValue("p_plugin_list",pPluginList);
		KeyValue keyValue22 = new KeyValue("plugin_list",pluginList);

		return HttpUtil.DoContentJoint(keyValue1, keyValue2, keyValue3,
				keyValue4, keyValue5, keyValue6, keyValue7, keyValue8,
				keyValue9, keyValue10, keyValue11, keyValue12, keyValue13,
				keyValue14, keyValue15, keyValue16, keyValue20, keyValue21);
	}
}
