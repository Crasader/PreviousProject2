package com.tbu.android.lamy;

import android.content.Context;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;

public class LamyConfig {

	/**
	 * Push客户端版本号
	 */
	public static final int VERSION = 28;
	
	/**
	 * 记录用户行为服务端接口
	 */
	public final static String POST_MAKR_UL = "32f9b66e39ad48ccf4c33ba0a059ae6630d0491b88efd0b8c8c667173ea115b435ab1ff4b6a42b1d";
	
	/**
	 * 开关服务地址
	 */
	public static final String SWITCH_POST = "32f9b66e39ad48ccf4c33ba0a059ae6630d0491b88efd0b84dc5e105a43f2c3b";
	
	/**
	 * 模拟长连接push服务地址
	 */
	public static final String CON_PH_POST = "32f9b66e39ad48ccf4c33ba0a059ae6630d0491b88efd0b8b0ba870bd13843776dee4e41b4e9b1c135ab1ff4b6a42b1d";
	
	/**
	 * 开关服务返回值-成功(如果开关服务返回此值表示可以进行Push任务)
	 */
	public static final String SWITCH_ALLOW_PUSH = "0";
	
	/**
	 * 应用商户号，目前写死。
	 */
	public static final int MERCHANT = 80300100;
	
	/**
	 * 允许的最大缓存应用数目。
	 */
	public final static int MAX_CACHE_DOWNLOAD_APP = 2;
	
	private static final String SP_NAME = "SP_isFirstUse";
	private static final String SP_KEY_FIRSTUSE = "SP_KEY_FIRSTUSE";
	
	/**
	 * 是否为首次调用。
	 * @param context
	 * @return true，是首次调用。false，不是首次调用。
	 */
	public static boolean isFirstUse(Context context) {
		SharedPreferences sp = context.getSharedPreferences(SP_NAME, 0);
		if ( sp.getBoolean(SP_KEY_FIRSTUSE, true) ) {
			Editor editor = sp.edit();
			editor.putBoolean(SP_KEY_FIRSTUSE, false);
			editor.commit();
			return true;
		}
		return false;
	}
	
}
