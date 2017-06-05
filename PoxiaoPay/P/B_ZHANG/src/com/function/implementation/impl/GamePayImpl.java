package com.function.implementation.impl;

import android.app.Activity;
import android.content.Context;

import com.a.b.c.d.ZPImpl;
import com.function.implementation.base.IGamePay;
import com.t.bfft.Buffett;
import com.t.bfft.OrderInfo;
import com.t.bfft.OrderResultInfo;
import com.t.bfft.PCallback;
import com.t.bfft.PInterface;
import com.t.p.PUI;
import com.t.pl.PluginDefine;
import com.tacitly.event.EventCallBack;
import com.tacitly.event.EventResult;
import com.tbu.androidtools.Debug;
import com.tbu.androidtools.TbuAndroidTools;
import com.tbu.androidtools.util.event.TbuEvent;
import com.tbu.androidtools.util.psspoint.PPoint;
import com.tbu.androidtools.util.psspoint.PPointUtil;

public class GamePayImpl extends IGamePay {

	private static GamePayImpl instance;
	private static boolean successInit = false;
	private Buffett buffett;
	private Activity activity;

	private GamePayImpl() {
	}

	public static GamePayImpl getInstance() {
		if (instance == null) {
			instance = new GamePayImpl();
		}
		return instance;
	}

	/**
	 * 在应用程序的第一个Activity中调用
	 * 
	 * @param activity
	 */
	public void initOnFirstActivity(final Activity activity) {
		// 打开TbuPush
		BApplication.getInstance().startPush();
		Debug.v("GamePay->initOnFirstActivity called...");
		this.activity = activity;
		setPayPlginByName();
		successInit = true;
	}

	/**
	 * 返回用来初始化插件的那个activity
	 * 
	 * @return
	 */
	public Activity getActivity() {
		return activity;
	}

	private void setPayPlginByName() {
		setPayPlugin((PInterface) new ZPImpl(), activity, false);
	}

	private void setPayPlugin(PInterface payImpl, Activity activity,
			boolean secondConfirm) {
		Buffett.setPPlugin(payImpl, activity, secondConfirm);
		buffett = Buffett.getInstance();
		successInit = true;
	}

	/**
	 * 支付插件选择协议 :字符串做静态定义
	 * 
	 * @param open
	 * @return
	 */

	public boolean doPayEvent(final Activity activity, final String eventId,
			final EventCallBack callback) {
		final TbuEvent event = TbuAndroidTools.getTbuEventById(activity,
				Integer.parseInt(eventId));
		if (null != event) {
			if (event.getEventState()) {
				pay(activity, eventId, true, false, new PCallback() {
					@Override
					public void result(OrderResultInfo orderResultInfo) {
						EventResult result = new EventResult();
						result.setPayResult(orderResultInfo.getResultCode() == OrderResultInfo.P_SUCCESS ? true
								: false);
						// 根据支付结果,返回奖励
						PPoint payPoint = PPointUtil.getPPointById(
								activity, event.getPyId());
						if (null != payPoint && null != payPoint.getReward()) {
							result.setReward(payPoint.getReward());
						} else {
							Debug.e("GamePay->doPayEvent,the payPoint is null, payid ="
									+ event.getPyId());
						}
						callback.setEventResult(result);
					}
				});
				return true;
			} else {
				Debug.e("GamePay->doPayEvent, this event is close, point = "
						+ eventId);
				return false;
			}
		} else {
			Debug.e("GamePay->doPayEvent, this event is null, point = "
					+ eventId);
			return false;
		}
	}

	/**
	 * 
	 * @param activity
	 * @param payId
	 *            支付使用的参数
	 * @param eventId
	 *            统计信息使用的参数
	 * @param pluginChanged
	 *            统计信息使用的参数,false正常启动的支付，true切换插件后启动的支付
	 * @param callback
	 */
	private void pay(final Activity activity, final String eventId,
			final boolean isShowUi, final boolean pluginChanged,
			final PCallback callback) {
		final TbuEvent event = TbuAndroidTools.getTbuEventById(activity,
				Integer.parseInt(eventId));
		OrderInfo orderInfo = OrderInfo.getOrderInfo(activity,
				event.getPyId(), "123456",
				String.valueOf(System.currentTimeMillis()),"","",6,"");
		if (orderInfo.getPrice() > 0) {
			buffett.py(activity, orderInfo, true, callback);
		} else {
			// 弹出免费计费
			payFree(activity, orderInfo.getPPointNum(), callback);
		}
	}

	/**
	 * 初始化结果
	 * 
	 * @return
	 */
	public static boolean isSuccessInit() {
		return successInit;
	}

	/**
	 * 在退出应用的时候调用
	 * 
	 * @param context
	 */
	public void quitOnApplication(final Context context) {
		Debug.v("GamePay->quitOnApplication called...");
	}

	public void initOnApplication(Context context) {
		Debug.v("GamePay->initOnApplication called...");
		ZPImpl.init(context);
	}

	/**
	 * 
	 * @param activity
	 * @param payId
	 * @param payCallback
	 */
	private void payFree(final Activity activity, final int payId,
			final PCallback payCallback) {
		Debug.i("GamePay->payFree;this is a free pay point,payid = " + payId);
		PUI.showPDialog(activity, payId, PluginDefine.P_PLUGINTYPE_FREE,
				new PCallback() {
					@Override
					public void result(OrderResultInfo orderResultInfo) {
						// 返回免费界面的支付结果
						Debug.i("GamePay->orderResultInfo.getResultCode()="
								+ orderResultInfo.getResultCode());
						OrderResultInfo result = new OrderResultInfo();
						if (orderResultInfo.getResultCode() == OrderResultInfo.CLICK_CONFIRM) {
							result.setErrorCode(""
									+ OrderResultInfo.P_SUCCESS);
							result.setErrorMsg("免费界面玩家点击确定");
							result.setResultCode(OrderResultInfo.P_SUCCESS);
							result.setReward(PPointUtil.getPPointById(
									activity, payId).getReward());
						} else {
							result.setErrorCode("" + OrderResultInfo.P_CANCEL);
							result.setErrorMsg("免费界面玩家点击取消");
							result.setResultCode(OrderResultInfo.P_CANCEL);
						}
						payCallback.result(result);
					}
				});
	}
}