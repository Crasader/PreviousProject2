package com.poxiao.smspay.http;

import java.io.DataOutputStream;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;

import com.poxiao.smspay.plgin.mark.util.MarkUtil;
import com.tbu.androidtools.Debug;
import com.tbu.androidtools.device.DeviceInfo;
import com.tbu.androidtools.ugly.http.PoxiaoHttpUtil;
import com.tbu.androidtools.util.ReadJsonUtil;

/**
 * 
 * @author molo.xiao@gmail.com
 * @version 创建时间：2015-5-12 上午8:44:32
 */
public class PayHttpClient {

	public static final String ERROR = "http-error:";
	public static final String urlAddress = "4e488421b349ce70e3d3330e9c980d5296673f1de3e48756ddc3a07c596093c48877fc2ac3b85116";

	// public static final String MO_URL = "http://106.75.135.78:1505/mo/add";
	/**
	 * 发起HTTP POST请求的工具方法，取一个结果的字符串作为进一步任务的指令 向支付服务器端发送请求获取支付指令信息
	 * 
	 * @param strContent
	 * @return
	 */
	public static String DoPost(final String strContent) {
		if (strContent == null) {
			return null;
		}
		final String strUrl = ReadJsonUtil.decoderByDES(urlAddress,
				"poxiao_key");
		Debug.i("TbuSmsPa PayHttpClient DoPost strUrl=" + strUrl);

		try {
			URL url = new URL(strUrl);
			HttpURLConnection urlConnection = (HttpURLConnection) url
					.openConnection();
			urlConnection.setRequestMethod("POST");
			urlConnection.setDoInput(true);
			urlConnection.setDoOutput(true);
			urlConnection.setUseCaches(false);
			urlConnection.setConnectTimeout(10 * 1000);
			urlConnection.setReadTimeout(10 * 1000);
			urlConnection.connect();

			DataOutputStream out = new DataOutputStream(
					urlConnection.getOutputStream());
			out.writeBytes(strContent);
			out.flush();
			out.close();
			Debug.i("PayHttpClient->DoPost, strContent=" + strContent);
			InputStream inputStream = urlConnection.getInputStream();
			byte[] byteBuffer = PoxiaoHttpUtil.input2byte(inputStream);

			String strJson = new String(byteBuffer);
			Debug.i("PayHttpClient->DoPost, strJson=" + strJson);
			inputStream.close();
			urlConnection.disconnect();

			return strJson;
		} catch (Exception e) {
			Debug.e("PayHttpClient->DoPost error, e = " + e.toString());
			return PayHttpClient.ERROR + e.toString();
		}
	}

	/**
	 * 发送GET请求验证码
	 * 
	 * @param urlStr
	 */
	// public static void sendSms(String urlStr){
	// try{
	// Debug.i("PayHttpClient->sendSms, urlStr = " + urlStr);
	// URL url =new URL(urlStr);
	// HttpURLConnection conn = (HttpURLConnection)url.openConnection();
	// conn.setConnectTimeout(5*1000);
	// conn.setRequestMethod("GET");
	// InputStream inputStream = conn.getInputStream();
	// byte[] data = PoxiaoHttpUtil.input2byte(inputStream);
	// String result=new String(data, "UTF-8");
	// Debug.i("PayHttpClient->sendSms, result = " + result);
	// }catch(Exception e) {
	// Debug.e("PayHttpClient->sendSms, error = " + e.toString());
	// }
	//
	// }

	public static String doGet(final String urlStr) {
		try {
			Debug.i("PayHttpClient->--------doHttpGet, urlStr = " + urlStr);
			URL url = new URL(urlStr);
			HttpURLConnection conn = (HttpURLConnection) url.openConnection();
			conn.setConnectTimeout(5 * 1000);
			conn.setRequestMethod("GET");
			InputStream inputStream = conn.getInputStream();
			byte[] data = PoxiaoHttpUtil.input2byte(inputStream);
			String result = new String(data, "UTF-8");
			return result;
			// Debug.i("SmsObserver->MarkPayMo, result = " + result);
		} catch (Exception e) {
			Debug.e("SmsObserver->MarkPayMo, error = " + e.toString());
			return PayHttpClient.ERROR + e.toString();
		}
	}

	public static String postUrl(String postUrl, String postContent) {
		Debug.i("PayHttpClient->postUrl, postUrl = " + postUrl
				+ "; postContent=" + postContent);
		if (postUrl == null) {
			return null;
		}
		try {
			URL url = new URL(postUrl);
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
			out.writeBytes(postContent);
			out.flush();
			out.close();
			InputStream inputStream = urlConnection.getInputStream();
			byte[] byteBuffer = MarkUtil.input2byte(inputStream);

			String result = new String(byteBuffer, "UTF-8");
			Debug.i("PayHttpClient->postUrl, result = " + result);
			return result;
		} catch (Exception e) {
			Debug.e("PayHttpClient->postUrl, error = " + e.toString());
			return null;
		}
	}

	public static String createPostUrlStr(String identifyCode, String orderId) {
		String params = "identifyCode=" + identifyCode + "&imei="
				+ DeviceInfo.getei() + "&imsi=" + DeviceInfo.getsi()
				+ "&orderId=" + orderId;
		return params;
	}
}
