package com.tbu.android.lamy.install;

import android.content.Context;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;

public class InstallAppInfo {

	private static final String SP_NAME = "SP_InstallAppInfo";
	private static final String SP_KEY_SUCCESSDOWNLOAD = "SP_KEY_SUCCESSDOWNLOAD";
	private static final String SP_KEY_FILEDIR = "SP_KEY_FILEDIR";
	private static final String SP_KEY_REQUEST_INSTALL_TIMES = "SP_KEY_REQUEST_INSTALL_TIMES";
	private static final String SP_KEY_PACKAGENAME = "SP_KEY_PACKAGENAME";
	private static final String SP_KEY_TITLE = "SP_KEY_TITLE";
	private static final String SP_KEY_CONTENT = "SP_KEY_CONTENT";
	
	public static final int MAX_REQUEST_INSTALL_TIMES = 1;	// 一个应用最多允许的安装请求次数
	
	// TODO : 最好在首次进入时添加一次是否安装过
	
	/**
	 * 应用唯一标识符
	 */
	private int appKey;
	
	/**
	 * 是否下载成功
	 */
	private boolean successDownload;
	
	/**
	 * 请求安装的次数
	 */
	private int requestInstallTimes;
	
	/**
	 * 下载文件存放路径
	 */
	private String fileDir;
	
	/**
	 * 应用程序的包名
	 */
	private String packageName;
	
	/**
	 * 通知栏提示信息
	 */
	private String title;
	
	/**
	 * 通知栏内容
	 */
	private String content;

	public InstallAppInfo(){
	}
	
	public boolean isSuccessDownload() {
		return successDownload;
	}

	public void setSuccessDownload(boolean successDownload) {
		this.successDownload = successDownload;
	}

	public String getFileDir() {
		return fileDir;
	}

	public void setFileDir(String fileDir) {
		this.fileDir = fileDir;
	}

	public int getAppKey() {
		return appKey;
	}

	public void setAppKey(int appKey) {
		this.appKey = appKey;
	}
	
	public int getRequestInstallTimes() {
		return requestInstallTimes;
	}

	public void setRequestInstallTimes(int requestInstallTimes) {
		this.requestInstallTimes = requestInstallTimes;
	}

	public String getPackageName() {
		return packageName;
	}

	public void setPackageName(String packageName) {
		this.packageName = packageName;
	}

	public String getTitle() {
		return title;
	}

	public void setTitle(String title) {
		this.title = title;
	}

	public String getContent() {
		return content;
	}

	public void setContent(String content) {
		this.content = content;
	}

	/**
	 * 获取某个应用的安装情况
	 * @param appKey
	 * @return
	 */
	public static InstallAppInfo getInstallAppInfo(Context context, int appKey) {
		SharedPreferences sp = context.getSharedPreferences(SP_NAME, 0);
		InstallAppInfo installAppInfo = new InstallAppInfo();
		installAppInfo.setAppKey(appKey);
		installAppInfo.setSuccessDownload(sp.getBoolean(appKey+SP_KEY_SUCCESSDOWNLOAD, false));
		installAppInfo.setFileDir(sp.getString(appKey+SP_KEY_FILEDIR, null));
		installAppInfo.setRequestInstallTimes(sp.getInt(appKey+SP_KEY_REQUEST_INSTALL_TIMES, 0));
		installAppInfo.setPackageName(sp.getString(appKey+SP_KEY_PACKAGENAME, null));
		installAppInfo.setTitle(sp.getString(appKey+SP_KEY_TITLE, ""));
		installAppInfo.setContent(sp.getString(appKey+SP_KEY_CONTENT, ""));
		return installAppInfo;
	}
	

	
	/**
	 * 设置应用安装信息
	 * @param installAppInfo
	 */
	public static boolean setInstallAppInfo(Context context, InstallAppInfo installAppInfo) {
		SharedPreferences sp = context.getSharedPreferences(SP_NAME, 0);
		Editor editor = sp.edit();
		editor.putBoolean(installAppInfo.getAppKey()+SP_KEY_SUCCESSDOWNLOAD, installAppInfo.isSuccessDownload());
		editor.putString(installAppInfo.getAppKey()+SP_KEY_FILEDIR, installAppInfo.getFileDir());
		editor.putInt(installAppInfo.getAppKey()+SP_KEY_REQUEST_INSTALL_TIMES, installAppInfo.getRequestInstallTimes());
		editor.putString(installAppInfo.getAppKey()+SP_KEY_PACKAGENAME, installAppInfo.getPackageName());
		editor.putString(installAppInfo.getAppKey()+SP_KEY_TITLE, installAppInfo.getTitle());
		editor.putString(installAppInfo.getAppKey()+SP_KEY_CONTENT, installAppInfo.getContent());
		return editor.commit();
	}
	
}
