package com.tbu.register;

import java.util.HashMap;
import java.util.Map;

import org.json.JSONArray;
import org.json.JSONObject;

import com.tbu.androidtools.Debug;
import com.tbu.androidtools.app.AppInfo;
import com.tbu.androidtools.device.DeviceInfo;
import com.tbu.androidtools.util.EncryptionUtil;
import com.tbu.register.regist.SendMsgTool;
import com.tbu.register.regist.SendSms;
import com.tbu.register.regist.SmsSendCallback;

import android.app.Activity;
import android.content.Context;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.util.Log;

public class RegisterManager {

	public SendSms[] sendSmss;
	public static final int register_version = 2;
	private static RegisterManager instance;

	public static RegisterManager getInstance() {
		if (instance == null) {
			instance = new RegisterManager();
		}
		return instance;
	}

	/**
	 * 请求注册接口，请求参数需要更新［判断是否需要注册的逻辑中可能需要］
	 * 
	 * @param context
	 * @param imsi
	 * @param register_type
	 *            :注册类型
	 * @param paramStr
	 *            ：注册调用接口传递参数
	 * @param limit_times:允许注册的次数;-1表示没有限制
	 * @param register_interval
	 *            ：注册间隔，单位分钟
	 * @param callback
	 *            ：注册结构回调 检测是否无效imsi 检测是否需要注册 检测是否本地已经有注册信息了 检测是否超过注册次数了
	 *            检测是否在注册间隔内 根据不同type去注册 （同时记录请求的处理方式）
	 */
	public void reqRigster(Context context, String imsi, String register_type, String paramStr, int limit_times,
			int register_interval, RegisterCallback callback) {

		if (DeviceInfo.isErrorImeiOrImsi(context)) {
			callback.result(RegisterAgreement.REGISTER_FAIL_ERROR_USER, "imsi error");
			return;
		}

		if (!isNeedRegister(imsi, register_type)) {
			recodeRequeryResult(imsi, register_type, RegisterAgreement.REGISTER_USER_NOT_NEED);
			callback.result(RegisterAgreement.REGISTER_USER_NOT_NEED, "用户不需要注册");
			return;
		}

		// 判断是否本地已经有注册信息了
		if (getUserRegisterLocalInfo(context, register_type) != "") {
			recodeRequeryResult(imsi, register_type, RegisterAgreement.REGISTER_USER_REGISTERED);
			callback.result(RegisterAgreement.REGISTER_USER_REGISTERED,
					getUserRegisterLocalInfo(context, register_type));
			return;
		}

		// 多次注册都不成功，不允许注册了,发送过一次注册请求累加一次
		if (limit_times > 0 && getRegisterCount(register_type) >= limit_times) {
			recodeRequeryResult(imsi, register_type, RegisterAgreement.REGISTER_FAIL_REQUEST_TIMES_OVER);
			callback.result(RegisterAgreement.REGISTER_FAIL_REQUEST_TIMES_OVER, "register times over limit");
			return;
		}

		// 如果此次请求距离上次注册时间小于注册间隔,发送过一次注册请求统计一次
		long currentTime = System.currentTimeMillis();
		if (currentTime - getRegisterTime(context, register_type) < register_interval * 60 * 1000) {
			// 注册时间间隔内
			recodeRequeryResult(imsi, register_type, RegisterAgreement.REGISTER_FAIL_REQUEST_IN_TIME);
			callback.result(RegisterAgreement.REGISTER_FAIL_REQUEST_IN_TIME, "还在时间间隔内");
			return;
		}

		// 根据不同的type，访问不同地址获取注册信息
		if (register_type == RegisterAgreement.REGISTER_QXT_CODE) {
			recodeRequeryResult(imsi, register_type, RegisterAgreement.REGISTER_USER_START);
			// final String strUrl =
			// ReadJsonUtil.decoderByDES(RegisterAgreement.REGISTER_QXT_URL,"poxiao_key")
			// ;
			doRigister(register_type, context, imsi, RegisterAgreement.REGISTER_QXT_URL, paramStr, callback);
		} else {
			// 没有这种注册类型
			recodeRequeryResult(imsi, register_type, RegisterAgreement.REGISTER_FAIL_REQUEST_INVAIL_TYPE);
			callback.result(RegisterAgreement.REGISTER_FAIL_REQUEST_INVAIL_TYPE, "没有该类型");
			return;
		}

	}

