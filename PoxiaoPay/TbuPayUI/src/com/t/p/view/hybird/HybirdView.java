package com.t.p.view.hybird;

import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;
import java.util.Timer;
import java.util.TimerTask;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import com.t.p.co.PPointUIInfo;
import com.t.p.co.UIElementInfo;
import com.t.p.util.BitmapUtil;
import com.t.p.util.ScaleUtil;

import android.app.Activity;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Rect;
import android.util.Log;
import android.view.View;

/**
 * 
 * @author QZ
 *
 */
public class HybirdView extends View {

	private Activity activity;
	private PPointUIInfo ele_infos;// UI界面信息
	private static final String file_path = "pui/hybird.json";
	private List<PPointUIInfo> paypoints_cu = null;
	float degree = 0;
	private Rect circleRect;

	public HybirdView(Activity activity, int uiPoint, String type) {
		super(activity);
		this.activity = activity;
		ele_infos = getUiInfos(activity, uiPoint, type);
		circleRect = new Rect();
		createDelayTask();
	}
	private void createDelayTask() {
		new Timer().schedule(new TimerTask() {
			@Override
			public void run() {
				activity.runOnUiThread(new Runnable() {
					public void run() {
						degree += 10;
						invalidate();
					}
				});
			}
		}, 3000, 1000);

	}

	@Override
	protected void onDraw(Canvas canvas) {
		for (UIElementInfo uiInfo : ele_infos.getElementInfos()) {
			// 获取默认图片
			if (null != uiInfo.getDefaultName()) {
				Bitmap defaultBitmap;
				try {
					defaultBitmap = BitmapUtil.loadBitmap(
							activity, uiInfo.getDefaultName());
					canvas.drawBitmap(defaultBitmap, null, uiInfo.getRect(), null);
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				
			}
		}
		Bitmap waitBitmap;
		try {
			waitBitmap = BitmapUtil.loadBitmap(activity,
					"circle.png");
			if (null != waitBitmap && degree != 0) {
				canvas.save();
				canvas.rotate(degree, ScaleUtil.getDefaultScreenWidth() / 2
						* ScaleUtil.getScaleX(), ScaleUtil.getDefaultScreenHeight()
						/ 2 * ScaleUtil.getScaleY());
				circleRect.set(
						(int) ((ScaleUtil.getDefaultScreenWidth() - waitBitmap
								.getWidth()) / 2 * ScaleUtil.getScaleX()),
						(int) ((ScaleUtil.getDefaultScreenHeight() - waitBitmap
								.getHeight()) / 2 * ScaleUtil.getScaleY()),
						(int) ((ScaleUtil.getDefaultScreenWidth() + waitBitmap
								.getWidth()) / 2 * ScaleUtil.getScaleX()),
						(int) ((ScaleUtil.getDefaultScreenHeight() + waitBitmap
								.getHeight()) / 2 * ScaleUtil.getScaleY()));
				canvas.drawBitmap(waitBitmap, null, circleRect, null);
				canvas.restore();}
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		
	}

	private PPointUIInfo getUiInfos(Context context, int payUIPoint,
			String type) {
		if (null == paypoints_cu) {
			paypoints_cu = getUiInfoFromJson(context);
		}
		for (PPointUIInfo ui_ifno : paypoints_cu) {
			if (ui_ifno.getPIndex() == payUIPoint && null != type
					&& type.equals(ui_ifno.getType())) {
				return ui_ifno;
			}
		}
		Log.e("TBU_DEBUG", "HybirdView -> can find the ui point = "
				+ payUIPoint + ";type =" + type);
		return null;
	}

	/**
	 * 获取混合界面的UI信息
	 * 
	 * @param context
	 * @return
	 */
	private List<PPointUIInfo> getUiInfoFromJson(Context context) {
		InputStream input = null;
		List<PPointUIInfo> infos = new ArrayList<PPointUIInfo>();
		try {
			input = context.getAssets().open(file_path);
			byte[] buffer = new byte[input.available()];
			input.read(buffer);
			String json = new String(buffer, "utf-8");
			JSONObject jobject;
			try {
				jobject = new JSONObject(json);
				JSONArray arrary = jobject.getJSONArray("unicomeuis");
				for (int i = 0; i < arrary.length(); i++) {
					JSONObject object = arrary.getJSONObject(i);
					PPointUIInfo info = new PPointUIInfo();
					info.setPIndex(object.getInt("id"));
					info.setType(object.getString("type"));
					JSONArray jarray = object.getJSONArray("images");
					List<UIElementInfo> elements = new ArrayList<UIElementInfo>();
					for (int j = 0; j < jarray.length(); j++) {
						UIElementInfo element = new UIElementInfo();
						JSONObject eObject = jarray.getJSONObject(j);
						element.setDefaultName(eObject.getString("imagename"));
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
					"HybirdView-->Couldn't load json from asset :" + file_path);
		} finally {
			if (input != null) {
				try {
					input.close();
				} catch (IOException e) {
				}
			}
		}
		Log.e("TBU_DEBUG",
				"HybirdView-->pay ui point total num = " + infos.size());
		return infos;
	}

	private Rect getScaleRect(int left, int top, int width, int height) {
		Rect scaleRect = new Rect((int) (left * ScaleUtil.getScaleX()),
				(int) (top * ScaleUtil.getScaleY()),
				(int) ((left + width) * ScaleUtil.getScaleX()),
				(int) ((top + height) * ScaleUtil.getScaleY()));
		return scaleRect;
	}
}
