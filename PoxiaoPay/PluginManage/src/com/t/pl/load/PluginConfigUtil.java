package com.t.pl.load;

import java.io.IOException;
import java.io.InputStream;
import java.util.HashMap;
import java.util.Map;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import android.content.Context;

import com.tbu.androidtools.Debug;
import com.tbu.androidtools.util.ReadJsonUtil;

public class PluginConfigUtil {
	private static boolean successInit = false;

	// 从本地的JSON读取需要通过反射加载的插件列表
	public static void init(Context context) {
		if (!successInit) {
			readConfig(context);
		}
	}

	private static final String CONFIG_PATH = "json/pluginconfig.json";

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
			String json = ReadJsonUtil.decoderByDES(context,info, "p_k");
			JSONObject jobject;
			try {
				// 解析JSON数据
				jobject = new JSONObject(json);
				// 第1段属于setPPlginByTypeName
				if (jobject.has("setPPlginByTypeName")) {
					JSONArray pluginList = jobject
							.getJSONArray("setPPlginByTypeName");
					// 解析setPPlginByTypeName方法会调用的pluginList的列表
					Map<String, String> plugins = new HashMap<String, String>();
					for (int i = 0; i < pluginList.length(); i++) {
						JSONObject obj = pluginList.getJSONObject(i);
						if (obj.has("pluginName") && obj.has("className")) {
							plugins.put(obj.getString("pluginName"),
									obj.getString("className"));
						} else {
							Debug.e("PluginConfig--> readConfig,json is not Compliance with Requirements");
							System.exit(0);
						}
					}
					PluginInfos.setPlugins(plugins);
				}
				// 第2段，属于defaultPluginName
				if (jobject.has("defaultPluginName")) {
					PluginInfos.setDefaultPlufinName(jobject
							.getString("defaultPluginName"));
				} else {
					Debug.e("PluginConfig--> readConfig,defaultPluginName can not find");
					System.exit(0);
				}
				// 第3段，属于initPPlginIfNeedOnApplication
				if (jobject.has("initPPlginIfNeedOnApplication")) {
					JSONArray funcList = jobject
							.getJSONArray("initPPlginIfNeedOnApplication");
					// 解析setPPlginByTypeName方法会调用的pluginList的列表
					Map<String, String> functions = new HashMap<String, String>();
					for (int i = 0; i < funcList.length(); i++) {
						JSONObject ob = funcList.getJSONObject(i);
						if (ob.has("className") && ob.has("function")) {
							functions.put(ob.getString("className"),
									ob.getString("function"));
						} else {
							Debug.e("PluginConfig--> readConfig,json is not Compliance with Requirements");
							System.exit(0);
						}
					}
					PluginInfos.setFunctions1(functions);
				}
				// 第4段，属于initPPlginIfNeedOnActivity
				if (jobject.has("initPPlginIfNeedOnActivity")) {
					JSONArray funcList2 = jobject
							.getJSONArray("initPPlginIfNeedOnActivity");
					// 解析setPPlginByTypeName方法会调用的pluginList的列表
					Map<String, String> functions2 = new HashMap<String, String>();
					for (int i = 0; i < funcList2.length(); i++) {
						JSONObject ob = funcList2.getJSONObject(i);
						if (ob.has("className") && ob.has("function")) {
							functions2.put(ob.getString("className"),
									ob.getString("function"));
						} else {
							Debug.e("PluginConfig--> readConfig,json is not Compliance with Requirements");
							System.exit(0);
						}
					}
					PluginInfos.setFunctions2(functions2);
				}
				// 第5段，属于quitPluginIfNeedOnApplicaton
				if (jobject.has("quitPluginIfNeedOnApplicaton")) {
					JSONArray funcList3 = jobject
							.getJSONArray("quitPluginIfNeedOnApplicaton");
					// 解析setPPlginByTypeName方法会调用的pluginList的列表
					Map<String, String> functions3 = new HashMap<String, String>();
					for (int i = 0; i < funcList3.length(); i++) {
						JSONObject ob = funcList3.getJSONObject(i);
						if (ob.has("className") && ob.has("function")) {
							functions3.put(ob.getString("className"),
									ob.getString("function"));
						} else {
							Debug.e("PluginConfig--> readConfig,json is not Compliance with Requirements");
							System.exit(0);
						}
					}
					PluginInfos.setFunctions3(functions3);
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