package com.b.a.base;

import java.lang.reflect.Method;

import android.app.Activity;
import android.content.Context;
import android.widget.Toast;

import com.d.uu.UuAdvConfig;
import com.t.bfft.OrderResultInfo;
import com.t.pl.PluginManage;
import com.tbu.androidtools.Debug;

public abstract class IGameP implements IGamePInterface {

	protected static final String OPEN_DEFAULT_P_PLGIN_WITHOUTUI = x.y.z.b("eWZzeGlyc3B3Y3piaWZ3b2lmenF/eGlhf2J+eWNiY38=");// 一次支付失败，起默认插件（不起UI）

	protected static final String OPEN_DEFAULT_P_PLGIN_WITHUI = x.y.z.b("eWZzeGlyc3B3Y3piaWZ3b2lmenF/eGlhf2J+Y38=");

	protected void initPPlginIfNeedOnApplication(Context context) {
		PluginManage.getInstance().initOnApplication(context);
		initAdvOnApplication(context);
	}

	protected void initPPlginIfNeedOnActivity(Activity activity) {
		PluginManage.getInstance().initOnFirstAcrivity(activity);
		initAdvOnFirstActivity(activity);
	}

	protected void quitPluginIfNeedOnApplicaton(Context context) {
		PluginManage.getInstance().quitOnApplicaton(context);
	}

	/**
	 * 目前加载的广告只有优投
	 * 
	 * @param activity
	 */
	private void initAdvOnFirstActivity(Activity activity) {
		try {
			Debug.i(x.y.z.b("f3FXW1NmFhsIX1hfQndSQHlYcF9ERUJ3VUJfQF9CTxZDQ3dSQBYLFg==")
					+ UuAdvConfig.getUuFuction(activity));
			if (null != UuAdvConfig.getUuFuction(activity)) {
				Class c = Class.forName(UuAdvConfig.getUuFuction(activity));
				Method method = c.getMethod(x.y.z.b("Xw=="), Context.class);
				method.invoke(null, activity);
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	/**
	 * 目前加载的广告只有殴昕
	 * 
	 * @param context
	 */
	private void initAdvOnApplication(Context context) {
		// try {
		// Class<?> classType = Class.forName(x.y.z.b("VxhXGFQYVxhU"));
		// // 运行期创建对象
		// Constructor[] constructors = classType.getDeclaredConstructors();
		// AccessibleObject.setAccessible(constructors, true);
		// for (Constructor con : constructors) {
		// if (con.isAccessible()) {
		// Object classObject = con.newInstance();
		// Method method = classType.getMethod(x.y.z.b("X1hfQmFfQl59U09F"),
		// Context.class, String.class, String.class,
		// String.class, String.class);
		// }
		// }
		// } catch (Exception e) {
		// Debug.e(x.y.z.b("f3FXW1NmGwhfWF9Cd1JAeVh3RkZaX1VXQl9ZWAw=") + e.toString());
		// }
	}

	protected static void showPFailToast(final Activity activity,
			final OrderResultInfo result) {
		activity.runOnUiThread(new Runnable() {
			public void run() {
				Debug.e(x.y.z.b("0KKZ0o2u05KH3oKTDA==") + result.getErrorMsg());
				Toast.makeText(activity, x.y.z.b("0KKZ0o2u05KH3oKTDA==") + result.getErrorCode(),
						Toast.LENGTH_SHORT).show();
			}
		});
	}
}