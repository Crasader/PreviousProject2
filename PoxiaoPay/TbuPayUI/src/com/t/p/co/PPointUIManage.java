package com.t.p.co;

import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import android.content.Context;
import android.graphics.Rect;
import android.util.Log;

import com.t.p.co.UIElementInfo.ELEMENTTYPE;
import com.t.p.util.ScaleUtil;
import com.t.pl.PluginDefine;

public class PPointUIManage {

	private static PPointUIManage instance = null;
	private List<PPointUIInfo> ppoints = null;
	// json文件的存放路径
	private static final String P_POINT_UI = "pui/ppointui.json";
	private static final String UI_POINTS = "pui/uitop.json";

	private PPointUIManage() {

	}

	public static PPointUIManage getInstance() {
		if (null == instance) {
			instance = new PPointUIManage();
		}
		return instance;
	}

	/**
	 * 获取缩放后的区域值
	 * 
	 * @param left
	 * @param top
	 * @param width
	 * @param height
	 * @return
	 */
	public Rect getScaleRect(int left, int top, int width, int height) {
		Rect scaleRect = new Rect((int) (left * ScaleUtil.getScaleX()),
				(int) (top * ScaleUtil.getScaleY()),
				(int) ((left + width) * ScaleUtil.getScaleX()),
				(int) ((top + height) * ScaleUtil.getScaleY()));
		return scaleRect;
	}

	/**
	 * json文件存放在assets目录下
	 * 
	 * @param context
	 * @return
	 */
	public List<PPointUIInfo> getPpointInfoFromJson(Context context) {
		InputStream input = null;
		List<PPointUIInfo> infos = new ArrayList<PPointUIInfo>();
		try {
			input = context.getAssets().open(P_POINT_UI);
			byte[] buffer = new byte[input.available()];
			input.read(buffer);
			String json = new String(buffer, "utf-8");
			JSONObject jobject;
			try {
				jobject = new JSONObject(json);
				if (jobject.has("config")) {
					JSONObject con = jobject.getJSONObject("config");
					if (con.has("screenWidth") && con.has("screenHeight")) {
						String scaleType = "";
						if (con.has("resolutionPolicy")) {
							scaleType = con.getString("resolutionPolicy");
						}
						ScaleUtil.init(context, con.getInt("screenWidth"),
								con.getInt("screenHeight"), scaleType);
					} else {
						Log.e("TBU_DEBUG", "PPointUIManage -> 配置缩放信息错误");
					}
				}

				JSONArray arrary = jobject.getJSONArray("ppoints");
				for (int i = 0; i < arrary.length(); i++) {
					JSONObject object = arrary.getJSONObject(i);
					PPointUIInfo info = new PPointUIInfo();
					info.setPIndex(object.getInt("id"));
					JSONArray jarray = object.getJSONArray("elements");
					List<UIElementInfo> elements = new ArrayList<UIElementInfo>();
					for (int j = 0; j < jarray.length(); j++) {
						UIElementInfo element = new UIElementInfo();
						JSONObject eObject = jarray.getJSONObject(j);
						element.setDefaultName(eObject.getString("defaultname"));
						element.setSpecialName(eObject.getString("specialname"));
						if (eObject.getString("type").equals("image")) {
							element.setType(ELEMENTTYPE.IMAGE);
						} else if (eObject.getString("type").equals(
								"confirmbutton")) {
							element.setType(ELEMENTTYPE.CONFIRMBUTTON);
						} else if (eObject.getString("type").equals(
								"cancelbutton")) {
							element.setType(ELEMENTTYPE.CANCELBUTTON);
						}
						int x = eObject.getInt("x");
						int y = eObject.getInt("y");
						int width = eObject.getInt("width");
						int height = eObject.getInt("height");
						element.setRect(getScaleRect(x, y, width, height));
						elements.add(element);
					}
					info.setElementInfos(elements);
					infos.add(info);
				}

			} catch (JSONException e) {
				e.printStackTrace();
			}

		} catch (IOException e) {
			throw new RuntimeException(
					"PPointUIManage->getPpointInfoFromJson,Couldn not load json from asset :"
							+ "ppointui.json");
		} finally {
			if (input != null) {
				try {
					input.close();
				} catch (IOException e) {
				}
			}
		}
		Log.i("TBU_DEBUG",
				"PPointUIManage->getPpointInfoFromJson,p ui point total num = "
						+ infos.size());
		return infos;
	}

