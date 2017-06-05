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
public class PInfoConfigS {

	private static final String S_P_INFO = "json/plugin/pinfos.json";
	private static boolean exsit = false;// 是否存在特殊配置
	private static List<PInfoS> pInfos;

	public static void init(Context context) {
		if (null==pInfos) {
			readZPInfo(context);
		}
	}

	public static boolean isExsit() {
		return exsit;
	}

	public static PInfoS getPInfos(int pId) {
		for (int i = 0; i < pInfos.size(); i++) {
			if (pId == pInfos.get(i).getPId()) {
				return pInfos.get(i);
			}else {
				System.out.println("pId=="+pId+";pInfos.get(i).getPId()=="+pInfos.get(i).getPId());
			}
		}
		Debug.e("PInfoConfigS -> 在pinfos.json表中未找到paid = " + pId);
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
			input = context.getAssets().open(S_P_INFO);
			byte[] buffer = new byte[input.available()];
			input.read(buffer);
			// 转化格式
			String info = new String(buffer, "utf-8");
			// 解密
			String json = ReadJsonUtil.decoderByDES(info, "p_k");
			JSONObject jobject;
			try {
				jobject = new JSONObject(json);
				if (jobject.has("pinfos")) {
					JSONArray jarray = jobject.getJSONArray("pinfos");
					pInfos = new ArrayList<PInfoS>();
					for (int i = 0; i < jarray.length(); i++) {
						PInfoS inf = new PInfoS();
						JSONObject obj = jarray.getJSONObject(i);
						if (obj.has("pid") && obj.has("pri")
								&& obj.has("sid")) {
							System.out.println("obj.getInt(pid)"+obj.getInt("pid"));
							inf.setPId(obj.getInt("pid"));
							inf.setPri(obj.getInt("pri"));
							inf.setSId(obj.getInt("sid"));
						}
						pInfos.add(inf);
					}
				}
				exsit = true;
			} catch (JSONException e) {
				exsit = false;
				Debug.e("PInfoConfigS--> readZnPInfo,JSONException:"
						+ e.toString());
			}
		} catch (Exception e) {
			exsit = false;
			Debug.e("PInfoConfigS-->readZPInfo,can not load json from asset :"
					+ e.toString());
		} finally {
			if (input != null) {
				try {
					input.close();
				} catch (IOException e) {
					Debug.e("PInfoConfigS-->readZPInfo, IOException :"
							+ e.toString());
				}
			}
		}
	}

}
