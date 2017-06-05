package com.tbu.wx.pay;

import java.net.URLEncoder;
import java.util.HashMap;
import java.util.Map;

import org.json.JSONObject;

import android.app.Activity;

import com.tallbigup.buffett.Buffett;
import com.tallbigup.buffett.OrderResultInfo;
import com.tbu.androidtools.Debug;
import com.tbu.wx.http.Addresses;
import com.tbu.wx.http.HttpUtil;
import com.tbu.wx.http.KeyValue;
import com.tbu.wx.http.callback.HttpCallBack;
import com.tbu.wx.http.callback.QueryCallBack;
import com.tbu.wx.http.data.WxOrderInfo;
import com.tbu.wx.util.WxAppInfo;
import com.tencent.mm.sdk.modelpay.PayReq;
import com.tencent.mm.sdk.openapi.IWXAPI;
import com.tencent.mm.sdk.openapi.WXAPIFactory;

public class TbuWxPay {

	private static TbuWxPay instance;
	private static Activity payActivity;
	private static IWXAPI msgApi;
	private static final String PACKAGEVALUE = "Sign=WXPay";
	private static Map<String, String> wxOrderList = new HashMap<String, String>();

	public static TbuWxPay getInstance() {
		if (null == instance) {
			instance = new TbuWxPay();
		}
		return instance;
	}

	public void initOnFirstActivity(Activity activity) {
		TbuWxPay.payActivity = activity;
		WxAppInfo.init(activity);
		// 将该app注册到微信
		msgApi = WXAPIFactory.createWXAPI(activity, WxAppInfo.getWxInfo()
				.getAppId(), false);
		msgApi.registerApp(WxAppInfo.getWxInfo().getAppId());
	}

	/**
	 * 支付接口
	 * 
	 * @param orderId
	 * @param tbuId
	 * @param productId
	 * @param productName
	 * @param price
	 */
	public void Pay(final String orderId, final String tbuId,
			final String productId, final String productName, final String price) {
		// 启动网络线程
		new Thread(new Runnable() {
			@Override
			public void run() {
				// 向服务器下单
				String content = createOrderInfo(orderId, tbuId, productId,
						productName, price);
				HttpUtil.doGet(Addresses.URL_ORDER, content,
						new HttpCallBack() {
							@Override
							public void callBack(String msg) {
								try {
									JSONObject object = new JSONObject(msg);
									System.out.println("3weixin");
									if (object.getInt("result") == 0) {
										System.out.println("4weixin");
										WxOrderInfo orderInfo = new WxOrderInfo();
										orderInfo.setWxOrderId(object
												.getString("wx_order_id"));
										orderInfo.setWxPrepayid(object
												.getString("wx_prepayid"));
										orderInfo.setWxSign(object
												.getString("wx_sign"));
										orderInfo.setWxTimestamp(object
												.getString("wx_timestamp"));
										orderInfo.setWxNonceStr(object
												.getString("wx_nonce_str"));
										wxOrderList.put(orderId,
												orderInfo.getWxOrderId());
										pay2Wx(orderInfo);
									} else {
										System.out.println("5weixin");
										Debug.e("微信支付向Tbu服务器下单失败");
										OrderResultInfo ori = new OrderResultInfo();
										ori.setResultCode(OrderResultInfo.PAY_FAIL);
										ori.setErrorCode("" + OrderResultInfo.PAY_FAIL);
										ori.setErrorMsg("支付失败!");
										Buffett.getInstance().getPayCallBack().result(ori);
									}
								} catch (Exception e) {
									System.out.println("6weixin");
									Debug.e("Exception:" + e.toString());
									OrderResultInfo ori = new OrderResultInfo();
									ori.setResultCode(OrderResultInfo.PAY_FAIL);
									ori.setErrorCode("" + OrderResultInfo.PAY_FAIL);
									ori.setErrorMsg("支付失败!");
									Buffett.getInstance().getPayCallBack().result(ori);
								}
							}
						});
			}
		}).start();
	}

