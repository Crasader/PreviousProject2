package com.t.p.util;

import android.content.Context;
import android.util.DisplayMetrics;

public class ScaleUtil {
	private static float scaleX = 1.0f;
	private static float scaleY = 1.0f;
	private static float defaultScreenWidth = 0;
	private static float defaultScreenHeight = 0;

	public static void init(Context context, float width, float height,
			String resolutionPolicy) {
		ScaleUtil.defaultScreenWidth = width;
		ScaleUtil.defaultScreenHeight = height;
		DisplayMetrics dm = context.getResources().getDisplayMetrics();
		float realwidth = dm.widthPixels;
		float realheight = dm.heightPixels;
		scaleX = realwidth / defaultScreenWidth;
		scaleY = realheight / defaultScreenHeight;
		if ("NO_BORDER".equalsIgnoreCase(resolutionPolicy)) {
			scaleX = scaleY = Max(scaleX, scaleY);
		} else if ("SHOW_ALL".equalsIgnoreCase(resolutionPolicy)) {
			scaleX = scaleY = Min(scaleX, scaleY);
		} else if ("FIXED_HEIGHT".equalsIgnoreCase(resolutionPolicy)) {
			scaleX = scaleY;
			ScaleUtil.defaultScreenWidth = realwidth / scaleX;
		} else if ("FIXED_WIDTH".equalsIgnoreCase(resolutionPolicy)) {
			scaleY = scaleX;
			ScaleUtil.defaultScreenHeight = realheight / scaleY;
		}

	}

	public static float getScaleX() {
		return scaleX;
	}

	public static float getScaleY() {
		return scaleY;
	}

	public static float getDefaultScreenWidth() {
		return defaultScreenWidth;
	}

	public static float getDefaultScreenHeight() {
		return defaultScreenHeight;
	}

	public static float Max(float x, float y) {
		float temp;
		if (x > y) {
			temp = x;
		} else {
			temp = y;
		}
		return temp;
	}

	public static float Min(float x, float y) {
		float temp;
		if (x > y) {
			temp = y;
		} else {
			temp = x;
		}
		return temp;
	}
}
