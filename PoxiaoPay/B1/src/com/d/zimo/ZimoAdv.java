package com.d.zimo;

import com.tbu.androidtools.Debug;
import android.app.Activity;
import android.os.Handler;
import android.os.Message;

public class ZimoAdv {
	/**
	 * 指盟广告
	 * 
	 * @param activity
	 */
	public static void zimonShowAdv(Activity activity) {
		// 第一种调用方法
		// com.skymobi.pay.sdk.normal.zimon.EpsEntry mEpsEntry =
		// com.skymobi.pay.sdk.normal.zimon.EpsEntry
		// .getInstance();
		// mEpsEntry.showSpotAdv(activity, new Handler() {
		// @Override
		// public void handleMessage(Message msg) {
		// super.handleMessage(msg);
		// if (msg.what ==
		// com.skymobi.pay.sdk.normal.zimon.EpsEntry.ADVER_SUCCESS_SHOW) {
		// Debug.i("插屏展示成功");
		// } else if (msg.what ==
		// com.skymobi.pay.sdk.normal.zimon.EpsEntry.ADVER_ERROR_NOAVAILABLESHOW)
		// {
		// Debug.i("无可展示插屏图片");
		// } else if (msg.what ==
		// com.skymobi.pay.sdk.normal.zimon.EpsEntry.ADVERT_NO_CAP) {
		// Debug.i("未开放此功能");
		// }
		// }
		// });
	}
}