	public void queryOrder(final String orderId, final QueryCallBack callBack,final String tbu_id) {
		new Thread(new Runnable() {
			@Override
			public void run() {
				String content = createOrderRecord(orderId,
						getWxOrderInfoByOrderInfo(orderId),tbu_id);
				HttpUtil.doGet(Addresses.URL_QUERY_ORDER, content,
						new HttpCallBack() {
							@Override
							public void callBack(String msg) {
								if (null == msg) {
									Debug.e("查询订单发生错误");
								}
								try {
									JSONObject object = new JSONObject(msg);
									if (object.getInt("result") == 0) {
										Debug.e("微信支付订单查询结果：支付成功");
										callBack.queryCallback(true);
									} else {
										Debug.e("微信支付订单查询结果：支付失败"
												+ object.getInt("msg"));
										callBack.queryCallback(false);
									}
								} catch (Exception e) {
									Debug.e("Exception:" + e.toString());
								}
							}
						});
			}
		}).start();
	}

	/**
	 * 关闭订单
	 * 
	 * @param orderId
	 * @param wxOrderId
	 */
	public void closeWxOrder(final String orderId,final String tbu_id) {
		new Thread(new Runnable() {
			@Override
			public void run() {
				String content = createOrderRecord(orderId,
						getWxOrderInfoByOrderInfo(orderId),tbu_id);
				HttpUtil.doGet(Addresses.URL_CLOSE_ORDER, content,
						new HttpCallBack() {
							@Override
							public void callBack(String msg) {
								if (null == msg) {
									Debug.e("关闭订单发生错误");
								}
							}
						});
			}
		}).start();
	}

	private void pay2Wx(final WxOrderInfo wxInfo) {
		Debug.e("wx pay coming ...");
		TbuWxPay.payActivity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				PayReq request = new PayReq();
				request.appId = WxAppInfo.getWxInfo().getAppId();
				request.partnerId = WxAppInfo.getWxInfo().getPartnerId();
				request.packageValue = PACKAGEVALUE;
				request.prepayId = wxInfo.getWxPrepayid();
				request.nonceStr = wxInfo.getWxNonceStr();
				request.timeStamp = wxInfo.getWxTimestamp();
				request.sign = wxInfo.getWxSign();
				msgApi.sendReq(request);
				Debug.e("wx pay end " + request.toString());
			}
		});
	}

	private String createOrderRecord(String orderId, String wxOrderId,String tbu_id) {
		KeyValue keyValue1 = new KeyValue("order_id", orderId);
		KeyValue keyValue2 = new KeyValue("wx_order_id", wxOrderId);
		KeyValue keyValue3 = new KeyValue("tbu_id", tbu_id);
		return HttpUtil.DoContentJoint(keyValue1, keyValue2,keyValue3);
	}

	private String createOrderInfo(String orderId, String tbuId,
			String productId, String productName, String price) {
		// 下单参数:order_id, tbu_id,product_id,product_name,price
		KeyValue keyValue1 = new KeyValue("tbu_id", tbuId);
		KeyValue keyValue2 = new KeyValue("product_id", productId);
		KeyValue keyValue3;
		try {
			keyValue3 = new KeyValue("product_name", URLEncoder.encode(
					productName, "utf-8"));
		} catch (Exception e) {
			keyValue3 = new KeyValue("product_name", productName);
		}
		KeyValue keyValue4 = new KeyValue("price", price);
		KeyValue keyValue5 = new KeyValue("order_id", orderId);
		return HttpUtil.DoContentJoint(keyValue1, keyValue2, keyValue3,
				keyValue4, keyValue5);
	}

	private String getWxOrderInfoByOrderInfo(String orderInfo) {
		String wxOrder = null;
		for (String key : wxOrderList.keySet()) {
			if (orderInfo.equals(key)) {
				wxOrder = wxOrderList.get(key);
			}
		}
		return wxOrder;
	}

}
