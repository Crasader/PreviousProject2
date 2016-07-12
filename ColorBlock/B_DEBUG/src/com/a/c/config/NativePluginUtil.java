package com.a.c.config;

import java.io.IOException;
import java.io.InputStream;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import android.content.Context;

import com.tbu.androidtools.Debug;
import com.tbu.androidtools.device.DeviceInfo;
import com.tbu.androidtools.util.ReadJsonUtil;

public class NativePluginUtil {
	private static final String P_CONFIG = "json/pconfig.json";// 定义json文件的目录及名称

	private static String defaultCMPayPlgin; // 默认移动支付
	private static String defaultCUPayPlgin; // 默认联通支付
	private static String defaultCNPayPlgin; // 默认电信支付
	private static String defaultNAPayPlgin; // 默认电信支付
	private static String supportPlagins;
	private static String gameId;
	private static String appId;

	public static String getDefaultPayPlgins() {
		if (DeviceInfo.getCarrier() == 1 || DeviceInfo.getCarrier() == 4) {
			// 移动或者铁通都是移动
			return changeDeal(defaultCMPayPlgin);
		} else if (DeviceInfo.getCarrier() == 2) { // 联通
			return changeDeal(defaultCUPayPlgin);
		} else if (DeviceInfo.getCarrier() == 3) { // 电信
			return changeDeal(defaultCNPayPlgin);
		}
		return changeDeal(defaultNAPayPlgin);
	}

	public static String getSupportPlagins() {
		return supportPlagins;
	}

	public static String getGameId() {
		return gameId;
	}

	public static String getAppId() {
		return appId;
	}

	public static void initPayConfigInfo(Context context) {

		InputStream input = null;
		try {
			// 获取文件内容
			input = context.getAssets().open(P_CONFIG);
			byte[] buffer = new byte[input.available()];
			input.read(buffer);
			// 转化格式
			String info = new String(buffer, "utf-8");
			// 解密
			String json = ReadJsonUtil.decoderByDES(context, info,
					ReadJsonUtil.KEY);
			JSONObject jobject;
			try {
				jobject = new JSONObject(json);
				JSONArray arrary = jobject.getJSONArray("pconfig");
				JSONObject object = arrary.getJSONObject(0);
				if (object.has("DEFAULT_P_LISTS")) {
					supportPlagins = object.getString("DEFAULT_P_LISTS");
				} else {
					Debug.e("NativePluginUtil->init, DEFAULT_P_LISTS can not find... ");
					System.exit(0);
				}

				if (object.has("P_SEQ_CM")) {
					defaultCMPayPlgin = object.getString("P_SEQ_CM");
				} else {
					Debug.e("NativePluginUtil->init, P_SEQ_CM can not find... ");
					System.exit(0);
				}
				if (object.has("P_SEQ_CU")) {
					defaultCUPayPlgin = object.getString("P_SEQ_CU");
				} else {
					Debug.e("NativePluginUtil->init, P_SEQ_CU can not load... ");
					System.exit(0);
				}
				if (object.has("P_SEQ_CT")) {
					defaultCNPayPlgin = object.getString("P_SEQ_CT");
				} else {
					Debug.e("NativePluginUtil->init, P_SEQ_CT can not load... ");
					System.exit(0);
				}
				if (object.has("P_SEQ_DEFAULT")) {
					defaultNAPayPlgin = object.getString("P_SEQ_DEFAULT");
				} else {
					Debug.e("NativePluginUtil->init, P_SEQ_DEFAULT can not load... ");
					System.exit(0);
				}

				if (object.has("GAMEID")) {
					gameId = object.getString("GAMEID");
				} else {
					Debug.e("NativePluginUtil->init, GAMEID can not load... ");
				}

				if (object.has("APPID")) {
					appId = object.getString("APPID");
				} else {
					Debug.e("NativePluginUtil->init, APPID can not load... ");
				}
			} catch (JSONException e) {
				Debug.e("NativePluginUtil--> initPayConfigInfo,JSONException:"
						+ e.toString());
				System.exit(0);
			}
		} catch (Exception e) {
			Debug.e("NativePluginUtil-->initPayConfigInfo,can not load json from asset :"
					+ e.toString());
			System.exit(0);
		} finally {
			if (input != null) {
				try {
					input.close();
				} catch (IOException e) {
					Debug.e("NativePluginUtil-->initPayConfigInfo, IOException :"
							+ e.toString());
					System.exit(0);
				}
			}

		}
	}

	/**
	 * 统一客户端个服务端的插件协议，方便切换插件的时候进行识别 切换插件的时候是一服务端的协议进行操作的，只能转化客户端的协议
	 * 但是服务端的协议里包含了2次的信息，混乱且不连续
	 * 
	 * @return
	 */
	private static String changeDeal(String plugins) {
		String[] seq = plugins.split(",");
		for (int i = 0; i < seq.length; i++) {
			switch (Integer.valueOf(seq[i])) {
			case 1:
				seq[i] = "0";
				break;
			case 2:
				seq[i] = "2";
				break;
			case 3:
				seq[i] = "3";
				break;
			case 4:
				seq[i] = "7";
				break;
			case 5:
				seq[i] = "9";
				break;
			case 6:
				seq[i] = "10";
				break;
			case 7:
				seq[i] = "11";
				break;
			case 8:
				seq[i] = "12";
				break;
			default:
				seq[i] = "0";
				break;
			}
		}
		String buf = new String();
		for (int j = 0; j < seq.length; j++) {
			if (j == 0) {
				buf += seq[j];
			} else {
				buf += "," + seq[j];
			}
		}
		Debug.i("NativePluginUtil->changeDeal():Plugin seq = " + buf);
		return buf;
	}

}
