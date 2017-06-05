package com.candy.futon.service;

public interface UpgradeEventListener{
	/**
	 * 
	 * @param haveUpgrade 是否有可用的升级
	 * @param desc	升级的内容描述信息
	 * @param forceUpgrade	
	 * @param size
	 */
	void onCheckResult(boolean haveUpgrade, String desc, boolean forceUpgrade, long size);
	
	void onError(int errorCode, String errorMsg);
	
	/**
	 * 下载进度
	 * @param size
	 */
	void onDownloading(int size);
	
	void onMsg(String msg);
	
	void onDownloadComplete();
	
	void onDownloadInterupted();
	
}