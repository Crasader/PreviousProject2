package com.tbu.hd.manage;

import java.io.IOException;
import java.io.InputStream;

import org.json.JSONException;
import org.json.JSONObject;

import com.tbu.androidtools.Debug;

import android.content.Context;

public class HdConfig {
	private static final String JSON_PATH = "hdconfig.json";
	private static String hdContent = "";
	private static boolean isHdOpen = false;

	public static String getHdContent() {
		return hdContent;
	}

	public static boolean isHdOpen() {
		return isHdOpen;
	}

	public static void init(Context context) {

		InputStream input = null;
		try {
			// 获取文件内容
			input = context.getAssets().open(JSON_PATH);
			byte[] buffer = new byte[input.available()];
			input.read(buffer);
			// 转化格式
			String json = new String(buffer, "utf-8");
			JSONObject jobject;
			try {
				jobject = new JSONObject(json);
				if (jobject.has("hdstate")) {
					isHdOpen = jobject.getBoolean("hdstate");
					if (jobject.has("desc")) {
						hdContent = jobject.getString("desc");
					}
				}
			} catch (JSONException e) {
				Debug.e("HdConfig--> init,JSONException:" + e.toString());
			}
		} catch (Exception e) {
			Debug.e("HdConfig-->init,can not load json from asset :"
					+ e.toString());
		} finally {
			if (input != null) {
				try {

					input.close();
				} catch (IOException e) {
					Debug.e("HdConfig-->init, IOException :" + e.toString());
				}
			}

		}
	}
}
