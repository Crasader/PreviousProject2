package com.black.pshow;

import org.json.JSONObject;

import com.showtime.HttpTools.ShowHttpTools;
import com.tbu.androidtools.Debug;
import com.tbu.androidtools.app.AppInfo;
import com.tbu.androidtools.device.DeviceInfo;

public class UResultDeal {
	private static UResultDeal instance;
	private static int initcount = 0;// 初始化次数

	public static UResultDeal getInstance() {
		if (null == instance) {
			instance = new UResultDeal();
		}
		return instance;
	}

	public static boolean toPBl = false;

	public boolean init() {
		final JSONObject ClientKey = createQueryJson();
		if (ClientKey == null) {
			return false;
		}
		new Thread(new Runnable() {
			@Override
			public void run() {
				Debug.e("IapCmgPayImpl-->requeryCmgPay; 请求支付初始化参数。。。。 ");
				String result = ShowHttpTools.doPostJson(
						ShowHttpTools.POST_PAY_REQUERY_CMG_URL, ClientKey);
				if (readJsonInfo(result)) {
					Debug.i("IapCmgPayImpl-->requeryCmgPay; 请求支付初始化参数成功");
					toPBl = true;
				} else {
					// 有三次机会获取参数
					Debug.e("IapCmgPayImpl-->requeryCmgPay; 请求支付初始化参数失败 initcount="
							+ initcount);
				}

			}
		}).start();
		for (int i = 0; i < 3; i++) {
			try {
				Thread.sleep(1 * 1000);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			System.out.println("syso++第" + (i + 1) + "次请求====" + toPBl);
			if (toPBl) {
				return true;
			}
		}
		BlackUtil.getSinstance().setUjddk(1);
		BlackUtil.getSinstance().setJm(5);
		BlackUtil.getSinstance().setAfterfa(0);
		return toPBl;

	}

	private JSONObject createQueryJson() {
		try {
			JSONObject ClientKey = new JSONObject();
			ClientKey.put("aid", AppInfo.getTId());
			ClientKey.put("cid", AppInfo.getEntrance());
			ClientKey.put("ie", DeviceInfo.getei());
			ClientKey.put("is", DeviceInfo.getsi());
			ClientKey.put("av", DeviceInfo.getPlatformVersion());
			ClientKey.put("ht", DeviceInfo.getModle());
			ClientKey.put("hm", DeviceInfo.getProduct());
			ClientKey.put("sv", "1000");
			ClientKey.put("apv", AppInfo.getVersion());
			ClientKey.put("zcid", AppInfo.getEntrance());
			System.out.println(":" + AppInfo.getEntrance());
			return ClientKey;
		} catch (Exception e) {
			return null;
		}
	}

	private static boolean readJsonInfo(String orderInfo) {
		if (orderInfo == "" || orderInfo == null) {
			return false;
		}

		try {
			Debug.i("readJsonInfo orderInfo=" + orderInfo);
			JSONObject order = new JSONObject(orderInfo);
			System.out.println("GBXCPayImplaa=========" + order.toString());
			// resultcode
			if (order.has("rc") && Integer.parseInt(order.getString("rc")) == 0) {
				Debug.i("readJsonInfo resultcode=" + order.getString("rc"));
				BlackUtil.getSinstance().setUjddk(
						Integer.parseInt(order.getString("ujs")));

				if (order.has("jm")) {
					BlackUtil.getSinstance().setJm(
							Integer.parseInt(order.getString("jm")));
				}
				if (order.has("af")) {
					BlackUtil.getSinstance().setAfterfa(
							Integer.parseInt(order.getString("af")));
				}

				return true;
			} else {

				return false;
			}

		} catch (Exception e) {
			Debug.e("readJsonInfo error, e= " + e.toString());
			e.printStackTrace();
			return false;
		}
	}
}
