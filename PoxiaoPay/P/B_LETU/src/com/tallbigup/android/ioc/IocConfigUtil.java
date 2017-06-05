package com.tallbigup.android.ioc;

import java.io.IOException;
import java.io.InputStream;

import org.json.JSONException;
import org.json.JSONObject;

import android.content.Context;

import com.tbu.androidtools.Debug;
import com.tbu.androidtools.util.ReadJsonUtil;

public class IocConfigUtil {
	private static boolean successInit = false;

	// 从本地的JSON读取需要通过反射加载的插件列表
	public static void init(Context context) {
		if (!successInit) {
			readConfig(context);
		}
	}

	private static final String CONFIG_PATH = "json/iocconfig.json";

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
		    String json = ReadJsonUtil.decoderByDES(context,info, ReadJsonUtil.KEY);
			JSONObject jobject;
			try {
				// 解析JSON数据
				jobject = new JSONObject(json);
				// 第一段
				if (jobject.has("applicationImpl")) {
					IocInfos.setApplicationImpl(jobject
							.getString("applicationImpl"));
				} else {
					Debug.e("PluginConfig--> readConfig,applicationImpl can not find");
					System.exit(0);
				}
				// 第二段
				if (jobject.has("payImpl")) {
					JSONObject obj = jobject.getJSONObject("payImpl");
					if (obj.has("className") && obj.has("function")) {
						IocInfos.setPayImplName(obj.getString("className"));
						IocInfos.setPayImplFunction(obj.getString("function"));
					} else {
						Debug.e("PluginConfig--> readConfig,json is not Compliance with Requirements");
						System.exit(0);
					}
				}
				successInit = true;
			} catch (JSONException e) {
				Debug.e("PluginConfig--> readConfig,JSONException:"
						+ e.toString());
				System.exit(0);
			}
		} catch (Exception e) {
			Debug.e("PluginConfig-->readConfig,can not load json from asset :"
					+ e.toString());
			System.exit(0);
		} finally {
			if (input != null) {
				try {
					input.close();
				} catch (IOException e) {
					Debug.e("PluginConfig-->readConfig, IOException :"
							+ e.toString());
					System.exit(0);
				}
			}

		}
	}
}
