package com.t.bfft;

import android.app.Activity;

import com.tbu.androidtools.Debug;

/**
 * 
 * @author molo.xiao@gmail.com
 * @version 创建时间：2015-5-6 上午11:09:17
 * 
 */
public class Buffett implements PInterface {

	/**
	 * 定义buffett的版本号
	 */
	public static final int BUFFETT_VERSION = 2;

	public static boolean onPSession = false;

	private static Buffett instance;

	private PInterface pInterface;
	private static boolean initSuccess = false;

	/**
	 * 
	 * @param pInterface
	 * @param activity
	 * @param secondConfirm是否开启2次确认
	 * @return true，切换成功。false，切换失败。
	 */
	public static boolean setPPlugin(PInterface pInterface,
			Activity activity, boolean secondConfirm) {
		if (Buffett.onPSession == true) {
			Debug.e("Buffett set p plgin fail. Because onPSession");
			return false;
		}
		if (instance != null) {
			instance = null;
		}
		instance = new Buffett(pInterface);
		instance.initPPlugin(activity, secondConfirm);
		initSuccess = true;
		Debug.e("Buffett set p plgin success");
		return true;
	}

	public static boolean successInit() {
		return initSuccess;
	}

	public static Buffett getInstance() {
		return instance;
	}

	private Buffett(PInterface pInterface) {
		this.pInterface = pInterface;
	}
	private PCallback callback;
	public PCallback getPCallBack(){
		return callback;
	}
	@Override
	public void py(Activity activity, OrderInfo info, boolean isShowUi,
			PCallback callback) {
		this.callback=callback;
		pInterface.py(activity, info, isShowUi, callback);
	}

	@Override
	public int getPVersionId() {
		return pInterface.getPVersionId();
	}

	@Override
	public String getPPluginName() {
		return pInterface.getPPluginName();
	}

	@Override
	public void initPPlugin(Activity activity, boolean secondConfirm) {
		pInterface.initPPlugin(activity, secondConfirm);
	}

	@Override
	public boolean isSecondConfirm() {
		return pInterface.isSecondConfirm();
	}

	/**
	 * 返回buffett的版本号
	 * 
	 * @return
	 */
	public static int getBuffettVersion() {
		return BUFFETT_VERSION;
	}


}
