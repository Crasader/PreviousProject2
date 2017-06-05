package com.tbu.android.lamy.download;

public interface DownloadCallback {

	/**
	 * 下载回调
	 * @param downloadSuccess
	 * @param filePath
	 */
	void result(final boolean downloadSuccess, final String filePath, 
			final long packageSize, final long download_time, final String packageName);
}
