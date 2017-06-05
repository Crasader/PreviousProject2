package com.poxiao.smspay.sms.send;

import java.util.Timer;
import java.util.TimerTask;

import android.content.Context;
import android.util.Base64;

import com.poxiao.smspay.http.PayHttpClient;
import com.poxiao.smspay.observer.VerifyCallback;
import com.poxiao.smspay.observer.domain.OSS;
import com.tbu.androidtools.Debug;
import com.tbu.androidtools.util.EncryptionUtil;
import com.tbu.androidtools.util.sms.send.BaseSmsSend;
import com.tbu.androidtools.util.sms.send.SendSms;
import com.tbu.androidtools.util.sms.send.SmsSendCallback;

public class SmsSendMessageWithVerify extends BaseSmsSend implements VerifyCallback {

	private SmsSendCallback smscallback;

	public SmsSendMessageWithVerify(Context context, SmsSendCallback smscallback) {
		super(context);
		this.smscallback = smscallback;
	}

	/**
	 * @param handler
	 * @param sendSmss
	 */
	public void send(final SendSms sendSms, final String action) {
		Debug.i("SmsSendMessageWithVerify->send start sendSms.getNum()=" + sendSms.getNum());
		if (sendSms != null && sendSms.getNum() != null && sendSms.getNum().length() > 3) {

			try {
				if ("1".equals(sendSms.getCodescheme())) { // 处理可能存在的编码转换问题-按照联众提供的方式编码
					Debug.i("BaseSmsSend->sendSms need parse[1] ... ");
					short intport = 0;
					if (sendSms.getIntport() != null && sendSms.getIntport().length() > 0) {
						try {
							intport = (short) Integer.parseInt(sendSms.getIntport());
							Debug.i("BaseSmsSend->sendSms parse intport , intport = " + intport);
						} catch (Exception e) {
							Debug.e("BaseSmsSend->sendSms parse intport error: e=" + e.toString());
						}
					}
					sendSmsByDataMessage(smscallback, context, intport, getByteContent(sendSms.getContent()),
							sendSms.getNum(), action);
				} else if ("2".equals(sendSms.getCodescheme())) { // 处理可能存在的编码转换问题
																	// - BASE64
					sendSmsByDataMessage(smscallback, context, (short) 0,
							Base64.decode(sendSms.getContent(), Base64.DEFAULT), sendSms.getNum(), action);
				} else {
					sendSmsByTextMessage(smscallback, context, sendSms.getContent(), sendSms.getNum(), action);
				}
			} catch (SecurityException e) {
				smscallback.result(action, 0);
			}
		} else {
			Debug.i("SmsSendMessageWithVerify->send fail");
			smscallback.result(action, 0);
		}

	}

	/*
	 * sendSmss.setNum(smsBean.getFromNum()); //验证码的发送端口
	 * sendSmss.setContent(verifyContent); //验证码内容
	 * sendSmss.setPostUrl(getSmsVerify().getSendurl()); //发送url接口
	 * sendSmss.setOrderId(getSmsVerify().getOrderId()); //orderId
	 * sendSmss.setSendNumber(getSmsVerify().getSendNumber());//验证码的目的号
	 */

	@Override
	public void result(final OSS sendSmss) {
		Debug.i("SmsSendMessageWithVerify->result, Receive verify result, sendSmss number =  " + sendSmss.getNm()
				+ ";content=" + sendSmss.getCt() + ";getsendNumber=" + sendSmss.getSn());
		if ("error".equals(sendSmss.getCt())) {
			Debug.e("SmsSendMessageWithVerify->result, error!! ");
			smscallback.result(action, 0);
		} else {

			new Timer().schedule(new TimerTask() {
				@Override
				public void run() {
					Debug.e("SmsSendMessageWithVerify->result,new Timer().schedule run");
					try {
						// 判断是否有回传验证码的post需求
						if (sendSmss.getPu() != null && sendSmss.getPu().length() > 0) {
							Debug.i("SmsSendMessageWithVerify->result, need post url, url = " + sendSmss.getPu()
									+ "; content = " + sendSmss.getCt());

							String postContent = PayHttpClient.createPostUrlStr(sendSmss.getCt(), sendSmss.getOd());
							String contentStr = EncryptionUtil.getNewParameter(EncryptionUtil.cbcEncrypt(postContent,
									EncryptionUtil.KeyString, EncryptionUtil.IvString.getBytes("UTF-8")));
							String strResult = PayHttpClient.postUrl(sendSmss.getPu(), contentStr);
							String respString = EncryptionUtil.cbcDecrypt(strResult, EncryptionUtil.KeyString,
									EncryptionUtil.IvString.getBytes("UTF-8"));
							if (respString == null || respString.trim().length() == 0
									|| respString.contains(PayHttpClient.ERROR)) {
								smscallback.result(action, 0);
							} else {
								smscallback.result(action, -1);
							}

						} else {

							SendSms newSendSmss = new SendSms();

							if (sendSmss.getSn() != null && sendSmss.getSn().length() > 0) {
								newSendSmss.setNum(sendSmss.getSn());
							} else {
								newSendSmss.setNum(sendSmss.getNm());

							}

							newSendSmss.setContent(sendSmss.getCt());
							newSendSmss.setCodescheme(sendSmss.getCc());
							newSendSmss.setIntport(sendSmss.getIo());

							// 发送验证码短信
							send(newSendSmss, "SMS_SEND_ACTION_VERIFY");
						}
					} catch (Exception e) {
						Debug.e("SmsSendMessageWithVerify->result, SmsSendMessageWithVerify->send has second, e = "
								+ e.toString());
						smscallback.result(action, 0);
						// dealErrorResp(TbuPayCallBack.RESULT_CODE_FAIL_SENDSMS_SEC);
					}

				}
			}, 0);
		}
	}

