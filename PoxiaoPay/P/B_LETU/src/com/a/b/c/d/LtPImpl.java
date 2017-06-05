package com.a.b.c.d;

import java.util.HashMap;
import java.util.Map;

import android.app.Activity;
import android.content.Context;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.os.Handler;
import android.os.Message;
import android.os.SystemClock;

import com.lyhtgh.pay.SdkPayServer;
import com.lyhtgh.pay.application.PayApplication;
import com.t.bfft.OrderInfo;
import com.t.bfft.OrderResultInfo;
import com.t.bfft.PCallback;
import com.t.bfft.PInterface;
import com.t.p.PUI;
import com.t.pl.PluginDefine;
import com.tbu.androidtools.Debug;

public class LtPImpl implements PInterface {

	private boolean secondConfirm = false;// 二次确认界面，默认关闭
	private static final int REQUEST_FIRST = 0; // 第1次请求支付
	private static final int REQUEST_SECOND = 1; // 第2次请求支付,在乐途支付时发现初始化失败则再请求一次。

	private static phandle mPHandler = null;
	private OrderInfo orderInfo;
	private PCallback altCallback;

	SdkPayServer mPServer = SdkPayServer.getInstance();

	private static boolean hasInitSuccess = false;
	private static boolean hasInit = false;
	private static String altChannelId = "";

	private static final int UI_SHOW_DEFAULT = 6;// 默认启动界面

	public static final int UI_SHOW_NONE = 1;// 不显示UI界面
	public static final int UI_SHOW_NORMAL = 2;// 显示自定义界面
	public static final int UI_SHOW_HYBIRD = 3;// 显示混合界面
	public static final int UI_SHOW_NORMAL_HYBIRD = 4;// 先显示自定义界面后显示混合界面
	public static final int UI_SHOW_APPLY = 5;// 自定义界面清晰版
	public static final int UI_SHOW_APPLY_MIDDLE = 6;// 自定义界面暗色调版

	@Override
	public void py(final Activity activity, final OrderInfo orderInfo,
			boolean isShowUi, final PCallback callback) {
		this.orderInfo = orderInfo;
		this.altCallback = callback;
		switch (orderInfo.getShowUiId()) {
		case UI_SHOW_NONE:
			apForLt(activity, REQUEST_SECOND);
			break;
		case UI_SHOW_NORMAL:
			atoPLTS(activity, orderInfo, isShowUi, "blacklt");
			break;

		case UI_SHOW_APPLY_MIDDLE:
			atoPLTS(activity, orderInfo, isShowUi, "lt");
			break;
		default:
			atoPLTS(activity, orderInfo, isShowUi, "lt");
			break;
		}
	}

	public void atoPLTS(final Activity activity, final OrderInfo orderInfo,
			boolean isShowUi, final String ltUi) {
		if (isShowUi) {
			try {
				PUI.showPDialog(activity, orderInfo.getPPointNum(), ltUi,
						new PCallback() {
							@Override
							public void result(OrderResultInfo info) {
								Debug.i("LtP Ui Result, resultCode = "
										+ info.getResultCode());

								if (info.getResultCode() == OrderResultInfo.CLICK_CONFIRM) {

									// 返回点击确定
									if (LtPImpl.this.secondConfirm) {

										asLtCf(activity, orderInfo);
									} else {
										apForLt(activity, REQUEST_SECOND);

									}
								} else if (info.getResultCode() == OrderResultInfo.CLICK_CANCEL) {

									cancelP(altCallback,
											OrderResultInfo.P_CANCEL);
									mPServer.cancelSdkServerPay(activity,
											OrderInfo2String(orderInfo));
								}
							}

						});
			} catch (Exception e) {

				Debug.i("没有配置type为" + ltUi + "的图片，实际错误：" + e.toString());
				if (ltUi.equals("blacklt")) {

					atoPLTS(activity, orderInfo, isShowUi, "lt");
				} else {

					apForLt(activity, REQUEST_SECOND);
				}
			}

		} else {
			apForLt(activity, REQUEST_SECOND);
		}
	}

