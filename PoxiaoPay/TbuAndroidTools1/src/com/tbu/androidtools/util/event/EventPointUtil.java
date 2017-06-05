package com.tbu.androidtools.util.event;

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

public class EventPointUtil {

	private static final String EVENT_TO_P = "json/event2p.json";// 定义json文件的目录及名称
	private static List<TbuEvent> events = new ArrayList<TbuEvent>();
	public static final int PROTECTED_P_POINT_ID_NA = -1;
	private static int protectedPPointId = PROTECTED_P_POINT_ID_NA;
	private static int eventVersion = 999;

	/**
	 * 
	 * @param context
	 * @param eventId
	 * @return
	 */
	public static TbuEvent getTbuEventById(Context context, int eventId) {
		if (events.isEmpty()) {
			getTbuEventByJson(context);
		}
		TbuEvent result = null;
		for (TbuEvent eventPoint : events) {
			if (eventPoint.getEventId() == eventId) {
				result = eventPoint;
				return result;
			}
		}
		if (null == result) {
			Debug.e("EventToPUtil ----> getTbuEventById,can not find the event id = "
					+ eventId);
		}
		return result;
	}

	/**
	 * 获取保护事件点的信息
	 * 
	 * @return
	 */
	public static int getProtectedPPoint(Context context) {
		if (null == events||events.isEmpty()) {
			getTbuEventByJson(context);
		}
		return protectedPPointId;
	}

	/**
	 * 获取事件点版本号
	 * 
	 * @param context
	 * @return
	 */
	public static int getEventPointVersion(Context context) {
		if (null == events||events.isEmpty()) {
			getTbuEventByJson(context);
		}
		return eventVersion;
	}

	public static void getTbuEventByJson(Context context) {
		InputStream input = null;
		try {
			input = context.getAssets().open(EVENT_TO_P);
			byte[] buffer = new byte[input.available()];
			input.read(buffer);
			String info = new String(buffer, "utf-8");
			String json = ReadJsonUtil.decoderByDES(context, info,
					"p_k");
			JSONObject jobject;
			try {
				jobject = new JSONObject(json);
				if (jobject.has("protected_p_point")) {
					protectedPPointId = jobject.getInt("protected_p_point");
				}
				if (jobject.has("event_version")) {
					eventVersion = jobject.getInt("event_version");
				}

				JSONArray arrary = jobject.getJSONArray("event2p");
				for (int i = 0; i < arrary.length(); i++) {
					JSONObject object = arrary.getJSONObject(i);
					TbuEvent eventPoint = new TbuEvent();
					eventPoint.setEventId(object.getInt("eventid"));
					eventPoint.setPId(object.getInt("pid"));
					eventPoint.setEventState(object.getBoolean("state"));
					if (object.has("isprotected")) {
						eventPoint.setProtected(object
								.getBoolean("isprotected"));
					}

					if (object.has("describe")) {
						JSONArray darray = object.getJSONArray("describe");
						Map<Integer, Integer> reward = new HashMap<Integer, Integer>();
						for (int j = 0; j < darray.length(); j++) {
							reward.put(
									darray.getJSONObject(j).getInt("propid"),
									darray.getJSONObject(j).getInt("propnum"));
						}
						eventPoint.setReward(reward);
					}
					events.add(eventPoint);
				}

			} catch (JSONException e) {
				Debug.e("EventToPUtil-->getTbuEventByJson, JSONException :"
						+ e.toString());
			}

		} catch (Exception e) {
			Debug.e("EventToPUtil-->getTbuEventByJson, can not load json from asset :"
					+ e.toString());
		} finally {
			if (input != null) {
				try {
					input.close();
				} catch (IOException e) {
					Debug.e("EventToPUtil-->getTbuEventByJson, IOException :"
							+ e.toString());
				}
			}

		}
	}

}
