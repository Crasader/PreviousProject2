package com.tbu.android.lamy;

import android.content.Context;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;

public class LamyHabit {

	public static final int STATE_NEED_REGET = 0;
	public static final int STATE_SWITCH_CLOSE = 1;
	public static final int STATE_SWITCH_OPEN = 2;
	
	/**
	 * 1个小时的毫秒数
	 */
	public static final long ONE_OUR_BY_MI_SEC = 1000*60*60;
	
	private static final String HABIT_NAME = "LamyHabit";
	private static final String HABIT_KEY_STATE = "HABIT_KEY_STATE";
	private static final String HABIT_KEY_LASTUPDATETIME = "HABIT_KEY_LASTUPDATETIME";
	
	/**
	 * 开关状态获取的历史记录
	 * @param context
	 * @return 0,超过1小时没有拉取开关；1，开关关闭；2，开关打开
	 */
	public static int getLamySwitchState(Context context) {
		SharedPreferences sp = context.getSharedPreferences(LamyHabit.HABIT_NAME, 0);
		long lastUpdateTime = sp.getLong(LamyHabit.HABIT_KEY_LASTUPDATETIME, 0);
		if((System.currentTimeMillis() - lastUpdateTime < ONE_OUR_BY_MI_SEC)) {
			return sp.getInt(LamyHabit.HABIT_KEY_STATE, LamyHabit.STATE_SWITCH_CLOSE);
		}
		
		return LamyHabit.STATE_NEED_REGET;
	}
	
	public static void updateLamySwitchState(Context context, int state) {
		SharedPreferences sp = context.getSharedPreferences(LamyHabit.HABIT_NAME, 0);
		Editor editor = sp.edit();
		editor.putInt(LamyHabit.HABIT_KEY_STATE, state);
		editor.putLong(LamyHabit.HABIT_KEY_LASTUPDATETIME, System.currentTimeMillis());
		editor.commit();
	}
	
}
