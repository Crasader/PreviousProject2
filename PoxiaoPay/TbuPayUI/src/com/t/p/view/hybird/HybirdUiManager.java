package com.t.p.view.hybird;

import com.t.p.view.hybird.HybirdView;

import android.app.Activity;
import android.graphics.PixelFormat;
import android.view.View;
import android.view.WindowManager;
import android.view.WindowManager.LayoutParams;

/**
 * 
 * @author molo
 *
 */
public class HybirdUiManager {

	private static HybirdUiManager instance;

	protected WindowManager mWindowManager;
	protected WindowManager.LayoutParams wmParams;
	protected View holderView;

	private boolean extendViewShowing = false;
	private boolean needRedrawExtendView = false;

	private HybirdUiManager() {
	}

	public static HybirdUiManager getInstance() {
		if (instance == null) {
			instance = new HybirdUiManager();
		}
		return instance;
	}

	public void dismissView() {
		if (holderView != null) {
			mWindowManager.removeView(holderView);
			holderView = null;
			extendViewShowing = false;
		}
	}

	public void createFloatView(final Activity activity, int uiPoint,
			String pluginType) {

		wmParams = new WindowManager.LayoutParams();
		mWindowManager = activity.getWindowManager();
		wmParams.type = LayoutParams.TYPE_PHONE;
		wmParams.format = PixelFormat.RGBA_8888;

		wmParams.flags = LayoutParams.FLAG_NOT_FOCUSABLE
				| LayoutParams.FLAG_NOT_TOUCH_MODAL
				| LayoutParams.FLAG_NOT_TOUCHABLE;
		holderView = new HybirdView(activity, uiPoint, pluginType);
		mWindowManager.addView(holderView, wmParams);
		extendViewShowing = true;
	}
}