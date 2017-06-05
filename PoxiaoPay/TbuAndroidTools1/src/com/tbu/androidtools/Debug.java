package com.tbu.androidtools;

import android.util.Log;

/**
 * 统一调试Log的TAG
 * 
 * @author molo.xiao@gmail.com
 * @version 创建时间：2015-5-12 下午4:10:06
 * 
 */
public class Debug {

	public static final String TAG_DEBUG = "TBU_DEBUG";

	public static void i(String info) {
		Log.i(TAG_DEBUG, info);
	}
	
	public static void e(String info) {
		Log.e(TAG_DEBUG, info);
	}
	
	public static void w(String info) {
		Log.w(TAG_DEBUG, info);
	}
	
	public static void v(String info) {
		Log.v(TAG_DEBUG, info);
	}
}
