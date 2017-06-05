package com.a.b.c.d;

import android.app.Activity;
import android.app.ProgressDialog;
import android.content.Context;

import com.poxiao.smspay.SmsPay;
import com.poxiao.smspay.TbuPayCallBack;
import com.t.bfft.OrderInfo;
import com.t.bfft.OrderResultInfo;
import com.t.bfft.PCallback;
import com.t.bfft.PInterface;
import com.t.p.PUI;
import com.t.pl.PluginDefine;
import com.tbu.androidtools.Debug;
import com.tbu.androidtools.app.AppInfo;
import com.tbu.androidtools.device.DeviceInfo;

public class PSPImpl implements PInterface {

	private boolean secondConfirm = false;// 二次确认开关，默认关闭
	private Activity activity;
	private PCallback callback;
	private static final int UI_SHOW_DEFAULT = 6;// 默认启动界面
	private OrderInfo orderInfo;

	public static final int UI_SHOW_NONE = 1;// 不显示UI界面
	public static final int UI_SHOW_NORMAL = 2;// 显示自定义界面
	public static final int UI_SHOW_HYBIRD = 3;// 显示混合界面
	public static final int UI_SHOW_NORMAL_HYBIRD = 4;// 先显示自定义界面后显示混合界面
	public static final int UI_SHOW_APPLY = 5;// 自定义界面清晰版
	public static final int UI_SHOW_APPLY_MIDDLE = 6;// 自定义界面暗色调版

	private TbuPayCallBack pxPCallback = new TbuPayCallBack() {

		@Override
		public void PayResult(int pxResultCode, String baseMsg) {
			Debug.i("SPImpl->PxPCallBack-----------------:pxResultCode="
					+ pxResultCode);
			OrderResultInfo result = new OrderResultInfo();
			if (pxResultCode == TbuPayCallBack.RESULT_CODE_SUCCESS) {
				result.setResultCode(OrderResultInfo.P_SUCCESS);
				result.setErrorCode("" + pxResultCode);
				result.setPri(orderInfo.getPrice());
				result.setErrorMsg("成功");
			} else {
				result.setResultCode(OrderResultInfo.P_FAIL);
				result.setErrorCode("" + pxResultCode);
				result.setPri(orderInfo.getPrice());
				result.setErrorMsg(baseMsg);
			}
			callback.result(result);
		}
	};

	@Override
	public String getPPluginName() {
		return PluginDefine.P_PLUGINTYPE_TBUSMS;
	}

	@Override
	public int getPVersionId() {
		return Integer.valueOf(SmsPay.PAY_VERSION);
	}

	@Override
	public void py(final Activity activity, final OrderInfo orderInfo,
			boolean isShowUi, final PCallback pCallback) {
		Debug.i("SPImpl->start do p pointId="
				+ orderInfo.getPPointNum());
		this.activity = activity;
		this.callback = pCallback;
		this.orderInfo = orderInfo;

		switch (orderInfo.getShowUiId()) {
		case UI_SHOW_NONE:
			pForPx(orderInfo);
			break;
		case UI_SHOW_NORMAL:
			toPSmsSend(activity, orderInfo, isShowUi, "blackpx");
			break;
		case UI_SHOW_APPLY_MIDDLE:
			toPSmsSend(activity, orderInfo, isShowUi, "px");
			break;
		default:
			toPSmsSend(activity, orderInfo, isShowUi, "px");
			break;
		}
	}

	/**
	 * 
	 * @param activity
	 * @param orderInfo
	 * @param isShowUi
	 * @param pluginname
	 *            **2为黑包界面 统一定义为支付插件缩写，6为主线界面 统一定义为apply+支付插件缩写
	 */
	public void toPSmsSend(final Activity activity,
			final OrderInfo orderInfo, boolean isShowUi, String pluginname) {
		if (isShowUi) {
			try {
				PUI.showPDialog(activity, orderInfo.getPPointNum(),
						pluginname, new PCallback() {
							@Override
							public void result(OrderResultInfo info) {
								if (info.getResultCode() == OrderResultInfo.CLICK_CONFIRM) {
									Debug.i("SmsPImpl.this.secondConfirm="
											+ PSPImpl.this.secondConfirm);
									if (PSPImpl.this.secondConfirm) {
										showTbuConfirm(activity, orderInfo);
									} else {
										pForPx(orderInfo);
									}
								} else if (info.getResultCode() == OrderResultInfo.CLICK_CANCEL) {
									cancelP(callback);
								}
							}

						});
			} catch (Exception e) {
				Debug.i("没有配置type为" + pluginname + "的图片，实际错误：" + e.toString());
				if (pluginname.equals("blackpx")) {
					toPSmsSend(activity, orderInfo, isShowUi, "px");
				} else {
					pForPx(orderInfo);
				}
			}

		} else {
			pForPx(orderInfo);
		}
	}

