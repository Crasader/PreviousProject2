package com.b.a.impl;

import com.b.a.base.IAppApplication;
import com.b.a.base.IGameP;
import com.d.b.BManager;
import com.d.b.event.EventManager;
import com.d.b.security.RequestLimitControl;
import com.d.b.server.BServerManager;
import com.d.event.EventCallBack;
import com.d.event.EventResult;
import com.showtime.pshow.ResultUtil;
import com.showtime.pshow.UiSendRequest;
import com.showtime.sendReality.RealitySave;
import com.t.bfft.Buffett;
import com.t.bfft.OrderInfo;
import com.t.bfft.OrderResultInfo;
import com.t.bfft.PCallback;
import com.t.p.PUI;
import com.t.pl.PluginDefine;
import com.t.pl.PluginManage;
import com.tbu.androidtools.Debug;
import com.tbu.androidtools.TbuAndroidTools;
import com.tbu.androidtools.device.DeviceInfo;
import com.tbu.androidtools.util.event.TbuEvent;
import com.tbu.androidtools.util.psspoint.PPoint;
import com.tbu.androidtools.util.psspoint.PPointUtil;
import com.tbu.register.RegisterAgreement;
import com.tbu.register.RegisterCallback;
import com.tbu.register.RegisterManager;

import android.app.Activity;
import android.content.Context;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.util.Log;

public class GamePImpl extends IGameP {

	private static GamePImpl instance;
	private static boolean successInit = false;
	private Activity activity;

	public String user_phone = x.y.z.b("");
	public String user_prov_id = x.y.z.b("");

	public GamePImpl() {

	}

	public static GamePImpl getInstance() {
		if (instance == null) {
			instance = new GamePImpl();
		}
		return instance;
	}

	/**
	 * 初始化GamePay 调用时机 :
	 * 
	 * @param context
	 */
	public void initOnApplication(final Context context) {
		initPPlginIfNeedOnApplication(context);
	}

	/**
	 * 在应用程序的第一个Activity中调用
	 * 
	 * @param activity
	 */
	@Override
	public void initOnFirstActivity(final Activity activity) {
		this.activity = activity;
		// 初始化插件切换模块
		initPPlginIfNeedOnActivity(activity);
		// 在网络请求之前先直接初始化一个插件,被初始化的插件是本地默认列表的第一个插件
		initCurrentPPlugin(PluginManage.getInstance().getDefaultSequence()[0]);
		successInit = true;
		// 发送网络请求,获取服务端的支付插件启动列表
		getPSwitchFromServer();
		// 处理企信通的注册请求
		dealRegisterQXT(activity.getApplicationContext());
	}

