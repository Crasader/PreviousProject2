package com.d.b.server;

import java.io.UnsupportedEncodingException;
import java.net.URLEncoder;

import android.content.Context;

import com.t.bfft.Buffett;
import com.t.bfft.OrderInfo;
import com.tbu.androidtools.Debug;
import com.tbu.androidtools.TbuAndroidTools;
import com.tbu.androidtools.app.AppInfo;
import com.tbu.androidtools.device.DeviceInfo;
import com.tbu.androidtools.ugly.http.KeyValue;
import com.tbu.androidtools.util.EncryptionUtil;
import com.tbu.androidtools.util.event.TbuEvent;
import com.tbu.androidtools.util.psspoint.PPoint;

/**
 * B工程统计信息记录工具类
 * 
 * @author molo
 * 
 */
public class BServerManager {

	public static final String POST_P_MARK_URL = x.y.z.b("XkJCRgwZGQcOBRgHBQcYAQ4YAQ8MBwMGBRlUWldVXWlBXl9CUxlGV09pRlpDUV9YaV9YUFk=");

	private static final String P_TYPE_REQUEST = x.y.z.b("Bg=="); // 请求
	private static final String P_TYPE_REPAY = x.y.z.b("Bg=="); // 切换支付插件
	private static final String P_TYPE_RESULT = x.y.z.b("Bw=="); // 支付结果
	private static final String P_TYPE_ERROR_USER = x.y.z.b("Ag==");// 异常imei或者imsi用户

	private static String orderId = null;
	private static long startTime = 0;
	private static int serialId = 0;

	public static void tbuMarkPStart(Context context) {
		orderId = BServerManager.createNewOrderId();
		startTime = System.currentTimeMillis();
	}

	public static void tbuMarkPChanged(Context context, String eventId,
			String pResult, OrderInfo pOredrInfo, String errorCode,
			int realMoey, String paypluginName, String bVersion, int uitype) {
		TbuEvent event = TbuAndroidTools.getTbuEventById(context,
				Integer.valueOf(eventId));
		PPoint pPoint = TbuAndroidTools.getPPointById(context,
				Integer.valueOf(event.getPyId()));
		if (orderId == null) {
			orderId = BServerManager.createNewOrderId();
		}
		boolean pTypeTwice = Buffett.getInstance().isSecondConfirm();
		if (null != orderId) {
			serialId = serialId + 1;
			long time = System.currentTimeMillis() - startTime;
			String payInfo = BServerManager.createPayInfo(context, orderId,
					pOredrInfo.getLinkId(), pResult, (int) (time / 1000),
					BServerManager.P_TYPE_REPAY, paypluginName, pTypeTwice,
					String.valueOf(event.getPyId()), pPoint.getName(),
					pPoint.getMoey(), realMoey, uitype,
					pOredrInfo.getPhoneNum(), eventId, errorCode, serialId,
					bVersion);
			BServerManager.remarkPayOnBackground(context,
					BServerManager.P_TYPE_REPAY, payInfo, 0);
		}
	}

	public static void tbuMarkPResult(Context context, String eventId,
			String pResult, OrderInfo payOredrInfo, String errorCode,
			int realMoey, String paypluginName, String bVersion, int uitype) {
		TbuEvent event = TbuAndroidTools.getTbuEventById(context,
				Integer.valueOf(eventId));
		PPoint pPoint = TbuAndroidTools.getPPointById(context,
				Integer.valueOf(event.getPyId()));
		boolean pTypeTwice = Buffett.getInstance().isSecondConfirm();
		if (orderId == null) {
			orderId = BServerManager.createNewOrderId();
		}
		if (null != orderId) {
			serialId = serialId + 1;
			long time = System.currentTimeMillis() - startTime;
			String payInfo = BServerManager.createPayInfo(context, orderId,
					payOredrInfo.getLinkId(), pResult, (int) (time / 1000),
					BServerManager.P_TYPE_RESULT, paypluginName, pTypeTwice,
					String.valueOf(event.getPyId()), pPoint.getName(),
					pPoint.getMoey(), realMoey, uitype,
					payOredrInfo.getPhoneNum(), eventId, errorCode, serialId,
					bVersion);
			BServerManager.remarkPayOnBackground(context,
					BServerManager.P_TYPE_RESULT, payInfo, 1);
			serialId = 0;
			startTime = System.currentTimeMillis();
			orderId = null;
		}
	}

