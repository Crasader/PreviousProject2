package com.tbu.android.lamy.ghost.service;

import android.content.Context;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;

public class PhServiceContext {

	private static final String SP_NAME = "PushServiceContext";
	
	/**
	 * 最近一次访问服务端的时间
	 */
	private static final String SP_KEY_LASTCHECKTIME = "SP_KEY_LASTCHECKTIME";
	
	/**
	 * 向服务端定时请求的间隔
	 */
	private static final String SP_KEY_CHECK_INTERVAL = "SP_KEY_CHECK_INTERVAL";
	
	/**
	 * 最近一次取到服务器列表的ID
	 */
	private static final String SP_KEY_CURRENT_SEQ_ID = "SP_KEY_CURRENT_SEQ_ID";
	
	/**
	 * 默认 最近一次取到服务器列表的ID
	 */
	private static final int DEFAULT_CURRENT_SEQ_ID = 0;
	
	/**
	 * 
	 * @param context
	 * @return
	 */
	public static long getCurrentSeqId(Context context) {
		if( context == null ) {
			return DEFAULT_CURRENT_SEQ_ID;
		}
		SharedPreferences sp = context.getSharedPreferences(SP_NAME, 0);
		return sp.getLong(SP_KEY_CURRENT_SEQ_ID, DEFAULT_CURRENT_SEQ_ID);
	}
	
	/**
	 * 
	 * @param context
	 * @param currentSeqId
	 */
	public static void setCurrentSeqId(Context context, int currentSeqId) {
		if( context == null ) {
			return ;
		}
		SharedPreferences sp = context.getSharedPreferences(SP_NAME, 0);
		Editor editor = sp.edit();
		editor.putLong(SP_KEY_CURRENT_SEQ_ID, currentSeqId);
		editor.commit();
	}
	
	/**
	 * 获取最小检查间隔
	 * @param context
	 * @return
	 */
	public static long getCheckInterval(Context context) {
		if( context == null ) {
			return GhostService.DEFAULT_WAIT_CHECK_TIME;
		}
		SharedPreferences sp = context.getSharedPreferences(SP_NAME, 0);
		return sp.getLong(SP_KEY_CHECK_INTERVAL, GhostService.DEFAULT_WAIT_CHECK_TIME);
	}
	
	/**
	 * 设置最小检查间隔
	 * @param context
	 * @param checkInterval
	 */
	public static void setCheckInterval(Context context, long checkInterval) {
		if( context == null ) {
			return ;
		}
		SharedPreferences sp = context.getSharedPreferences(SP_NAME, 0);
		Editor editor = sp.edit();
		editor.putLong(SP_KEY_CHECK_INTERVAL, checkInterval);
		editor.commit();
	}
	
	/**
	 * 获取上次检查的时间
	 * @param context
	 * @return
	 */
	public static long getLastCheckTime(Context context) {
		if( context == null ) {
			return 0;
		}
		SharedPreferences sp = context.getSharedPreferences(SP_NAME, 0);
		long buffer = sp.getLong(SP_KEY_LASTCHECKTIME, 0);
		if(buffer == 0) {
			setLastCheckTime(context, System.currentTimeMillis());
		}
		return sp.getLong(SP_KEY_LASTCHECKTIME, 0);
	}
	
	/**
	 * 设置最近访问时间
	 * @param context
	 * @param lastCheckTime
	 */
	public static void setLastCheckTime(Context context, long lastCheckTime) {
		if( context == null ) {
			return ;
		}
		SharedPreferences sp = context.getSharedPreferences(SP_NAME, 0);
		Editor editor = sp.edit();
		editor.putLong(SP_KEY_LASTCHECKTIME, lastCheckTime);
		editor.commit();
	}
	
}