	/**
	 * 
	 * @param context
	 * @param pUIPoint
	 *            对应的ui point
	 * @return
	 */
	public PPointUIInfo getPPointUIInfo(Context context, int pUIPoint) {
		if (null == ppoints) {
			ppoints = getPpointInfoFromJson(context);
		}
		for (PPointUIInfo ui_ifno : ppoints) {
			if (ui_ifno.getPIndex() == pUIPoint) {
				return ui_ifno;
			}
		}
		Log.e("TBU_DEBUG",
				"PPointUIManage->getPPointUIInfo,can not find the ui point = "
						+ pUIPoint);
		return null;
	}

	private List<UIPointMap> ui_point_map = null;

	/**
	 * 从ppoint到puipoint的对应方法
	 * 
	 * @param pluginName
	 *            :当pluginName为null或者""的时候不再检查类型
	 * @param pPiont
	 * @return
	 */
	public int getPUIPointByPPoint(Context context, String pluginName,
			int pPiont) {
		if (null == ui_point_map) {
			ui_point_map = getUIPointMapFromJson(context);
		}
		int count = 0;
		for (UIPointMap iterable : ui_point_map) {
			if (PluginDefine.P_PLUGINTYPE_SECOND.equals(iterable.getType())) {
				count++;
			}
			if (null != pluginName && !pluginName.equals("")) {
				// 为了方便打包人员的方便,兼容新的(tbusms)和旧的(poxiao)自有支付插件的界面配置
				if (PluginDefine.P_PLUGINTYPE_TBUSMS.equals(pluginName)) {
					if (iterable.getPpoint() == pPiont
							&& (pluginName.equalsIgnoreCase(iterable.getType()) || "px"
									.equals(iterable.getType()))) {
						return iterable.getUiPoint();
					}
				} else {
					if (iterable.getPpoint() == pPiont
							&& pluginName.equalsIgnoreCase(iterable.getType())) {
						return iterable.getUiPoint();
					}
				}
			} else {
				if (iterable.getPpoint() == pPiont) {
					return iterable.getUiPoint();
				}
			}
		}
		// 此处是为了兼容只有一个2次界面的模式
		if (PluginDefine.P_PLUGINTYPE_SECOND.equals(pluginName)) {
			if (count == 1) {
				for (UIPointMap iterable : ui_point_map) {
					if (PluginDefine.P_PLUGINTYPE_SECOND.equals(iterable
							.getType()))
						return iterable.getUiPoint();
				}
			}
		}
		if (null != pluginName && !pluginName.equals("")) {
			Log.e("TBU_DEBUG",
					"PPointUIManage->getPUIPointByPoint,can not find the ui point maping pluginName = "
							+ pluginName + " payPiont = " + pPiont);
		} else {
			Log.e("TBU_DEBUG",
					"PPointUIManage->getPUIPointByPoint,pluginName is null,can not find the ui point maping payPiont = "
							+ pPiont);
		}
		return 0;
	}

	private List<UIPointMap> getUIPointMapFromJson(Context context) {
		InputStream is = null;
		List<UIPointMap> uipoints = new ArrayList<UIPointMap>();
		try {
			is = context.getAssets().open(UI_POINTS);
			byte[] buffer = new byte[is.available()];
			is.read(buffer);
			String json = new String(buffer, "utf-8");
			JSONObject jobject;
			try {
				jobject = new JSONObject(json);
				JSONArray arrary = jobject.getJSONArray("uipoints");
				for (int i = 0; i < arrary.length(); i++) {
					JSONObject object = arrary.getJSONObject(i);
					UIPointMap point = new UIPointMap();
					point.setUiPoint(object.getInt("uipoint"));
					point.setType(object.getString("type"));
					point.setPpoint(object.getInt("ppoint"));
					uipoints.add(point);
				}

			} catch (JSONException e) {
				e.printStackTrace();
			}

		} catch (IOException e) {
			throw new RuntimeException(
					"PPointUIManage->getUIPointMapFromJson,Couldn not load json from asset :"
							+ "uitop.json");
		} finally {
			if (is != null) {
				try {
					is.close();
				} catch (IOException e) {
				}
			}
		}
		return uipoints;
	}

}