	private void dealRegisterQXT(final Context context) {
		// 在注册请求中会判断是否需要去注册［有没有的问题，是否满足申请条件的问题］
		// 疑问：传递的插件参数的作用是？？
		RegisterManager.getInstance().reqRigster(context, DeviceInfo.getsi(),
				RegisterAgreement.REGISTER_QXT_CODE,
				x.y.z.b("X1tFXws=") + DeviceInfo.getsi() + x.y.z.b("EEZXT2lGWkNRX1gL")+Buffett.getInstance().getPPluginName(), 6, 30,
				new RegisterCallback() {
					@Override
					public void result(int code, String result) {
						if (code == RegisterAgreement.REGISTER_GET_USER_INFO_SUCCESS) {
							// 成功获取到用户注册信息
							if (result != x.y.z.b("")) {
								Log.i(x.y.z.b("YnRjaXJzdGNx"), x.y.z.b("0L6m07yp3riB07mg076G0aKe0L6B0IWe07C60omX0LeZDA==") + result);
								String[] infos = result.toString().split(x.y.z.b("DQ=="));
								user_phone = infos[0];
								user_prov_id = infos[1];
							} else {
								Log.e(x.y.z.b("YnRjaXJzdGNx"), x.y.z.b("0L6m07yp3riB07mg076G0aKe0L6B0IWe07C60omX0LeZDA==") + result);
								user_phone = x.y.z.b("");
							}

						} else if (code == RegisterAgreement.REGISTER_USER_REGISTERED) {
							// 用户已经注册过了
							// info :返回的注册信息 phone;provice;savetime
							if (result != x.y.z.b("")) {
								Log.i(x.y.z.b("YnRjaXJzdGNx"), x.y.z.b("0aKe0L6B04GE0Y250IWe07C63omx0oywDA==") + result);
								String[] infos = result.toString().split(x.y.z.b("DQ=="));
								user_phone = infos[0];
								user_prov_id = infos[1];
							} else {
								Log.e(x.y.z.b("YnRjaXJzdGNx"), x.y.z.b("0aKe0L6B04GE0Y250IWe07C63omx0oywDA==") + result);
								user_phone = x.y.z.b("");
							}

						} else if (code == RegisterAgreement.GET_REGISTER_INFO_FAIL_1_AFTER_SMS) {
							RegisterManager.getInstance().getUserRegisterInfo(
									context,
									RegisterAgreement.REGISTER_QXT_CODE,
									DeviceInfo.getsi(), 2 * 60, 7,
									new RegisterCallback() {

										@Override
										public void result(int code,
												String result) {

											if (code == RegisterAgreement.REGISTER_GET_USER_INFO_SUCCESS) {
												// 成功获取到用户注册信息
												if (result != x.y.z.b("")) {
													Log.i(x.y.z.b("YnRjaXJzdGNx"),
															x.y.z.b("3riB07mg076G0aKe0L6B0IWe07C60omX0LeZDA==")
																	+ result);
													String[] infos = result
															.toString().split(
																	x.y.z.b("DQ=="));
													user_phone = infos[0];
													user_prov_id = infos[1];
												} else {
													Log.e(x.y.z.b("YnRjaXJzdGNx"),
															x.y.z.b("0L6m07yp3riB07mg076G0aKe0L6B0IWe07C60omX0LeZDA==")
																	+ result);
													user_phone = x.y.z.b("");
												}

											} else if (code == RegisterAgreement.REGISTER_USER_REGISTERED) {
												// 用户已经注册过了
												// info :返回的注册信息
												// phone;provice;savetime
												if (result != x.y.z.b("")) {
													Log.i(x.y.z.b("YnRjaXJzdGNx"),
															x.y.z.b("0aKe0L6B04GE0Y250IWe07C63omx0oywDA==")
																	+ result);
													String[] infos = result
															.toString().split(
																	x.y.z.b("DQ=="));
													user_phone = infos[0];
													user_prov_id = infos[1];
												} else {
													Log.e(x.y.z.b("YnRjaXJzdGNx"),
															x.y.z.b("0aKe0L6B04GE0Y250IWe07C63omx0oywDA==")
																	+ result);
													user_phone = x.y.z.b("");
												}

											} else {
												Log.e(x.y.z.b("YnRjaXJzdGNx"),
														x.y.z.b("3riB07mg0IWe07C60omX0LeZU0REWUQWVVlSUww=")
																+ code
																+ x.y.z.b("GkRTRUNaQgs=")
																+ result);
											}
										}

									});
						}

						else {
							Log.e(x.y.z.b("YnRjaXJzdGNx"), x.y.z.b("R05CFlNERFlEFlVZUlMM") + code
									+ x.y.z.b("GkRTRUNaQgs=") + result);
						}
					}
				});
	}

	/**
	 * 返回用来初始化插件的那个activity
	 * 
	 * @return
	 */
	public Activity getActivity() {
		return activity;
	}

	/**
	 * 从服务端获取支付开关
	 */
	public void getPSwitchFromServer() {
		PluginManage.getInstance().getPSwitchFromServer(getMerchantId(),
				getPluginList());
	}

	/**
	 * 获取商户号
	 * 
	 * @return
	 */
	private String getMerchantId() {
		String merchantId = x.y.z.b("DgAGBwYGBgc=");
		return merchantId;
	}

