package com.poxiao.smspay;

import android.app.Activity;
import android.content.Context;

import com.poxiao.smspay.observer.SmsObserverManager;

/**
 * 用于全局管理短信支付业务
 * 
 * @author molo.xiao@gmail.com
 * @version 创建时间：2015-5-27 下午5:07:53
 *
 */
public class SmsPay {

	/**
	 * 当前支付计费版本号。每次更新计费版本号+1
	 * 更新记录：[100]更新短信协议的实现：可支持验证码回调
	 * 
	 * 更新记录：[101]更新支付会话过程为同步会话，验证码支持模糊号码发送，
	 * 服务端会根据版本号下发指令内容，兼容老版本
	 * 
	 * 更新记录：[102]增加上传参数UA
	 */
	public static final String PAY_VERSION = "102";
	

	private static Context context;

	/**
	 * 
	 * @param context
	 *  要求传入Application Context
	 */
	public static void init(Context context) {
		SmsPay.context = context;
		SmsObserverManager.setContext(context);
		SmsObserverManager.registerObserver(context);
	}

	public static void quit(Context context) {
		SmsObserverManager.unregisterObserver(context);
	}

	/**
	 * 取应用传入的ApplcationContext值
	 * 
	 * @return
	 */
	public static Context getApplicationContext() {
		return SmsPay.context;
	}

	public static void pay(final Activity activity,
			final TbuPayCallBack pxPayCallback, final String merchantId,
			final String appId, final String gameId, final int payPoint,
			final String payPointName, final int payMoney,
			final String gameVersion, final String phone, final String prov_id,
			final String lac, final String cid, final String sim_sn, final String ua) {

		new SmsPayBasis().DoGetGameBasisCode(activity, pxPayCallback,
				merchantId, appId, gameId, payPoint, payPointName, payMoney,
				gameVersion, phone, prov_id, lac, cid, sim_sn,ua);

	}
}
