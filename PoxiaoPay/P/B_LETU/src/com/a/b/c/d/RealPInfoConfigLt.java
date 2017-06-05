package com.a.b.c.d;

import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import android.content.Context;

import com.tbu.androidtools.Debug;
import com.tbu.androidtools.util.ReadJsonUtil;

/**
 * 指盟插件的支付信息,特殊化的部分 例如:主线的价格的10元,可以特俗配置为6元 其他插件走10元的计费,斯凯走6元的计费
 * 
 * @author QZ
 * 
 */
public class RealPInfoConfigLt {

	private static final String LT_P_INFO = "json/plugin/realpinfolt.json";
	private static boolean exsit = false;// 是否存在特殊配置
	private static List<RealPInfoLt> pInfos;

	public static void init(Context context) {
		readLtPInfo(context);
	}

	public static boolean isExsit() {
		return exsit;
	}

	public static RealPInfoLt getPInfos(int pId) {
		for (int i = 0; i < pInfos.size(); i++) {
			if (pId == pInfos.get(i).getPId()) {
				return pInfos.get(i);
			}
		}
		Debug.e("RealPInfoConfigLt -> 在pinfolt.json表中未找到pId = " + pId);
		return null;
	}

	/**
	 * 获取斯凯支付配置信息
	 * 
	 * @param pointId
	 * @return
	 */
	private static void readLtPInfo(Context context) {
		InputStream input = null;
		try {
			// 获取文件内容
			input = context.getAssets().open(LT_P_INFO);
			byte[] buffer = new byte[input.available()];
			input.read(buffer);
			// 转化格式
			String info = new String(buffer, "utf-8");
			// 解密
			String json = ReadJsonUtil.decoderByDES(info, "p_k");
			JSONObject jobject;
			try {
				jobject = new JSONObject(json);
				if (jobject.has("pinfolt")) {
					JSONArray jarray = jobject.getJSONArray("pinfolt");
					pInfos = new ArrayList<RealPInfoLt>();
					for (int i = 0; i < jarray.length(); i++) {
						RealPInfoLt inf = new RealPInfoLt();
						JSONObject obj = jarray.getJSONObject(i);
						if (obj.has("pid") && obj.has("pri")
								&& obj.has("ltid")) {
							if (obj.has("ltpid")) {
								inf.setLtPId(obj.getInt("ltpid"));
							}
							inf.setPId(obj.getInt("pid"));
							inf.setP(obj.getInt("pri"));
							inf.setLtId(obj.getInt("ltid"));
						}
						pInfos.add(inf);
					}
				}
				exsit = true;
			} catch (JSONException e) {
				exsit = false;
				Debug.e("RealPInfoConfigLt--> readLtPInfo,JSONException:"
						+ e.toString());
			}
		} catch (Exception e) {
			exsit = false;
			Debug.e("RealPInfoConfigLt-->readLtPInfo,can not load json from asset :"
					+ e.toString());
		} finally {
			if (input != null) {
				try {
					input.close();
				} catch (IOException e) {
					Debug.e("RealPInfoConfigLt-->readLtPInfo, IOException :"
							+ e.toString());
				}
			}
		}
	}

}
