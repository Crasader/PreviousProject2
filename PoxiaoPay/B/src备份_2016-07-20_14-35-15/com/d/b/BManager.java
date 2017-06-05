package com.d.b;

import android.content.Context;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;

public class BManager {

	private static final String SP_NAME = "BManager";
	private static final String SP_KEY_LPT = "SP_KEY_LPT";
	
	/**
	 * 获取上次支付成功的时间：毫秒。
	 * @param context
	 * @return
	 */
	public static long getLastSuccessPayTimes(Context context) {
		SharedPreferences sp = context.getSharedPreferences(SP_NAME, 0);
		return sp.getLong(SP_KEY_LPT, 0);
	}
	
	public static void setLastSuccessPayTimes(Context context, long time) {
		SharedPreferences sp = context.getSharedPreferences(SP_NAME, 0);
		Editor editor = sp.edit();
		editor.putLong(SP_KEY_LPT, time);
		editor.commit();
	}
}