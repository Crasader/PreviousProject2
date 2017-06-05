package com.function.implementation.base;

import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;

import android.app.Activity;
import android.content.Context;
import android.widget.Toast;

import com.t.bfft.OrderResultInfo;
import com.tbu.androidtools.Debug;

public abstract class IGamePay implements IGamePayInterface {

	// 是否添加自有支付付费成功提示
	public static boolean OPEN_POXIAO_PAY_SUCCESS_TIP = false;

	protected static final String OPEN_DEFAULT_PAY_PLGIN_WITHOUTUI = "OPEN_DEFAULT_PAY_PLGIN_WITHOUTUI";// 一次支付失败，起默认插件（不起UI）

	protected static final String OPEN_DEFAULT_PAY_PLGIN_WITHUI = "OPEN_DEFAULT_PAY_PLGIN_WITHUI";

	protected static void showPaySuccessToast(final Activity activity,
			final OrderResultInfo result) {
		activity.runOnUiThread(new Runnable() {
			public void run() {
				Debug.e("购买成功");
				Toast.makeText(activity, "购买成功", Toast.LENGTH_SHORT).show();
			}
		});
	}

	protected static void showPayFailToast(final Activity activity,
			final OrderResultInfo result) {
		activity.runOnUiThread(new Runnable() {
			public void run() {
				Debug.e("支付失败:" + result.getErrorMsg());
				Toast.makeText(activity, "支付失败:" + result.getErrorCode(),
						Toast.LENGTH_SHORT).show();
			}
		});
	}

	private static final String PROP_FILE_NAME = "gamepayplugin.px";
	private static final String PROP_KEY_ENTERID = "PAYPLUGIN_TYPE";

	/**
	 * 返回客户端当前支持的插件类型(从Assets/gamepayplugin.px获取)
	 * 
	 * @param context
	 * @return sky :2 乐途：3 联通：4;“2,3”表示可支持sky，乐途，和裸代码 “2,3,4”表示sky，乐途，联通和裸代码
	 */
	public static String getPayPluginTypeFromPx(Context context) {
		Properties pro = new Properties();
		InputStream is = null;
		try {
			is = context.getAssets().open(PROP_FILE_NAME);
			pro.load(is);
			String payPluginObj = pro.getProperty(PROP_KEY_ENTERID);
			if (payPluginObj != null) {
				return payPluginObj;
			}
		} catch (IOException e) {
			e.printStackTrace();
			System.exit(0);
		} finally {
			if (is != null) {
				try {
					is.close();
				} catch (IOException e) {

				}
			}
		}
		return ""; // TODO : 读取不到应该直接让应用程序崩溃
	}
}
