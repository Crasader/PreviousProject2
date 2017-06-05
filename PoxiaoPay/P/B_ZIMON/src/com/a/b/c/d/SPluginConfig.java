package com.a.b.c.d;

import java.io.IOException;
import java.io.InputStream;

import org.json.JSONException;
import org.json.JSONObject;

import android.content.Context;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;

import com.tbu.androidtools.Debug;
import com.tbu.androidtools.util.ReadJsonUtil;

public class SPluginConfig {

	private static SPInfo sPInfo = null;
	private static final String SKY_P_INFO = "json/plugin/spinfo.json";// 定义sky的json文件的目录及名称

	public static void init(Context context) {
		if (null == sPInfo) {
			sPInfo = new SPInfo();

			readSPInfo(context);

			readSpInfoFromXml(context);
		}
	}

	public static SPInfo getSPInfo() {
		return sPInfo;
	}

	private static final String APPID = "ZMAppId";
	private static final String MERCHANTID = "ZMMerchantId";

	private static void readSpInfoFromXml(Context context) {
		ApplicationInfo appInfo = null;
		try {
			appInfo = context.getPackageManager().getApplicationInfo(
					context.getPackageName(), PackageManager.GET_META_DATA);

		} catch (Exception e) {
			e.printStackTrace();
		}
		sPInfo.setAppId(String.valueOf(appInfo.metaData.getInt(APPID)));
		sPInfo.setMerchantId(String.valueOf(appInfo.metaData
				.getInt(MERCHANTID)));
	}

	/**
	 * 获取斯凯支付配置信息
	 * 
	 * @param pointId
	 * @return
	 */
	private static void readSPInfo(Context context) {

		InputStream input = null;
		try {
			// 获取文件内容
			input = context.getAssets().open(SKY_P_INFO);
			byte[] buffer = new byte[input.available()];
			input.read(buffer);
			// 转化格式
			String info = new String(buffer, "utf-8");
			// 解密
			String json = ReadJsonUtil.decoderByDES(info, "p_k");
			JSONObject jobject;
			try {
				jobject = new JSONObject(json);
				if (jobject.has("merchantpasswd")) {
					sPInfo.setMerchantPasswd(jobject
							.getString("merchantpasswd"));
				} else {
					Debug.e("SPluginConfig--> getSPInfo: can not find property merchantpasswd");
					System.exit(0);
				}
			} catch (JSONException e) {
				Debug.e("SPluginConfig--> getSPInfo:,JSONException:"
						+ e.toString());
				System.exit(0);
			}
		} catch (Exception e) {
			Debug.e("SPluginConfig--> getSPInfo:,can not load json from asset :"
					+ e.toString());
			System.exit(0);
		} finally {
			if (input != null) {
				try {
					input.close();
				} catch (IOException e) {
					Debug.e("SPluginConfig--> getSPInfo:, IOException :"
							+ e.toString());
					System.exit(0);
				}
			}
		}
	}

}
