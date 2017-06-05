package com.tbu.androidtools.util.psspoint;

import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import android.content.Context;

import com.tbu.androidtools.Debug;
import com.tbu.androidtools.util.ReadJsonUtil;

public class PPointUtil {
	private static final String P_POINT = "json/ppoint.json";// 定义json文件的目录及名称
	private static List<PPoint> points = new ArrayList<PPoint>();
	private static int pPointVersion = 999;

	/**
	 * 获取计费点信息
	 * 
	 * @param context
	 * @param eventId
	 * @return
	 */
	public static PPoint getPPointById(Context context, int pId) {
		if (points.isEmpty()) {
			getPPointByJson(context);
		}
		PPoint result = null;
		for (PPoint pPoint : points) {
			if (pPoint.getType() == pId) {
				result = pPoint;
				return result;
			}
		}
		if (null == result) {
			Debug.e("PayPointUtil ----> getPayPointById,can not find the payId id = "
					+ pId);
		}
		return result;
	}

	/**
	 * 获取计费点版本号
	 * 
	 * @param context
	 * @return
	 */
	public static int getPPointVersion(Context context) {
		if (null == points||points.isEmpty()) {
			getPPointByJson(context);
		}
		return pPointVersion;
	}

	public static void getPPointByJson(Context context) {
		InputStream input = null;
		try {
			input = context.getAssets().open(P_POINT);
			byte[] buffer = new byte[input.available()];
			input.read(buffer);
			String info = new String(buffer, "utf-8");
			String json = ReadJsonUtil.decoderByDES(context, info,
					"p_k");
			JSONObject jobject;
			try {
				jobject = new JSONObject(json);
				if (jobject.has("p_version")) {
					pPointVersion = jobject.getInt("p_version");
				}

				JSONArray arrary = jobject.getJSONArray("ppoint");
				for (int i = 0; i < arrary.length(); i++) {
					JSONObject object = arrary.getJSONObject(i);
					PPoint payPoint = new PPoint();
					payPoint.setType(object.getInt("id"));
					payPoint.setDesc(object.getString("desc"));
					payPoint.setMoey(object.getInt("pri"));
					payPoint.setName(object.getString("name"));
					if (object.has("describe")) {
						JSONArray darray = object.getJSONArray("describe");
						Map<Integer, Integer> reward = new HashMap<Integer, Integer>();
						for (int j = 0; j < darray.length(); j++) {
							reward.put(
									darray.getJSONObject(j).getInt("propid"),
									darray.getJSONObject(j).getInt("propnum"));
						}
						payPoint.setReward(reward);
					}
					points.add(payPoint);
				}

			} catch (JSONException e) {
				Debug.e("PPointUtil-->getPayPointByJson, JSONException :"
						+ e.toString());
			}

		} catch (Exception e) {
			Debug.e("PPointUtil-->getPayPointByJson, can not load json from asset :"
					+ e.toString());
		} finally {
			if (input != null) {
				try {
					input.close();
				} catch (IOException e) {
					Debug.e("PPointUtil-->getPayPointByJson, IOException :"
							+ e.toString());
				}
			}

		}
	}

}
