package com.candy.futon.service;

import java.io.IOException;
import java.net.URLEncoder;
import java.text.SimpleDateFormat;
import java.util.Date;

import org.apache.http.HttpResponse;
import org.apache.http.HttpStatus;
import org.apache.http.StatusLine;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.params.BasicHttpParams;
import org.apache.http.params.HttpConnectionParams;
import org.apache.http.params.HttpParams;

import android.app.Activity;
import android.content.Context;
import android.os.Build;
import android.telephony.TelephonyManager;
import android.util.Log;

import com.andy.canvasgame.service.GameConstantsService;
import com.candy.futon.FutonDdzApplication;
import com.candy.futon.domain.GameConfig;




public class CellPhoneNumberUpdater {
	
	private final static String TAG = "CellPhoneNumberUpdater";
	
	private static CellPhoneNumberUpdater instance;
	
	private boolean inWorkProcess = false;
	
	private final static String LOG_SERVER_URL ="http://115.236.18.198:8088/fn/recordPrizeInfo.htm";
	
	private SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
	
	public interface CellPhoneUploadListener{
		public void onUploadDone(int result);
	}
	
	private CellPhoneUploadListener listener;
	
	private CellPhoneNumberUpdater(){
		
	}
	
	public static CellPhoneNumberUpdater getInstance(){
		if(instance == null){
			instance = new CellPhoneNumberUpdater();
		}
		return instance;
	}
	
	public void upload(final Context context, final String phone){
		if(inWorkProcess == true){
			return;
		}
		inWorkProcess = true;
		Thread thread = new Thread(){
			@Override
			public void run() {
				
				doUpload(context, phone);
				inWorkProcess = false;
				
			}
		};
		thread.setDaemon(true);
		thread.start();
		
	}
	
	protected void doUpload(Context context, String phone) {
		
		FutonDdzApplication app = (FutonDdzApplication)((Activity)context).getApplication();
		String imsi = "";
		try{
			TelephonyManager tm = (TelephonyManager) context.getSystemService(Activity.TELEPHONY_SERVICE);
			
			imsi = tm.getSubscriberId();
		}catch(SecurityException e){
//			e.printStackTrace();
		}
		String imei = "";
		try{
			TelephonyManager tm = (TelephonyManager) context.getSystemService(Activity.TELEPHONY_SERVICE);
			imei = tm.getDeviceId();
		}catch(SecurityException e){
			//e.printStackTrace();
		}
		String param = "gameId="+app.getGameId() +"&channelId="
				+GameConstantsService.getInstance().getEnterId()+"&appId="
				+GameConfig.getInstance().APP_ID+"&imei="+ imei
				+"&imsi="+imsi+"&submit_time="+ df.format(new Date())
				+"&hsman="+Build.MANUFACTURER +"&hstype="+Build.DISPLAY +"_"+ Build.MODEL+"&content=游戏累计玩5局就送3000银币，还有机会赢实物大奖"+
				"&phone="+phone;
				
		
		if(param == null || param.trim().equals("")){
			Log.d(TAG, "no record to upload");
			return;
		}
		
		HttpParams httpParameters = new BasicHttpParams();
		// Set the timeout in milliseconds until a connection is established.
		// The default value is zero, that means the timeout is not used. 
		int timeoutConnection = 4000;
		HttpConnectionParams.setConnectionTimeout(httpParameters, timeoutConnection);
		// Set the default socket timeout (SO_TIMEOUT) 
		// in milliseconds which is the timeout for waiting for data.
		HttpConnectionParams.setSoTimeout(httpParameters, timeoutConnection);
		HttpClient httpclient = new DefaultHttpClient(httpParameters);
		
		HttpResponse response = null;
		try {
			String url = param;
			
			url = url.replaceAll(" ", "%20");
			Log.d(TAG,"cellphone param:"+ url);
			HttpGet httpRequest =new HttpGet(LOG_SERVER_URL+"?"+url);
		    //Post运作传送变数必须用NameValuePair[]阵列储存
		    //传参数 服务端获取的方法为request.getParameter("name")
		    
			
		    response = httpclient.execute(httpRequest);
			StatusLine statusLine = response.getStatusLine();
		    if(statusLine.getStatusCode() == HttpStatus.SC_OK){
		    	if(listener != null){
		    		listener.onUploadDone(0);
		    		listener = null;
		    	}
		    }
		} catch (ClientProtocolException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} finally{
			if(response !=null){
				try {
					response.getEntity().getContent().close();
				} catch (IllegalStateException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
			
		}
		if(listener != null){
    		listener.onUploadDone(1);
    		listener = null;
    	}
	
	}

	public boolean isInWorkProcess() {
		return inWorkProcess;
	}
	
	public void setListener(CellPhoneUploadListener listener) {
		this.listener = listener;
	}
	
}
