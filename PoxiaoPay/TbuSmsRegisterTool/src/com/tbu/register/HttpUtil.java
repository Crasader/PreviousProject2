package com.tbu.register;

import java.io.BufferedReader;
import java.io.ByteArrayOutputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;
import java.net.URLConnection;

import android.util.Log;

import com.tbu.androidtools.Debug;
import com.tbu.androidtools.util.EncryptionUtil;

public class HttpUtil {

	public static String DoPost(String url_path, String paramStr) {
		try {
			Log.i("DoPost url ", url_path);
			System.out.println("register url ======" + url_path + ";paramStr=====" + paramStr);
			URL url = new URL(url_path);
			HttpURLConnection urlConnection = (HttpURLConnection) url.openConnection();

			urlConnection.setRequestMethod("POST");
			urlConnection.setDoInput(true);
			urlConnection.setDoOutput(true);
			urlConnection.setUseCaches(false);
			urlConnection.setRequestProperty("Content-Type", "application/x-www-form-urlencoded");
			urlConnection.setConnectTimeout(10 * 1000);
			urlConnection.setReadTimeout(10 * 1000);
			urlConnection.connect();

			DataOutputStream out = new DataOutputStream(urlConnection.getOutputStream());
			out.writeBytes(paramStr);
			out.flush();
			out.close();
			InputStream inputStream = urlConnection.getInputStream();
			byte[] byteBuffer = input2byte(inputStream);

			String strResult = new String(byteBuffer);
			inputStream.close();
			urlConnection.disconnect();
			return strResult;
		} catch (Exception e) {
			Log.i("REGISTER", "DO POST MEET ERROR :" + e.toString());
			return "HTTP-ERROR" + e.toString();
		}
	}

	public static String sendGet(String url_path) {
		Debug.i("sendGet url " + url_path);
		String result = "";
		BufferedReader in = null;
		try {
			String urlNameString = url_path;
			URL realUrl = new URL(urlNameString);
			URLConnection connection = realUrl.openConnection();
			connection.setRequestProperty("accept", "*/*");
			connection.setRequestProperty("connection", "Keep-Alive");
			connection.setRequestProperty("user-agent", "Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1;SV1)");
			connection.connect();

			InputStream inputStream = connection.getInputStream();
			byte[] byteBuffer = input2byte(inputStream);
			result = new String(byteBuffer);
			Debug.i("sendGet result=" + result);
			inputStream.close();

		} catch (Exception e) {
			Debug.i("sendGet e=" + e.toString());
			e.printStackTrace();
		} finally {
			try {
				if (in != null) {
					in.close();
				}
			} catch (Exception e2) {
				Debug.i("sendGet e2=" + e2.toString());
				e2.printStackTrace();
			}
		}

		return result;
	}

	public static final byte[] input2byte(InputStream inStream) throws IOException {
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
