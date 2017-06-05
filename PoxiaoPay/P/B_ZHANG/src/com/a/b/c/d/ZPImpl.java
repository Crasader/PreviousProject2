package com.a.b.c.d;

import java.util.HashMap;
import java.util.Map;

import android.app.Activity;
import android.content.Context;
import android.os.Handler;

import com.t.bfft.OrderInfo;
import com.t.bfft.OrderResultInfo;
import com.t.bfft.PCallback;
import com.t.bfft.PInterface;
import com.t.p.PUI;
import com.t.pl.PluginDefine;
import com.tbu.androidtools.Debug;
import com.tbu.androidtools.app.AppInfo;
import com.zhangzhifu.sdk.ZhangPayCallback;
import com.zhangzhifu.sdk.ZhangPaySdk;

public class ZPImpl implements PInterface {

	private boolean second_confirm = false;
	private OrderResultInfo ori;
	private PCallback pCallback;
	private Handler handler;
	private static Context context;
	private OrderInfo orderInfo;

	private static final int UI_SHOW_DEFAULT = 6;// 默认启动界面

	public static final int UI_SHOW_NONE = 1;// 不显示UI界面
	public static final int UI_SHOW_NORMAL = 2;// 显示自定义界面
	public static final int UI_SHOW_HYBIRD = 3;// 显示混合界面
	public static final int UI_SHOW_NORMAL_HYBIRD = 4;// 先显示自定义界面后显示混合界面
	public static final int UI_SHOW_APPLY = 5;// 自定义界面清晰版
	public static final int UI_SHOW_APPLY_MIDDLE = 6;// 自定义界面暗色调版

	@Override
	public String getPPluginName() {
		return PluginDefine.P_PLUGINTYPE_ZP;
	}

	@Override
	public int getPVersionId() {
		return 0;
	}

	@Override
	public void py(final Activity activity, final OrderInfo orderInfo,
			boolean isShowUi, final PCallback pCallback) {
		this.pCallback = pCallback;
		this.orderInfo = orderInfo;
		ori = new OrderResultInfo();
		switch (orderInfo.getShowUiId()) {
		case UI_SHOW_NONE:
			p2Z(activity, orderInfo);
			break;
		case UI_SHOW_NORMAL:
			toPZSend(activity, orderInfo, isShowUi, pCallback,
					"blackz");
			break;

		case UI_SHOW_APPLY_MIDDLE:
			toPZSend(activity, orderInfo, isShowUi, pCallback, "z");
			break;
		default:
			toPZSend(activity, orderInfo, isShowUi, pCallback, "z");
			break;
		}

	}

	public void toPZSend(final Activity activity,
			final OrderInfo orderInfo, boolean isShowUi,
			final PCallback pCallback, String zid) {
		if (isShowUi) {
			try {
				PUI.showPDialog(activity, orderInfo.getPPointNum(),
						zid, new PCallback() {
							@Override
							public void result(OrderResultInfo orderResultInfo) {
								if (orderResultInfo.getResultCode() == OrderResultInfo.CLICK_CONFIRM) {
									if (ZPImpl.this.second_confirm) {
										showSecondConfirm(activity, orderInfo,
												pCallback);
									} else {
										p2Z(activity, orderInfo);
									}
								} else {
									ori.setResultCode(OrderResultInfo.P_CANCEL);
									ori.setErrorCode(""
											+ OrderResultInfo.P_CANCEL);
									ori.setErrorMsg("支付");
									ori.setPri(Integer.parseInt(RealPInfoConfigZ
											.getPInfos(
													String.valueOf(orderInfo
															.getPPointNum()))
											.getPri()));
									pCallback.result(ori);
								}
							}

						});
			} catch (Exception e) {
				Debug.i("没有配置type为" + zid + "的图片，实际错误：" + e.toString());
				if (zid.equals("blackz")) {
					toPZSend(activity, orderInfo, isShowUi, pCallback,
							"z");
				} else {
					p2Z(activity, orderInfo);
				}
			}

		} else {
			p2Z(activity, orderInfo);
		}
	}

