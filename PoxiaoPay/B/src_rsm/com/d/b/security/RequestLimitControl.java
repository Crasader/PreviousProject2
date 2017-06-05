package com.d.b.security;

import android.content.Context;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;

import com.tbu.androidtools.Debug;

/**
 * 请求次数控制
 * @author molo
 *
 */
public class RequestLimitControl {

	/**
	 * 判断本次是否请求是否允许执行
	 * @param payPlginName
	 * @return
	 */
	public static boolean allowRequest(Context context, String payPlginName) {
		if( RequestLimitControl.isLimitedPlgin(context, payPlginName) ) {
			for(RequestLimitPPlgin rlpp : RequestLimitConfig.Rlpp) {
				if(rlpp != null && payPlginName.equals(rlpp.getPlginName())) {
					if(RequestLimitControl.getPlginRequestTimes(context, rlpp.getPlginName()) >=
							rlpp.getLimitTimes() ) {	// 查询次数是否达到了配置限制数
						return false;
					}
				}
			}
		}
		return true;
	}
	
	/**
	 * 判断插件是否为需要限制请求次数的插件
	 * @param payPlginName
	 * @return
	 */
	private static boolean isLimitedPlgin(Context context, String payPlginName) {
		if(payPlginName != null && payPlginName.length() > 0) {
			if(RequestLimitConfig.Rlpp != null && RequestLimitConfig.Rlpp.length > 0) {
				for(RequestLimitPPlgin rlpp : RequestLimitConfig.Rlpp) {
					if(rlpp != null && payPlginName.equals(rlpp.getPlginName())) {
						return true;
					}
				}
			}
		}
		return false;
	}
	
	private static final String SP_NAME_RLC = "RequestLimitControl";
	
	
	/**
	 * 获取某个支付插件的支付请求次数，默认为0。
	 * @param context
	 * @param plginName
	 * @return
	 */
	private static int getPlginRequestTimes(Context context, String plginName) {
		if( plginName != null && plginName.length()>0 ) {
			SharedPreferences sp = context.getSharedPreferences(RequestLimitControl.SP_NAME_RLC, 0);
			return sp.getInt(plginName, 0);
		}
		return 0;
	}
	
	/**
	 * 为某个支付插件添加一次请求计数
	 * @param context
	 * @param plginName
	 * @return
	 */
	public static int addPlginRequestTimeOnce(Context context, String plginName) {
		if( plginName != null && plginName.length()>0 ) {
			SharedPreferences sp = context.getSharedPreferences(RequestLimitControl.SP_NAME_RLC, 0);
			Editor editor = sp.edit();
			editor.putInt(plginName, sp.getInt(plginName, 0) + 1 );
			editor.commit();
			int newTimes = sp.getInt(plginName, 0);
			Debug.i("RequestLimitControl->addPlginRequestTimeOnce, plginName = " + plginName + 
					"; new requestTimes = " + newTimes);
			return newTimes;
		}
		return 0;
	}
}