	public void asLtCf(final Activity activity, final OrderInfo orderInfo) {
		try {
			PUI.showPDialog(activity, orderInfo.getPPointNum(),
					PluginDefine.P_PLUGINTYPE_SECOND, new PCallback() {
						@Override
						public void result(OrderResultInfo resultSecond) {
							if (resultSecond.getResultCode() == OrderResultInfo.CLICK_CONFIRM) {
								apForLt(activity, REQUEST_SECOND);
							} else {
								cancelP(altCallback, 2);
								mPServer.cancelSdkServerPay(activity,
										OrderInfo2String(orderInfo));
							}
						}
					});
		} catch (Exception e) {
			Debug.i("没有配置二次界面图片，实际错误：" + e.toString());
			apForLt(activity, REQUEST_SECOND);
		}
	}

	// 返回取消支付
	private void cancelP(PCallback apCallback, int apCancel) {
		OrderResultInfo result = new OrderResultInfo();
		result.setResultCode(apCancel);
		result.setErrorCode("" + apCancel);
		result.setErrorMsg("取消");
		result.setPri(RealPInfoConfigLt.getPInfos(orderInfo.getPPointNum())
				.getPr());
		apCallback.result(result);
	}

	private String OrderInfo2String(final OrderInfo orderInfo) {
		String apm = String.valueOf(orderInfo.getPPointNum());
		try {
			String ltPId = String.valueOf(RealPInfoConfigLt.getPInfos(
					orderInfo.getPPointNum()).getLtPId());
			if (!ltPId.equals("0")) {
				apm = ltPId;
			}
		} catch (Exception e) {
			e.toString();
		}

		return apm;
	}

	// 乐途的下单实现
	private void apForLt(Activity activity, int tryCount) {
		final LtPInfo ltPInfo = LtPluginConfig.getLtPInfo();
		mPHandler = new phandle();
		if (!hasInitSuccess) {
			int initRet = SdkPayServer.getInstance().initSdkPayServer();
			if (initRet == 0) {
				// 乐途付费实例初始化成功！
				Debug.i("LtPImpl->pForLt, [not init before]success init lt p plgin");
				hasInitSuccess = true;
			} else {
				// 服务正处于付费状态 或 传入参数为空
				Debug.e("LtPImpl->pForLt, [not init before]Lt PImpl fail, initRet = "
						+ initRet);
				hasInitSuccess = false;
				OrderResultInfo result = new OrderResultInfo();
				result.setErrorCode(String.valueOf(initRet));
				result.setErrorMsg("支付初始化失败");
				result.setResultCode(OrderResultInfo.P_FAIL);
				result.setSequence(orderInfo.getSequence());
				result.setPri(RealPInfoConfigLt.getPInfos(
						orderInfo.getPPointNum()).getPr());
				altCallback.result(result);
				return;
			}
		}
		Debug.i("LtPImpl->pForLt,start ...>>"+OrderInfo2String(orderInfo));
		String appId = ltPInfo.getAppId(); // "3030003";
		int re = mPServer.startSdkSmsPay(activity, mPHandler,
				ltPInfo.getMerchantKey(),
				appId + "-" + SystemClock.elapsedRealtime(), altChannelId,
				OrderInfo2String(orderInfo), "noFailedUI=true");
		if (re != 0) {
			Debug.e("LtPImpl->pForLt, p fail, result = " + re);
		}
		if (re == 3 && tryCount == REQUEST_FIRST) { // 3表示初始化未成功
			Debug.e("LtPImpl->pForLt, p fail, because fuck lt result = " + re);
			hasInitSuccess = false;
			apForLt(activity, REQUEST_SECOND);
		}

	}

	class phandle extends Handler {

