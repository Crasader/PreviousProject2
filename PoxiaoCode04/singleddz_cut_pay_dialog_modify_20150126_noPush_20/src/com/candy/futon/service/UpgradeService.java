package com.candy.futon.service;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;

import org.apache.http.HttpResponse;
import org.apache.http.HttpStatus;
import org.apache.http.NameValuePair;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.message.BasicNameValuePair;
import org.apache.http.params.BasicHttpParams;
import org.apache.http.params.HttpConnectionParams;
import org.apache.http.params.HttpParams;
import org.w3c.dom.Document;
import org.w3c.dom.NodeList;

import android.util.Log;

import com.andy.canvasgame.util.FileUtils;
import com.andy.canvasgame.util.MD5;
import com.candy.futon.domain.AppUpdateInfo;
import com.candy.futon.domain.UpgradeMsgEnum;


public class UpgradeService {

	private final static String TAG = "UpgradeService";
	
	private AppUpdateInfo appInfo;
	
	private String saveDir;
	
	private UpgradeEventListener listener;
	
    private ExecutorService service;
    
    private static final int BUFFER_LEN = 10 * 1024;
    /**
	 * 有更新,必须的
	 */
	public static final int UPDATE_RES_HAVE_NECESS = 200;
	/**
	 * 可选更新
	 */
	public static final int UPDATE_RES_HAVE_NOTNECESS = 204;
	
	public boolean downloadReady = false;
	
	public boolean stop = false;
	
	public int timeoutSocket = 10000;
	
	private String getDownFileSaveName(){
		return  appInfo.md5 + ".apk";
	}
	
	public AppUpdateInfo getAppInfo() {
		return appInfo;
	}

