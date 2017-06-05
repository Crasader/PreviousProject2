package com.t.h;

import java.io.ByteArrayOutputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;

import com.tbu.androidtools.ugly.http.KeyValue;

public class HttpUtil {
	/**
	 * POST
	 * 
	 * @param urlStr
	 * @param strContent
	 * @return
	 */
	public static  String doPost(final String urlStr, final String strContent) {
		System.out.println("HttpUtil->DoPost, urlStr:" + urlStr);
		System.out.println("HttpUtil->DoPost, strContent:" + strContent);
		if (strContent == null) {
			return null;
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
			System.out
					.println("HttpUtil->DoPost, strJson result =" + strResult);
			inputStream.close();
			urlConnection.disconnect();

			return strResult;
		} catch (Exception e) {
			System.out.println("HttpUtil->DoPost, e = " + e.toString());
			return null;
		}
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

	public static String DoContentJoint(KeyValue... keyValueArray) {
		if (keyValueArray.length > 0) {
			String httpContent = new String();
			for (int i = 0; i < keyValueArray.length; i++) {
				if (0 == i)
					httpContent += keyValueArray[i].getmKeyString() + "="
							+ keyValueArray[i].getmValueString();// "?"+
				else
					httpContent += "&" + keyValueArray[i].getmKeyString() + "="
							+ keyValueArray[i].getmValueString();
			}

			return httpContent;
		}

		return null;
	}
}
