package com.d.avos;

import java.io.IOException;
import java.io.InputStream;

import org.json.JSONException;
import org.json.JSONObject;

import android.content.Context;

import com.tbu.androidtools.Debug;
import com.tbu.androidtools.util.ReadJsonUtil;

public class AvosConfigUtil {

	private static final String AVOS_CONFIG_INFO = "json/avosconfig.json";// 定义letu的json文件的目录及名称
	private static boolean recordGameDetail = false;
	private static boolean openExtendPush = false;
	private static String avosAppId = null;
	private static String avosAppKey = null;

	public static void init(Context context) {
		readAvosConfigInfo(context);
	}

	private static void readAvosConfigInfo(Context context) {

		InputStream input = null;
		try {
			// 获取文件内容
			input = context.getAssets().open(AVOS_CONFIG_INFO);
			byte[] buffer = new byte[input.available()];
			input.read(buffer);
			// 转化格式
			String info = new String(buffer, "utf-8");
			// 解密
			String json = ReadJsonUtil.decoderByDES(info, ReadJsonUtil.KEY);
			JSONObject jobject;
			try {
				jobject = new JSONObject(json);
				if (jobject.has("appid")) {
					avosAppId = jobject.getString("appid");
				} else {
					Debug.e("AvosConfig--> readAvosConfigInfo: can not find property appid");
				}

				if (jobject.has("appkey")) {
					avosAppKey = jobject.getString("appkey");
				} else {
					Debug.e("AvosConfig--> readAvosConfigInfo: can not find property appkey");
				}

				if (jobject.has("openextendpush")) {
					openExtendPush = jobject.getBoolean("openextendpush");
				} else {
					Debug.e("AvosConfig--> readAvosConfigInfo: can not find property openextendpush");
				}

			} catch (JSONException e) {
				Debug.e("AvosConfig--> readAvosConfigInfo,JSONException:"
						+ e.toString());
			}
		} catch (Exception e) {
			Debug.e("AvosConfig-->readAvosConfigInfo,can not load json from asset :"
					+ e.toString());
		} finally {
			if (input != null) {
				try {

					input.close();
				} catch (IOException e) {
					Debug.e("AvosConfig-->readAvosConfigInfo, IOException :"
							+ e.toString());
				}
			}

		}

	}

	public static boolean isRecordGameDetail() {
		return recordGameDetail;
	}

	public static boolean isOpenExtendPush() {
		return openExtendPush;
	}

	public static String getAvosAppId() {
		if (null == avosAppId) {
			Debug.e("AvosConfig-->getAvosAppId,avosAppId init fail");
		}
		return avosAppId;
	}

	public static String getAvosAppKey() {
		if (null == avosAppKey) {
			Debug.e("AvosConfig-->getAvosAppKey,avosAppKey init fail");
		}
		return avosAppKey;
	}

}
