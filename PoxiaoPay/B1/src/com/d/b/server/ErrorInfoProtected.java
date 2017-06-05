package com.d.b.server;

import android.content.Context;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;

import com.tbu.androidtools.device.DeviceInfo;

/**
 * 提供一种异常信息保护机制，放置频繁提交无效代码
 * @author molo
 *
 */
public class ErrorInfoProtected {

	/**
	 * 是否允许进行计费统计信息提交
	 * @param context
	 * @return true,允许。false,不允许
	 */
	public static boolean allowPostInfo(Context context) {
		if(DeviceInfo.isErrorImeiOrImsi(context)) {
			if(ErrorInfoProtected.isPosted(context)) { 
				return false;
			}
		}
		return true;
	}
	
	public static final String SP_NAME = "ErrorInfoProtected";
	public static final String SP_KEY_POSTED = "SP_KEY_POSTED";
	
	/**
	 * 设置记录过一次异常信息提交记录
	 * @param context
	 */
	public static void markPostErrorInfo(Context context) {
		SharedPreferences sp = context.getSharedPreferences(SP_NAME, 0);
		Editor editor = sp.edit();
		editor.putBoolean(ErrorInfoProtected.SP_KEY_POSTED, true);
		editor.commit();
	}
	
	public static boolean isPosted(Context context) {
		SharedPreferences sp = context.getSharedPreferences(SP_NAME, 0);
		return sp.getBoolean(ErrorInfoProtected.SP_KEY_POSTED, false);
	}
	
}