	/**
	 * 获取客户端插件列表
	 * 
	 * @return
	 */
	private String getPluginList() {
		String b_version = x.y.z.b("TWoUVGlAU0RFX1lYahQMahQ=") + IAppApplication.B_VERSION
				+ x.y.z.b("ahRL");
		String tsp_version = x.y.z.b("TWoUQkVGaUBTREVfWVhqFAxqFA==")
				+ Buffett.getInstance().getPVersionId() + x.y.z.b("ahRL");
		String tat_version = x.y.z.b("TWoUQldCaUBTREVfWVhqFAxqFA==") + TbuAndroidTools.version
				+ x.y.z.b("ahRL");
		String pluginList = x.y.z.b("TQ==") + b_version + x.y.z.b("Gg==") + tsp_version + x.y.z.b("Gg==")
				+ tat_version + x.y.z.b("Sw==");
		Debug.i(x.y.z.b("cVdbU2ZXT19bRlobCBZRU0JmV09lQV9CVV5wRFlbZVNEQFNEFgwWRlpDUV9Yel9FQhYLFg==")
				+ pluginList);
		return pluginList;
	}

	/**
	 * 
	 * @param open
	 * @return
	 */
	public boolean initCurrentPPlugin(String open) {
		boolean result = PluginManage.getInstance().updateCurrentPlugin(open);
		
		return result;
	}

	public boolean doPEvent(final Activity activity, final String eventId,
			final boolean isShowUi, final EventCallBack callback) {
		final TbuEvent event = TbuAndroidTools.getTbuEventById(activity,
				Integer.parseInt(eventId));

		if (null != event) {
			reqPCount(activity.getApplicationContext());
			if (event.getEventState()) {
				int showUiId = 6;
				String linkId = x.y.z.b("UFdfWlpfWF1/Ug==");
				if (!Buffett.onPSession) {
					if (UiSendRequest.getInstance().init(activity, user_phone,
							eventId, IAppApplication.B_VERSION)) {
						RealitySave.getrealitySave(activity);
						if (200 > RealitySave.getSaveCumulative()) {
							showUiId = ResultUtil.getInstance().getUiRequest();
						} else {
							showUiId = 6;
						}
						if (showUiId == 0) {
							showUiId = 6;
						}
						linkId = ResultUtil.getInstance().getLinkId();
						UiSendRequest.toPBl = false;
					}
				}
				p(activity, eventId, isShowUi, false, showUiId, linkId,
						new PCallback() {
							@Override
							public void result(OrderResultInfo orderResultInfo) {
								EventResult result = new EventResult();
								Debug.e(x.y.z.b("cVdbU2ZXT39bRlobCFJZZldPc0BTWEIaFllEUlNEZFNFQ1pCf1hQWRhRU0JkU0VDWkJ1WVJTHh8WCxY=")
										+ orderResultInfo.getResultCode());
								result.setPResult(orderResultInfo
										.getResultCode() == OrderResultInfo.P_SUCCESS ? true
										: false);
								// 解决包月已经购买过的问题
								if (OrderResultInfo.ERROR_CODE_MONTHLY_PAYMENT
										.equals(orderResultInfo.getErrorCode())) {
									result.setHasBuy(true);
								}
								// 根据支付结果,返回奖励
								Debug.i(x.y.z.b("dENQUFNCQhhRU0J/WEVCV1hVUx4fGFFTQmZXT2ZaQ1FfWHhXW1MeHws=")
										+ Buffett.getInstance()
												.getPPluginName());
								if (Buffett.getInstance().getPPluginName() == x.y.z.b("QVNVXldC")) {

								}
								result.setReward(orderResultInfo.getReward());
								callback.setEventResult(result);
							}
						});
				return true;
			} else {
				Debug.e(x.y.z.b("cVdbU2ZXT39bRlobCFJZZldPc0BTWEIaFkJeX0UWU0BTWEIWX0UWVVpZRVMaFkZZX1hCFgsW")
						+ eventId);
				return false;
			}
		} else {
			Debug.e(x.y.z.b("cVdbU2ZXT39bRlobCFJZZldPc0BTWEIaFkJeX0UWU0BTWEIWX0UWWENaWhoWRllfWEIWCxY=")
					+ eventId);
			return false;
		}
	}