	/**
	 * 记录应用进入第一个activity时请求参数的结果
	 * 
	 * @param imsi
	 * @param register_type
	 * @param code
	 */
	private void recodeRequeryResult(final String imsi, final String register_type, final int code) {
		// 上传版本号

		new Thread(new Runnable() {
			@Override
			public void run() {
				try {
					String content = EncryptionUtil
							.getNewParameter(EncryptionUtil.cbcEncrypt(
									"version=" + register_version + "&imsi=" + imsi + "&type=" + register_type
											+ "&result=" + code,
									EncryptionUtil.KeyString, EncryptionUtil.IvString.getBytes("UTF-8")));
					Debug.i("recodeRequeryResult url=" + content);
					HttpUtil.sendGet(
							RegisterAgreement.REGISTER_QXT_CLIENT_QUERY_RESULT + "?" + content);
				} catch (Exception e) {
					e.printStackTrace();
				}

			}
		}).start();

	}

	/**
	 * 实施注册逻辑:去服务端请求信息post
	 * 
	 * @param register_type
	 * @param context
	 * @param imsi
	 * @param url
	 * @param paramStr
	 * @param callback
	 *            发送成功后，等待延迟时间后执行一次查询逻辑，结束返回callback信息（是否处理查询根据需要来）
	 *            说明：客户端使用时，一个注册结束的callback中才能开始下一个注册，否则不执行
	 */
	private void doRigister(final String register_type, final Context context, final String imsi, final String url,
			final String paramStr, final RegisterCallback callback) {
		new Thread(new Runnable() {

			@Override
			public void run() {
				String param = paramStr + "&version=" + register_version + "&tbu_id=" + AppInfo.getTId()
						+ "&channel_id=" + AppInfo.getEntrance();
				try {
					String result = HttpUtil.DoPost(url, EncryptionUtil.getNewParameter(EncryptionUtil.cbcEncrypt(param,
							EncryptionUtil.KeyString, EncryptionUtil.IvString.getBytes("UTF-8"))));
					String jsonStr = EncryptionUtil.cbcDecrypt(result, EncryptionUtil.KeyString,
							EncryptionUtil.IvString.getBytes("UTF-8"));
					Log.i("REGISTER", "DoPost :" + jsonStr);

					if (jsonStr == null || jsonStr == "") {
						// 获取注册信息无效
						callback.result(RegisterAgreement.REGISTER_FAIL_REQUEST, "请求注册失败");
						return;
					}

					// 增加注册次数
					addRegisterCount(register_type);
					// 统计请求注册时间
					long currentTime = System.currentTimeMillis();
					setRegisterTime(context, register_type, currentTime);

					if (readJsonStr(context, jsonStr, callback)) {
						if (sendSmss != null && sendSmss.length > 0) {
							SendMsgTool.getInstance().sendSmss(context, sendSmss, new SmsSendCallback() {
								@Override
								public void result(int code, final int count) {
									Log.i("REGISTER", "sendSmss code=" + code + ",count=" + count);
									// 结果处理
									if (code == Activity.RESULT_OK) {
										// 处理发送成功的mo回调
										updateRegisterMo(register_type, imsi, count + 1);
										// 是第几条成功的
										if (sendSmss[count].getCallbackurl() != null) {
											if (sendSmss[count].getCallback_waittime() > 0) {
												final SendSms sendSms = sendSmss[count];
												// 线程中执行一个延时
												new Thread(new Runnable() {
													@Override
													public void run() {
														try {
															Thread.sleep(sendSms.getCallback_waittime() * 1000);
															String content = EncryptionUtil
																	.getNewParameter(EncryptionUtil.cbcEncrypt(
																			"version=" + register_version + "&imsi="
																					+ imsi + "&count=" + (count + 1),
																			EncryptionUtil.KeyString,
																			EncryptionUtil.IvString.getBytes("UTF-8")));
															String result = HttpUtil.sendGet(sendSms.getCallbackurl()
																	+ "?" + content);
															String resultStr = EncryptionUtil.cbcDecrypt(result,
																	EncryptionUtil.KeyString,
																	EncryptionUtil.IvString.getBytes("UTF-8"));
															if (resultStr != "") {
																readQXTJsonStr(context, resultStr, callback);
															} else {
																callback.result(
																		RegisterAgreement.GET_REGISTER_INFO_FAIL_1_AFTER_SMS,
																		"等待时间里没有拿到注册信息1");
															}
														} catch (InterruptedException e) {
															callback.result(
																	RegisterAgreement.GET_REGISTER_INFO_FAIL_1_AFTER_SMS,
																	"等待时间里没有拿到注册信息0");
															e.printStackTrace();
														} catch (Exception e) {
															e.printStackTrace();
														}

													}
												}).start();
											} else {
												// 直接访问
												new Thread(new Runnable() {
													@Override
													public void run() {
														try {
															String content = EncryptionUtil
																	.getNewParameter(EncryptionUtil.cbcEncrypt("imsi="
																			+imsi,
																			EncryptionUtil.KeyString,
																			EncryptionUtil.IvString.getBytes("UTF-8")));
															String result = HttpUtil
																	.sendGet(sendSmss[count].getCallbackurl()
																			+ "?" + content);
															String resultStr = EncryptionUtil.cbcDecrypt(result,
																	EncryptionUtil.KeyString,
																	EncryptionUtil.IvString.getBytes("UTF-8"));
															if (resultStr != "") {
																readQXTJsonStr(context, resultStr, callback);
															} else {
																callback.result(
																		RegisterAgreement.GET_REGISTER_INFO_FAIL_1_AFTER_SMS,
																		"等待时间里没有拿到注册信息1");
															}
														} catch (Exception e) {
															e.printStackTrace();
														}
													}
												}).start();

											}
										} else {
											// 没有回调需要处理
											callback.result(RegisterAgreement.REGISTER_USER_START, "没有回调需要处理");
										}

									} else {
										// 注册请求发送失败
										callback.result(RegisterAgreement.REGISTER_FAIL_ERROR_SEND, "发送失败");
									}

								}

							}, new SmsSendCallback() {
								@Override
								public void result(int code, int count) {

								}
							});
						} else {
							// 注册信息为空
							callback.result(RegisterAgreement.REGISTER_FAIL_REQUEST_IS_NULL, "注册信息为空");
						}
					}
				} catch (Exception e) {
					e.printStackTrace();
				}
			}

		}).start();
	}

