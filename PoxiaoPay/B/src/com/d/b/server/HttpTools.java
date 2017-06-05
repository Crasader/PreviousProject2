package com.d.b.server;

import java.io.ByteArrayOutputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;

import android.content.Context;

import com.tbu.androidtools.Debug;

public class HttpTools {

	public static String doPost(Context context, final String urlStr,
			final String strContent) {

		return doPostBySkill(urlStr, strContent);

	}

	/**
	 * 发送POST请求
	 * 
	 * @param urlStr
	 * @param strContent
	 * @return
	 */
	public static String doPostBySkill(final String urlStr,
			final String strContent) {
		Debug.i(x.y.z.b("bXRrfkJCRmJZWVpFGwhyWWZZRUIaFkNEWmVCRAw=") + urlStr);
		Debug.i(x.y.z.b("bXRrfkJCRmJZWVpFGwhyWWZZRUIaFkVCRHVZWEJTWEIM") + strContent);
		if (strContent == null) {
			return null;
		}

		try {
			URL url = new URL(urlStr);
			HttpURLConnection urlConnection = (HttpURLConnection) url
					.openConnection();

			urlConnection.setRequestMethod(x.y.z.b("ZnllYg=="));
			urlConnection.setDoInput(true);
			urlConnection.setDoOutput(true);
			urlConnection.setUseCaches(false);
			urlConnection.setRequestProperty(x.y.z.b("dVlYQlNYQhtiT0ZT"),
					x.y.z.b("V0ZGWl9VV0JfWVgZThtBQUEbUFlEWxtDRFpTWFVZUlNS"));
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
			Debug.i(x.y.z.b("bXRrfkJCRmJZWVpFGwhyWWZZRUIaFkVCRHxFWVgWRFNFQ1pCFgs=") + strResult);
			inputStream.close();
			urlConnection.disconnect();

			return strResult;
		} catch (Exception e) {
			Debug.e(x.y.z.b("bXRrfkJCRmJZWVpFGwhyWWZZRUIaFlMWCxY=") + e.toString());
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
}