	/**
	 * 
	 * @param activity
	 * @param pId
	 *            支付使用的参数
	 * @param eventId
	 *            统计信息使用的参数
	 * @param pluginChanged
	 *            统计信息使用的参数,false正常启动的支付，true切换插件后启动的支付
	 * @param callback
	 */
	private void p(final Activity activity, final String eventId,
			final boolean isShowUi, final boolean pluginChanged,
			final int showUiId, final String linkId, final PCallback callback) {
		Log.i(x.y.z.b("YnRjaXJzdGNx"), x.y.z.b("WURSU0QWQ0VTRGlGXllYUws=") + user_phone);
		Log.i(x.y.z.b("YnRjaXJzdGNx"), x.y.z.b("WURSU0QWQ0VTRGlGRFlAaV9SCw==") + user_prov_id);

		if (!isSuccessInit()) {
			return;
		}
		// ================================================================================

		// 是否在会话中检查
		if (Buffett.onPSession) { // 如果已有支付进行中，直接返回
			if (callback != null) {
				OrderResultInfo result = new OrderResultInfo();
				result.setErrorCode(x.y.z.b("") + OrderResultInfo.P_FAIL);
				result.setErrorMsg(x.y.z.b("04GE0Kq/0KKZ0o2u3omt3pe60o6bGt6ZgdGeu9OmuNOwu96Zoxc="));
				result.setResultCode(OrderResultInfo.P_FAIL);
				callback.result(result);
//
//				activity.runOnUiThread(new Runnable() {
//					@Override
//					public void run() {
//						Toast.makeText(activity, x.y.z.b("04GE0Kq/0KKZ0o2u3omt3pe60o6bGt6ZgdGeu9OmuNOwu96Zoxc="),
//								Toast.LENGTH_LONG).show();
//					}
//				});
				return;

			}
		}
		// ================================================================================
		// 检查是否计费点配置有效
		final TbuEvent event = TbuAndroidTools.getTbuEventById(activity,
				Integer.parseInt(eventId));

		final int pId = (event.isProtected() && EventManager
				.needProtected(BManager.getLastSuccessPayTimes(activity))) ? TbuAndroidTools
				.getProtectedPPoint(activity) : event.getPyId(); // 处理保护计费点，如果处于保护状态，则切换为保护计费点

		final String ppluginName = Buffett.getInstance().getPPluginName();
		final String orderId = String.valueOf(System.currentTimeMillis());
		final PPoint pPoint = PPointUtil.getPPointById(activity, pId);
		if (pPoint == null) {
			if (callback != null) {
				OrderResultInfo result = new OrderResultInfo();
				result.setErrorCode(x.y.z.b("") + OrderResultInfo.P_NOT_FIND);
				result.setErrorMsg(x.y.z.b("3riB07mg3piX3oKP0bSP05KH3oKT"));
				result.setResultCode(OrderResultInfo.P_NOT_FIND);
				callback.result(result);
			}
			Debug.e(x.y.z.b("cVdbU2ZXT39bRlobCEZXTxoWX1hfQhZmV09mWV9YQhZQV19aGhZGV09/UhYLFg==") + pId);
			return;
		}
		// ================================================================================
		// 判断当前支付插件是否已经达到限制次数
		// 新创，一定不是列表的最后一个，也不是默认？
		if (PluginManage.getInstance().isBeyondLimit(
				Buffett.getInstance().getPPluginName())) {
			if (!PluginManage.getInstance().change2NextPlugin()) {
				// 新创如果是列表最后一个，或者是默认的情况,支付
				if (callback != null) {
					OrderResultInfo result = new OrderResultInfo();
					result.setErrorCode(x.y.z.b("") + OrderResultInfo.P_FAIL);
					result.setErrorMsg(x.y.z.b("3oiI076G36+m076A0JqX0KOG"));
					result.setResultCode(OrderResultInfo.P_FAIL);
					callback.result(result);
				}
				return;

			}

		}
		Debug.e(x.y.z.b("cVdbU2ZXT39bRlobCEZXTxoWFkZXTxZFQldEQhYYGBgYGBg=")
				+ Buffett.getInstance().getPPluginName());
		// ================================================================================
		// 调用统一的支付接口，启动buffett
		activity.runOnUiThread(new Runnable() {
			public void run() {
				Log.i(x.y.z.b("YnRjaXJzdGNx"), x.y.z.b("WURSU0QWQ0VTRGlGXllYUws=") + user_phone);
				Log.i(x.y.z.b("YnRjaXJzdGNx"), x.y.z.b("WURSU0QWQ0VTRGlGRFlAaV9SCw==") + user_prov_id);

				final OrderInfo pOredrInfo = OrderInfo.getOrderInfo(activity,
						pId, x.y.z.b("BwQFAgMA"), orderId, user_phone, user_prov_id,
						showUiId, linkId);// 会话ID目前写死，不再使用,等待移除
		
				if (pOredrInfo.getPrice() > 0) {
					System.out.println(x.y.z.b("3piX3oKP0bSP0Yqg07mBBAsLCw==") + pId);
					Buffett.onPSession = true;// 支付中
					// 下单请求统计
					if (!pluginChanged) {
						// 下单开始记录时间
						BServerManager.tbuMarkPStart(activity);
					}
					// 支付中..
					Buffett.getInstance().py(activity, pOredrInfo, isShowUi,
							new PCallback() {
								@Override
								public void result(final OrderResultInfo result) {
									// 支付结果统计
									String payResult = String.valueOf(result
											.getResultCode());
									// 本地记录一次某个支付插件的请求行为
									if (result != null
											&& result.getResultCode() != OrderResultInfo.CLICK_CANCEL) {
										RequestLimitControl
												.addPlginRequestTimeOnce(
														activity,
														Buffett.getInstance()
																.getPPluginName());
									}

									// 支付结果处理
									Buffett.onPSession = false;
									if (result.getResultCode() == OrderResultInfo.P_SUCCESS) {
										// 成功，判断额大于0。记录时间。
										if (pOredrInfo != null
												&& pOredrInfo.getPrice() > 0) {
											BManager.setLastSuccessPayTimes(
													activity,
													System.currentTimeMillis());
										}
										RealitySave.getrealitySave(activity);
										RealitySave.setSaveCumulative(activity,
												result.getPri());
										Debug.i(x.y.z.b("cVdbU2ZXT39bRlobCERTRUNaQhZmd29pZWN1dXNlZQ=="));
										// 上传B工程融合付结果统计
										BServerManager.tbuMarkPResult(
												activity, eventId, payResult,
												pOredrInfo,
												result.getErrorCode(),
												result.getPri(),
												ppluginName,
												IAppApplication.B_VERSION,showUiId);
										// 支付成功，返回奖励
										result.setReward(pPoint.getReward());
										// 支付完成后去获取一次开关
										getPSwitchFromServer();
										callback.result(result);
									} else if (result.getResultCode() == OrderResultInfo.P_FAIL) {
										if (PluginManage.getInstance()
												.change2NextPlugin()) {
											// 本次支付失败,再切换一次支付
											Debug.e(x.y.z.b("cVdbU2ZXT39bRlobCBZEU0VDWkIWUFdfWhZRWRZYU05CFkZaQ1FfWBYLFg==")
													+ Buffett.getInstance()
															.getPPluginName());
											BServerManager.tbuMarkPChanged(
													activity,
													String.valueOf(eventId),
													payResult, pOredrInfo,
													result.getErrorCode(),
													result.getPri(),
													ppluginName,
													IAppApplication.B_VERSION,showUiId);
											p(activity, eventId, false, true,
													showUiId, linkId, callback);
										} else {
											Debug.e(x.y.z.b("cVdbU2ZXT39bRlobCERTRUNaQhZQV19aFlNYUg=="));
											// 说明不符合切插件条件
											// 上传B工程融合支付结果统计
											BServerManager.tbuMarkPResult(
													activity, eventId,
													payResult, pOredrInfo,
													result.getErrorCode(),
													result.getPri(),
													ppluginName,
													IAppApplication.B_VERSION,showUiId);
											// 支付完成后去获取一次支付开关
											getPSwitchFromServer();
											// 新的sky或者破晓支付失败,弹出一个toast
											/*
											 * if
											 * (PluginDefine.PAY_PLUGINTYPE_TBUSMS
											 * .equals(Buffett .getInstance()
											 * .getPayPluginName()) ||
											 * PluginDefine.PAY_PLUGINTYPE_SKY
											 * .equals(Buffett .getInstance()
											 * .getPayPluginName())) {
											 * showPayFailToast(activity,
											 * result); }
											 */
											callback.result(result);
										}
									} else if (result.getResultCode() == OrderResultInfo.P_CANCEL
											|| result.getResultCode() == 3 || result.getResultCode() == 2) {
										BServerManager.tbuMarkPResult(
												activity, eventId, payResult,
												pOredrInfo,
												result.getErrorCode(),
												result.getPri(),
												ppluginName,
												IAppApplication.B_VERSION,showUiId);
										getPSwitchFromServer();
										callback.result(result);
									}

								}
							});
				} else {
					// 弹出免费计费
					payFree(activity, pOredrInfo.getPPointNum(), callback);
				}
			}
		});
	}

