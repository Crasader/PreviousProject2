package com.tbu.android.lamy.util;

import java.util.List;

import android.app.ActivityManager;
import android.app.ActivityManager.RunningTaskInfo;
import android.content.Context;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;

public class SessionUtil {

	public static final String SP_NAME = "SP_SessionUtil";
	public static final String SP_KEY_SESSIONID = "SP_KEY_SESSIONID";
	public static final String SP_KEY_ALARMID = "SP_KEY_ALARMID";
	
	/**
	 * 获取会话ID。每次调用值+1
	 * @param context
	 * @return
	 */
	public static int getSessionId(Context context) {
		SharedPreferences sp = context.getSharedPreferences(SP_NAME, 0);
		int result = sp.getInt(SP_KEY_SESSIONID, 0);
		Editor editor = sp.edit();
		editor.putInt(SP_KEY_SESSIONID, result+1);
		editor.commit();
		return result;
	}
	
	/**
	 * 获取闹钟ID。每次调用值+1
	 * @param context
	 * @return
	 */
	public static int getAlarmId(Context context) {
		SharedPreferences sp = context.getSharedPreferences(SP_NAME, 0);
		int result = sp.getInt(SP_KEY_ALARMID, 0);
		Editor editor = sp.edit();
		editor.putInt(SP_KEY_ALARMID, result+1);
		editor.commit();
		return result;
	}
	
	/**
	 * 判断传入的包名是否为顶层应用
	 * @param context
	 * @param packageName
	 * @return
	 */
	public static boolean isTopApp(Context context, String packageName) {
		if(packageName == null) {
			return false;
		}
		if("".equals(packageName)){
			return false;
		}
		
		ActivityManager manager = (ActivityManager) context.getSystemService (Context.ACTIVITY_SERVICE);
		List<RunningTaskInfo> task_info = manager.getRunningTasks(10);

		if(task_info.get(0) != null && task_info.get(0).topActivity != null && 
				task_info.get(0).topActivity.getPackageName().equals(packageName)) {
			return true;
		}
		
		return false;
	}
}
