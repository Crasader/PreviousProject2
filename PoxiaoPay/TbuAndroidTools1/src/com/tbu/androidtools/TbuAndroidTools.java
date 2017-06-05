package com.tbu.androidtools;

import android.content.Context;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;

import com.tbu.androidtools.app.AppInfo;
import com.tbu.androidtools.device.DeviceInfo;
import com.tbu.androidtools.util.event.EventPointUtil;
import com.tbu.androidtools.util.event.TbuEvent;
import com.tbu.androidtools.util.psspoint.PPoint;
import com.tbu.androidtools.util.psspoint.PPointUtil;
import com.tbu.androidtools.util.spcode.SpCodeUtil;

public class TbuAndroidTools {

	public static final String version = "16";

	private static String APP_MODEL = "debug_model";

	private static boolean isDebugModel = false;

	public static void init(final Context context) {
		initDebugState(context);
		DeviceInfo.init(context);
		AppInfo.init(context);
		new Thread(new Runnable() {
			public void run() {
				EventPointUtil.getTbuEventByJson(context);
				PPointUtil.getPPointByJson(context);
			}
		}).start();
	}

	/**
	 * 返回当前是否是Debug模式,debug模式下外部配置的json不需要加密
	 * 
	 * @return
	 */
	public static boolean isDebugModel() {
		return isDebugModel;
	}

	/**
	 * 获取事件点
	 * 
	 * @param context
	 * @param eventId
	 * @return
	 */
	public static TbuEvent getTbuEventById(Context context, int eventId) {
		return EventPointUtil.getTbuEventById(context, eventId);
	}

	/**
	 * 获取保护计费点的信息
	 * 
	 * @param context
	 * @return
	 */
	public static int getProtectedPPoint(Context context) {
		return EventPointUtil.getProtectedPPoint(context);
	}

	/**
	 * 获取事件点的版本号
	 * 
	 * @param context
	 * @return
	 */
	public static int getEventPointVersion(Context context) {
		return EventPointUtil.getEventPointVersion(context);
	}

	/**
	 * 获取计费点
	 * 
	 * @param context
	 * @param pId
	 * @return
	 */
	public static PPoint getPPointById(Context context, int pId) {
		return PPointUtil.getPPointById(context, pId);
	}

	public static int getPPointVersion(Context context) {
		return PPointUtil.getPPointVersion(context);
	}

	/**
	 * 获取运营商的特殊计费编码
	 * 
	 * @param context
	 * @param pluginName
	 * @param pId
	 * @return
	 */
	public static String getSPointById(Context context, String pluginName,
			int pId) {
		return SpCodeUtil.getSpPointById(context, pluginName, pId);
	}

	private static void initDebugState(Context context) {

		ApplicationInfo appInfo = null;
		try {
			appInfo = context.getPackageManager().getApplicationInfo(
					context.getPackageName(), PackageManager.GET_META_DATA);

		} catch (Exception e) {
			Debug.e("TbuAndroidTools->init, meet error. e = " + e.toString());
		}
		if (appInfo.metaData.getBoolean(APP_MODEL)) {
			isDebugModel = true;
		}
	}

}