	public void showSecondConfirm(final Activity activity,
			final OrderInfo orderInfo, final PCallback pCallback) {
		try {
			PUI.showPDialog(activity, orderInfo.getPPointNum(),
					PluginDefine.P_PLUGINTYPE_SECOND, new PCallback() {
						@Override
						public void result(OrderResultInfo res) {
							if (res.getResultCode() == OrderResultInfo.CLICK_CONFIRM) {
								p2Z(activity, orderInfo);
							} else {
								ori.setResultCode(2);
								ori.setErrorCode("" + 2);
								ori.setErrorMsg("二次界面取消");
								ori.setPri(Integer.parseInt(RealPInfoConfigZ
										.getPInfos(
												String.valueOf(orderInfo
														.getPPointNum()))
										.getPri()));
								pCallback.result(ori);
							}
						}
					});
		} catch (Exception e) {
			Debug.i("没有配置二次界面图片，实际错误：" + e.toString());
			p2Z(activity, orderInfo);
		}

	}

	private boolean hasResult = false;

	private void p2Z(final Activity activity, final OrderInfo orderInfo) {
		activity.runOnUiThread(new Runnable() {
			public void run() {
				Map<String, String> map = getMapConfig(orderInfo);
				Debug.e("z p content : " + map.toString());
				hasResult = false;
				ZhangPaySdk.getInstance().pay(activity, map, callBack, true);
			}
		});
	}

	private Map<String, String> map = new HashMap<String, String>();

	private Map<String, String> getMapConfig(OrderInfo orderInfo) {
		map.put("channelId", ZBaseConfig.getZPInfo().getChannelId());
		map.put("key", ZBaseConfig.getZPInfo().getKey());
		map.put("appId", ZBaseConfig.getZPInfo().getAppId());
		map.put("appName", AppInfo.getAppName());
		map.put("appVersion", AppInfo.getVersion());
		map.put("priciePointId",
				RealPInfoConfigZ.getPInfos(
						String.valueOf(orderInfo.getPPointNum()))
						.getZhangId());
		map.put("money",
				RealPInfoConfigZ.getPInfos(
						String.valueOf(orderInfo.getPPointNum())).getPri());
		map.put("priciePointDec", orderInfo.getOrderDesc());
		map.put("priciePointName", orderInfo.getProductName());
		map.put("qd", ZBaseConfig.getZPInfo().getQd());
		map.put("cpparam", "");

		return map;
	}

	private ZhangPayCallback callBack = new ZhangPayCallback() {

		@Override
		public void onZhangPayBuyProductOK(String priciePointId, String okCode) {
			Debug.i("成功！响应码：" + okCode + "，计费id：" + priciePointId);
			// Message msg = new Message();
			// msg.what = Integer.parseInt(okCode);
			// handler.sendMessage(msg);
			if (!hasResult) {
				ori = new OrderResultInfo();
				ori.setResultCode(OrderResultInfo.P_SUCCESS);
				ori.setErrorCode("" + OrderResultInfo.P_SUCCESS);
				ori.setErrorMsg("成功!");
				ori.setPri(Integer.parseInt(RealPInfoConfigZ
						.getPInfos(String.valueOf(orderInfo.getPPointNum()))
						.getPri()));
				pCallback.result(ori);
				hasResult = true;
			}
		}

		@Override
		public void onZhangPayBuyProductFaild(String priciePointId,
				String errorCode) {
			Debug.e("失败！响应码：" + errorCode + "，计费id：" + priciePointId);
			// Message msg = new Message();
			// msg.what = Integer.parseInt(errorCode);
			// handler.sendMessage(msg);
			if (!hasResult) {
				ori = new OrderResultInfo();
				ori.setResultCode(OrderResultInfo.P_FAIL);
				ori.setErrorCode("" + errorCode);
				ori.setErrorMsg("失败!");
				ori.setPri(Integer.parseInt(RealPInfoConfigZ
						.getPInfos(String.valueOf(orderInfo.getPPointNum()))
						.getPri()));
				pCallback.result(ori);
				hasResult = true;
			}
		}

	};

	@Override
	public void initPPlugin(Activity activity, boolean secondConfirm) {
		Debug.i("ZPImpl -> initPPlugin...");
		this.second_confirm=secondConfirm;
		System.out.println("getChannelId==="
				+ ZBaseConfig.getZPInfo().getChannelId() + "getAppId"
				+ ZBaseConfig.getZPInfo().getAppId() + "getQd==="
				+ ZBaseConfig.getZPInfo().getQd());
		ZhangPaySdk.getInstance().init(activity,
				ZBaseConfig.getZPInfo().getChannelId(),
				ZBaseConfig.getZPInfo().getAppId(),
				ZBaseConfig.getZPInfo().getQd());
	}

