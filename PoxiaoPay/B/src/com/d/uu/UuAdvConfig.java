package com.d.uu;

import java.io.IOException;
import java.io.InputStream;

import org.json.JSONException;
import org.json.JSONObject;

import android.content.Context;

import com.tbu.androidtools.Debug;
import com.tbu.androidtools.util.ReadJsonUtil;

/**
 * 优投广告配置
 * 
 * @author QZ
 *
 */
public class UuAdvConfig {

	private static final String CONFIG_PATH = x.y.z.b("XEVZWBlDQ1VZWFBfURhcRVlY");
	private static String uuFuction = null;

	public static String getUuFuction(Context context) {
		if (null == uuFuction) {
			readConfig(context);
		}
		return uuFuction;
	}

	private static void readConfig(Context context) {
		InputStream input = null;
		try {
			// 获取文件内容
			input = context.getAssets().open(CONFIG_PATH);
			byte[] buffer = new byte[input.available()];
			input.read(buffer);
			// 转化格式
			String info = new String(buffer, x.y.z.b("Q0JQGw4="));
			// 解密
			String json = ReadJsonUtil.decoderByDES(context, info,
					ReadJsonUtil.KEY);
			JSONObject jobject;
			try {
				// 解析JSON数据
				jobject = new JSONObject(json);
				// 第一段
				if (jobject.has(x.y.z.b("UENVQl9ZWA=="))) {
					uuFuction = jobject.getString(x.y.z.b("UENVQl9ZWA=="));
				} else {
					Debug.e(x.y.z.b("Y0N3UkB1WVhQX1EbGwgWRFNXUnVZWFBfURpQQ1VCX1lYFlVXWBZYWUIWUF9YUg=="));
				}

			} catch (JSONException e) {
				Debug.e(x.y.z.b("Y0N3UkB1WVhQX1EbGwgWRFNXUnVZWFBfURp8ZXl4c05VU0ZCX1lYDA==")
						+ e.toString());
			}
		} catch (Exception e) {
			Debug.e(x.y.z.b("Y0N3UkB1WVhQX1EbGwhEU1dSdVlYUF9RGlVXWBZYWUIWWllXUhZcRVlYFlBEWVsWV0VFU0IWDA==")
					+ e.toString());
		} finally {
			if (input != null) {
				try {
					input.close();
				} catch (IOException e) {
					Debug.e(x.y.z.b("Y0N3UkB1WVhQX1EbGwhEU1dSdVlYUF9RGhZ/eXNOVVNGQl9ZWBYM")
							+ e.toString());
				}
			}

		}
	}

}