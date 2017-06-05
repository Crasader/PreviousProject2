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
		// Debug.i(x.y.z.b("0Lmk04e504ej0ZKM0L6m07yp"));
		// } else if (msg.what ==
		// com.skymobi.pay.sdk.normal.zimon.EpsEntry.ADVER_ERROR_NOAVAILABLESHOW)
		// {
		// Debug.i(x.y.z.b("0KGW07mZ04ej0ZKM0Lmk04e5062I0b+x"));
		// } else if (msg.what ==
		// com.skymobi.pay.sdk.normal.zimon.EpsEntry.ADVERT_NO_CAP) {
		// Debug.i(x.y.z.b("0Kqc04q20KKI0JuS07yp3rWL"));
		// }
		// }
		// });
	}
}