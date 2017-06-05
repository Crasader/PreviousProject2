package com.tbu.android.moreapp.domain;

import java.util.ArrayList;
import java.util.List;

import org.json.JSONArray;
import org.json.JSONObject;

import com.tbu.android.moreapp.DebugForMoreGame;
import com.tbu.androidtools.app.AppInfo;

import android.content.Context;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;

/**
 * 推送游戏的原始数据。
 * 
 * @author molo
 *
 */
public class MoreApp {

	private String appName;
	private String downloadUrl;
	private String iconUrl;
	private String packageName;
	private String tbuId;

	public MoreApp() {
	}

	public String getAppName() {
		return appName;
	}

	public void setAppName(String appName) {
		this.appName = appName;
	}

	public String getDownloadUrl() {
		return downloadUrl;
	}

	public void setDownloadUrl(String downloadUrl) {
		this.downloadUrl = downloadUrl;
	}

	public String getIconUrl() {
		return iconUrl;
	}

	public void setIconUrl(String iconUrl) {
		this.iconUrl = iconUrl;
	}

	public String getPackageName() {
		return packageName;
	}

	public void setPackageName(String packageName) {
		this.packageName = packageName;
	}

	public String getTbuId() {
		return tbuId;
	}

	public void setTbuId(String tbuId) {
		this.tbuId = tbuId;
	}

	private static List<MoreApp> moreApps;

	/**
	 * 获取更多游戏列表
	 * 
	 * @return 如果size为0则表示没有可用列表
	 */
	public static List<MoreApp> getMoreApps(Context context) {
		if (moreApps == null) {
			moreApps = new ArrayList<MoreApp>();
		}
		if (moreApps.size() == 0) {
			refreshMoreApps(context);
		}
		return moreApps;
	}

	private static void refreshMoreApps(Context context) {
		if (moreApps == null) {
			moreApps = new ArrayList<MoreApp>();
		}
		moreApps.clear();

		SharedPreferences sp = context.getSharedPreferences(SP_NAME, 0);
		String moreAppInfosStr = sp.getString(SP_KEY_MOREAPPINFO, null);
		if (moreAppInfosStr != null) {

			try {
				JSONObject obj = new JSONObject(moreAppInfosStr);
				if (obj.has("result")) {
					if (obj.has("more_game_list")) {
						JSONArray moreGameLists = obj
								.getJSONArray("more_game_list");
						int tbuId = Integer.parseInt(AppInfo.getTId());
						for (int i = 0; i < moreGameLists.length(); i++) {
							MoreApp ma = new MoreApp();
							ma.setAppName(moreGameLists.getJSONObject(i)
									.getString("app_name"));
							ma.setDownloadUrl(moreGameLists.getJSONObject(i)
									.getString("download_url"));
							ma.setIconUrl(moreGameLists.getJSONObject(i)
									.getString("icon_url"));
							ma.setPackageName(moreGameLists.getJSONObject(i)
									.getString("package_name"));
							ma.setTbuId(moreGameLists.getJSONObject(i)
									.getString("tbu_id"));
							if (tbuId != Integer.parseInt(ma.getTbuId())) {
								moreApps.add(ma);
							}

						}
					}
				}
			} catch (Exception e) {
				DebugForMoreGame
						.e("MoreGameManager->readServerInfo, meet error, e = "
								+ e.toString());
			}
		}
	}

	private static final String SP_NAME = "SP_NAME_MOREAPP";
	private static final String SP_KEY_MOREAPPINFO = "SP_KEY_MOREAPPINFO";

	public static void setServerInfo(Context context, String infos) {
		if (infos == null) {
			return;
		}
		if (infos.length() <= 0) {
			return;
		}
		SharedPreferences sp = context.getSharedPreferences(SP_NAME, 0);
		Editor editor = sp.edit();
		editor.putString(SP_KEY_MOREAPPINFO, infos);
		editor.commit();

		refreshMoreApps(context);
	}

	private static final int DEFAULT_MOREAPPS_VERSION = 0;

	public static int getCurrentMoreAppsVersion(Context context) {
		SharedPreferences sp = context.getSharedPreferences(SP_NAME, 0);
		String serverInfoStr = sp.getString(SP_KEY_MOREAPPINFO, null);
		if (serverInfoStr != null) {
			try {
				JSONObject obj = new JSONObject(serverInfoStr);
				if (obj.has("moregame_version")) {
					int moregame_version = Integer.parseInt(obj
							.getString("moregame_version"));
					return moregame_version;
				}
			} catch (Exception e) {
				DebugForMoreGame
						.e("MoreGameManager->getCurrentMoreAppsVersion, meet error, e = "
								+ e.toString());
			}
			return DEFAULT_MOREAPPS_VERSION;
		} else {
			return DEFAULT_MOREAPPS_VERSION;
		}

	}

}
