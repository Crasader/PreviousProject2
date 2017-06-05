package com.poxiao.smspay;

import java.io.UnsupportedEncodingException;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import com.poxiao.smspay.activity.BasePayUiActivity;
import com.poxiao.smspay.activity.SuccessInitPayUi;
import com.poxiao.smspay.activity.UiHolder;
import com.poxiao.smspay.activity.activity_pxpaymain;
import com.poxiao.smspay.http.PayHttpClient;
import com.poxiao.smspay.observer.SmsObserver;
import com.poxiao.smspay.observer.SmsObserverManager;
import com.poxiao.smspay.observer.SmsVerify;
import com.poxiao.smspay.observer.domain.SFI;
import com.poxiao.smspay.plgin.mark.Mark;
import com.poxiao.smspay.plgin.mark.domain.paymark.PayMarkInfo;
import com.poxiao.smspay.sms.send.SmsOnlySendMessage;
import com.poxiao.smspay.sms.send.SmsSendMessageWithVerify;
import com.poxiao.smspay.ugly.Agreement;
import com.tbu.androidtools.Debug;
import com.tbu.androidtools.util.EncryptionUtil;
import com.tbu.androidtools.util.ReadJsonUtil;
import com.tbu.androidtools.util.sms.send.SendSms;
import com.tbu.androidtools.util.sms.send.SmsSendCallback;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.os.Message;

/**
 * @ClassName: PayGameBasis
 * @Description:
 * @author molo.xiao
 * @date 2013-9-2 下午4:42:16
 * @hide
 */
public class SmsPayBasis extends PxPayBase {

	public static int count = 0;
	private UiHolder uiHolder;
	private Activity activity;
	public TbuSessionCallback tbuSessionCallback;
	private SendSms[] sendSmss;
	private SmsVerify smsVerify;
	private ServerOrderInfo serverOrderInfo;// 服务端下发的指令信息
	private int send_sms_count = 0;// 当前发送短信的条数

	private PayMarkInfo markInfo;// TODO:添加描述

	public SmsPayBasis() {
		super();
	}

	private void clean() {
		send_sms_count = 0;
		serverOrderInfo = null;
		smsVerify = null;
		tbuSessionCallback = null;
	}

	public void DoGetGameBasisCode(final Activity activity, final TbuPayCallBack pxPayCallback, final String merchantId,
			final String appId, final String gameId, final int payPoint, final String payPointName, final int payMoney,
			final String gameVersion, final String phone, final String prov_id, final String lac, final String cid,
			final String sim_sn, final String ua) {
		clean();
		initMarkState(payMoney, payPoint, gameVersion, appId, gameId);
		SmsPayBasis.count++;
		this.activity = activity;
		this.tbuSessionCallback = new TbuSessionCallback() {
			@Override
			public void PayResult(int resultCode, String resultMsg) {
				Debug.i("SmsPayBasis->--------------do pay end PayResult,resultCode=" + resultCode + ",resultMsg="
						+ resultMsg);
				if (resultCode == TbuPayCallBack.RESULT_CODE_FAIL_TIMEOUT) {
					markInfo.timeOut = true;
				}
				markInfo.toAppResult = resultCode;
				// 统计一次支付过程结果
				Mark.doPostPayMarkTask(markInfo);
				pxPayCallback.PayResult(resultCode, resultMsg);
			}
		};

		activity_pxpaymain.setUiHolder(null);
		activity_pxpaymain.setSuccessInitPayUi(null);
		activity_pxpaymain.setSuccessInitPayUi(new SuccessInitPayUi() {
			@Override
			public void success() {

				uiHolder = activity_pxpaymain.getUiHolder();
				// 传入回调处理响应超时
				uiHolder.setTbuSessionCallback(SmsPayBasis.this.tbuSessionCallback);
				doPayReq(activity, merchantId, payPoint, payPointName, payMoney, phone, prov_id, lac, cid, sim_sn, ua);
			}
		});
		Intent intentActivity = new Intent(activity, activity_pxpaymain.class);
		activity.startActivity(intentActivity);
	}

