package com.tbu.wx.util;

import java.io.IOException;
import java.io.InputStream;

import org.json.JSONObject;

import android.content.Context;

import com.tbu.androidtools.Debug;
import com.tbu.androidtools.util.ReadJsonUtil;

public class WxAppInfo {

	private static WxInfo wxInfo = null;
	private static final String WX_INFO = "json/wx/wexininfo.json";

	public static void init(Context context) {
		if (wxInfo == null) {
			wxInfo = getWxInfoFromJson(context);
		}
	}

	public static WxInfo  getWxInfo() {
		return wxInfo;
	}

	/**
	 * 获取微信支付的商户号和APPID
	 * 
	 * @param context
	 */
	private static WxInfo getWxInfoFromJson(Context context) {
		InputStream input = null;
		WxInfo wxData = new WxInfo();
		try {
			// 获取文件内容
			input = context.getAssets().open(WX_INFO);
			byte[] buffer = new byte[input.available()];
			input.read(buffer);
			// 转化格式
			String info = new String(buffer, "utf-8");
			// 解密
			String json = ReadJsonUtil.decoderByDES(info, ReadJsonUtil.KEY);
			JSONObject jobject;
			jobject = new JSONObject(json);

			if (jobject.has("appId")) {
				wxData.setAppId(jobject.getString("appId"));
			} else {
				Debug.e("WxAppInfo--> getWxInfoFromJson: can not find property appId");
			}
			if (jobject.has("partnerId")) {
				wxData.setPartnerId(jobject.getString("partnerId"));
			} else {
				Debug.e("WxAppInfo--> getWxInfoFromJson: can not find property partnerId");
			}
		} catch (Exception e) {
			Debug.e("WxAppInfo-->getWxInfoFromJson,can not load json from asset :"
					+ e.toString());
		} finally {
			if (input != null) {
				try {
					input.close();
				} catch (IOException e) {
					Debug.e("WxAppInfo-->getWxInfoFromJson, IOException :"
							+ e.toString());
				}
			}
		}
		return wxData;
	}

}