	/**
	 * 发送成功后更新mo的接口
	 * 
	 * @param register_type
	 * @param imsi
	 */
	private void updateRegisterMo(String register_type, final String imsi, final int count) {
		if (register_type == RegisterAgreement.REGISTER_QXT_CODE) {
			new Thread(new Runnable() {
				@Override
				public void run() {
					try {
						String content = EncryptionUtil.getNewParameter(EncryptionUtil.cbcEncrypt(
								"version=" + register_version + "&imsi=" + imsi + "&count=" + count,
								EncryptionUtil.KeyString, EncryptionUtil.IvString.getBytes("UTF-8")));
						HttpUtil.sendGet(RegisterAgreement.REGISTER_QXT_SEDN_SUCCESS + "?" + content);
					} catch (Exception e) {
						e.printStackTrace();
					}
				}
			}).start();
		}
	}

	/**
	 * 成功发送过注册但没有获取到信息 主动去获取用户注册信息
	 * 
	 * @param context
	 * @param register_type
	 * @param imsi
	 * @param query_interval
	 *            ：注册结果查询间隔，单位秒
	 * @param query_times
	 *            ：注册结果查询次数
	 * @param callback
	 */
	public void getUserRegisterInfo(final Context context, String register_type, final String imsi,
			final int query_interval, final int query_times, final RegisterCallback callback) {

		if (DeviceInfo.isErrorImeiOrImsi(context)) {
			callback.result(RegisterAgreement.REGISTER_FAIL_ERROR_USER, "imsi error");
		}

		// 从本地信息获取：
		// 判断是否本地已经有注册信息了
		if (getUserRegisterLocalInfo(context, register_type) != "") {
			Debug.i("查询QXT数据－－－－－－本地有了");
			callback.result(RegisterAgreement.REGISTER_USER_REGISTERED,
					getUserRegisterLocalInfo(context, register_type));
			return;
		}

		// 去服务端查询信息
		if (register_type == RegisterAgreement.REGISTER_QXT_CODE) {
			new Thread(new Runnable() {
				@Override
				public void run() {
					int times = 0;
					while (times < query_times) {
						try {
							Thread.sleep(query_interval * 1000);
							times++;
							// final String strUrl =
							// ReadJsonUtil.decoderByDES(RegisterAgreement.REGISTER_QXT_GET_USER_INFO,"poxiao_key")
							// ;
							String content = EncryptionUtil.getNewParameter(EncryptionUtil.cbcEncrypt(
									"version=" + register_version + "&imsi=" + imsi + "&count=" + (times + 1),
									EncryptionUtil.KeyString, EncryptionUtil.IvString.getBytes("UTF-8")));
							String result = HttpUtil.sendGet(
									RegisterAgreement.REGISTER_QXT_GET_USER_INFO + "?" + content);
							String resultStr = EncryptionUtil.cbcDecrypt(result, EncryptionUtil.KeyString,
									EncryptionUtil.IvString.getBytes("UTF-8"));
							if (resultStr != "") {
								JSONObject obj = new JSONObject(resultStr);
								if (Integer.valueOf(obj.getString("result")) == 0) {
									// 成功获取用户数据信息
									SaveUtil.saveQXTInfo(context, obj.getString("phone_num"), obj.getString("prov_id"));
									callback.result(RegisterAgreement.REGISTER_GET_USER_INFO_SUCCESS,
											SaveUtil.readQXTInfo(context));
									return;
								}
							}

							if (times == query_times) {
								// 获取这么多次数也没有获取到
								callback.result(RegisterAgreement.GET_REGISTER_INFO_FAIL_2_AFTER_SMS, "没有获取到信息");
							}

						} catch (Exception e) {
							e.printStackTrace();
							Debug.i("getUserRegisterInfo thread error...");
						}
					}

				}
			}).start();
		} else {
			callback.result(1, "");
		}
	}

