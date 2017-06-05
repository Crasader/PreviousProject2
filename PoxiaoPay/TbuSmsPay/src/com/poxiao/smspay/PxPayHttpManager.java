package com.poxiao.smspay;

import java.io.IOException;
import java.net.SocketTimeoutException;
import java.net.UnknownHostException;

import org.apache.http.HttpHost;
import org.apache.http.HttpResponse;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.conn.ConnectTimeoutException;
import org.apache.http.conn.ConnectionPoolTimeoutException;
import org.apache.http.conn.params.ConnRoutePNames;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.params.HttpConnectionParams;
import org.apache.http.params.HttpParams;
import org.apache.http.params.HttpProtocolParams;
import org.apache.http.util.EntityUtils;

import android.content.Context;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;

import com.poxiao.smspay.activity.activity_pxpaymain;
import com.tbu.androidtools.Debug;
import com.tbu.androidtools.device.DeviceInfo;

/**
 * 所谓H5支付代码流程
* @author molo.xiao@gmail.com 
* @version 创建时间：2015-5-28 上午9:56:57
* @hide
 */
public class PxPayHttpManager {
	
	private static final String TAG = "PayManager";
		
	public static void pay(final Context context,final Handler handler,final String port){
		Debug.i("PxPayHttpManager->pay, port=" + port);
		if(!isNetConnect(context)){
			Message msg = new Message();
			Bundle b = new Bundle();
			msg.what = activity_pxpaymain.PXPAY_RESULT_NOTIFY_CODE;
            b.putInt(TbuPayCallBack.RESULT_CODE_KEY,
            		TbuPayCallBack.RESULT_CODE_FAIL_ONHTTPPAY);
            b.putString(TbuPayCallBack.RESULT_MESSAGE_KEY,
                     "网络未连接");
            msg.setData(b);
            Debug.e("PxPayHttpManager->pay, isNetConnect = false");
            handler.sendMessage(msg);
			return;
		}
		new AsyncTask<String, Integer, String>() {

			@Override
			protected String doInBackground(String... params) {			
				HttpClient httpClient = null;
				String result = null;
				try {
					httpClient = new DefaultHttpClient();
					HttpParams connectionParams = httpClient.getParams();
					if(isMobileConnect(context) && DeviceInfo.getCarrier()==1){
						HttpHost proxy = new HttpHost("10.0.0.172", 80);
						connectionParams.setParameter(ConnRoutePNames.DEFAULT_PROXY, proxy);
					}
					HttpConnectionParams.setConnectionTimeout(connectionParams, 15*1000);
					HttpConnectionParams.setSoTimeout(connectionParams, 15*1000);
			        String userAgent = "Mozilla/5.0 (Windows; U; Windows NT 5.1; zh-CN; rv:1.9.2) Gecko/20100115 Firefox/3.6";  
			        HttpProtocolParams.setUserAgent(connectionParams, userAgent); 
					HttpGet httpRequest = new HttpGet(params[0]);
					HttpResponse response = httpClient.execute(httpRequest);
					if(response.getStatusLine().getStatusCode() == 200){
						result = EntityUtils.toString(response.getEntity());
						if(result == null){
							result = "0";
						}else if(result.equals("")){
							result = "1";
						}
					}else{						
						result = String.valueOf(response.getStatusLine().getStatusCode());
					}
					Log.e(TAG,"result=" + result);
				} catch (ConnectionPoolTimeoutException e) {
					result = "2";
					Log.i(TAG,">>>>>>>>>>>>>>>>>>>>>>catch ConnectionPoolTimeoutException");
					e.printStackTrace();
				} catch (ConnectTimeoutException e) {
					result = "3";
					Log.i(TAG,">>>>>>>>>>>>>>>>>>>>>>catch ConnectTimeoutException");
					e.printStackTrace();
				} catch (SocketTimeoutException e) {
					result = "4";
					Log.i(TAG,">>>>>>>>>>>>>>>>>>>>>>catch SocketTimeoutException");
					e.printStackTrace();
				} catch (ClientProtocolException e) {
					result = "5";
					Log.i(TAG,">>>>>>>>>>>>>>>>>>>>>>catch ClientProtocolException");
					e.printStackTrace();
				} catch (UnknownHostException e) {
					result = "6";
					Log.i(TAG,">>>>>>>>>>>>>>>>>>>>>>catch UnknownHostException");
					e.printStackTrace();
				} catch (IOException e) {
					result = "7";
					Log.i(TAG,">>>>>>>>>>>>>>>>>>>>>>catch IOException");
					e.printStackTrace();
				} catch (Exception e) {
					result = "8";
					Log.i(TAG,">>>>>>>>>>>>>>>>>>>>>>catch Exception");
					e.printStackTrace();
				}finally {
					if(httpClient != null){
						httpClient.getConnectionManager().shutdown();
					}
				}
				
				return result;
			}
			
			@Override
			protected void onPostExecute(String result) {
				if(result != null && result.length() > 0){
					if(result.contains("g")){
						String target = port.substring(port.length()-4, port.length());
						Log.e(TAG,"target=" + target);
						Log.e(TAG,"result=" + result.substring(result.length()-4, result.length()));
						if(result.substring(result.length()-4, result.length()).equals(target)){
							Message msg = new Message();
							Bundle b = new Bundle();
							msg.what = activity_pxpaymain.PXPAY_RESULT_NOTIFY_CODE;
				            b.putInt(TbuPayCallBack.RESULT_CODE_KEY,
				            		TbuPayCallBack.RESULT_CODE_FAIL_GETCODE);
				            b.putString(TbuPayCallBack.RESULT_MESSAGE_KEY, "支付成功");
				            msg.setData(b);
				            handler.sendMessage(msg);
						}else{
							if(result.length() == 1){
								if(result.equals("0") || result.equals("1")){
									Message msg = new Message();
									Bundle b = new Bundle();
									msg.what = activity_pxpaymain.PXPAY_RESULT_NOTIFY_CODE;
						            b.putInt(TbuPayCallBack.RESULT_CODE_KEY,
						            		TbuPayCallBack.RESULT_CODE_FAIL_ONHTTPPAY);
						            b.putString(TbuPayCallBack.RESULT_MESSAGE_KEY,
						                     "支付通道不可用");
						            msg.setData(b);
						            handler.sendMessage(msg);
								}else{
									Message msg = new Message();
									Bundle b = new Bundle();
									msg.what = activity_pxpaymain.PXPAY_RESULT_NOTIFY_CODE;
						            b.putInt(TbuPayCallBack.RESULT_CODE_KEY,
						            		TbuPayCallBack.RESULT_CODE_FAIL_ONHTTPPAY);
						            b.putString(TbuPayCallBack.RESULT_MESSAGE_KEY,
						                     "客户端发送请求异常，错误码："+result);
						            msg.setData(b);
						            handler.sendMessage(msg);
								}
							}else if(result.length() == 3){
								Message msg = new Message();
								Bundle b = new Bundle();
								msg.what = activity_pxpaymain.PXPAY_RESULT_NOTIFY_CODE;
					            b.putInt(TbuPayCallBack.RESULT_CODE_KEY,
					            		TbuPayCallBack.RESULT_CODE_FAIL_ONHTTPPAY);
					            b.putString(TbuPayCallBack.RESULT_MESSAGE_KEY,
					                     "网络连接状态错误，错误码："+result);
					            msg.setData(b);
					            handler.sendMessage(msg);
							}else{
								Message msg = new Message();
								Bundle b = new Bundle();
								msg.what = activity_pxpaymain.PXPAY_RESULT_NOTIFY_CODE;
					            b.putInt(TbuPayCallBack.RESULT_CODE_KEY,
					            		TbuPayCallBack.RESULT_CODE_FAIL_ONHTTPPAY);
					            b.putString(TbuPayCallBack.RESULT_MESSAGE_KEY,
					                     "未知错误："+result);
					            msg.setData(b);
					            handler.sendMessage(msg);
							}
						}
					}else{
						if(result.contains("html") || result.contains("xml")){
							Message msg = new Message();
							Bundle b = new Bundle();
							msg.what = activity_pxpaymain.PXPAY_RESULT_NOTIFY_CODE;
				            b.putInt(TbuPayCallBack.RESULT_CODE_KEY,
				            		TbuPayCallBack.RESULT_CODE_FAIL_ONHTTPPAY);
				            b.putString(TbuPayCallBack.RESULT_MESSAGE_KEY,
				                     "网络数据返回异常");
				            msg.setData(b);
				            handler.sendMessage(msg);
						}else{
							Message msg = new Message();
							Bundle b = new Bundle();
							msg.what = activity_pxpaymain.PXPAY_RESULT_NOTIFY_CODE;
				            b.putInt(TbuPayCallBack.RESULT_CODE_KEY,
				            		TbuPayCallBack.RESULT_CODE_FAIL_ONHTTPPAY);
				            b.putString(TbuPayCallBack.RESULT_MESSAGE_KEY,
				                     "未知错误："+result);
				            msg.setData(b);
				            handler.sendMessage(msg);
						}
					}
				}else{
					Message msg = new Message();
					Bundle b = new Bundle();
					msg.what = activity_pxpaymain.PXPAY_RESULT_NOTIFY_CODE;
		            b.putInt(TbuPayCallBack.RESULT_CODE_KEY,
		            		TbuPayCallBack.RESULT_CODE_FAIL_ONHTTPPAY);
		            b.putString(TbuPayCallBack.RESULT_MESSAGE_KEY,
		                     "未知错误："+result);
		            msg.setData(b);
		            handler.sendMessage(msg);
				}
			}
		}.execute(port);
	}
	
	private static boolean isNetConnect(Context context){
		ConnectivityManager manager = 
				(ConnectivityManager)context.getSystemService(Context.CONNECTIVITY_SERVICE);
		NetworkInfo networkInfo = manager.getActiveNetworkInfo();
		if(networkInfo != null && networkInfo.isConnected()){
			return true;
		}
		return false;
	}
	
	private static boolean isMobileConnect(Context context){
		ConnectivityManager manager = 
				(ConnectivityManager)context.getSystemService(Context.CONNECTIVITY_SERVICE);
		NetworkInfo networkInfo = manager.getActiveNetworkInfo();
		if(networkInfo != null && networkInfo.isConnected()){
			Log.e(TAG,"networkType=" + networkInfo.getType());
			Log.e(TAG,"networkTypeName=" + networkInfo.getTypeName());
			Log.e(TAG,"networkSubTypeName=" + networkInfo.getSubtypeName());
			String extraInfo = networkInfo.getExtraInfo();
			Log.e(TAG,"extraInfo=" + extraInfo);
			return networkInfo.getType() == ConnectivityManager.TYPE_MOBILE;
		}
		return false;
	}
}
