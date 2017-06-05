package com.a.b.c.d;

import java.util.HashMap;
import java.util.Map;

import android.app.Activity;
import android.content.Context;
import android.os.Handler;
import android.os.Message;

import com.skymobi.pay.sdk.normal.zimon.EpsApplication;
import com.skymobi.pay.sdk.normal.zimon.EpsEntry;
import com.skymobi.pay.sdk.normal.zimon.event.RecordEvent;
import com.skymobi.pay.sdk.normal.zimon.util.SkyPaySignerInfo;
import com.t.bfft.OrderInfo;
import com.t.bfft.OrderResultInfo;
import com.t.bfft.PCallback;
import com.t.bfft.PInterface;
import com.t.p.PUI;
import com.t.pl.PluginDefine;
import com.tbu.androidtools.Debug;
import com.tbu.androidtools.app.AppInfo;
import com.tbu.androidtools.device.DeviceInfo;

public class SPImpl implements PInterface {

	private boolean secondConfirm = false;// 默认2次
	// 订单参数
	private static final String ORDER_INFO_P_METHOD = "payMethod";
	private static final String ORDER_INFO_SYSTEM_ID = "systemId";
	private static final String ORDER_INFO_CHANNEL_ID = "channelId";
	private static final String ORDER_INFO_P_POINT_NUM = "payPointNum";
	private static final String ORDER_INFO_ORDER_DESC = "orderDesc";
	private static final String ORDER_INFO_GAME_TYPE = "gameType";
	private static final String ORDER_INFO_SKIP_TIP = "order_skipTip";
	private static final String ORDER_INFO_SKIP_RESULT = "order_skipResult";
	private static final String ORDER_INFO_ACCOUNT = "appUserAccount";

	private static final String STRING_MSG_CODE = "msg_code";
	private static final String STRING_ERROR_CODE = "error_code";
	private static final String STRING_P_STATUS = "pay_status";
	private static final String ORDER_INFO_PRICENOTIFYADDRESS = "priceNotifyAddress";

	// 是否使用定制界面
	private static final boolean SKY_USE_APPUI = false;

	private EpsEntry mEpsEntry = null;
	private OrderResultInfo result;
	private OrderInfo orderInfo;
	private PCallback callback;
	private int pPointNum;

	private Handler mPHandler;

	private static final int UI_SHOW_DEFAULT = 6;// 默认启动界面

	public static final int UI_SHOW_NONE = 1;// 不显示UI界面
	public static final int UI_SHOW_NORMAL = 2;// 显示自定义界面
	public static final int UI_SHOW_HYBIRD = 3;// 显示混合界面
	public static final int UI_SHOW_NORMAL_HYBIRD = 4;// 先显示自定义界面后显示混合界面
	public static final int UI_SHOW_APPLY = 5;// 自定义界面清晰版
	public static final int UI_SHOW_APPLY_MIDDLE = 6;// 自定义界面暗色调版