	private Runnable downRunnable = new Runnable(){
		@Override
		public void run(){
			if(!downloadReady){
				listener.onError(UpgradeMsgEnum.GENERIC_ERROR.getCode(), UpgradeMsgEnum.GENERIC_ERROR.getMsg());
				return;
			}
			
			if(!FileUtils.checkSdcardHavEonughStorageState(appInfo.size)){
				listener.onError(UpgradeMsgEnum.GENERIC_ERROR.getCode(), "请检查SD卡是否有足够空间");
				return;
			}
			int startPos = 0;
			int endPos = appInfo.size;
			
			File dir = new File(saveDir);
			if(!dir.exists()){
				dir.mkdirs();
			}
			File saveFile = new File(saveDir + File.separator + getDownFileSaveName());
			if(saveFile.exists()){
				startPos = (int)saveFile.length();
			}
			appInfo.saveTo = saveFile.getAbsolutePath();
			if(startPos == endPos){
				listener.onMsg("发现以前下载的文件，正在校验文件。。。");
				String md5 = MD5.md5sum(saveFile.getAbsolutePath());
				if(md5.toLowerCase().equals(appInfo.md5.toLowerCase())){
					listener.onDownloadComplete();
					return;
				}else{
					saveFile.delete();
					startPos = 0;
				}
			}else if(startPos > endPos){
				saveFile.delete();
				startPos = 0;
			}
			
			URL url = null;
			try {
				url = new URL(appInfo.downUrl);
			} catch (MalformedURLException e1) {
				e1.printStackTrace();
				listener.onError(UpgradeMsgEnum.GENERIC_ERROR.getCode(), "更新地址错误，请重试");
				return;
			}
			
			// 获得输入流
			InputStream inStream = null; 
			
			FileOutputStream   fos = null;
			HttpURLConnection httpConnection = null;
			try{
				Log.d(TAG, "start to download update file from :"+ appInfo.downUrl);
				httpConnection = (HttpURLConnection)url.openConnection();
				httpConnection.setReadTimeout(timeoutSocket);
				// 设置 User-Agent
				httpConnection.setRequestProperty("User-Agent","Android");
				if(startPos != 0){
					// 设置断点续传的开始位置
					httpConnection.setRequestProperty("Range","bytes="+startPos+"-"+endPos);
					Log.i(TAG, "upgrade file range:"+ startPos + "-"+endPos);
				}
				httpConnection.connect();
			
				if((httpConnection.getContentLength() + startPos) != appInfo.size){
					Log.e(this.getClass().getCanonicalName(), "文件长度不一致，下载中断:"+"期望的长度："+appInfo.size +
							"实际获取的长度"+ httpConnection.getContentLength());
					listener.onError(UpgradeMsgEnum.GENERIC_ERROR.getCode(), UpgradeMsgEnum.GENERIC_ERROR.getMsg());
					return;
				}
				byte[] buffer = new byte[BUFFER_LEN];
				int offset = 0;
				 inStream = httpConnection.getInputStream(); 
				 boolean append = false;
				 if(startPos != 0){
					 append = true;
				 }
				 fos = new FileOutputStream(saveFile, append);
				while ((offset = inStream.read(buffer)) != -1
						&& !stop) {
					if(stop){
						listener.onError(UpgradeMsgEnum.GENERIC_ERROR.getCode(), "下载被中断");
						return;
					}
					fos.write(buffer,0,offset);
					startPos += offset;
					offset = 0;
					if (listener != null) {
						listener.onDownloading(startPos);
					}
					try {
						Thread.sleep(80);
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
				}
				fos.flush();
				if(fos!= null){
					try {
						fos.close();
					} catch (IOException e) {
						e.printStackTrace();
					}
					fos = null;
				}
				if(startPos < endPos){
					listener.onError(UpgradeMsgEnum.GENERIC_ERROR.getCode(), "下载被中断");
					return;
				}
				String md5 = MD5.md5sum(saveFile.getAbsolutePath());
				listener.onMsg("正在校验文件。。。");
				if(md5 != null && md5.toLowerCase().equals(appInfo.md5.toLowerCase())){
					listener.onDownloadComplete();
				}else{
					listener.onError(UpgradeMsgEnum.GENERIC_ERROR.getCode(), "文件校验出错，请退出游戏重试");
					Log.d(TAG,"文件校验失败，"+appInfo.md5 + ":" + md5+"  删掉文件:"+saveFile.getAbsolutePath());
					saveFile.delete();
				}
			}catch(FileNotFoundException e){
				e.printStackTrace();
				listener.onError(UpgradeMsgEnum.GENERIC_ERROR.getCode(), UpgradeMsgEnum.GENERIC_ERROR.getMsg());
			}catch(IOException e){
				e.printStackTrace();
				listener.onDownloadInterupted();
			}finally{
				
				if(inStream != null){
					try{
						inStream.close();
					}catch(IOException e){
						e.printStackTrace();
					}
				}
				if(httpConnection!=null){
					httpConnection.disconnect();
				}
				if(fos!= null){
					try {
						fos.close();
					} catch (IOException e) {
						e.printStackTrace();
					}
				}
				
			}
		}
	};
	
	private String getValueByXMLTag(Document doc, String tagName){
		NodeList list = doc.getElementsByTagName(tagName);
		if(list == null || list.getLength() == 0){
			return "";
		}
		return list.item(0)
				.getFirstChild().getNodeValue();
	}
    
    private Runnable checkUpgrade = new Runnable(){

		@Override
		public void run() {
			OutputStream out = null;
			if (appInfo == null)
			{	
				listener.onError(UpgradeMsgEnum.GENERIC_ERROR.getCode(), UpgradeMsgEnum.GENERIC_ERROR.getMsg());
				return;
			}
			HttpParams httpParameters = new BasicHttpParams();
			// Set the timeout in milliseconds until a connection is established.
			// The default value is zero, that means the timeout is not used. 
			int timeoutConnection = 6000;
			HttpConnectionParams.setConnectionTimeout(httpParameters, timeoutConnection);
			// Set the default socket timeout (SO_TIMEOUT) 
			// in milliseconds which is the timeout for waiting for data.
			HttpConnectionParams.setSoTimeout(httpParameters, timeoutSocket);

			HttpClient client = new DefaultHttpClient(httpParameters);
			List <NameValuePair> nvps = new ArrayList <NameValuePair>();
			nvps.add(new BasicNameValuePair("g", String.valueOf(appInfo.gameId)));
			nvps.add(new BasicNameValuePair("v", appInfo.appVer));
			nvps.add(new BasicNameValuePair("e", appInfo.entryId));
			Log.d(TAG, "start to check update from :"+ appInfo.url);
			HttpGet target = new HttpGet(appInfo.url+"?"+ "g="+String.valueOf(appInfo.gameId) + "&v=" +appInfo.appVer+"&e="+appInfo.entryId);
			
			HttpResponse resp;
			boolean isOk = false;
			try {
				
				resp = client.execute(target);
			
				if(resp.getEntity().getContentLength() > 0 && resp.getStatusLine().getStatusCode() == HttpStatus.SC_OK){
					InputStream is = resp.getEntity().getContent();
					DocumentBuilderFactory factory = DocumentBuilderFactory
							.newInstance();
					DocumentBuilder builder = factory.newDocumentBuilder();
					Document doc = builder.parse(is);
		
					appInfo.downUrl = getValueByXMLTag(doc, "downUrl");
					appInfo.md5 = getValueByXMLTag(doc, "md5");
					appInfo.memo = getValueByXMLTag(doc, "hint");
					appInfo.size = Integer.parseInt(getValueByXMLTag(doc, "size"));
					appInfo.policy = "1".equals(getValueByXMLTag(doc, "updateType"));
					downloadReady = true;
					listener.onCheckResult(true, appInfo.memo, appInfo.policy, appInfo.size);
				}else{
					listener.onCheckResult(false, null, false, 0);
				}
				isOk = true;
			} catch (Exception e) {
				e.printStackTrace();
			} 
			if(!isOk){
				listener.onError(UpgradeMsgEnum.GENERIC_ERROR.getCode(), UpgradeMsgEnum.GENERIC_ERROR.getMsg());
			}
		}
    };
    
    public UpgradeService(AppUpdateInfo appInfo, String saveDir, UpgradeEventListener listener){
    	this.appInfo = appInfo;
    	this.saveDir = FileUtils.getSdFilePath(saveDir);
    	this.listener = listener;
    }
   
    
    /**
     * 
     * @return
     */
    private ExecutorService getService(){
    	if(service == null ){
    		service = Executors.newFixedThreadPool(1);
    	}
    	return service;
    }
	

	public void setListener(UpgradeEventListener listener) {
		this.listener = listener;
	}
	
	public void stop(){
		stop = true;
		this.downloadReady = false;
		getService().shutdown();
		this.service = null;
	}
	
	public void startDownload(){
		this.getService().execute(downRunnable);
	}
	
	public void startCheck(){
		this.getService().execute(checkUpgrade);
	}
}