	@Override
	public boolean isSecondConfirm() {
		return false;
	}

	public static void init(Context context) {
		Debug.i("ZPImpl -> init...");
		ZPImpl.context = context;
		ZBaseConfig.init(context);
		RealPInfoConfigZ.init(context);
	}

	// public ZhangPayImpl() {
	// handler = new Handler(ZhangPayImpl.context.getMainLooper()) {
	// @Override
	// public void handleMessage(Message msg) {
	// super.handleMessage(msg);
	// switch (msg.what) {
	// case 1001:
	// returnSuccess();
	// Debug.i("客户端计费付费短信发送成功，可以下发道具，实际以服务端为准");
	// break;
	// // case 990:
	// // Debug.i("同一天发短信次数超过设定值");
	// // break;
	// // case 991:
	// // Debug.i("请求计费数据间隔太短，请在10秒后请求");
	// // break;
	// // case 1002:
	// // Debug.i("用户取消操作，计费失败");
	// // break;
	// // case 1004:
	// // Debug.i("调用间隔太短（调用间隔为10秒）");
	// // break;
	// // case 1005:
	// // Debug.i("超过一天付费的值");
	// // break;
	// // case 1006:
	// // Debug.i("没有sim卡，请检查");
	// // break;
	// // case 1007:
	// // Debug.i("网络连接失败，请检查");
	// // break;
	// // case 1008:
	// // Debug.i("下载付费协议失败，网络连接失败或参数不正确");
	// // break;
	// // case 10091:
	// // Debug.i("没有成功解析数据计费失败，该计费点没有匹配相应的扣费通道");
	// // break;
	// // case 10092:
	// // Debug.i("没有成功解析数据计费失败，该手机号码被列入黑名单");
	// // break;
	// // case 10093:
	// // Debug.i("有成功解析数据计费失败， 没有相应的计费点");
	// // break;
	// //
	// // case 10094:
	// // Debug.i("没有成功解析数据计费失败，验签错误");
	// // break;
	// // case 10095:
	// // Debug.i("没有成功解析数据计费失败，key秘钥异常");
	// // break;
	// // case 10096:
	// // Debug.i("没有成功解析数据计费失败，系统资费异常");
	// // break;
	// // case 10097:
	// // Debug.i("没有成功解析数据计费失败，未知错误");
	// // break;
	// // case 10098:
	// // Debug.i("请求超过月限的设定");
	// // break;
	// // case 10099:
	// // Debug.i("请求超过日限的设定，请明天再来");
	// // break;
	// // case 100910:
	// // Debug.i("实时数据超过月限的设定");
	// // break;
	// // case 100911:
	// // Debug.i("实时数据超过日限的设定，请明天再来");
	// // break;
	// // case 100912:
	// // Debug.i("请求过于频繁，请稍后重试");
	// // break;
	// //
	// // case 1010:
	// // Debug.i("短信没有发出，用户拒绝或是安全软件拦截，下次请允许");
	// // break;
	// // case 1011:
	// // Debug.i("没有获得结果，可能是阻止了短信发送");
	// // break;
	// // case 1012:
	// // Debug.i("没有获得结果，可能是阻止了短信发送");
	// // break;
	// default:
	// returnFail();
	// break;
	// }
	// }
	//
	// };
	// }

	// private void returnSuccess() {
	// ori = new OrderResultInfo();
	// ori.setResultCode(OrderResultInfo.PAY_SUCCESS);
	// ori.setErrorCode("" + OrderResultInfo.PAY_SUCCESS);
	// ori.setErrorMsg("支付成功!");
	// payCallback.result(ori);
	// }

	// private void returnFail() {
	// ori = new OrderResultInfo();
	// ori.setResultCode(OrderResultInfo.PAY_FAIL);
	// ori.setErrorCode("" + OrderResultInfo.PAY_FAIL);
	// ori.setErrorMsg("支付失败!");
	// payCallback.result(ori);
	// }
}