		@Override
		public void handleMessage(Message msg) {
			super.handleMessage(msg);

			if (msg.what == SdkPayServer.MSG_WHAT_TO_APP) {
				String retInfo = (String) msg.obj;
				Debug.e("LtPImpl->Handler,插件返回的内容为:" + retInfo);
				Map<String, String> map = new HashMap<String, String>();

				String[] keyValues = retInfo.split("&|=");
				for (int i = 0; i < keyValues.length; i = i + 2) {
					map.put(keyValues[i], keyValues[i + 1]);
				}
				Debug.i("消息MAP数量为:" + map.size());
				String msgCode = map.get(SdkPayServer.PAYRET_KEY_RESULT_STATUS);
				// 解析付费状态和已付费价格
				// 使用其中一种方式请删掉另外一种
				if (msgCode != null
						&& Integer.valueOf(msgCode) == SdkPayServer.PAY_RESULT_SUCCESS) {
					OrderResultInfo result = new OrderResultInfo();
					result.setErrorCode("0");
					result.setErrorMsg("成功");
					result.setResultCode(0);
					result.setPri(RealPInfoConfigLt.getPInfos(
							orderInfo.getPPointNum()).getPr());
					result.setSequence(orderInfo.getSequence());
					altCallback.result(result);

				} else {
					OrderResultInfo result = new OrderResultInfo();
					result.setErrorCode(map
							.get(SdkPayServer.PAYRET_KEY_FAILED_CODE));
					result.setErrorMsg("失败："
							+ map.get(SdkPayServer.PAYRET_KEY_FAILED_CODE));
					Debug.i("LtPImpl->Handler,SdkPayServer.PAYRET_KEY_FAILED_CODE="
							+ map.get(SdkPayServer.PAYRET_KEY_FAILED_CODE));
					result.setResultCode(OrderResultInfo.P_FAIL);
					result.setPri(RealPInfoConfigLt.getPInfos(
							orderInfo.getPPointNum()).getPr());
					result.setSequence(orderInfo.getSequence());
					altCallback.result(result);
				}
			}
		}
	}

	@Override
	public String getPPluginName() {
		return PluginDefine.P_PLUGINTYPE_LETU;
	}

	@Override
	public int getPVersionId() {
		return 1031;
	}

	@Override
	public void initPPlugin(Activity activity, boolean secondConfirm) {
		Debug.i("LtPImpl->initPPlgin, start ...");
		initOnApplication(LtPImpl.applicationContext);
		if (null != activity) {
			this.secondConfirm = secondConfirm;
			LtPluginConfig.init(activity);
			RealPInfoConfigLt.init(activity);
			Debug.i("LtPImpl->initPPlgin,[before] hasInitSuccess = "
					+ hasInitSuccess);
			if (hasInit) {
				Debug.w("LtPImpl->initPPlgin,[before] hasInited please not init again ");
				return;
			}
			hasInit = true;
			if (!hasInitSuccess) {
				int initRet = SdkPayServer.getInstance().initSdkPayServer();
				if (initRet == 0) {
					Debug.i("LtPImpl->initPPlgin, success init sdk, initRet = "
							+ initRet);
					hasInitSuccess = true;
				} else {
					hasInitSuccess = false;
					Debug.e("LtPImpl->initPPlgin, fail init sdk, initRet = "
							+ initRet);
				}
			}
		} else {
			Debug.i("LtPImpl->initPPlgin, parameter activity is null");
		}
	}

	private static PayApplication pApplicaton = new PayApplication();

	private static Context applicationContext;

	public static void init(Context context) {
		LtPImpl.applicationContext = context;
		Debug.i("LtPImpl->init(static), working...");
	}

	private static boolean initApplicationSuccess = false;

	private static void initOnApplication(Context context) {
		if (!initApplicationSuccess) {
			Debug.i("LtPImpl->init(static), working...");
			altChannelId = getChannelId(context);
			try {
				pApplicaton.a(context);
				initApplicationSuccess = true;
			} catch (Exception e) {
				Debug.e("LtPImpl->init(static), e  = " + e.toString());
			}
		}
	}

	private static String getChannelId(Context context) {
		if (null == context) {
			Debug.e("LtPImpl->getChannelId,param context is null");
			return "unknow";
		}
		try {
			ApplicationInfo appInfo = context.getPackageManager()
					.getApplicationInfo(context.getPackageName(),
							PackageManager.GET_META_DATA);
			if (null != appInfo) {
				return appInfo.metaData.getString("lltt_cpchannelid");
			} else {
				Debug.e("LtPImpl->getChannelId, ApplicationInfo is null");
				return "unknow";
			}
		} catch (NameNotFoundException e) {
			e.printStackTrace();
			Debug.e("LtPImpl->getChannelId,get ApplicationInfo fail");
			return "unknow";
		}
	}

	@Override
	public boolean isSecondConfirm() {
		return false;
	}
}