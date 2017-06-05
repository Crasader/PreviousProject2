package com.t.pl.config;

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

	private static String defaultCMPPlgin; // 默认移动
	private static String defaultCUPPlgin; // 默认联通
	private static String defaultCNPPlgin; // 默认电信
	private static String defaultNAPPlgin; // 默认电信
	private static String supportPlagins;
	private static String gameId;
	private static String appId;

	public static String getDefaultPPlugins() {
		if (DeviceInfo.getCarrier() == 1 || DeviceInfo.getCarrier() == 4) {
			// 移动或者铁通都是移动
			return defaultCMPPlgin;
		} else if (DeviceInfo.getCarrier() == 2) { // 联通
			return defaultCUPPlgin;
		} else if (DeviceInfo.getCarrier() == 3) { // 电信
			return defaultCNPPlgin;
		}
		return defaultNAPPlgin;
	}

	public static String getSupportPlugins() {
		return supportPlagins;
	}

	public static String getGameId() {
		return gameId;
	}

	public static String getAppId() {
		return appId;
	}

	public static void initPConfigInfo(Context context) {

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
					"p_k");
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
					defaultCMPPlgin = object.getString("P_SEQ_CM");
				} else {
					Debug.e("NativePluginUtil->init, P_SEQ_CM can not find... ");
					System.exit(0);
				}
				if (object.has("P_SEQ_CU")) {
					defaultCUPPlgin = object.getString("P_SEQ_CU");
				} else {
					Debug.e("NativePluginUtil->init, P_SEQ_CU can not load... ");
					System.exit(0);
				}
				if (object.has("P_SEQ_CT")) {
					defaultCNPPlgin = object.getString("P_SEQ_CT");
				} else {
					Debug.e("NativePluginUtil->init, P_SEQ_CT can not load... ");
					System.exit(0);
				}
				if (object.has("P_SEQ_DEFAULT")) {
					defaultNAPPlgin = object.getString("P_SEQ_DEFAULT");
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
				Debug.e("NativePluginUtil--> initPConfigInfo,JSONException:"
						+ e.toString());
				System.exit(0);
			}
		} catch (Exception e) {
			Debug.e("NativePluginUtil-->initPConfigInfo,can not load json from asset :"
					+ e.toString());
			System.exit(0);
		} finally {
			if (input != null) {
				try {
					input.close();
				} catch (IOException e) {
					Debug.e("NativePluginUtil-->initPConfigInfo, IOException :"
							+ e.toString());
					System.exit(0);
				}
			}

		}
	}

}
