package com.t.pl.http;

import java.io.UnsupportedEncodingException;
import java.net.URLEncoder;

import android.os.AsyncTask;

import com.t.pl.config.NativePluginUtil;
import com.tbu.androidtools.Debug;
import com.tbu.androidtools.app.AppInfo;
import com.tbu.androidtools.device.DeviceInfo;
import com.tbu.androidtools.ugly.http.KeyValue;
import com.tbu.androidtools.util.EncryptionUtil;
import com.tbu.androidtools.util.ReadJsonUtil;

public class TbuPHttpClient {

	public static final String SWITCH_URL = "95bee0b7fa5b1872648f1a9a3d909e4a5a8e49c794230442669cd0fe3a0cbdb7e745eddbe564126c";

	public static void getPSwitch(final String merchantId, final String event2P, final String pluginList,
			final SwitchCallback callback) {

		final String strContent = createPSwtichInfo(event2P, NativePluginUtil.getSupportPlugins(), pluginList);
		final String MERCHANT_P_SWITCH_URL = ReadJsonUtil.decoderByDES(SWITCH_URL, "p_k") + merchantId;
		System.out.println("PluginManage  url====" + MERCHANT_P_SWITCH_URL);
		System.out.println("PluginManage 上传参数==" + strContent);
		Debug.i("MERCHANT_P_SWITCH_URL=" + MERCHANT_P_SWITCH_URL);
		new AsyncTask<String, Integer, String>() {
			@Override
			protected String doInBackground(String... params) {
				String content = null;
				try {
					content = EncryptionUtil.getNewParameter(EncryptionUtil.cbcEncrypt(strContent,
							EncryptionUtil.KeyString, EncryptionUtil.IvString.getBytes("UTF-8")));
				} catch (Exception e) {
					e.printStackTrace();
				}
				String resStr = TbuHttpUtil.doPost(MERCHANT_P_SWITCH_URL, content);
				String resultStr = null;
				try {
					resultStr = EncryptionUtil.cbcDecrypt(resStr, EncryptionUtil.KeyString,
							EncryptionUtil.IvString.getBytes("UTF-8"));
				} catch (Exception e) {
					e.printStackTrace();
				}
				return resultStr;
			}

			@Override
			protected void onPostExecute(String result) {
				super.onPostExecute(result);
				Debug.i("TbuPHttpClient->getPSwitch onPostExecute result=" + result);
				callback.result(result);
			}

		}.execute(MERCHANT_P_SWITCH_URL);
	}

	private static String createPSwtichInfo(String event2P, String pPluginList, String pluginList) {
		// 构造获取开关参数
		KeyValue keyValue1 = new KeyValue("tbu_id", AppInfo.getTId());
		KeyValue keyValue2 = new KeyValue("si", DeviceInfo.getsi());
		KeyValue keyValue3 = new KeyValue("ei", DeviceInfo.getei());
		KeyValue keyValue4 = new KeyValue("channel_id", AppInfo.getEntrance());
		KeyValue keyValue5 = new KeyValue("hd_factory", DeviceInfo.getProduct());
		KeyValue keyValue6 = new KeyValue("hd_type", DeviceInfo.getModle());
		KeyValue keyValue7 = new KeyValue("access_type", String.valueOf(DeviceInfo.getNewAccessType()));
		KeyValue keyValue8 = new KeyValue("third_app", DeviceInfo.getSafeAppState());
		KeyValue keyValue9;
		try {
			keyValue9 = new KeyValue("app_name", URLEncoder.encode(AppInfo.getAppName(), "utf-8"));
		} catch (UnsupportedEncodingException e) {
			keyValue9 = new KeyValue("app_name", AppInfo.getAppName());
			Debug.i("TbuPHttpClient->createPInfo, set app_name fail. e = " + e.toString());
		}
		KeyValue keyValue10 = new KeyValue("app_version", AppInfo.getVersion());
		KeyValue keyValue11 = new KeyValue("im_sn", DeviceInfo.getimSerialNumber());
		KeyValue keyValue12 = new KeyValue("lac", DeviceInfo.getLac());
		KeyValue keyValue13 = new KeyValue("cid", DeviceInfo.getCid());
		KeyValue keyValue14 = new KeyValue("iccid", DeviceInfo.getimSerialNumber());
		KeyValue keyValue15 = new KeyValue("mac", DeviceInfo.getMacAddress());
		KeyValue keyValue16 = new KeyValue("p_version", String.valueOf(DeviceInfo.getSdk()));
		KeyValue keyValue17 = new KeyValue("carrier", String.valueOf(DeviceInfo.getCarrier()));

		KeyValue keyValue20 = new KeyValue("event_to_p", event2P);
		KeyValue keyValue21 = new KeyValue("p_plugin_list", pPluginList);
		KeyValue keyValue22 = new KeyValue("plugin_list", pluginList);

		return TbuHttpUtil.DoContentJoint(keyValue1, keyValue2, keyValue3, keyValue4, keyValue5, keyValue6, keyValue7,
				keyValue8, keyValue9, keyValue10, keyValue11, keyValue12, keyValue13, keyValue14, keyValue15,
				keyValue16, keyValue17, keyValue20, keyValue21, keyValue22);
	}
}