	public void showTbuConfirm(final Activity activity,
			final OrderInfo orderInfo) {
		try {
			PUI.showPDialog(activity, orderInfo.getPPointNum(),
					PluginDefine.P_PLUGINTYPE_SECOND, new PCallback() {
						@Override
						public void result(OrderResultInfo resultSecond) {
							if (resultSecond.getResultCode() == OrderResultInfo.CLICK_CONFIRM) {
								pForPx(orderInfo);
							} else {
								cancelP(callback);
							}
						}
					});
		} catch (Exception e) {
			Debug.i("没有配置二次界面图片，实际错误：" + e.toString());
			pForPx(orderInfo);
		}

	}

	// 返回取消支付
	private void cancelP(PCallback pCallback) {
		OrderResultInfo result = new OrderResultInfo();
		result.setResultCode(OrderResultInfo.P_CANCEL);
		result.setErrorCode("" + OrderResultInfo.P_CANCEL);
		result.setErrorMsg("取消");
		result.setPri(orderInfo.getPrice());
		pCallback.result(result);
	}

	private void pForPx(OrderInfo orderInfo) {
		try {
			Debug.i("SPImpl->pForPx start -----"
					+ orderInfo.getPrice());
			SmsPay.pay(activity, pxPCallback, PxPluginConfig.getMerchantId(),
					PxPluginConfig.getAppId(), PxPluginConfig.getGameId(),
					orderInfo.getPPointNum(), orderInfo.getProductName(),
					orderInfo.getPrice(), AppInfo.getVersion(),
					orderInfo.getPhoneNum(), orderInfo.getProviceId(),
					DeviceInfo.getLac(), DeviceInfo.getCid(),
					DeviceInfo.getimSerialNumber(), DeviceInfo.getUA());
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	@Override
	public void initPPlugin(Activity activity, boolean secondConfirm) {
		if (activity != null) {
			PxPluginConfig.init(activity);
			this.activity = activity;
			this.secondConfirm = secondConfirm;

		} else {
			Debug.e("SPImpl->initPPlugin, activity is null ");
		}
	}

	public static void init(Context context) {
		Debug.i("SPImpl->init(static), working...");
		SmsPay.init(context);

	}

	public static void quitOnApplication(Context context) {
		Debug.i("SPImpl->quit(static), working...");
		SmsPay.quit(context);
	}

	@Override
	public boolean isSecondConfirm() {
		return this.secondConfirm;
	}
	
	private ProgressDialog m_pDialog;
	/**
	 * 显示支付进度
	 */
	private void showPayProgress(final Activity activity) {
		activity.runOnUiThread(new Runnable() {
			public void run() {
				m_pDialog = new ProgressDialog(activity);
				// 设置进度条风格，风格为圆形，旋转的
				m_pDialog.setMax(UI_SHOW_APPLY);
				m_pDialog.setProgressStyle(ProgressDialog.STYLE_SPINNER);
				// 设置ProgressDialog 标题
				m_pDialog.setTitle("提示");
				// 设置ProgressDialog 的进度条是否不明确
				m_pDialog.setIndeterminate(false);
				// 设置ProgressDialog 是否可以按退回按键取消
				m_pDialog.setCancelable(false);
				// 让ProgressDialog显示
				m_pDialog.show();
			}
		});
	}

	private void removePayProgress() {
		if (null != m_pDialog) {
			m_pDialog.dismiss();
			m_pDialog = null;
		}
	}

}
