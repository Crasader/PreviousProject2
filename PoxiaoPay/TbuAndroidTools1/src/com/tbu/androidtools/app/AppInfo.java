package com.tbu.androidtools.app;

import android.app.ActivityManager;
import android.content.ComponentName;
import android.content.Context;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.webkit.WebSettings;
import android.webkit.WebView;

import com.tbu.androidtools.Debug;
import com.tbu.androidtools.util.ReadJsonUtil;
import com.tbu.androidtools.util.StringUtils;

/**
 * 获取应用相关的信息。
 * 
 * @author molo.xiao@gmail.com
 * @version 创建时间：2015-5-6 上午11:03:17
 *
 */
public class AppInfo {

	public static final String DEFAULT_VERSION = "1";
	private static final String TBU_ID_KEY = "tbu_id";

	/*
	 * 游戏版本号
	 */
	private static String version = null;

	/*
	 * 渠道ID
	 */
	private static String entrance = null;

	/*
	 * 游戏打包的名称
	 */
	private static String appName = null;

	/**
	 * 游戏统一ID
	 */
	private static String tId = null;

	private static Context context;

	public static void init(Context context) {
		AppInfo.context = context;
	}

	/**
	 * 获取游戏版本号
	 * 
	 * @return
	 */
	public static String getVersion() {
		if (null == version) {
			version = initAppVersion(AppInfo.context);
		}
		return version;
	}

	/**
	 * 获取游戏道号
	 * 
	 * @return
	 */
	public static String getEntrance() {
		if (null == entrance) {
			entrance = getEntrance(AppInfo.context);
		}
		return entrance;
	}

	/**
	 * 获取游戏显示名称
	 * 
	 * @return
	 */
	public static String getAppName() {
		if (null == appName) {
			appName = getAppName(AppInfo.context);
		}
		return appName;
	}
	


	/**
	 * 获取游戏的统一ID(融合工程)
	 * 
	 * @return
	 */
	public static String getTId() {
		if (null == tId) {
			tId = getTId(AppInfo.context);
		}
		return tId;
	}

	private static String getTId(Context context) {
		ApplicationInfo appInfo = null;
		try {
			appInfo = context.getPackageManager().getApplicationInfo(
					context.getPackageName(), PackageManager.GET_META_DATA);

		} catch (Exception e) {
			Debug.e("AppInfo->getTbuId, meet error. e = " + e.toString());
		}
		String tbuId = String.valueOf(appInfo.metaData.getString(TBU_ID_KEY));
		Debug.i("AppInfo->getTbuId, tbuId = " + tbuId);
		return ReadJsonUtil.decoderByDES(tbuId,ReadJsonUtil.KEY);
	}

	private static String initAppVersion(Context context) {
		String version = DEFAULT_VERSION;
		try {
			PackageManager pm = context.getPackageManager();
			PackageInfo pi = pm.getPackageInfo(context.getPackageName(), 0);
			version = String.valueOf(pi.versionCode);
		} catch (Exception e) {
			version = DEFAULT_VERSION;
		}
		if (StringUtils.isBlank(version)) {
			version = DEFAULT_VERSION;
		}
		return version;
	}

	private static String getAppName(Context context) {
		PackageManager pm = context.getPackageManager();
		ApplicationInfo ai;
		try {
			ai = pm.getApplicationInfo(context.getPackageName(), 0);
		} catch (NameNotFoundException e) {
			ai = null;
			e.printStackTrace();
		}

		String applicationName = (String) pm.getApplicationLabel(ai);
		return applicationName;
	}

	private static final String CHANNEL_ID_KEY = "Channel ID";

	private static String getEntrance(Context context) {
		ApplicationInfo appInfo = null;
		try {
			appInfo = context.getPackageManager().getApplicationInfo(
					context.getPackageName(), PackageManager.GET_META_DATA);

		} catch (Exception e) {
			e.printStackTrace();
		}
		String entranceBuffer = appInfo.metaData.getString(CHANNEL_ID_KEY);
		if (StringUtils.isBlank(entranceBuffer)) {
			entranceBuffer = "unknow";
		}
		if (entranceBuffer.length() > 32) {
			// 判断如果入口值长度大于32，则截取前32位
			entranceBuffer = entranceBuffer.substring(0, 32);
		}
		return ReadJsonUtil.decoderByDES(entranceBuffer,ReadJsonUtil.KEY);
	}
	
	


	/**
	 * 判断当前应用是否显示(工具类)。
	 * 
	 * @param context
	 * @return
	 */
	public static boolean isAppVisible(Context context) {
		if (context != null) {
			ActivityManager am = (ActivityManager) context
					.getSystemService(Context.ACTIVITY_SERVICE);
			ComponentName cn = am.getRunningTasks(1).get(0).topActivity;
			if (cn.getPackageName().equals(context.getPackageName())) {
				return true;
			}
		}
		return false;
	}
}