	/**
	 * 
	 * @param context
	 * @param orderId
	 *            订单号
	 * @param linkId
	 *            订单标识
	 * @param pResult
	 *            支结果
	 * @param sessionTime
	 *            支会话时间
	 * @param pType
	 *            订单类型（0下单||切换；1 结果）
	 * @param pPluginName
	 *            当前插件名称
	 * @param pTypeTwice
	 *            是否开了二次
	 * @param pPintId
	 *            计费点编号
	 * @param pPintName
	 *            计费点名称
	 * @param moey
	 *            请求支金额
	 * @param realMoey
	 *            实际支金额
	 * @param uitype
	 *            游戏计费点界面1 直接启sdk（无界面）；2 黑包；6 主线包（沿用之前黑白包一套的定义）
	 * @param phone
	 *            手机号
	 * @param eventId
	 *            事件点
	 * @param errorCode
	 *            支结果码
	 * @return
	 */

	private static String createPayInfo(Context context, String orderId,
			String linkId, String pResult, int sessionTime, String pType,
			String pPluginName, boolean pTypeTwice, String pPintId,
			String pPointName, int moey, int realMoey, int uitype,
			String phone, String eventId, String errorCode, int serialId,
			String bVersion) {
		KeyValue keyValue1 = new KeyValue(x.y.z.b("WURSU0RpX1I="), orderId);
		KeyValue keyValue2 = new KeyValue(x.y.z.b("Wl9YXWlfUg=="), linkId);
		KeyValue keyValue3 = new KeyValue(x.y.z.b("VV5XWFhTWmlfUg=="), AppInfo.getEntrance());
		KeyValue keyValue4 = new KeyValue(x.y.z.b("QlRDaV9S"), AppInfo.getTId());
		KeyValue keyValue5;
		try {
			keyValue5 = new KeyValue(x.y.z.b("V0ZGaVhXW1M="), URLEncoder.encode(
					AppInfo.getAppName(), x.y.z.b("Q0JQGw4=")));
		} catch (UnsupportedEncodingException e) {
			keyValue5 = new KeyValue(x.y.z.b("V0ZGaVhXW1M="), AppInfo.getAppName());
			Debug.i(x.y.z.b("dGVTREBTRHtXWFdRU0QbCFVEU1dCU0Z/WFBZGhZFU0IWV0ZGaVhXW1MWUFdfWhgWUxYLFg==")
					+ e.toString());
		}
		KeyValue keyValue6 = new KeyValue(x.y.z.b("UVdbU2lAU0RFX1lY"), AppInfo.getVersion());
		KeyValue keyValue7 = new KeyValue(x.y.z.b("RmlGWV9YQmlfUg=="), pPintId);
		KeyValue keyValue8;
		try {
			keyValue8 = new KeyValue(x.y.z.b("RmlGWV9YQmlYV1tT"), URLEncoder.encode(
					pPointName, x.y.z.b("Q0JQGw4=")));
		} catch (UnsupportedEncodingException e) {
			keyValue8 = new KeyValue(x.y.z.b("RmlGWV9YQmlYV1tT"), pPointName);
			Debug.i(x.y.z.b("dGVTREBTRHtXWFdRU0QbCFVEU1dCU0Z/WFBZGhZFU0IWV0ZGaVhXW1MWUFdfWhgWUxYLFg==")
					+ e.toString());
		}
		KeyValue keyValue9 = new KeyValue(x.y.z.b("U0BTWEJpX1I="), eventId);
		KeyValue keyValue10 = new KeyValue(x.y.z.b("RkJPRlNpQkFfVVM="),
				pTypeTwice ? String.valueOf(0) : String.valueOf(1));
		KeyValue keyValue11;

		try {
			keyValue11 = new KeyValue(x.y.z.b("RmlEU0VDWkI="), URLEncoder.encode(pResult,
					x.y.z.b("Q0JQGw4=")));

		} catch (UnsupportedEncodingException e) {
			keyValue11 = new KeyValue(x.y.z.b("RmlEU0VDWkI="), pResult);
			Debug.i(x.y.z.b("dGVTREBTRHtXWFdRU0QbCFVEU1dCU0Z/WFBZGhZFU0IWRmlEU0VDWkIWUFdfWhgWUxYLFg==")
					+ e.toString());
		}
		KeyValue keyValue12 = new KeyValue(x.y.z.b("U0REWURpVVlSUw=="), errorCode);
		KeyValue keyValue13 = new KeyValue(x.y.z.b("RmlGWkNRX1hpWFdbUw=="), pPluginName);
		KeyValue keyValue14 = new KeyValue(x.y.z.b("W1lYU08="), String.valueOf(moey));
		KeyValue keyValue15;
		if (realMoey != 0) {
			keyValue15 = new KeyValue(x.y.z.b("RFNXWmlbWVhTTw=="), String.valueOf(realMoey));
		} else {
			keyValue15 = new KeyValue(x.y.z.b("RFNXWmlbWVhTTw=="), String.valueOf(moey));
		}
		KeyValue keyValue16 = new KeyValue(x.y.z.b("RVNFRV9ZWA=="),
				String.valueOf(sessionTime));
		KeyValue keyValue17 = new KeyValue(x.y.z.b("Q19pQk9GUw=="), String.valueOf(uitype));
		KeyValue keyValue18 = new KeyValue(x.y.z.b("RVNEX1daaV9S"),
				String.valueOf(serialId));
		KeyValue keyValue19;
		if (DeviceInfo.isErrorImeiOrImsi(context)) {
			keyValue19 = new KeyValue(x.y.z.b("RmlCT0ZT"), String.valueOf(pType));
		} else {
			keyValue19 = new KeyValue(x.y.z.b("RmlCT0ZT"), String.valueOf(pType));
		}
		KeyValue keyValue20 = new KeyValue(x.y.z.b("X1VVX1I="),
				DeviceInfo.getimSerialNumber());
		KeyValue keyValue21 = new KeyValue(x.y.z.b("RV8="), DeviceInfo.getsi());
		KeyValue keyValue22 = new KeyValue(x.y.z.b("U18="), DeviceInfo.getei());
		KeyValue keyValue23 = new KeyValue(x.y.z.b("RlpXQlBZRFtpQFNERV9ZWA=="),
				DeviceInfo.getPlatformVersion());
		KeyValue keyValue24 = new KeyValue(x.y.z.b("Rl5ZWFM="), phone);
		KeyValue keyValue25 = new KeyValue(x.y.z.b("XlJpQk9GUw=="), DeviceInfo.getModle());
		KeyValue keyValue26 = new KeyValue(x.y.z.b("XlJpUFdVQllETw=="),
				DeviceInfo.getProduct());
		KeyValue keyValue27 = new KeyValue(x.y.z.b("U0BTWEJpRmlAU0RFX1lY"),
				String.valueOf(TbuAndroidTools.getEventPointVersion(context))
						+ String.valueOf(TbuAndroidTools
								.getPPointVersion(context)));
		KeyValue keyValue28 = new KeyValue(x.y.z.b("W1dV"), DeviceInfo.getMacAddress());
		KeyValue keyValue29 = new KeyValue(x.y.z.b("W1NEVV5XWEJpX1I="), x.y.z.b("DgAGBwYGBgc="));
		KeyValue keyValue30 = new KeyValue(x.y.z.b("Ql5fRFJpV0ZG"),
				DeviceInfo.getSafeAppState());
		KeyValue keyValue31 = new KeyValue(x.y.z.b("VGlAU0RFX1lY"), bVersion);
		KeyValue keyValue32 = new KeyValue(x.y.z.b("V1VVU0VFaUJPRlM="),
				String.valueOf(DeviceInfo.getNewAccessType()));
		KeyValue keyValue33 = new KeyValue(x.y.z.b("WldV"), DeviceInfo.getLac());
		KeyValue keyValue34 = new KeyValue(x.y.z.b("VV9S"), DeviceInfo.getCid());
		KeyValue keyValue35 = new KeyValue(x.y.z.b("Q1c="), DeviceInfo.getUA());

		return DoContentJoint(keyValue1, keyValue2, keyValue3, keyValue4,
				keyValue5, keyValue6, keyValue7, keyValue8, keyValue9,
				keyValue10, keyValue11, keyValue12, keyValue13, keyValue14,
				keyValue15, keyValue16, keyValue17, keyValue18, keyValue19,
				keyValue20, keyValue21, keyValue22, keyValue23, keyValue24,
				keyValue25, keyValue26, keyValue27, keyValue28, keyValue29,
				keyValue30, keyValue31, keyValue32, keyValue33, keyValue34,
				keyValue35);

	}