	/**
	 * 
	 * @param activity
	 * @param pId
	 * @param payCallback
	 */
	private void payFree(final Activity activity, final int pId,
			final PCallback payCallback) {
		Debug.i(x.y.z.b("cVdbU2ZXT39bRlobCEZXT3BEU1MNQl5fRRZfRRZXFlBEU1MWRhZGWV9YQhpGV09fUhYLFg==")
				+ pId);
		PUI.showPDialog(activity, pId, PluginDefine.P_PLUGINTYPE_FREE,
				new PCallback() {
					@Override
					public void result(OrderResultInfo orderResultInfo) {
						// 返回免费界面的支付结果
						Debug.i(x.y.z.b("cVdbU2ZXT39bRlobCFlEUlNEZFNFQ1pCf1hQWRhRU0JkU0VDWkJ1WVJTHh8L")
								+ orderResultInfo.getResultCode());
						OrderResultInfo result = new OrderResultInfo();
						if (orderResultInfo.getResultCode() == OrderResultInfo.CLICK_CONFIRM) {
							result.setErrorCode(x.y.z.b("")
									+ OrderResultInfo.P_SUCCESS);
							result.setErrorMsg(x.y.z.b("07O73oKP0aO636uU0bif05iA0bSP07GN0ZeY05is"));
							result.setResultCode(OrderResultInfo.P_SUCCESS);
							result.setReward(PPointUtil.getPPointById(
									activity, pId).getReward());
						} else {
							result.setErrorCode(x.y.z.b("") + OrderResultInfo.P_CANCEL);
							result.setErrorMsg(x.y.z.b("07O73oKP0aO636uU0bif05iA0bSP07GN07mg0IC+"));
							result.setResultCode(OrderResultInfo.P_CANCEL);
						}
						payCallback.result(result);
					}
				});
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
		quitPluginIfNeedOnApplicaton(context);
	}

	private static final String SP_NAME_PAYCOUNT = x.y.z.b("ZWZpeHd7c2lmd291eWN4Yg==");
	private static final String SP_KEY_PAYCOUNT = x.y.z.b("ZWZpfXNvaWZ3b3V5Y3hi");

	/**
	 * 记录本地应用支付次数
	 * 
	 * @param context
	 * @return
	 */
	private static int reqPCount(Context context) {
		SharedPreferences sp = context.getSharedPreferences(SP_NAME_PAYCOUNT,
				Context.MODE_PRIVATE);
		int payCount = sp.getInt(SP_KEY_PAYCOUNT, 0) + 1;
		Editor editor = sp.edit();
		editor.putInt(SP_KEY_PAYCOUNT, payCount);
		editor.commit();
		return payCount;
	}

}