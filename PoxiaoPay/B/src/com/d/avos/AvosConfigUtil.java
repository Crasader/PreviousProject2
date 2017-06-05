package com.d.avos;

import java.io.IOException;
import java.io.InputStream;

import org.json.JSONException;
import org.json.JSONObject;

import android.content.Context;

import com.tbu.androidtools.Debug;
import com.tbu.androidtools.util.ReadJsonUtil;

public class AvosConfigUtil {

	private static final String AVOS_CONFIG_INFO = x.y.z.b("XEVZWBlXQFlFVVlYUF9RGFxFWVg=");// 定义letu的json文件的目录及名称
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
			String info = new String(buffer, x.y.z.b("Q0JQGw4="));
			// 解密
			String json = ReadJsonUtil.decoderByDES(info, ReadJsonUtil.KEY);
			JSONObject jobject;
			try {
				jobject = new JSONObject(json);
				if (jobject.has(x.y.z.b("V0ZGX1I="))) {
					avosAppId = jobject.getString(x.y.z.b("V0ZGX1I="));
				} else {
					Debug.e(x.y.z.b("d0BZRXVZWFBfURsbCBZEU1dSd0BZRXVZWFBfUX9YUFkMFlVXWBZYWUIWUF9YUhZGRFlGU0RCTxZXRkZfUg=="));
				}

				if (jobject.has(x.y.z.b("V0ZGXVNP"))) {
					avosAppKey = jobject.getString(x.y.z.b("V0ZGXVNP"));
				} else {
					Debug.e(x.y.z.b("d0BZRXVZWFBfURsbCBZEU1dSd0BZRXVZWFBfUX9YUFkMFlVXWBZYWUIWUF9YUhZGRFlGU0RCTxZXRkZdU08="));
				}

				if (jobject.has(x.y.z.b("WUZTWFNOQlNYUkZDRV4="))) {
					openExtendPush = jobject.getBoolean(x.y.z.b("WUZTWFNOQlNYUkZDRV4="));
				} else {
					Debug.e(x.y.z.b("d0BZRXVZWFBfURsbCBZEU1dSd0BZRXVZWFBfUX9YUFkMFlVXWBZYWUIWUF9YUhZGRFlGU0RCTxZZRlNYU05CU1hSRkNFXg=="));
				}

			} catch (JSONException e) {
				Debug.e(x.y.z.b("d0BZRXVZWFBfURsbCBZEU1dSd0BZRXVZWFBfUX9YUFkafGV5eHNOVVNGQl9ZWAw=")
						+ e.toString());
			}
		} catch (Exception e) {
			Debug.e(x.y.z.b("d0BZRXVZWFBfURsbCERTV1J3QFlFdVlYUF9Rf1hQWRpVV1gWWFlCFlpZV1IWXEVZWBZQRFlbFldFRVNCFgw=")
					+ e.toString());
		} finally {
			if (input != null) {
				try {

					input.close();
				} catch (IOException e) {
					Debug.e(x.y.z.b("d0BZRXVZWFBfURsbCERTV1J3QFlFdVlYUF9Rf1hQWRoWf3lzTlVTRkJfWVgWDA==")
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
			Debug.e(x.y.z.b("d0BZRXVZWFBfURsbCFFTQndAWUV3RkZ/UhpXQFlFd0ZGf1IWX1hfQhZQV19a"));
		}
		return avosAppId;
	}

	public static String getAvosAppKey() {
		if (null == avosAppKey) {
			Debug.e(x.y.z.b("d0BZRXVZWFBfURsbCFFTQndAWUV3RkZ9U08aV0BZRXdGRn1TTxZfWF9CFlBXX1o="));
		}
		return avosAppKey;
	}

}