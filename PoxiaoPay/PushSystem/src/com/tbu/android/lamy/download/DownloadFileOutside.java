package com.tbu.android.lamy.download;

import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;

import com.tbu.android.lamy.util.Debug;
import com.tbu.android.lamy.util.DownloadUtil;

import android.content.Context;
import android.os.AsyncTask;

/**
 * TODO : 如果多个应用使用此插件，可能会有写文件的问题 将文件下载到外部存储中。
 * 
 * @author molo
 *
 */
public class DownloadFileOutside extends AsyncTask<String, Integer, String> {

	private String fileDir = "";
	private boolean successDownload = false;
	private DownloadCallback downloadCallback;
	private Context context;
	private String packageName;

	public DownloadFileOutside(Context context,
			DownloadCallback downloadCallback, final String packageName) {
		this.context = context;
		this.packageName = packageName;
		this.downloadCallback = downloadCallback;
	}

	private long fileLength;
	private long createTime;

	@Override
	protected String doInBackground(String... sInfos) {
		createTime = System.currentTimeMillis();
		Debug.i("DownloadFileOutside->doInBackground, download url is : "
				+ sInfos[0]);
		Debug.i("DownloadFileOutside->doInBackground, sInfos[1]version = "
				+ sInfos[1]);
		Debug.i("DownloadFileOutside->doInBackground, sInfos[2]appname = "
				+ sInfos[2]);
		try {
			URL url = new URL(sInfos[0]);

			HttpURLConnection connection = (HttpURLConnection) url
					.openConnection();
			long downloaded = 0;

			Debug.i("DownloadFileOutside->doInBackground, sd card exist");
			DownloadUtil.makeRootDirectory();
			fileDir = DownloadUtil.getSdFilePath(context, sInfos[2], sInfos[1]);
			Debug.i("DownloadFileOutside->doInBackground, sdcard fileDir = "
					+ fileDir);
			connection.setDoInput(true);
			connection.setConnectTimeout(10000);

			Debug.i("DownloadFileOutside->doInBackground, connect ready");
			connection.connect();
			Debug.i("DownloadFileOutside->doInBackground, connect do");

			int status = connection.getResponseCode();
			if (!(status == 200 || status == 206 || status == 201 || status == 202)) {
				Debug.e("DownloadFileOutside->doInBackground, erroe status = "
						+ status);
				successDownload = false;
				return null;
			}
			Debug.i("DownloadFileOutside->doInBackground, connect status="
					+ status);
			fileLength = connection.getContentLength();

			// 本地文件分析，如果已经下载完成则直接返回结果
			File downloadFile = new File(fileDir);
			if (downloadFile.exists() && downloadFile.isFile()) {
				Debug.i("DownloadFileOutside->doInBackground, downloadFile is exist and is File, fileDir = "
						+ fileDir);
				downloaded = downloadFile.length();
			}

			Debug.i("DownloadFileOutside->doInBackground, fileLength = "
					+ fileLength);
			Debug.i("DownloadFileOutside->doInBackground, downloaded = "
					+ downloaded);

			if (fileLength == downloaded) {
				Debug.i("DownloadFileOutside->doInBackground, connect arg same file length");
				successDownload = true;
				return null;
			}

			byte data[] = new byte[1024];
			long total = 0;
			int count;

			Debug.i("DownloadFileOutside->doInBackground, start process = "
					+ ((int) ((total + downloaded) * 100 / (downloaded + fileLength))));
			publishProgress((int) ((total + downloaded) * 100 / (downloaded + fileLength)));

			InputStream input = new BufferedInputStream(
					connection.getInputStream());
			OutputStream output;

			Debug.i("DownloadFileOutside->doInBackground, write to sd card , fileDir= "
					+ fileDir);
			output = new FileOutputStream(fileDir);

			// 处理下载
			while ((count = input.read(data)) != -1) {
				total += count;
				publishProgress((int) ((total + downloaded) * 100 / (downloaded + fileLength)));
				output.write(data, 0, count);
			}
			fileLength = total;
			output.flush();
			output.close();
			input.close();
			successDownload = true;
		} catch (Exception e) {
			Debug.i("DownloadFileOutside-> doInBackground,get error message on download."
					+ e.getMessage());
			successDownload = false;
		}
		return null;
	}

	@Override
	protected void onPreExecute() {
		super.onPreExecute();
	}

	private int count;

	@Override
	protected void onProgressUpdate(Integer... progress) {
		super.onProgressUpdate(progress);
		count++;
		if (count >= 200) {
			count = 0;
			// Debug.i("DownloadFileOutside->onProgressUpdate, 已下载" +
			// progress[0] + "%");
		}

	}

	@Override
	protected void onPostExecute(String result) {
		super.onPostExecute(result);
		if (successDownload) { // 处理下载成功
			Debug.i("DownloadFileOutside->onPostExecute, 下载完成...");
			downloadCallback.result(true, fileDir, fileLength,
					(System.currentTimeMillis() - createTime), packageName);
		} else { // 处理下载失败
			Debug.i("DownloadFileOutside->onPostExecute, 很遗憾,下载失败,请稍后再试...");
			downloadCallback.result(false, "", fileLength,
					(System.currentTimeMillis() - createTime), packageName);
		}
	}

}
