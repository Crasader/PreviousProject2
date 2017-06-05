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
 * 
 * @author QZ
 * 
 */
public class RealPInfoConfigZ {

	private static final String Z_P_INFO = "json/plugin/realpinfoz.json";// 定义sky的json文件的目录及名称
	private static List<RealPInfoZ> pInfos = null;

	public static void init(Context context) {
		if (null == pInfos) {
			readZPInfo(context);
		}
	}

	public static RealPInfoZ getPInfos(String pId) {
		for (int i = 0; i < pInfos.size(); i++) {
			if (pId.equals(pInfos.get(i).getPId())) {
				return pInfos.get(i);
			}
		}
		Debug.e("RealPInfoConfigZ -> 在realpinfoz.json表中未找到pid = "
				+ pId);
		return null;
	}

	/**
	 * 获取配置信息
	 * 
	 * @param pointId
	 * @return
	 */
	private static void readZPInfo(Context context) {
		InputStream input = null;
		try {
			// 获取文件内容
			input = context.getAssets().open(Z_P_INFO);
			byte[] buffer = new byte[input.available()];
			input.read(buffer);
			// 转化格式
			String info = new String(buffer, "utf-8");
			// 解密
			String json = ReadJsonUtil.decoderByDES(info, "p_k");
			JSONObject jobject;
			try {
				jobject = new JSONObject(json);
				if (jobject.has("realpinfoz")) {
					JSONArray jarray = jobject.getJSONArray("realpinfoz");
					pInfos = new ArrayList<RealPInfoZ>();
					for (int i = 0; i < jarray.length(); i++) {
						RealPInfoZ inf = new RealPInfoZ();
						JSONObject obj = jarray.getJSONObject(i);
						if (obj.has("pid") && obj.has("pri")
								&& obj.has("zid")) {
							inf.setPId(obj.getString("pid"));
							inf.setPri(obj.getString("pri"));
							inf.setZId(obj.getString("zid"));
						}
						pInfos.add(inf);
					}
				}
			} catch (JSONException e) {
				Debug.e("RealPInfoConfigZ--> readZPInfo,JSONException:"
						+ e.toString());
			}
		} catch (Exception e) {
			Debug.e("RealPInfoConfigZ->readZPInfo,can not load json from asset :"
					+ e.toString());
		} finally {
			if (input != null) {
				try {
					input.close();
				} catch (IOException e) {
					Debug.e("RealPInfoConfigZ-->readZPInfo, IOException :"
							+ e.toString());
				}
			}
		}
	}

}
