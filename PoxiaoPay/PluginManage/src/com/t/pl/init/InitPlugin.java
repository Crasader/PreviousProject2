package com.t.pl.init;

import java.lang.reflect.Method;
import java.util.Map;

import android.app.Activity;
import android.content.Context;

import com.t.pl.PluginDefine;
import com.t.pl.load.PluginInfos;
import com.tbu.androidtools.Debug;
import com.tbu.androidtools.device.DeviceInfo;

public  class InitPlugin {
	
	public static void initPPlginIfNeedOnApplication(Context context) {
		for (Map.Entry<String, String> entry : PluginInfos.getFunctions1()
				.entrySet()) {
			initPPlginByName(context, entry.getKey(), entry.getValue());
		}
	}

	public static void initPPlginIfNeedOnActivity(Activity activity) {
		if (DeviceInfo.getCarrier() == 1) {
			for (Map.Entry<String, String> entry : PluginInfos.getFunctions2()
					.entrySet()) {
				initPPlginByName(activity, entry.getKey(), entry.getValue());
			}
		}

	}

	public static void quitPluginIfNeedOnApplicaton(Context context) {
		for (Map.Entry<String, String> entry : PluginInfos.getFunctions3()
				.entrySet()) {
			initPPlginByName(context, entry.getKey(), entry.getValue());
		}
	}

	public static boolean isBeyondLimit(String plginName) {
		if (plginName.equals(PluginDefine.P_PLUGINTYPE_IAPCMCC)) {
			return isBeyondLimitByName(
					"com.poxiao.p.xbll.plugin.IapMMPImpl", "isBeyondLimit");
		}
		return false;
	}

	private static boolean isBeyondLimitByName(String plginClassName, String methodName) {
		boolean re;
		try {
			Class c = Class.forName(plginClassName);
			Method method = c.getMethod(methodName);
			re = Boolean.parseBoolean(method.invoke(null).toString());
			return re;
		} catch (Exception e) {
			Debug.e("IGameP->isBeyondLimitByName, with error,plginClassName = "
					+ plginClassName + ",e = " + e.toString());
			return true;
		}

	}

	
	/**
	 * 
	 * @param context
	 * @param plginClassName
	 * @param methodName
	 * @return
	 */
	private static boolean initPPlginByName(Context context, String plginClassName,
			String methodName) {
		try {
			Class c = Class.forName(plginClassName);
			Method method = c.getMethod(methodName, Context.class);
			method.invoke(null, context);
			return true;
		} catch (Exception e) {
			Debug.e("IGameP->initPPlginByName, with error,plginClassName = "
					+ plginClassName + ",e = " + e.toString()+"11"+methodName);
			return false;
		}
	}

	/**
	 * 
	 * @param activity
	 * @param plginClassName
	 * @param methodName
	 * @return
	 */
	private static boolean initPPlginByName(Activity activity,
			String plginClassName, String methodName) {
		try {
			Class c = Class.forName(plginClassName);
			Method method = c.getMethod(methodName, Activity.class);
			method.invoke(null, activity);
			return true;
		} catch (Exception e) {
			Debug.e("IGameP->initPPlginByName, with error,plginClassName = "
					+ plginClassName + ",e = " + e.toString()+"121"+methodName);
			return false;
		}
	}
}
