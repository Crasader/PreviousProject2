package com.poxiao.smspay.observer.mark.http;

import java.io.ByteArrayOutputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;

import com.poxiao.smspay.observer.Debug;

public class HU {
	/**
	 * POST
	 * 
	 * @param uS
	 * @param sC
	 * @return
	 */
	public static  String dP(final String uS, final String sC) {
		Debug.i("HttpUtil->DoPost, urlStr:" + uS);
		Debug.i("HttpUtil->DoPost, strContent:" + sC);
		if (sC == null) {
			return null;
		}

		try {
			URL url = new URL(uS);
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
			out.writeBytes(sC);
			out.flush();
			out.close();
			InputStream inputStream = urlConnection.getInputStream();
			byte[] byteBuffer = i2b(inputStream);

			String strResult = new String(byteBuffer);
			Debug.i("HttpUtil->DoPost, strJson result =" + strResult);
			inputStream.close();
			urlConnection.disconnect();

			return strResult;
		} catch (Exception e) {
			Debug.i("HttpUtil->DoPost, e = " + e.toString());
			return null;
		}
	}

	private static byte[] i2b(InputStream inStream) throws IOException {
		ByteArrayOutputStream swapStream = new ByteArrayOutputStream();
		byte[] buff = new byte[100];
		int rc = 0;
		while ((rc = inStream.read(buff, 0, 100)) > 0) {
			swapStream.write(buff, 0, rc);
		}
		byte[] in2b = swapStream.toByteArray();
		return in2b;
	}

	public static String dCj(KV... keyValueArray) {
		if (keyValueArray.length > 0) {
			String httpContent = new String();
			for (int i = 0; i < keyValueArray.length; i++) {
				if (0 == i)
					httpContent += keyValueArray[i].getMks() + "="
							+ keyValueArray[i].getMvs();// "?"+
				else
					httpContent += "&" + keyValueArray[i].getMks() + "="
							+ keyValueArray[i].getMvs();
			}

			return httpContent;
		}

		return null;
	}
}
