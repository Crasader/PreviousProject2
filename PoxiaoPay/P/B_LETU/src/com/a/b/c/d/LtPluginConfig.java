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

public class LtPluginConfig {

	private static LtPInfo ltPInfo = null;
	private static final String L_P_INFO = "json/plugin/ltpinfo.json";// 定义lt的json文件的目录及名称

	public static void init(Context context) {
		if (ltPInfo == null) {
			ltPInfo = new LtPInfo();

			readLtPInfoFromJson(context);

			readLtPInfoFromXml(context);
		}
	}

	private static final String APPID = "lltt_mappid";
	private static final String MERCHANTID = "lltt_merchantid";

	private static void readLtPInfoFromXml(Context context) {
		ApplicationInfo appInfo = null;
		try {
			appInfo = context.getPackageManager().getApplicationInfo(
					context.getPackageName(), PackageManager.GET_META_DATA);

		} catch (Exception e) {
			e.printStackTrace();
		}
		ltPInfo.setAppId(String.valueOf(appInfo.metaData.getInt(APPID)));
		ltPInfo.setMerchantId(appInfo.metaData.getString(MERCHANTID));
	}

	/**
	 * 获取斯凯支付配置信息
	 * 
	 * @param pointId
	 * @return
	 */
	private static void readLtPInfoFromJson(Context context) {
		InputStream input = null;
		try {
			// 获取文件内容
			input = context.getAssets().open(L_P_INFO);
			byte[] buffer = new byte[input.available()];
			input.read(buffer);
			// 转化格式
			String info = new String(buffer, "utf-8");
			// 解密
			String json = ReadJsonUtil.decoderByDES(info, "p_k");
			JSONObject jobject;
			try {
				jobject = new JSONObject(json);

				if (jobject.has("merchantKey")) {
					ltPInfo
							.setMerchantKey(jobject.getString("merchantKey"));
				} else {
					Debug.e("LtPluginConfig--> getltpInfo: can not find property merchantKey");
					System.exit(0);
				}
				if (jobject.has("showuikey")) {
					ltPInfo.setShowUiKey(jobject.getString("showuikey"));
				} else {
					Debug.e("LtPluginConfig--> getltpInfo: can not find property showuikey");
					System.exit(0);
				}
			} catch (JSONException e) {
				Debug.e("LtPluginConfig--> getltpInfo,JSONException:"
						+ e.toString());
				System.exit(0);
			}
		} catch (Exception e) {
			Debug.e("LtPluginConfig-->getltpInfo,can not load json from asset :"
					+ e.toString());
			System.exit(0);
		} finally {
			if (input != null) {
				try {
					input.close();
				} catch (IOException e) {
					Debug.e("LtPluginConfig-->getltpInfo, IOException :"
							+ e.toString());
					System.exit(0);
				}
			}
		}
	}

	public static LtPInfo getLtPInfo() {
		return ltPInfo;
	}

}