	public SPImpl() {
		mPHandler = new Handler(SPImpl.context.getMainLooper()) {
			@Override
			public void handleMessage(Message msg) {
				super.handleMessage(msg);
				Debug.e("SPImpl->SPImpl, mPHandler msg = " + msg);

				if (msg.what == EpsEntry.MSG_WHAT_TO_APP) {
					String retInfo = (String) msg.obj;
					Map<String, String> map = new HashMap<String, String>();
					String[] keyValues = retInfo.split("&|=");
					for (int i = 0; i < keyValues.length; i = i + 2) {
						map.put(keyValues[i], keyValues[i + 1]);
					}

					int msgCode = Integer.parseInt(map.get(STRING_MSG_CODE));
					// 解析付费状态和已付费价格
					// 使用其中一种方式请删掉另外一种
					if (msgCode == 100) {

						// 短信付费返回
						if (map.get(STRING_P_STATUS) != null) {
							int pStatus = Integer.parseInt(map
									.get(STRING_P_STATUS));
							int errcrCode = 0;
							if (map.get(STRING_ERROR_CODE) != null) {
								errcrCode = Integer.parseInt(map
										.get(STRING_ERROR_CODE));
							}
							if (errcrCode == 503 || errcrCode == 805
									|| errcrCode == 508 || errcrCode == 506
									|| errcrCode == 592) {
								result.setErrorCode(String.valueOf(errcrCode));
								result.setErrorMsg("取消");
								result.setResultCode(3);
								result.setSequence(orderInfo.getSequence());
								result.setPri(PInfoConfigS.getPInfos(
										pPointNum)
										.getPr());
								callback.result(result);
							} else {
								switch (pStatus) {
								case 102:
									result.setErrorCode("0");
									result.setErrorMsg("成功");
									result.setResultCode(0);
									result.setPri(PInfoConfigS
											.getPInfos(pPointNum)
											.getPr());
									result.setSequence(orderInfo.getSequence());
									callback.result(result);
									break;
								case 101:
									result.setErrorCode(String
											.valueOf(errcrCode));
									result.setErrorMsg("失败：" + errcrCode);
									result.setResultCode(1);
									result.setSequence(orderInfo.getSequence());
									result.setPri(PInfoConfigS
											.getPInfos(pPointNum)
											.getPr());
									callback.result(result);
									break;
								}
							}
						}
					} else if (msgCode == 101) {
						int errcrCode = Integer.parseInt(map
								.get(STRING_ERROR_CODE));
						if (errcrCode == 1999) {
							// 用户处于包月状态
							result.setErrorCode(OrderResultInfo.ERROR_CODE_MONTHLY_PAYMENT);
							result.setErrorMsg("已经是包月用户：" + errcrCode);
							result.setResultCode(0);
							result.setSequence(orderInfo.getSequence());
							result.setPri(PInfoConfigS.getPInfos(
									pPointNum)
									.getPr());
							callback.result(result);
						} else if (errcrCode == 503 || errcrCode == 805
								|| errcrCode == 508 || errcrCode == 506
								|| errcrCode == 592) {
							result.setErrorCode(String.valueOf(errcrCode));
							result.setErrorMsg("取消");
							result.setResultCode(-3);
							result.setSequence(orderInfo.getSequence());
							result.setPri(PInfoConfigS.getPInfos(
									pPointNum)
									.getPr());
							callback.result(result);
						} else {
							result.setErrorCode(String.valueOf(errcrCode));
							result.setErrorMsg("失败：" + errcrCode);
							result.setResultCode(1);
							result.setSequence(orderInfo.getSequence());
							result.setPri(PInfoConfigS.getPInfos(
									pPointNum)
									.getPr());
							callback.result(result);
						}
					} else {
						// 解析错误码
						int errcrCode = Integer.parseInt(map
								.get(STRING_ERROR_CODE));
						if (errcrCode == 503 || errcrCode == 805
								|| errcrCode == 508 || errcrCode == 506
								|| errcrCode == 592) {
							result.setErrorCode(String.valueOf(errcrCode));
							result.setErrorMsg("取消");
							result.setResultCode(3);
							result.setSequence(orderInfo.getSequence());
							result.setPri(PInfoConfigS.getPInfos(
									pPointNum).getPr());
							callback.result(result);
						} else {
							result.setErrorCode(String.valueOf(errcrCode));
							result.setErrorMsg("失败：" + errcrCode);
							result.setResultCode(1);
							result.setSequence(orderInfo.getSequence());
							result.setPri(PInfoConfigS.getPInfos(
									pPointNum).getPr());
							callback.result(result);
						}
					}
				} else {
					result.setErrorCode("" + msg.what);
					result.setErrorMsg("失败");
					result.setResultCode(1);
					result.setSequence(orderInfo.getSequence());
					result.setPri(PInfoConfigS.getPInfos(pPointNum).getPr());
					callback.result(result);
				}
			}
		};
	}

	@Override
	public String getPPluginName() {
		return PluginDefine.P_PLUGINTYPE_SKY;
	}

	@Override
	public int getPVersionId() {
		return 10019;
	}

	@Override
	public void initPPlugin(Activity activity, boolean secondConfirm) {
		System.out.println("secondConfirm=====:" + secondConfirm);
		this.secondConfirm = secondConfirm;
		SPluginConfig.init(activity);
		PInfoConfigS.init(activity);
		initOnApplication(SPImpl.context);
	}

	@Override
	public void py(final Activity activity, final OrderInfo orderInfo,
			boolean isShowUi, final PCallback callback) {
		this.callback = callback;
		System.out.println("s-->" + orderInfo.toString());
		switch (orderInfo.getShowUiId()) {
		case UI_SHOW_NONE:
			pForS(activity, orderInfo);
			break;
		case UI_SHOW_NORMAL:
			toPSSend(activity, orderInfo, isShowUi, callback, "blacks");
			break;
		case UI_SHOW_APPLY_MIDDLE:
			toPSSend(activity, orderInfo, isShowUi, callback, "s");
			break;
		default:
			toPSSend(activity, orderInfo, isShowUi, callback, "s");
			break;
		}
	}

