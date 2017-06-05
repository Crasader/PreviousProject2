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

	private static final String CONFIG_PATH = "json/uuconfig.json";
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
			String info = new String(buffer, "utf-8");
			// 解密
			String json = ReadJsonUtil.decoderByDES(context, info,
					ReadJsonUtil.KEY);
			JSONObject jobject;
			try {
				// 解析JSON数据
				jobject = new JSONObject(json);
				// 第一段
				if (jobject.has("fuction")) {
					uuFuction = jobject.getString("fuction");
				} else {
					Debug.e("UuAdvConfig--> readConfig,fuction can not find");
				}

			} catch (JSONException e) {
				Debug.e("UuAdvConfig--> readConfig,JSONException:"
						+ e.toString());
			}
		} catch (Exception e) {
			Debug.e("UuAdvConfig-->readConfig,can not load json from asset :"
					+ e.toString());
		} finally {
			if (input != null) {
				try {
					input.close();
				} catch (IOException e) {
					Debug.e("UuAdvConfig-->readConfig, IOException :"
							+ e.toString());
				}
			}

		}
	}

}