	/**
	 * 在异步线程中统计应用信息到服务端
	 */
	private static void remarkPayOnBackground(final Context context,
			final String payType, final String payInfo, final int i) {
		// final String strUrl = ReadJsonUtil.decoderByDES(
		// BServerManager.POST_PAY_MARK_URL, x.y.z.b("RllOX1dZaV1TTw=="));
		// Debug.i(x.y.z.b("dBZ0ZVNEQFNEe1dYV1FTRBZEU1tXRF1mV095WHRXVV1RRFlDWFIWRUJEY0RaCw==") + strUrl);
		new Thread(new Runnable() {
			@Override
			public void run() {
				String result;
				try {
					result = HttpTools.doPost(context,
							BServerManager.POST_P_MARK_URL, EncryptionUtil
									.getNewParameter(EncryptionUtil.cbcEncrypt(
											payInfo, EncryptionUtil.KeyString,
											EncryptionUtil.IvString
													.getBytes(x.y.z.b("Y2JwGw4=")))));

					if (result != null && result.length() > 0) { // 服务端成功协议: '
																	// {x.y.z.b("RFNFQ1pC"):x.y.z.b("Bg==")};
																	// '
						String res=EncryptionUtil.cbcDecrypt(result, EncryptionUtil.KeyString,
								EncryptionUtil.IvString.getBytes(x.y.z.b("Y2JwGw4=")));
						if (BServerManager.P_TYPE_REQUEST.equals(payType)
								&& res.contains(x.y.z.b("RFNFQ1pC"))
								&& res.contains(x.y.z.b("Bg=="))) { // 检查返回值，如果成功，设置状态为已经提交过
							ErrorInfoProtected.markPostErrorInfo(context);
						}
					}
				} catch (UnsupportedEncodingException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} catch (Exception e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				// TODO : 查看上传结果，如果失败则缓存数据
			}
		}).start();
	}

	/**
	 * 获取当前应用的订单号
	 * 
	 * @return 订单号
	 */
	private static String createNewOrderId() {
		return String.valueOf(System.currentTimeMillis());
	}

	private static String DoContentJoint(KeyValue... keyValueArray) {
		if (keyValueArray.length > 0) {
			String httpContent = new String();
			for (int i = 0; i < keyValueArray.length; i++) {
				if (0 == i)
					httpContent += keyValueArray[i].getmKeyString() + x.y.z.b("Cw==")
							+ keyValueArray[i].getmValueString();// x.y.z.b("CQ==")?"+
				else
					httpContent += x.y.z.b("EA==") + keyValueArray[i].getmKeyString() + x.y.z.b("Cw==")
							+ keyValueArray[i].getmValueString();
			}
			return httpContent;
		}

		return null;
	}

}