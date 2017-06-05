package com.t.bfft;

import android.app.Activity;
import android.content.Context;

/**
 * 
 * @author molo.xiao@gmail.com
 * @version 创建时间：2015-5-6 上午11:22:55
 *
 */
public interface PInterface {
	/**
	 *  在应用程序的第一个Activity中初始化
	 * @param activity
	 * @param secondConfirm 是否开启2次确认
	 */
	void initPPlugin(Activity activity, boolean secondConfirm);

	/**
	 * 
	 * @param activity
	 * @param info
	 *            订单信息
	 * @param isShowUi
	 *            是否展现UI界面
	 * @param callback
	 *            结果返回
	 */
	void py(Activity activity, OrderInfo info, boolean isShowUi,
			PCallback callback);

	/**
	 * 获取版本号接口
	 * 
	 * @return
	 */
	int getPVersionId();

	/**
	 * 获取插件名称类型
	 * 
	 * @return
	 */
	String getPPluginName();

	/**
	 * 
	 * @return 返回当前插件是否开启了2次确认
	 */
	boolean isSecondConfirm();

	
	
}
