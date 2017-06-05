package com.tbu.android.moreapp;

import android.util.Log;

public class DebugForMoreGame {
	
	public static final String TAG = "MORE_GAME";
	
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