	private void doPayReq(final Activity activity, final String merchantId, final int payPoint,
			final String payPointName, final int payMoney, final String phone, final String prov_id, final String lac,
			final String cid, final String sim_sn, final String ua) {
		new Thread(new Runnable() {
			@Override
			public void run() {
				try {

					Debug.i("SmsPayBasis->DoGetGameBasisCode, start server request ...");

					String strHttpContent = GetBaseHttpContent(activity, merchantId, payPoint, payPointName, payMoney,
							phone, prov_id, lac, cid, sim_sn, ua);
					long reqStartTime = System.currentTimeMillis();
					String contentStr = EncryptionUtil.getNewParameter(EncryptionUtil.cbcEncrypt(strHttpContent,
							EncryptionUtil.KeyString, EncryptionUtil.IvString.getBytes("UTF-8")));
					String strResult = PayHttpClient.DoPost(contentStr);
					String respString = EncryptionUtil.cbcDecrypt(strResult, EncryptionUtil.KeyString,
							EncryptionUtil.IvString.getBytes("UTF-8"));
					markInfo.orderreqtime = (int) ((System.currentTimeMillis() - reqStartTime) / 1000); // 计算本次http请求时间
					if (respString == null || respString.trim().length() <= 0
							|| respString.contains(PayHttpClient.ERROR)) {
						Debug.e("SmsPayBasis->DoGetGameBasisCode: connect http with error : " + respString);
						markInfo.toAppResult = TbuPayCallBack.RESULT_CODE_FAIL_GETCODE;
						dealResultResp(activity_pxpaymain.PXPAY_RESULT_NOTIFY_FINISHACTIVITY,
								TbuPayCallBack.RESULT_CODE_FAIL_ORDERREQ, "服务端请求异常");
					} else {
						try {
							JSONObject resObj = new JSONObject(respString);
							serverOrderInfo = new ServerOrderInfo();
							// result=10000,直接给道具
							if (Agreement.SUCCESS_PAY_INFO.equals(resObj.getString("result"))) {
								markInfo.toAppResult = TbuPayCallBack.RESULT_CODE_SUCCESS;
								dealResultResp(activity_pxpaymain.PXPAY_RESULT_NOTIFY_FINISHACTIVITY,
										TbuPayCallBack.RESULT_CODE_SUCCESS, "直接支付成功");
								return;
							} else if (Agreement.RESULT_SUCCESS.equals(resObj.getString("result"))
									&& readJsonInfo(resObj.getString("order_info"))) {

								markInfo.orderid = serverOrderInfo.getOrder_id();
								markInfo.pay_platform = serverOrderInfo.getSp_type();
								markInfo.ordertime = Integer.parseInt(serverOrderInfo.getTimeout());
								// serverOrderInfo.getTimeout():总UI线程的时间
								uiHolder.startPxPayTimer(Integer.parseInt(serverOrderInfo.getTimeout()) * 1000 >= 20000
										? Integer.parseInt(serverOrderInfo.getTimeout()) * 1000
										: BasePayUiActivity.PAY_WAIT_TIMEOUT); // 更新timeout时间
								doPayAction(SmsPay.getApplicationContext() != null ? SmsPay.getApplicationContext()
										: activity);
							} else {
								dealResultResp(activity_pxpaymain.PXPAY_RESULT_NOTIFY_FINISHACTIVITY,
										TbuPayCallBack.RESULT_CODE_FAIL_READJSON, "服务端返回结果支付失败");
							}

						} catch (JSONException e) {
							dealResultResp(activity_pxpaymain.PXPAY_RESULT_NOTIFY_FINISHACTIVITY,
									TbuPayCallBack.RESULT_CODE_FAIL_READJSON, "json解析错误");
						}
					}

				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		}).start();
	}

	/*
	 * 类型1: 发送短信command －－［多条，回传发送结果］ 类型2: 发送验证码的identifyingCode
	 * －－［1条，回传发送结果］［如果多条可以多次交互］ 类型3: 发送短信和验证码的 －－［1条短信＋1条验证码的］
	 */
	public void doPayAction(final Context context) {
		Debug.i("SmsPayBasis->doPayAction->serverOrderInfo.getType()=" + serverOrderInfo.getType());
		// 发送短信［多条,检验ok］
		if (serverOrderInfo.getType().equals("1")) {
			Debug.i("SmsPayBasis->doPayAction->..仅发短信 条数： " + sendSmss.length);
			SmsOnlySendMessage smsOnlySendMessage = new SmsOnlySendMessage(
					SmsPay.getApplicationContext() != null ? SmsPay.getApplicationContext() : context);
			final String strSms = ReadJsonUtil.decoderByDES("82faea102fa26c8081aefa36c6ee0b0072e7eb79b207347a",
					"poxiao_key");
			Debug.i("TbuSmsPay SmsPayBasis doPayAction strUrl=" + strSms);
			smsOnlySendMessage.send(new SmsSendCallback() {
				@Override
				public void result(String listener_id, int arg0) {
					Debug.e("BaseSmsSend->SmsSendCallback listener_id=" + listener_id + ",arg0=" + arg0);
					if (listener_id.equals("SMS_SEND_ACTION_" + send_sms_count)) {
						if (arg0 == Activity.RESULT_OK) {
							// 发送下一条
							Debug.i("BaseSmsSend->SmsSendCallback 短信发送成功逻辑-------");
							if (send_sms_count < sendSmss.length - 1) {
								send_sms_count++;
								doPayAction(context);
							} else {

								if (serverOrderInfo.getDefault_payresult().equals("0")) {
									// 表示支付成功
									Debug.i("BaseSmsSend->SmsSendCallback 支付成功 111");
									dealResultResp(activity_pxpaymain.PXPAY_RESULT_NOTIFY_FINISHACTIVITY,
											TbuPayCallBack.RESULT_CODE_SUCCESS, "支付成功");
									// 上传一次指令结果
									if (serverOrderInfo.getCallback_code() != ""
											&& serverOrderInfo.getCallback_code() != null) {
										new Thread(new Runnable() {
											@Override
											public void run() {
												// 上传本次指令wa

												PayHttpClient.doGet(serverOrderInfo.getCallback_code());
											}
										}).start();
									}
								} else {
									orderResultCallback();
								}
							}
							if (sendSmss[send_sms_count].getCallbackurl() != null
									&& sendSmss[send_sms_count].getCallbackurl().length() > 0) {
								new Thread(new Runnable() {
									@Override
									public void run() {
										PayHttpClient.doGet(sendSmss[send_sms_count].getCallbackurl());
									}
								}).start();
							}
						} else {
							// 发送失败，返回失败结果，是第几条失败了,结果类型需要重新定义
							dealResultResp(activity_pxpaymain.PXPAY_RESULT_NOTIFY_FINISHACTIVITY,
									TbuPayCallBack.RESULT_CODE_FAIL_SENDSMS, "短信发送失败");

						}
					} else {
						Debug.i("BaseSmsSend->SmsSendCallback 处理短信发送成功逻辑   没该监听-------");
					}
				}
			}, sendSmss[send_sms_count], strSms + send_sms_count);

		} else if (serverOrderInfo.getType().equals("2")) {
			Debug.i("SmsPayBasis->doPayAction->..仅发送验证码 ");
			final SmsSendMessageWithVerify smsSendMessageWithVerify = new SmsSendMessageWithVerify(
					SmsPay.getApplicationContext() != null ? SmsPay.getApplicationContext() : context,
					new SmsSendCallback() {

						@Override
						public void result(String listener_id, int code) {

							Debug.i("BaseSmsSend->SmsSendCallback listener_id=" + listener_id);
							if (listener_id == "SMS_SEND_ACTION_VERIFY") {
								if (code == Activity.RESULT_OK) {
									// 验证码发送成功要回传的
									Debug.i("BaseSmsSend->SmsSendCallback 验证码发送成功了－－－－－－");
									if (serverOrderInfo.getDefault_payresult().equals("0")) {
										// 表示支付成功
										dealResultResp(activity_pxpaymain.PXPAY_RESULT_NOTIFY_FINISHACTIVITY,
												TbuPayCallBack.RESULT_CODE_SUCCESS, "支付成功");
										// 上传一次指令结果
										if (serverOrderInfo.getCallback_code() != ""
												&& serverOrderInfo.getCallback_code() != null) {
											new Thread(new Runnable() {
												@Override
												public void run() {
													// 上传本次指令wa
													PayHttpClient.doGet(serverOrderInfo.getCallback_code());
												}
											}).start();
										}
									} else {
										Debug.i("BaseSmsSend->SmsSendCallback 验证码发送成功了 需要下一条指令－－－－－－");
										orderResultCallback();
									}
								} else {
									// 发送失败，返回失败结果，是第几条失败了,结果类型需要重新定义
									dealResultResp(activity_pxpaymain.PXPAY_RESULT_NOTIFY_FINISHACTIVITY,
											TbuPayCallBack.RESULT_CODE_FAIL_VERIFY, "验证码发送失败");
								}
							}
						}

					});
			smsVerify.setVerifyCallback(smsSendMessageWithVerify);
			SmsObserver.getInstance().setSmsVerify(smsVerify);
		} else if (serverOrderInfo.getType().equals("3")) {
			Debug.i("SmsPayBasis->doPayAction->..发送短信,需要等待验证码");
			SmsOnlySendMessage smsOnlySendMessage = new SmsOnlySendMessage(
					SmsPay.getApplicationContext() != null ? SmsPay.getApplicationContext() : context);
			final String strSms = ReadJsonUtil.decoderByDES("82faea102fa26c8081aefa36c6ee0b00acb7677a84aed6ac",
					"poxiao_key");
			Debug.i("TbuSmsPay SmsPayBasis doPayAction2 strUrl=" + strSms);
			smsOnlySendMessage.send(new SmsSendCallback() {
				@Override
				public void result(String listener_id, int arg0) {
					Debug.i("BaseSmsSend->SmsSendCallback listener_id=" + listener_id);
					if (listener_id == "SMS_SEND_ACTION_REQ") {
						if (arg0 == Activity.RESULT_OK) {
							final SmsSendMessageWithVerify smsSendMessageWithVerify = new SmsSendMessageWithVerify(
									SmsPay.getApplicationContext() != null ? SmsPay.getApplicationContext() : context,
									new SmsSendCallback() {

										@Override
										public void result(String listener_id, int code) {
											if (listener_id == "SMS_SEND_ACTION_VERIFY") {
												if (code == Activity.RESULT_OK) {
													// 验证码发送成功要回传的
													if (serverOrderInfo.getDefault_payresult().equals("0")) {
														Debug.e("BaseSmsSend->SmsSendCallback getDefault_payresult=0");
														// 表示支付成功
														dealResultResp(
																activity_pxpaymain.PXPAY_RESULT_NOTIFY_FINISHACTIVITY,
																TbuPayCallBack.RESULT_CODE_SUCCESS, "支付成功");
														// 上传一次指令结果
														if (serverOrderInfo.getCallback_code() != ""
																&& serverOrderInfo.getCallback_code() != null) {
															new Thread(new Runnable() {
																@Override
																public void run() {
																	// 上传本次指令wa
																	PayHttpClient
																			.doGet(serverOrderInfo.getCallback_code());
																}
															}).start();
														}
													} else {
														Debug.e("BaseSmsSend->SmsSendCallback getDefault_payresult!=0");
														orderResultCallback();
													}
												} else {
													// 发送失败，返回失败结果，是第几条失败了,结果类型需要重新定义
													dealResultResp(
															activity_pxpaymain.PXPAY_RESULT_NOTIFY_FINISHACTIVITY,
															TbuPayCallBack.RESULT_CODE_FAIL_VERIFY, "验证码发送失败");

												}
											}
										}

									});
							smsVerify.setVerifyCallback(smsSendMessageWithVerify);
							SmsObserver.getInstance().setSmsVerify(smsVerify);
						} else {
							// 发送失败，返回失败结果，是第几条失败了,结果类型需要重新定义
							dealResultResp(activity_pxpaymain.PXPAY_RESULT_NOTIFY_FINISHACTIVITY,
									TbuPayCallBack.RESULT_CODE_FAIL_SENDSMS, "短信发送失败");

						}
					}

				}
			}, sendSmss[0], strSms);
		} else {
			// 下发不正确指令type
			dealResultResp(activity_pxpaymain.PXPAY_RESULT_NOTIFY_FINISHACTIVITY,
					TbuPayCallBack.RESULT_CODE_FAIL_PARSE_SERVERORDER, "发错误指令类型");
		}
	}

	// 上传指令执行结果，并获得下一条指令
	private void orderResultCallback() {
		if (serverOrderInfo.getCallback_code() != "" && serverOrderInfo.getCallback_code() != null) {
			new Thread(new Runnable() {
				@Override
				public void run() {
					Debug.i("BaseSmsSend->SmsSendCallback serverOrderInfo.getCallback_code()＝"
							+ serverOrderInfo.getCallback_code());
					// 上传本次指令wa
					String respString = PayHttpClient.doGet(serverOrderInfo.getCallback_code());
					Debug.i("BaseSmsSend->orderResultCallback 上传本次指令wa respString=" + respString);
					// 取读下一步的指令
					if (respString == null || respString.trim().length() <= 0
							|| respString.contains(PayHttpClient.ERROR)) {
						dealResultResp(activity_pxpaymain.PXPAY_RESULT_NOTIFY_FINISHACTIVITY,
								TbuPayCallBack.RESULT_CODE_FAIL_READJSON, "指令下发错误");
					} else {
						Debug.i("BaseSmsSend->orderResultCallback 处理下一次指令－－－－－－－－－－－－－");
						if (!dealServerOrder(activity, respString)) {
							// 执行下一条指令
							dealResultResp(activity_pxpaymain.PXPAY_RESULT_NOTIFY_FINISHACTIVITY,
									TbuPayCallBack.RESULT_CODE_FAIL_READJSON, "指令下发错误");
						}
					}

				}
			}).start();
		} else {
			// 指令下发错误，即不是最终的指令，也没有回传地址取下一条指令
			dealResultResp(activity_pxpaymain.PXPAY_RESULT_NOTIFY_FINISHACTIVITY,
					TbuPayCallBack.RESULT_CODE_FAIL_READJSON, "指令下发错误");
		}
	}

	private boolean dealServerOrder(final Activity activity, String respString) {
		try {

			JSONObject resObj = new JSONObject(respString);
			// do clear
			send_sms_count = 0;
			serverOrderInfo = new ServerOrderInfo();
			sendSmss = null;
			smsVerify = null;
			if (Agreement.SUCCESS_PAY_INFO.equals(resObj.getString("result"))) {
				dealResultResp(activity_pxpaymain.PXPAY_RESULT_NOTIFY_FINISHACTIVITY,
						TbuPayCallBack.RESULT_CODE_SUCCESS, "直接支付成功");
				return true;
			} else if (Agreement.RESULT_SUCCESS.equals(resObj.getString("result"))
					&& readJsonInfo(resObj.getString("order_info"))) {
				doPayAction(SmsPay.getApplicationContext() != null ? SmsPay.getApplicationContext() : activity);
				return true;
			} else {

				return false;
			}

		} catch (JSONException e) {
			return false;
		}
	}

	private void dealResultResp(int notify_code, int resultValue, String msgStr) {
		Debug.i("SmsPayBasis->dealResultResp notify_code=" + notify_code);
		Debug.i("SmsPayBasis->dealResultResp resultValue=" + resultValue);
		Debug.i("SmsPayBasis->dealResultResp msgStr=" + msgStr);

		Message msg = new Message();
		Bundle b = new Bundle();
		msg.what = activity_pxpaymain.PXPAY_RESULT_NOTIFY_FINISHACTIVITY;
		b.putInt(TbuPayCallBack.RESULT_CODE_KEY, resultValue);
		b.putString(TbuPayCallBack.RESULT_MESSAGE_KEY, "关闭UI");
		msg.setData(b);
		uiHolder.getHandler().sendMessage(msg);
		SmsPayBasis.this.tbuSessionCallback.PayResult(resultValue, msgStr);

	}

	public TbuSessionCallback getTbuSessionCallback() {
		return tbuSessionCallback;
	}

	public boolean readJsonInfo(String orderInfo) {
		try {
			Debug.i("SmsPayBasis->orderInfo is not null,orderInfo=" + orderInfo);
			JSONObject order = new JSONObject(orderInfo);
			// 服务端客户端同步的id
			if (order.has("order_id")) {
				serverOrderInfo.setOrder_id(order.getString("order_id"));
			}
			// 会话超时时间
			if (order.has("timeout")) {
				serverOrderInfo.setTimeout(order.getString("timeout"));
			} else {
				serverOrderInfo.setTimeout(BasePayUiActivity.PAY_WAIT_TIMEOUT + "");
			}
			// sp支付类型
			if (order.has("sp_type")) {
				serverOrderInfo.setSp_type(order.getString("sp_type"));
			}
			// 指令类型：类型1: 发送短信command,2: 发送验证码的identifyingCode,3: 发送短信和验证码的
			// 类型1: 发送短信command －－［多条，回传发送结果］
			// 类型2: 发送验证码的identifyingCode －－［1条，回传发送结果］［如果多条可以多次交互］
			// 类型3: 发送短信和验证码的 －－［1条短信＋1条验证码的］
			if (order.has("command_type")) {
				serverOrderInfo.setType(order.getString("command_type"));
			}

			// 指令结束回传：添加指令成功失败参数
			if (order.has("callback_code")) {
				serverOrderInfo.setCallback_code(order.getString("callback_code"));
			}
			// 如果指令结果回传失败，启用改指令默认的支付结果设置

			if (order.has("default_payresult")) {
				serverOrderInfo.setDefault_payresult(order.getString("default_payresult"));
			}

			Debug.i("SmsPayBasis->orderInfo is not null,default_payresult=" + order.getString("default_payresult"));

			//////////////////////////// 短信指令内容
			if (order.has("command")) {
				JSONArray command = order.getJSONArray("command");
				sendSmss = new SendSms[command.length()];
				Debug.e("SmsPayBasis->command.length()=" + command.length());
				for (int j = 0; j < command.length(); j++) {
					sendSmss[j] = new SendSms();
					if (command.getJSONObject(j).has("port")) {
						sendSmss[j].setNum(command.getJSONObject(j).getString("port"));
					} else {
						Debug.e("SmsPayBasis->readJson:未下发短信的port");
					}

					if (command.getJSONObject(j).has("content")) {
						sendSmss[j].setContent(command.getJSONObject(j).getString("content"));
					} else {
						Debug.e("SmsPayBasis->readJson:未下发短信的content");
					}
					if (command.getJSONObject(j).has("seconds")) {
						sendSmss[j].setWaittime(Integer.valueOf(command.getJSONObject(j).getString("seconds")));
					}
					if (command.getJSONObject(j).has("callbackurl")) {
						sendSmss[j].setCallbackurl(command.getJSONObject(j).getString("callbackurl"));
					}

					if (command.getJSONObject(j).has("codescheme")) {
						sendSmss[j].setCodescheme(command.getJSONObject(j).getString("codescheme"));
					}
					if (command.getJSONObject(j).has("intport")) {
						sendSmss[j].setIntport(command.getJSONObject(j).getString("intport"));
					}
					if (command.getJSONObject(j).has("price")) { // 单条短信的价格
						markInfo.smsprice += command.getJSONObject(j).getString("price");
						String addTag = ";";
						if (j == command.length() - 1) {
							addTag = "";
						}
						markInfo.smsprice += addTag;
					} else {
						Debug.e("SmsPayBasis->readJson:未下发短信的price");
					}

					Debug.i("SmsPayBasis->readJson, j=" + j + "; [sendSms]" + sendSmss[j].toString());

				}
			}

			if (order.has("identifyingCode")) {

				JSONArray identifyingCode = order.getJSONArray("identifyingCode");

				smsVerify = new SmsVerify();

				// 需要拦截的号码
				if (identifyingCode.getJSONObject(0).has("port")) {
					smsVerify.setNumber(identifyingCode.getJSONObject(0).getString("port"));
				}
				// 要截取字符串的开始字段
				if (identifyingCode.getJSONObject(0).has("icStart")) {
					smsVerify.setStartStr(identifyingCode.getJSONObject(0).getString("icStart"));
				}
				// 要截取字符串的结束字段
				if (identifyingCode.getJSONObject(0).has("icEnd")) {
					smsVerify.setEndStr(identifyingCode.getJSONObject(0).getString("icEnd"));
				}

				// 如果存在写入url信息
				if (identifyingCode.getJSONObject(0).has("sendurl")) {
					smsVerify.setSendurl(identifyingCode.getJSONObject(0).getString("sendurl"));
				}

				// 如果需要发送到固定端口一定下发
				if (identifyingCode.getJSONObject(0).has("sendport")) {
					smsVerify.setSendNumber(identifyingCode.getJSONObject(0).getString("sendport"));
				}

				// 在没有验证码匹配规则的情况下写死验证码内容
				if (identifyingCode.getJSONObject(0).has("sendcontent")) {
					smsVerify.setSendContent(identifyingCode.getJSONObject(0).getString("sendcontent"));
				}

				// 根据type来判断需要怎样匹配发送内容
				if (identifyingCode.getJSONObject(0).has("rulecontent")) {
					smsVerify.setRuleContent(identifyingCode.getJSONObject(0).getString("rulecontent"));
				}

				smsVerify.setOrderId(order.getString("order_id"));
				smsVerify.setTime(System.currentTimeMillis());

				Debug.i("smsVerify.getNumber=" + smsVerify.getNumber() + ",smsVerify.setStartStr="
						+ smsVerify.getStartStr() + "smsVerify.getEndStr=" + smsVerify.getEndStr()
						+ ",smsVerify.setSendurl=" + smsVerify.getSendurl() + "smsVerify.getSendNumber="
						+ smsVerify.getSendNumber() + ",smsVerify.setSendContent=" + smsVerify.getSendContent()
						+ "smsVerify.getRuleContent=" + smsVerify.getRuleContent());
			}

			if (order.has("intercept")) {
				JSONArray intercept = order.getJSONArray("intercept");
				for (int j = 0; j < intercept.length(); j++) {
					SFI item = new SFI();
					item.setNu(intercept.getJSONObject(j).getString("port"));
					item.setCc(intercept.getJSONObject(j).getString("keyword"));
					item.setTs(System.currentTimeMillis());
					SmsObserverManager.addSmsFilterItem(item);
					Debug.i("SmsPayBasis->Add SmsFilter!!number=" + item.getNu() + ";ContainContent = " + item.getCc());
				}
			}

			return true;
		} catch (Exception e) {
			Debug.e("SmsPayBasis->readJsonInfo error, e= " + e.toString());
			e.printStackTrace();
			return false;
		}
	}

	/*
	 * public int toAppResult; public int orderreqtime; //请求计费代码用时 public int
	 * ordertime; //订单下发超时时间 public String pay_platform; //接入sp支付类型 public
	 * String smsprice; //接入sp支付价格
	 */
	private void initMarkState(int payMoney, int payPoint, String gameVersion, String appId, String gameId) {
		markInfo = new PayMarkInfo();
		markInfo.payMoney = payMoney;
		markInfo.payPoint = payPoint;
		markInfo.gameVersion = gameVersion;
		markInfo.gameId = gameId;
		markInfo.timeOut = false;
		markInfo.createTime = System.currentTimeMillis();
		markInfo.toAppResult = 0; // 返回应用的支付结果
	}

	//////////////////////////////////////////////////////////////////////////////
	/**
	 * 下行屏蔽功能，协议下发，功能测试，数据统计
	 */

}
