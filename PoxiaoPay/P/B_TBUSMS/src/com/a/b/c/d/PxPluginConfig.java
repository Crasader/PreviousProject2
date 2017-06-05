package com.a.b.c.d;

import java.io.IOException;
import java.io.InputStream;

import org.json.JSONException;
import org.json.JSONObject;

import android.content.Context;

import com.tbu.androidtools.Debug;
import com.tbu.androidtools.util.ReadJsonUtil;

public class PxPluginConfig {

	private static final String PX_P_INFO = "json/plugin/pxpinfo.json";// 定义破晓的json文件的目录及名称

	private static String appId = null;
	private static String gameId = null;
	private static String merchantId = "86010001";
	

	public static void init(Context context) {
		if (appId == null || gameId == null) {
			readPxPInfo(context);
		}
	}

	public static String getAppId() {
		return appId;
	}

	public static String getGameId() {
		return gameId;
	}

	
	
	public static String getMerchantId() {
		return merchantId;
	}

	/**
	 * 获取配置信息
	 * 
	 * @param pointId
	 * @return
	 */
	private static void readPxPInfo(Context context) {
		InputStream input = null;
		try {
			// 获取文件内容
			input = context.getAssets().open(PX_P_INFO);
			byte[] buffer = new byte[input.available()];
			input.read(buffer);
			// 转化格式
			String info = new String(buffer, "utf-8");
			// 解密
			String json = ReadJsonUtil.decoderByDES(info,"p_k");
			JSONObject jobject;
			try {
				jobject = new JSONObject(json);
				if (jobject.has("appid")) {
					appId = jobject.getString("appid");
				} else {
					Debug.e("PxPluginConfig--> readPxPInfo: can not find property appid");
					System.exit(0);
				}
				if (jobject.has("gameid")) {
					gameId = jobject.getString("gameid");
				} else {
					Debug.e("PxPluginConfig--> readPxPInfo: can not find property gameid");
					System.exit(0);
				}
			} catch (JSONException e) {
				Debug.e("PxPluginConfig--> readPxPInfo,JSONException:"
						+ e.toString());
				System.exit(0);
			}
		} catch (Exception e) {
			Debug.e("PxPluginConfig-->readPxPInfo,can not load json from asset :"
					+ e.toString());
			System.exit(0);
		} finally {
			if (input != null) {
				try {
					input.close();
				} catch (IOException e) {
					Debug.e("PxPluginConfig-->readPxPInfo, IOException :"
							+ e.toString());
					System.exit(0);
				}
			}
		}

	}

}
