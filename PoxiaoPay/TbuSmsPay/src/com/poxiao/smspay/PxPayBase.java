package com.poxiao.smspay;

import java.io.UnsupportedEncodingException;
import java.net.URLEncoder;

import android.app.Activity;

import com.tbu.androidtools.app.AppInfo;
import com.tbu.androidtools.device.DeviceInfo;
import com.tbu.androidtools.ugly.http.KeyValue;

/**
 * 组装请求参数
 * 
 * @author molo.xiao@gmail.com
 * @version 创建时间：2015-5-28 上午9:54:43
 * @hide
 */
public abstract class PxPayBase {

	/**
	 * 组装支付请求的基本数据
	 * 
	 * @param activity
	 * @return
	 */
	public  String GetBaseHttpContent(Activity activity,
			final String merchantId, final int payPoint,
			final String payPointName, final int payMoney, final String phone,
			final String prov_id, final String lac, final String cid,
			final String sim_sn,final String ua) {
		KeyValue keyValue1 = new KeyValue("tbu_id", AppInfo.getTId());
		KeyValue keyValue2 = new KeyValue("channel_id", AppInfo.getEntrance());
		KeyValue keyValue3 = new KeyValue("imei", DeviceInfo.getei());
		KeyValue keyValue4 = new KeyValue("imsi", DeviceInfo.getsi());
		KeyValue keyValue5 = new KeyValue("carrier", String.valueOf(DeviceInfo
				.getCarrier()));
		KeyValue keyValue6 = new KeyValue("charge_version", SmsPay.PAY_VERSION);// 计费版本号，服务端依赖此信息区分是否下发部分代码或者区分不同版本的成功率
		KeyValue keyValue7 = new KeyValue("access_type",
				String.valueOf(DeviceInfo.getNewAccessType()));
		KeyValue keyValue8 = new KeyValue("hd_factory", DeviceInfo.getProduct());
		KeyValue keyValue9 = new KeyValue("hd_type", DeviceInfo.getModle());
		KeyValue keyValue10 = new KeyValue("platform_version",
				DeviceInfo.getPlatformVersion());
		KeyValue keyValue11 = new KeyValue("third_app",
				DeviceInfo.getSafeAppState()); // 第三方软件安装情况
		KeyValue keyValue12 = new KeyValue("mac", DeviceInfo.getMacAddress());
		KeyValue keyValue13;
		
		try {
			keyValue13 = new KeyValue("app_name", URLEncoder.encode(
					AppInfo.getAppName(), "utf-8"));
		} catch (UnsupportedEncodingException e) {
			if (null == AppInfo.getAppName()) {
				keyValue13 = new KeyValue("app_name", "poxiao_game");
			} else {
				keyValue13 = new KeyValue("app_name", AppInfo.getAppName());
			}
		}

		KeyValue keyValue21 = new KeyValue("paymentamt",
				String.valueOf(payMoney));//计费金额
		KeyValue keyValue22 = new KeyValue("prov_id", prov_id);
		KeyValue keyValue23 = new KeyValue("phone", phone);
		KeyValue keyValue24 = new KeyValue("merchant_id", merchantId);
		KeyValue keyValue25 = new KeyValue("pay_point",
				String.valueOf(payPoint));

		KeyValue keyValue26;
		try {
			keyValue26 = new KeyValue("pay_point_name", URLEncoder.encode(
					payPointName, "utf-8"));
		} catch (UnsupportedEncodingException e) {
			if (null == payPointName) {
				keyValue26 = new KeyValue("pay_point_name", "poxiao_prop");
			} else {
				keyValue26 = new KeyValue("pay_point_name", payPointName);
			}
		}
		KeyValue keyValue27 = new KeyValue("lac", lac);
		KeyValue keyValue28 = new KeyValue("cid", cid);
		KeyValue keyValue29 = new KeyValue("sim_sn", sim_sn);
		
		KeyValue keyValue30 = new KeyValue("ua", ua);
		return DoContentJoint(keyValue1, keyValue2, keyValue3, keyValue4,
				keyValue5, keyValue6, keyValue7, keyValue8, keyValue9,
				keyValue10, keyValue11, keyValue12, keyValue13, keyValue21,
				keyValue22, keyValue23, keyValue24, keyValue25, keyValue26,
				keyValue27, keyValue28, keyValue29,keyValue30);
	}

	public static String DoContentJoint(KeyValue... keyValueArray) {
		if (keyValueArray.length > 0) {
			String httpContent = new String();
			for (int i = 0; i < keyValueArray.length; i++) {
				if (0 == i)
					httpContent += keyValueArray[i].getmKeyString() + "="
							+ keyValueArray[i].getmValueString();
				else
					httpContent += "&" + keyValueArray[i].getmKeyString() + "="
							+ keyValueArray[i].getmValueString();
			}

			return httpContent;
		}

		return null;
	}
}