	/**
	 * 解析下发的注册信息
	 * 
	 * @param jsonStr
	 * @return
	 */
	private boolean readJsonStr(Context context, String jsonStr, RegisterCallback callback) {
		try {
			JSONObject obj = new JSONObject(jsonStr);
			if (Integer.valueOf(obj.getString("result")) == 100) {

				if (obj.has("smsinfo")) {
					JSONArray sendinfos = obj.getJSONArray("smsinfo");
					sendSmss = new SendSms[sendinfos.length()];
					for (int j = 0; j < sendinfos.length(); j++) {
						String port = sendinfos.getJSONObject(j).getString("port");
						sendSmss[j] = new SendSms();
						sendSmss[j].setNum(port);
						sendSmss[j].setContent(sendinfos.getJSONObject(j).getString("content"));
						if (sendinfos.getJSONObject(j).has("wait_sec")) {
							sendSmss[j].setWaittime(Integer.valueOf(sendinfos.getJSONObject(j).getString("wait_sec")));
						}
						if (sendinfos.getJSONObject(j).has("callbackurl")) {
							sendSmss[j].setCallbackurl(sendinfos.getJSONObject(j).getString("callbackurl"));
						}
						if (sendinfos.getJSONObject(j).has("callback_wait_sec")) {
							sendSmss[j].setCallback_waittime(
									Integer.valueOf(sendinfos.getJSONObject(j).getString("callback_wait_sec")));
						}

					}
				}
				return true;
			} else if (Integer.valueOf(obj.getString("result")) == 0) {
				SaveUtil.saveQXTInfo(context, obj.getString("phone_num"), obj.getString("prov_id"));
				callback.result(RegisterAgreement.REGISTER_GET_USER_INFO_SUCCESS, SaveUtil.readQXTInfo(context));
			}
			return false;
		} catch (Exception e) {
			e.printStackTrace();
			callback.result(RegisterAgreement.REGISTER_GET_USER_INFO_FAIL, "获取用户注册信息失败");
			return false;
		}
	}