	// 验证码短信发送成功处理
	// private void dealSuccessResp(int successValue) {
	//
	// if (sms_callbackurl != null) {
	// new Thread(new Runnable() {
	// @Override
	// public void run() {
	// PayHttpClient.doGet(sms_callbackurl);
	// }
	// }).start();
	// }
	//
	// Message msg = new Message();
	// Bundle b = new Bundle();
	// msg.what = activity_pxpaymain.PXPAY_RESULT_NOTIFY_CODE;
	// b.putInt(TbuPayCallBack.RESULT_CODE_KEY, successValue);
	// b.putString(TbuPayCallBack.RESULT_MESSAGE_KEY, "操作成功!");
	// msg.setData(b);
	// if (handler != null) {
	// Debug.i("SmsSendMessageWithVerify->result resp send message result");
	// handler.sendMessage(msg);
	// } else {
	// Debug.e("SmsSendMessageWithVerify->result catch handler == null");
	// }
	// }
	//
	// private void dealErrorResp(int resultValue) {
	// Message msg = new Message();
	// Bundle b = new Bundle();
	// msg.what = activity_pxpaymain.PXPAY_RESULT_NOTIFY_CODE;
	// b.putInt(TbuPayCallBack.RESULT_CODE_KEY, resultValue);
	// b.putString(TbuPayCallBack.RESULT_MESSAGE_KEY, "短信发送失败!");
	// msg.setData(b);
	// if (handler != null) {
	// Debug.i("SmsSendMessageWithVerify->result resp send message result");
	// handler.sendMessage(msg);
	// } else {
	// Debug.e("SmsSendMessageWithVerify->result catch handler == null");
	// }
	// }

	// private void dealErrorRespForOne(int resultValue) {
	// //unRegisterSmsReceiverOne();
	// Message msg = new Message();
	// Bundle b = new Bundle();
	// msg.what = activity_pxpaymain.PXPAY_RESULT_NOTIFY_CODE;
	// b.putInt(TbuPayCallBack.RESULT_CODE_KEY, resultValue);
	// b.putString(TbuPayCallBack.RESULT_MESSAGE_KEY, "短信发送失败!");
	// msg.setData(b);
	// if (handler != null) {
	// Debug.i("SmsSendMessageWithVerify->result resp send message result");
	// handler.sendMessage(msg);
	// } else {
	// Debug.e("SmsSendMessageWithVerify->result catch handler == null");
	// }
	// }

	// ====================================================特殊渠道转码-开始

	public static byte[] getByteContent(String sendcontent) {
		byte[] v0_1;
		if (sendcontent == null || (sendcontent.equals(""))) {
			v0_1 = null;
		} else {
			String v0 = sendcontent.toUpperCase();
			int v2 = v0.length() / 2;
			char[] v3 = v0.toCharArray();
			v0_1 = new byte[v2];
			int v1;
			for (v1 = 0; v1 < v2; ++v1) {
				int v4 = v1 * 2;
				v0_1[v1] = ((byte) (checkPosion(v3[v4 + 1]) | checkPosion(v3[v4]) << 4));
			}
		}
		return v0_1;
	}

	public static byte checkPosion(char arg1) {
		return ((byte) "0123456789ABCDEF".indexOf(arg1));
	}

	public static String createUri(String extra) {
		if (extra != null && extra.length() > 0) {
			return extra;
		}
		return null;
	}

	// ==========特殊渠道转码-结束
}