	public void toPSSend(final Activity activity,
			final OrderInfo orderInfo, boolean isShowUi,
			final PCallback callback, String sId) {
		if (isShowUi) {
			try {
				PUI.showPDialog(activity, orderInfo.getPPointNum(),
						sId, new PCallback() {
							@Override
							public void result(OrderResultInfo info) {
								Debug.i("SPImpl->SPImpl, resultCode = "
										+ info.getResultCode());
								if (info.getResultCode() == OrderResultInfo.CLICK_CONFIRM) {
									// 正式支付开始,分为有2次和无2次
									if (SPImpl.this.secondConfirm) {
										System.out
												.println("SPImpl.this.secondConfirm+====:"
														+ SPImpl.this.secondConfirm);

										showSecondConfirm(activity,orderInfo,
												callback);

									} else {
										pForS(activity, orderInfo);
									}
								} else if (info.getResultCode() == OrderResultInfo.CLICK_CANCEL) {
									cancelP(
											callback,
											PInfoConfigS.getPInfos(
													orderInfo.getPPointNum()).getPr(),
											OrderResultInfo.P_CANCEL);
								}
							}


						});
			} catch (Exception e) {
				Debug.i("没有配置type为" + sId + "的图片，实际错误："+e.toString());
				if (sId.equals("blacks")) {
					toPSSend(activity, orderInfo, isShowUi, callback, "s");
				} else {
					pForS(activity, orderInfo);
				}

			}
		} else {
			pForS(activity, orderInfo);
		}
	}

	public void showSecondConfirm(final Activity activity,final OrderInfo orderInfo,
			 final PCallback callback) {

		try {
			PUI.showPDialog(activity, orderInfo.getPPointNum(),
					PluginDefine.P_PLUGINTYPE_SECOND, new PCallback() {
						@Override
						public void result(OrderResultInfo info) {
							if (info.getResultCode() == OrderResultInfo.CLICK_CONFIRM) {
								pForS(activity, orderInfo);
							} else if (info.getResultCode() == OrderResultInfo.CLICK_CANCEL) {
								cancelP(
										callback,
										PInfoConfigS.getPInfos(
												orderInfo.getPPointNum()).getPr(), 2);
							}
						}
					});
		} catch (Exception e) {
			Debug.i("没有配置二次界面图片，实际错误："+e.toString());
			pForS(activity, orderInfo);
		}
	}

	// 返回取消支付
	private void cancelP(PCallback pCallback, int realm, int pCancel) {
		OrderResultInfo result = new OrderResultInfo();
		result.setResultCode(pCancel);
		result.setErrorCode("" + pCancel);
		result.setErrorMsg("取消");
		result.setPri(realm);
		pCallback.result(result);
	}

