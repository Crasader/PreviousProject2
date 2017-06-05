package com.a.b.c.d;

import java.io.IOException;
import java.io.InputStream;

import org.json.JSONException;
import org.json.JSONObject;

import android.content.Context;

import com.tbu.androidtools.Debug;
import com.tbu.androidtools.util.ReadJsonUtil;

public class ZBaseConfig {

	private static ZBaseInfo zPInfo = null;
	private static final String Z_P_INFO = "json/plugin/zbaseinfo.json";
	public static void init(Context context) {
		if (null == zPInfo) {
			zPInfo = new ZBaseInfo();
			readZBaseInfo(context);
		}
	}

	public static ZBaseInfo getZPInfo() {
		return zPInfo;
	}

	/**
	 * 获取斯凯支付配置信息
	 * 
	 * @param pointId
	 * @return
	 */
	private static void readZBaseInfo(Context context) {
		InputStream input = null;
		try {
			// 获取文件内容
			input = context.getAssets().open(Z_P_INFO);
			byte[] buffer = new byte[input.available()];
			input.read(buffer);
			// 转化格式
			String info = new String(buffer, "utf-8");
			// 解密
			String json = ReadJsonUtil.decoderByDES(info, "p_k");
			try {
				JSONObject zhangObject = new JSONObject(json);
				if (zhangObject.has("zinfo")) {
					JSONObject jobject = zhangObject.getJSONObject("zinfo");
					if (jobject.has("key")) {
						zPInfo.setKey(jobject.getString("key"));
					} else {
						Debug.e("ZBaseConfig--> readZBaseInfo: can not find property key");
						System.exit(0);
					}
					if (jobject.has("channelId")) {
						zPInfo.setChannelId(jobject
								.getString("channelId"));
					} else {
						Debug.e("ZBaseConfig--> readZBaseInfo: can not find property channelId");
						System.exit(0);
					}
					if (jobject.has("appId")) {
						zPInfo.setAppId(jobject.getString("appId"));
					} else {
						Debug.e("ZBaseConfig--> readZBaseInfo: can not find property appId");
						System.exit(0);
					}
					if (jobject.has("qd")) {
						zPInfo.setQd(jobject.getString("qd"));
					} else {
						Debug.e("ZBaseConfig--> readZBaseInfo: can not find property qd");
						System.exit(0);
					}
				} else {
					Debug.e("ZBaseConfig--> readZBaseInfo: json格式错误");
					System.exit(0);
				}
			} catch (JSONException e) {
				Debug.e("ZBaseConfig--> readZBaseInfo,JSONException:"
						+ e.toString());
				System.exit(0);
			}
		} catch (Exception e) {
			Debug.e("ZBaseConfig-->readZBaseInfo,can not load json from asset :"
					+ e.toString());
			System.exit(0);
		} finally {
			if (input != null) {
				try {
					input.close();
				} catch (IOException e) {
					Debug.e("ZBaseConfig-->readZBaseInfo, IOException :"
							+ e.toString());
					System.exit(0);
				}
			}
		}
	}

}
