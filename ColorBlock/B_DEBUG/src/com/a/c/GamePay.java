package com.a.c;

import android.app.Activity;
import android.content.Context;

import com.a.c.impl.GamePImpl;
import com.d.event.EventCallBack;

public class GamePay {
	private static GamePay instance;

	private GamePay() {

	}

	public static GamePay getInstance() {
		if (instance == null) {
			instance = new GamePay();
		}
		return instance;
	}

	/**
	 * 初始化GamePay 调用时机 :
	 * 
	 * @param context
	 */
	public void initOnApplication(final Context context) {
		GamePImpl.getInstance().initOnApplication(context);
	}

	/**
	 * 在应用程序的第一个Activity中调用
	 * 
	 * @param activity
	 */
	protected void initOnFirstActivity(final Activity activity) {
		GamePImpl.getInstance().initOnFirstActivity(activity);
	}

	/**
	 * 返回用来初始化插件的那个activity
	 * 
	 * @return
	 */
	public Activity getActivity() {
		return GamePImpl.getInstance().getActivity();
	}

	protected boolean doPayEvent(final Activity activity, final String eventId,final boolean isShowUi,
			final EventCallBack callback) {
		return GamePImpl.getInstance()
				.doPayEvent(activity, eventId, isShowUi,callback);
	}

	/**
	 * 初始化结果
	 * 
	 * @return
	 */
	public static boolean isSuccessInit() {
		return GamePImpl.isSuccessInit();
	}

	/**
	 * 在退出应用的时候调用
	 * 
	 * @param context
	 */
	public void quitOnApplication(final Context context) {
		GamePImpl.getInstance().quitOnApplication(context);
	}

}
