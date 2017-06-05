package com.tbu.wx.http;

import java.io.ByteArrayOutputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;

import com.tbu.androidtools.Debug;
import com.tbu.wx.http.callback.HttpCallBack;

public class HttpUtil {
	/**
	 * POST
	 * 
	 * @param urlStr
	 * @param strContent
	 * @return
	 */
	public static void doPost(final String urlStr, final String strContent,
			HttpCallBack httpCallBack) {
		Debug.e("HttpUtil->DoPost, urlStr:" + urlStr);
		Debug.e("HttpUtil->DoPost, strContent:" + strContent);
		if (strContent == null) {
			httpCallBack.callBack(null);
		}
		try {
			URL url = new URL(urlStr);
			HttpURLConnection urlConnection = (HttpURLConnection) url
					.openConnection();

			urlConnection.setRequestMethod("POST");
			urlConnection.setDoInput(true);
			urlConnection.setDoOutput(true);
			urlConnection.setUseCaches(false);
			urlConnection.setRequestProperty("Content-Type",
					"application/x-www-form-urlencoded");
			urlConnection.setConnectTimeout(10 * 1000);
			urlConnection.setReadTimeout(10 * 1000);
			urlConnection.connect();

			DataOutputStream out = new DataOutputStream(
					urlConnection.getOutputStream());
			out.writeBytes(strContent);
			out.flush();
			out.close();
			InputStream inputStream = urlConnection.getInputStream();
			byte[] byteBuffer = input2byte(inputStream);

			String strResult = new String(byteBuffer);
			Debug.e("HttpUtil->DoPost, strJson result =" + strResult);
			inputStream.close();
			urlConnection.disconnect();
			httpCallBack.callBack(strResult);
		} catch (Exception e) {
			Debug.e("HttpUtil->DoPost, e = " + e.toString());
			httpCallBack.callBack(null);
		}
	}

	public static void doGet(final String urlStr, final String strContent,
			HttpCallBack httpCallBack) {
		if (strContent == null) {
			httpCallBack.callBack(null);
		}
		try {
			URL url = new URL(urlStr + "?" + strContent);
			Debug.e("doGet URL:" + url);
			HttpURLConnection urlConnection = (HttpURLConnection) url
					.openConnection();
			urlConnection.setRequestMethod("GET");
			urlConnection.setUseCaches(false);
			urlConnection.setConnectTimeout(10 * 1000);
			urlConnection.setReadTimeout(10 * 1000);

			InputStream inputStream = urlConnection.getInputStream();
			byte[] byteBuffer = input2byte(inputStream);

			String strResult = new String(byteBuffer);
			Debug.e("HttpUtil->DoGet, strJson result =" + strResult);
			inputStream.close();
			urlConnection.disconnect();
			httpCallBack.callBack(strResult);
		} catch (Exception e) {
			Debug.e("HttpUtil->DoGet, e = " + e.toString());
			httpCallBack.callBack(null);
		}
	}

	public static String DoContentJoint(KeyValue... keyValueArray) {
		if (keyValueArray.length > 0) {
			String httpContent = new String();
			for (int i = 0; i < keyValueArray.length; i++) {
				if (0 == i)
					httpContent += keyValueArray[i].getmKeyString() + "="
							+ keyValueArray[i].getmValueString();
				else
					httpContent += "&" + keyValueArray[i].getmKeyString() + "="
							+ keyValueArray[i].getmValueString();
			}

			return httpContent;
		}
		return null;
	}

	private static byte[] input2byte(InputStream inStream) throws IOException {
		ByteArrayOutputStream swapStream = new ByteArrayOutputStream();
		byte[] buff = new byte[100];
		int rc = 0;
		while ((rc = inStream.read(buff, 0, 100)) > 0) {
			swapStream.write(buff, 0, rc);
		}
		byte[] in2b = swapStream.toByteArray();
		return in2b;
	}
}
