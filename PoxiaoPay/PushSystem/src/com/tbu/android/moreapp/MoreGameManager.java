package com.tbu.android.moreapp;

import java.util.List;

import org.json.JSONObject;

import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.ResolveInfo;
import android.net.Uri;

import com.tbu.android.moreapp.domain.MoreApp;
import com.tbu.android.moreapp.domain.MoreAppCallback;
import com.tbu.android.moreapp.server.ServerManager;
import com.tbu.androidtools.Debug;
import com.tbu.androidtools.app.AppInfo;
import com.tbu.androidtools.util.EncryptionUtil;
import com.tbu.androidtools.util.ReadJsonUtil;

public class MoreGameManager {

	/**
	 * 更多游戏版本号
	 */
	public static final int VERSION = 1;

	public static final String MORE_GAME_URL = "32f9b66e39ad48ccf4c33ba0a059ae6630d0491b88efd0b8bde65717313c9f8d89e7d4736997c18b";

	/**
	 * 初始化更多游戏模块
	 * 
	 * @param context
	 * @param moreAppCallback
	 *            本次数据是否有更新的回调，true，有数据更新，false，没有数据更新
	 */
	public static void init(final Context context, final MoreAppCallback moreAppCallback) {
		new Thread(new Runnable() {

			@Override
			public void run() {
				try {
					String content = EncryptionUtil.getNewParameter(EncryptionUtil.cbcEncrypt(
							ServerManager.createMoreGameReqStr(context, String.valueOf(MoreGameManager.VERSION),
									AppInfo.getEntrance(), String.valueOf(MoreApp.getCurrentMoreAppsVersion(context)),
									AppInfo.getTId()),
							EncryptionUtil.KeyString, EncryptionUtil.IvString.getBytes("UTF-8")));
					String result = EncryptionUtil.cbcDecrypt(
							ServerManager.doPost(ReadJsonUtil.decoderByDES(MORE_GAME_URL, "p_k"), content),
							EncryptionUtil.KeyString, EncryptionUtil.IvString.getBytes("UTF-8"));

					boolean changed = readServerInfo(context, result);
					if (moreAppCallback != null) {
						moreAppCallback.result(changed);
					}
				} catch (Exception e) {
					e.printStackTrace();
				}
			}

		}).start();
	}

	public static List<MoreApp> getMoreApps(Context context) {
		return MoreApp.getMoreApps(context);
	}

	private static boolean readServerInfo(Context context, String result) {
		boolean changed = false;
		if (result == null) {
			return changed;
		}

		try {
			JSONObject obj = new JSONObject(result);
			if (obj.has("result")) {
				boolean allow = "0".equals(obj.getString("result")) ? true : false;
				updateAllowShowMoreApps(context, allow);
				if (allow && obj.has("moregame_version")) {
					int moregame_version = Integer.parseInt(obj.getString("moregame_version"));
					DebugForMoreGame.i("MoreGameManager->readServerInfo,moregame_version = " + moregame_version);
					if (moregame_version > MoreApp.getCurrentMoreAppsVersion(context)) {
						MoreApp.setServerInfo(context, result);
						changed = true;
					}
				} else if (!allow) {
					MoreApp.setServerInfo(context, result);
				}

			}
		} catch (Exception e) {
			DebugForMoreGame.e("MoreGameManager->readServerInfo, meet error, e = " + e.toString());
		}

		return changed;
	}

	private static final String SP_NAME = "SP_NAME_MOREAPP_SWITCH";
	private static final String SP_KEY_MOREAPPINFO_SWITCH = "SP_KEY_MOREAPPINFO_SWITCH";

	/**
	 * 是否允许显示更多游戏
	 * 
	 * @param context
	 * @return
	 */
	public static boolean allowShowMoreApps(Context context) {
		SharedPreferences sp = context.getSharedPreferences(SP_NAME, 0);
		return sp.getBoolean(SP_KEY_MOREAPPINFO_SWITCH, false);
	}

	public static void updateAllowShowMoreApps(Context context, boolean allow) {
		SharedPreferences sp = context.getSharedPreferences(SP_NAME, 0);
		Editor editor = sp.edit();
		editor.putBoolean(SP_KEY_MOREAPPINFO_SWITCH, allow);
		editor.commit();
	}

	/**
	 * 处理启动其它应用的接口
	 * 
	 * @param param
	 * @param url
	 */
	public static void doStartNewGame(Context context, String packageName, String url) {
		PackageInfo pi;
		try {
			pi = context.getPackageManager().getPackageInfo(packageName, 0);
			Intent resolveIntent = new Intent(Intent.ACTION_MAIN, null);
			resolveIntent.setPackage(pi.packageName);
			PackageManager pManager = context.getPackageManager();
			List<ResolveInfo> apps = pManager.queryIntentActivities(resolveIntent, 0);

			ResolveInfo ri = (ResolveInfo) apps.iterator().next();
			if (ri != null) {
				packageName = ri.activityInfo.packageName;
				String className = ri.activityInfo.name;
				Intent intent = new Intent(Intent.ACTION_MAIN);
				intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
				ComponentName cn = new ComponentName(packageName, className);
				intent.setComponent(cn);
				context.startActivity(intent);
			} else {
				Intent intent = new Intent();
				intent.setAction("android.intent.action.VIEW");
				intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
				Uri content_url = Uri.parse(url);
				intent.setData(content_url);
				context.startActivity(intent);
			}
		} catch (Exception e) {
			try {
				Intent intent = new Intent();
				intent.setAction("android.intent.action.VIEW");
				intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
				Uri content_url = Uri.parse(url);
				intent.setData(content_url);
				context.startActivity(intent);
			} catch (Exception e2) {
				Debug.e("" + e2.toString());
			}
		}

	}
}
