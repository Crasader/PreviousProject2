package com.tbu.androidtools.util.spcode;

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
 * 破晓游戏中的ppoint和申请的运营商计费编号之间的对应关系
 * 
 * @author QZ
 * 
 */
public class SpCodeUtil {

	private static final String P_POINT_TO_SP = "json/ptosp.json";// 定义json文件的目录及名称
	private static List<SpCodeMap> spoints = new ArrayList<SpCodeMap>();

	/**
	 * 返回从自由计费点转化到运营商计费点编号
	 * 
	 * @return
	 */
	public static String getSpPointById(Context context, String pluginName,
			int pId) {
		if (spoints.isEmpty()) {
			getSpPointFromJson(context);
		}
		String value = null;
		for (SpCodeMap iterable : spoints) {
			if (null != pluginName && !pluginName.equals("")) {
				if (iterable.getPId() == pId
						&& pluginName.equalsIgnoreCase(iterable.getType())) {
					value = iterable.getSpPoint();
				}
			} else {
				if (iterable.getPId() == pId) {
					value = iterable.getSpPoint();
				}
			}
		}
		if (null == value) {
			Debug.e("pToSpUtil-->getSpPointById,can not find SpPoint by pId = "
					+ pId + " pluginName=" + pluginName);
		}
		return value;
	}

	private static void getSpPointFromJson(Context context) {
		InputStream input = null;

		try {
			input = context.getAssets().open(P_POINT_TO_SP);
			byte[] buffer = new byte[input.available()];
			input.read(buffer);
			String info = new String(buffer, "utf-8");
			String json = ReadJsonUtil.decoderByDES(context, info,
					ReadJsonUtil.KEY);
			JSONObject jobject;
			try {
				jobject = new JSONObject(json);
				JSONArray arrary = jobject.getJSONArray("ptosp");
				for (int i = 0; i < arrary.length(); i++) {
					JSONObject object = arrary.getJSONObject(i);
					SpCodeMap point = new SpCodeMap();
					point.setPId(object.getInt("pid"));
					point.setType(object.getString("type"));
					point.setSpPoint(object.getString("spoint"));
					spoints.add(point);

				}

			} catch (JSONException e) {
				Debug.e("pToSpUtil--> getSpPointFromJson,JSONException:"
						+ e.toString());
			}

		} catch (Exception e) {
			Debug.e("pToSpUtil-->getSpPointFromJson,can not load json from asset :"
					+ e.toString());
		} finally {
			if (input != null) {
				try {
					input.close();
				} catch (IOException e) {
					Debug.e("pToSpUtil-->getSpPointFromJson, IOException:"
							+ e.toString());
				}
			}

		}
	}
}
