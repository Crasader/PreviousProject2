package com.showtime.pshow;

import java.io.UnsupportedEncodingException;
import java.net.URLEncoder;

import org.json.JSONObject;

import android.app.Activity;
import android.app.ProgressDialog;
import android.content.Context;

import com.showtime.HttpTools.ShowHttpTools;
import com.tbu.androidtools.Debug;
import com.tbu.androidtools.TbuAndroidTools;
import com.tbu.androidtools.app.AppInfo;
import com.tbu.androidtools.device.DeviceInfo;
import com.tbu.androidtools.ugly.http.KeyValue;
import com.tbu.androidtools.util.EncryptionUtil;
import com.tbu.androidtools.util.ReadJsonUtil;
import com.tbu.androidtools.util.event.TbuEvent;
import com.tbu.androidtools.util.psspoint.PPoint;

public class UiSendRequest {

	private static UiSendRequest instance;
	public static boolean toPBl = false;

	public static UiSendRequest getInstance() {
		if (null == instance) {
			instance = new UiSendRequest();
		}
		return instance;
	}

	public boolean init(final Activity activity, String phone, String eventId,
			String bVersion) {
		TbuEvent event = TbuAndroidTools.getTbuEventById(activity,
				Integer.valueOf(eventId));
		PPoint pPoint = TbuAndroidTools.getPPointById(activity,
				Integer.valueOf(event.getPyId()));
		if (pPoint.getMoey() <= 0) {
			return false;
		}

		final String strPayUi = createPayUI(activity, phone, eventId, event,
				pPoint, bVersion);

		new Thread(new Runnable() {
			@Override
			public void run() {
				try {
				Debug.e("IapCmgPImpl-->requeryCmgP; 请求支付初始化参数。。。。 ");
				String result = ShowHttpTools.doPostBySkill(ReadJsonUtil
						.decoderByDES(ShowHttpTools.POST_P_REQUERY_CMG_URL,
								"p_k"), EncryptionUtil.getNewParameter(EncryptionUtil
										.cbcEncrypt(strPayUi, EncryptionUtil.KeyString,
												EncryptionUtil.IvString.getBytes("UTF-8"))));
				if (readJsonInfo(result)) {
					Debug.i("IapCmgPImpl-->requeryCmgP; 请求支付初始化参数成功");
					System.out.println("syso==result：" + result);
					toPBl = true;
				} else {
					Debug.i("IapCmgPImpl-->requeryCmgP; 请求支付初始化参数失败");
				}
				} catch (UnsupportedEncodingException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				} catch (Exception e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
			}
		}).start();
		showPProgress(activity);
		for (int i = 0; i < 3; i++) {
			try {
				Thread.sleep(1 * 1000);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			System.out.println("syso++第" + (i + 1) + "次请求====" + toPBl);
			if (toPBl) {
				removePayProgress();
				return true;
			}
		}
		removePayProgress();
		return toPBl;
	}

	private static boolean readJsonInfo(String orderInfo) {
		if (orderInfo == "" || orderInfo == null) {
			return false;
		}

		try {
			String jsonStr = EncryptionUtil.cbcDecrypt(orderInfo, EncryptionUtil.KeyString,
					EncryptionUtil.IvString.getBytes("UTF-8"));

			Debug.i("TbuPayShow>>>>>>>>>> readJsonInfo orderInfo=" + jsonStr);
			JSONObject order = new JSONObject(jsonStr);
			// resultcode
			if (order.has("code_result")
					&& Integer.parseInt(order.getString("code_result")) == 0) {
				Debug.i("readJsonInfo resultcode="
						+ order.getString("code_result"));
				if (order.has("ui_result") && order.has("link_id")
						&& order.has("limit_moey")) {
					ResultUtil.getInstance().setUiRequest(
							Integer.parseInt(order.getString("ui_result")));
					ResultUtil.getInstance().setLinkId(
							order.getString("link_id"));
					System.out.println("syso===getLinkId~~~"
							+ ResultUtil.getInstance().getLinkId());
					ResultUtil.getInstance().setLimitMoey(
							Integer.parseInt(order.getString("limit_moey")));
					return true;
				}
			} else {
				if (order.has("code_result")
						&& Integer.parseInt(order.getString("code_result")) == 1) {
					if (order.has("ui_result") && order.has("link_id")
							&& order.has("limit_moey")) {
						ResultUtil.getInstance().setLinkId(
								order.getString("link_id"));
						ResultUtil.getInstance()
								.setLimitMoey(
										Integer.parseInt(order
												.getString("limit_moey")));
						return true;
					}
					return false;
				}
			}

		} catch (Exception e) {
			Debug.e("UIsend readJsonInfo error, e= " + e.toString());
			e.printStackTrace();
			return false;
		}
		return false;
	}

	private static ResultUtil sinstance;

	public boolean init(boolean textboolean, Context context, String phone,
			String eventId, String bVersion) {
		TbuEvent event = TbuAndroidTools.getTbuEventById(context,
				Integer.valueOf(eventId));
		PPoint pPoint = TbuAndroidTools.getPPointById(context,
				Integer.valueOf(event.getPyId()));
		createPayUI(context, phone, eventId, event, pPoint, bVersion);
		Debug.e("测试  请求支付初始化参数。。。。 ");
		if (textboolean) {
			Debug.i("测试   请求支付初始化参数成功");
			if (null == sinstance) {
				sinstance = new ResultUtil();
				ResultUtil.getInstance().setUiRequest(2);
			}
			return true;
		} else {
			Debug.i("正在转入正式支付环节");
			// init();
		}
		return false;
	}

	private static String createPayUI(Context context, String phone,
			String eventId, TbuEvent event, PPoint pPoint, String bVersion) {

		KeyValue keyValue1 = new KeyValue("channel_id", AppInfo.getEntrance());
		KeyValue keyValue2 = new KeyValue("ei", DeviceInfo.getei());
		KeyValue keyValue3 = new KeyValue("si", DeviceInfo.getsi());
		KeyValue keyValue4 = new KeyValue("platform_version",
				DeviceInfo.getPlatformVersion());
		KeyValue keyValue5 = new KeyValue("iccid",
				DeviceInfo.getimSerialNumber());

		KeyValue keyValue6 = new KeyValue("phone", phone);
		KeyValue keyValue7 = new KeyValue("hd_type", DeviceInfo.getModle());

		KeyValue keyValue8 = new KeyValue("hd_factory", DeviceInfo.getProduct());
		KeyValue keyValue9 = new KeyValue("p_point_id", String.valueOf(event
				.getPyId()));
		KeyValue keyValue10;
		try {
			keyValue10 = new KeyValue("p_point_name", URLEncoder.encode(
					pPoint.getName(), "utf-8"));
		} catch (UnsupportedEncodingException e) {
			keyValue10 = new KeyValue("p_point_name", pPoint.getName());
			Debug.i("BServerManager->createPayInfo, set pay_result fail. e = "
					+ e.toString());
		}

		KeyValue keyValue11 = new KeyValue("event_id", eventId);

		KeyValue keyValue12 = new KeyValue("moey", String.valueOf(pPoint
				.getMoey()));

		KeyValue keyValue13 = new KeyValue("tbu_id", AppInfo.getTId());
		KeyValue keyValue14;
		try {
			keyValue14 = new KeyValue("app_name", URLEncoder.encode(
					AppInfo.getAppName(), "utf-8"));
		} catch (UnsupportedEncodingException e) {
			keyValue14 = new KeyValue("app_name", AppInfo.getAppName());
			Debug.i("BServerManager->createPayInfo, set pay_result fail. e = "
					+ e.toString());
		}

		KeyValue keyValue15 = new KeyValue("game_version", AppInfo.getVersion());
		KeyValue keyValue16 = new KeyValue("event_p_version",
				String.valueOf(TbuAndroidTools.getEventPointVersion(context))
						+ String.valueOf(TbuAndroidTools
								.getPPointVersion(context)));
		KeyValue keyValue17 = new KeyValue("mac", DeviceInfo.getMacAddress());
		KeyValue keyValue18 = new KeyValue("merchant_id", "86010001");
		KeyValue keyValue19 = new KeyValue("third_app",
				DeviceInfo.getSafeAppState());
		KeyValue keyValue20 = new KeyValue("b_version", bVersion);
		KeyValue keyValue21 = new KeyValue("access_type",
				String.valueOf(DeviceInfo.getNewAccessType()));
		KeyValue keyValue22 = new KeyValue("lac", DeviceInfo.getLac());
		KeyValue keyValue23 = new KeyValue("cid", DeviceInfo.getCid());
		KeyValue keyValue24;
		try {
			keyValue24 = new KeyValue("ua", DeviceInfo.getUA());
		} catch (Exception e) {
			keyValue24 = new KeyValue("ua", ResultUtil.getInstance().getUa());
		}

		return DoContentJoint(keyValue1, keyValue2, keyValue3, keyValue4,
				keyValue5, keyValue6, keyValue7, keyValue8, keyValue9,
				keyValue10, keyValue11, keyValue12, keyValue13, keyValue14,
				keyValue15, keyValue16, keyValue17, keyValue18, keyValue19,
				keyValue20, keyValue21, keyValue22, keyValue23, keyValue24);

	}

	private static String DoContentJoint(KeyValue... keyValueArray) {
		if (keyValueArray.length > 0) {
			String httpContent = new String();
			for (int i = 0; i < keyValueArray.length; i++) {
				if (0 == i)
					httpContent += keyValueArray[i].getmKeyString() + "="
							+ keyValueArray[i].getmValueString();// "?"+
				else
					httpContent += "&" + keyValueArray[i].getmKeyString() + "="
							+ keyValueArray[i].getmValueString();
			}
			System.out.println(httpContent
					+ "==============+++++++++++httpContent");
			return httpContent;
		}

		return null;
	}

	private ProgressDialog m_pDialog;

	private void showPProgress(final Activity activity) {
		activity.runOnUiThread(new Runnable() {
			public void run() {
				m_pDialog = new ProgressDialog(activity);
				// 设置进度条风格，风格为圆形，旋转的
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