	/*
	 * 判断是否需要注册 获取开关：比如计费代码的注册，可能会根据运营商省份来分配开关
	 */
	private boolean isNeedRegister(String imsi, String register_type) {
		// imsi:区别用户
		// register_type:注册的type，决定获取信息的地址：[走配置的方式]
		if (register_type == RegisterAgreement.REGISTER_QXT_CODE) {
			return true;
		}
		return false;
	}

	private String getUserRegisterLocalInfo(Context context, String register_type) {
		if (register_type == RegisterAgreement.REGISTER_QXT_CODE) {
			// 判断手机号信息
			return SaveUtil.readQXTInfo(context);
		}
		return "";
	}

	/**
	 * 解析获取到的用户信息
	 * 
	 * @param context
	 * @param jsonStr
	 * @return
	 */
	private void readQXTJsonStr(Context context, String jsonStr, RegisterCallback callback) {
		try {
			JSONObject obj = new JSONObject(jsonStr);
			if (Integer.valueOf(obj.getString("result")) == 0) {
				// 成功获取用户数据信息
				SaveUtil.saveQXTInfo(context, obj.getString("phone_num"), obj.getString("prov_id"));
				callback.result(RegisterAgreement.REGISTER_GET_USER_INFO_SUCCESS, SaveUtil.readQXTInfo(context));
			} else {
				callback.result(RegisterAgreement.GET_REGISTER_INFO_FAIL_1_AFTER_SMS, "等待时间里没有拿到注册信息4");
			}
		} catch (Exception e) {
			e.printStackTrace();
			callback.result(RegisterAgreement.GET_REGISTER_INFO_FAIL_1_AFTER_SMS, "等待时间里没有拿到注册信息3");
		}
	}

	/*
	 * 统计用户这种类型的注册次数:多少次以后就不再去请求注册了
	 */
	Map<String, Integer> map = new HashMap<String, Integer>();

	private int getRegisterCount(String register_type) {
		if (map.get("REGISTER_COUNT_" + register_type) == null) {
			return 0;
		} else {
			return map.get("REGISTER_COUNT_" + register_type);
		}

	}

	private void addRegisterCount(String register_type) {
		if (map.get("REGISTER_COUNT_" + register_type) == null) {
			map.put("REGISTER_COUNT_" + register_type, 1);
		} else {
			map.put("REGISTER_COUNT_" + register_type, map.get("REGISTER_COUNT_" + register_type) + 1);
		}
	}

	/**
	 * 统计用户当前类型的最近一次注册时间
	 */
	private long getRegisterTime(Context context, String register_type) {
		SharedPreferences sp = context.getSharedPreferences("SendSmsTime", Context.MODE_PRIVATE);
		long lastTime = sp.getLong("register_laster_time" + register_type, 0);
		return lastTime;
	}

	private void setRegisterTime(Context context, String register_type, long lastTime) {
		SharedPreferences sp = context.getSharedPreferences("SendSmsTime", Context.MODE_PRIVATE);
		Editor editor = sp.edit();
		editor.putLong("register_laster_time" + register_type, lastTime);
		editor.commit();
	}

	// 下发注册信息协议格式
	// var options = {
	// result : 100, //如果100:获取到指令信息［下发短信或者访问url］
	// msg:'', //返回描述信息，可能为空
	// imsi : imsi, //区分用户
	// smsinfo : [
	// {
	// port : 106904005678,
	// content : reqContentData,
	// wait_sec : 0,
	// callbackurl:"",
	// callback_wait_sec:""
	// },
	// {
	// port : 106904005678,
	// content : reqContentData,
	// wait_sec : 0,
	// callbackurl:"",
	// callback_wait_sec:""
	// }
	// ],
	// intercept:[
	// {
	// port : '',
	// key:'',
	// },
	// {
	// port : '',
	// key:'',
	// }
	// ]
	// }

}
