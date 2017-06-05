package com.tbu.android.lamy.download;

import android.content.Context;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;

public class DownloadAppInfo {
	
	private int tbuId;
	private int version;
	private String packagename;
	private String url;
	private String urlweb;
	private String title;
	private String content;

	public DownloadAppInfo(int tbuId, int version, String packagename,
			String url, String urlweb, String title, String content) {
		super();
		this.tbuId = tbuId;
		this.version = version;
		this.packagename = packagename;
		this.url = url;
		this.urlweb = urlweb;
		this.title = title;
		this.content = content;
	}
	
	public int getTbuId() {
		return tbuId;
	}

	public int getVersion() {
		return version;
	}

	public String getPackagename() {
		return packagename;
	}

	public String getUrl() {
		return url;
	}

	public String getUrlweb() {
		return urlweb;
	}

	public String getTitle() {
		return title;
	}

	public String getContent() {
		return content;
	}
	
	private static final String SP_NAME = "SP_DownloadAppInfo";
	private static final String SP_KEY_DOWNLOADAPPINFO_VERSION = "SP_KEY_DOWNLOADAPPINFO_VERSION";
	
	public static int getDownloadAppInfoVersion(Context context) {
		SharedPreferences sp = context.getSharedPreferences(SP_NAME, 0);
		return sp.getInt(SP_KEY_DOWNLOADAPPINFO_VERSION, 0);
	}
	
	public static boolean setDownloadAppInfoVersion(Context context, int version) {
		SharedPreferences sp = context.getSharedPreferences(SP_NAME, 0);
		Editor editor = sp.edit();
		editor.putInt(SP_KEY_DOWNLOADAPPINFO_VERSION, version);
		return editor.commit();
	}
}