	private void pForS(Activity activity, OrderInfo order) {
		if (PInfoConfigS.isExsit()) {
			pPointNum = order.getPPointNum();
			PInfoS pi = PInfoConfigS.getPInfos(pPointNum);
			order.setPPointNum(pi.getSId());
			order.setPrice(pi.getPr());
		} else {
			Debug.i("SPImpl->没有找到pinfos.josn");
		}
		Debug.i("SPImpl->startP Z... ");
		result = new OrderResultInfo();
		this.orderInfo = order;
		mEpsEntry = EpsEntry.getInstance();
		String pmethod = "sms";
		String merchantId = SPluginConfig.getSPInfo().getMerchantId();
		String merchantPasswd = SPluginConfig.getSPInfo()
				.getMerchantPasswd();
		String orderId = order.getOrderId();
		String appId = String.valueOf(SPluginConfig.getSPInfo()
				.getAppId());
		String appName = AppInfo.getAppName(); // 游戏名称
		String appVersion = AppInfo.getVersion(); // 游戏版本号
		String systemId = "300024";
		String channelId = AppInfo.getEntrance();
	
		String pri = String.valueOf(orderInfo.getPrice());
		String pType = "1";

		/*
		 * 注解A 如果配置服务端，由取消下面注解 notifyAddress设置CP的回调地址 reserved1 reserved2
		 * reserved3 扩展字段，会随地址一起同步到CP的服务端 以http get的方式同步给CP端，具体回调参数看文档
		 */

		String notifyAddress = "http://www.notify.com";
		String reserved1 = "reserved1";
		String reserved2 = "reserved2";
		String reserved3 = "reserved3|=2/3";

		reserved1 = order.getPPointNum() + "";
		reserved2 = order.getProductName();
		// 10.自动生成订单签名
		SkyPaySignerInfo sPSignerInfo = new SkyPaySignerInfo();

		sPSignerInfo.setMerchantPasswd(merchantPasswd);
		sPSignerInfo.setMerchantId(merchantId);
		sPSignerInfo.setAppId(appId);
		sPSignerInfo.setAppName(appName);
		sPSignerInfo.setAppVersion(appVersion);
		sPSignerInfo.setPayType(pType);
		sPSignerInfo.setPrice(pri);
		sPSignerInfo.setOrderId(orderId);

		// 注解B 如果配置了服务端，则取消如下四条注解

		sPSignerInfo.setNotifyAddress(notifyAddress);
		sPSignerInfo.setReserved1(reserved1, true);
		sPSignerInfo.setReserved2(reserved2, true);
		sPSignerInfo.setReserved3(reserved3, true);

		String pPointNum = String.valueOf(order.getPPointNum());
		String gameType = "2"; // 0-单机、1-联网、2-弱联网
		String signOrderInfo = sPSignerInfo.getOrderString();

		String orderInfo = ORDER_INFO_P_METHOD + "=" + pmethod + "&"
				+ ORDER_INFO_SYSTEM_ID + "=" + systemId + "&"
				+ ORDER_INFO_CHANNEL_ID + "=" + channelId + "&"
				+ ORDER_INFO_P_POINT_NUM + "=" + pPointNum + "&"
				+ ORDER_INFO_GAME_TYPE
				+ "="
				+ gameType
				+ "&"
				// 注解C 如果配置了服务端，则取消该条注解
				+ ORDER_INFO_PRICENOTIFYADDRESS + "=" + notifyAddress + "&"
				+ "useAppUI=" + SKY_USE_APPUI + "&" + ORDER_INFO_SKIP_TIP + "="
				+ true + "&" + ORDER_INFO_SKIP_RESULT + "=" + true + "&"
				+ ORDER_INFO_ACCOUNT + "=" + DeviceInfo.getsi() + "&"
				+ signOrderInfo;

		Debug.i("SPImpl->pForS,orderInfo = " + orderInfo);

		String orderDesc = order.getOrderDesc();

		orderInfo += "&" + ORDER_INFO_ORDER_DESC + "=" + orderDesc;

		int payRet = mEpsEntry.startPay(activity, orderInfo, mPHandler);
		if (EpsEntry.PAY_RETURN_SUCCESS == payRet) {
			// 初始化成功
			Debug.i("SPImpl->Z init Success... ");
		} else {
			// 未初始化 \ 传入参数有误 \ 服务正处于付费状态
			Debug.e("SPImpl->Z init fail... ");
			result.setErrorCode(String.valueOf(payRet));
			result.setErrorMsg("服务正处于状态或传入参数为空");
			result.setResultCode(1);
			result.setSequence(order.getSequence());
			result.setPri(PInfoConfigS.getPInfos(
					order.getPPointNum()).getPr());
			callback.result(result);
		}
	}

	private static Context context;
	private static EpsApplication espApplaction = new EpsApplication();

	public static void init(Context context) {
		Debug.i("SPImpl->init(static), working...");
		SPImpl.context = context;
		SPluginConfig.init(context);
		PInfoConfigS.init(context);
	}

	private static boolean initOnApplicationSuccess = false;

	private static void initOnApplication(Context context) {
		if (!initOnApplicationSuccess) {
			try {
				espApplaction.onStart(context);
				initOnApplicationSuccess = true;
			} catch (Exception e) {
				Debug.e("SPImpl->init(static), e  = " + e.toString());
			}
			// 实现指盟统计入口
			RecordEvent event = new RecordEvent(RecordEvent.Type_Start_Exit);
			event.put(RecordEvent.KEY_Action, RecordEvent.Action_Start);
			event.upload(context);
			Debug.i("SPImpl->init(static);z start app RecordEvent");
		}
	}

	public static void quitOnActivity(Context context) {
		// 实现指盟统计入口
		RecordEvent event = new RecordEvent(RecordEvent.Type_Start_Exit);
		event.put(RecordEvent.KEY_Action, RecordEvent.Action_Exit);
		event.upload(context);
		Debug.i("SPImpl->init(static);exitApp upload");
	}

	@Override
	public boolean isSecondConfirm() {
		return this.secondConfirm;
	}
}
