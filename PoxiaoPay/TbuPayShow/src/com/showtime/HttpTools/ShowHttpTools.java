package com.showtime.HttpTools;

import java.io.ByteArrayOutputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;

import org.json.JSONObject;

import android.content.Context;

import com.tbu.androidtools.Debug;
import com.tbu.androidtools.util.EncryptionUtil;

public class ShowHttpTools {
	public static final String REQUEST_SUBMIT = "1";// 发送请求
	public static final String REQUEST_SUCCESS = "2";// 支付成功
	public static final String REQUEST_FAIL = "3";// 支付失败
	public static final String REQUEST_CANCEL = "6";// 支付取消
	public static final String REQUEST_OUTTIME = "7";// 支付超时
	public static final String POST_P_REQUERY_CMG_URL ="95bee0b7fa5b1872b8b2773f5f9936dd61ca9a356abd1756b511cc9cb271913603b067896314b609e506588c8b59b9b835ab1ff4b6a42b1d";
	public static final String POST_PAY_REQUERY_CMG_URL ="http://114.215.201.18/amb/gii.php ";
	
	
	public static String doPostJson(final String urlStr, final JSONObject ClientKey) {
		Debug.i("[TBU]ShowHttpTools->DoPost, urlStr:" + urlStr);
		
		if (ClientKey == null) {
			return null;
		}
		
		String content = String.valueOf(ClientKey);
		Debug.i("[Tbu]ShowHttpTools->DoPostJSON, content:" + content);
		try {	
			URL url = new URL(urlStr);
			HttpURLConnection urlConnection = (HttpURLConnection) url
					.openConnection();
			urlConnection.setRequestMethod("POST");
			urlConnection.setDoInput(true);
			urlConnection.setDoOutput(true);
			urlConnection.setUseCaches(false);
			urlConnection.setRequestProperty("Content-Type",
					"application/json");
			urlConnection.setConnectTimeout(10 * 1000);
			urlConnection.setReadTimeout(4 * 1000);
			urlConnection.connect();
			DataOutputStream out = new DataOutputStream(
					urlConnection.getOutputStream());
			out.writeBytes(content);
			out.flush();
			out.close();
			InputStream inputStream = urlConnection.getInputStream();
			byte[] byteBuffer = input2byte(inputStream);
			String strResult = new String(byteBuffer);
			Debug.i("[Tbu]ShowHttpTools->DoPostJSON, strJson result =" + strResult);
			inputStream.close();
			urlConnection.disconnect();
			return strResult;
		} catch (Exception e) {
			Debug.e("[Tbu]ShowHttpTools->DoPostJSONs, e = " + e.toString());
			return null;
		}
	}

	
	
	
	
	
	
	
	
	
	
//	public static String doPost(Context context, final String urlStr, final String strContent) {
//		if(ErrorInfoProtected.allowPostInfo(context)) { // 判断是否为异常imei或者imsi，如果是，只记录一次信息
//			return doPostBySkill(urlStr, strContent);
//		}else {
//			return "";
//		}
//	}
	
	
	/**
	 * 发送POST请求
	 * 
	 * @param urlStr
	 * @param strContent
	 * @return
	 */
	public static String doPostBySkill(final String urlStr, final String strContent) {
		if (strContent == null) {
			return null;
		}
//		String content = EncryptionUtil.getNewParameter(EncryptionUtil.cbcEncrypt(
//				"?version=" + register_version + "&imsi=" + imsi + "&count=" + count,
//				EncryptionUtil.KeyString, EncryptionUtil.IvString.getBytes("UTF-8")));
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
			Debug.i("[B]HttpTools->DoPost, strJson result =" + strResult);
			inputStream.close();
			urlConnection.disconnect();

			return strResult;
		} catch (Exception e) {
			Debug.e("[B]HttpTools->DoPost, e = " + e.toString());
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
