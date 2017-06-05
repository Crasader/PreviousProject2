package com.tbu.android.lamy.util;

import android.util.Log;

public class Debug {
	
	public static final String TAG = "TBU_PUSH";
	
	public static void i(String info) {
		Log.i(TAG, info);
	}
	
	public static void e(String info) {
		Log.e(TAG, info);
	}
	
	public static void w(String info) {
		Log.w(TAG, info);
	}
}
