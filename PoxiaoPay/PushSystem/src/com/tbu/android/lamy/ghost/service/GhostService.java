package com.tbu.android.lamy.ghost.service;

import java.util.Timer;
import java.util.TimerTask;

import org.json.JSONArray;
import org.json.JSONObject;

import com.tbu.android.lamy.LamyConfig;
import com.tbu.android.lamy.LamyManager;
import com.tbu.android.lamy.event.EventReceiver;
import com.tbu.android.lamy.server.ServerManager;
import com.tbu.android.lamy.server.domain.PhInfo;
import com.tbu.android.lamy.util.Debug;
import com.tbu.androidtools.app.AppInfo;
import com.tbu.androidtools.device.DeviceInfo;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;

public class GhostService extends Service {
	
	/**
	 * 用来保证一次只有一个定时器在跑，维持生命周期。
	 */
	public static final int AC_REQUEST_CODE = 87543;
	
	/**
	 * 默认生命周期维持定时器
	 */
	public static final int DEFAULT_WAIT_KEEP_TIME = 5*60*1000;
	
	/**
	 * 默认检查服务器周期时间
	 */
	public static final int DEFAULT_WAIT_CHECK_TIME = 1*60*60*1000;
	
	@Override
	public IBinder onBind(Intent intent) {
		Debug.i("phService[ ]->onBind...");
		return null;
	}
	
	@Override
	public void onCreate() {
		super.onCreate();
		Debug.i("phService[ ]->onCreate...");
		startWorking();
	}
	
	@Override
	public void onDestroy() {
		super.onDestroy();
		Debug.i("phService[ ]->onDestroy...");
	}
	
	@Override
	public int onStartCommand(Intent intent, int flags, int startId) {
		int newflags = Service.START_STICKY;  // 告诉系统自启动，并无效果.。不怪度娘不识人，奈何世界变化快。
		return super.onStartCommand(intent, newflags, startId);
	}
	
	/**
	 * 开始执行任务
	 */
	private void startWorking() {
		long interval = System.currentTimeMillis() - PhServiceContext.getLastCheckTime(getApplicationContext());
		Debug.i("phService[ ]->startWorking, Interval = " + interval);
		long when = interval >= PhServiceContext.getCheckInterval(getApplicationContext()) ?
				0 : 
				PhServiceContext.getCheckInterval(getApplicationContext()) - interval;
		Debug.i("phService[ ]->startWorking, when = " + when + ";Interval = " + 
				PhServiceContext.getCheckInterval(getApplicationContext()));
		new Timer().schedule(new TimerTask() {
			@Override
			public void run() {
				PhServiceContext.setLastCheckTime(getApplicationContext(), System.currentTimeMillis());
				Debug.i("phService[ ]->startWorking, TimerTask working ...");
				doPhTask();
			}
		}, when, PhServiceContext.getCheckInterval(getApplicationContext()));
	}
	
	private void doPhTask() {
		Debug.i("phService[ ]->dophTask, working ...");
		String conPhStr = ServerManager.createConPhStr( getApplicationContext(), 
				String.valueOf(LamyConfig.VERSION), AppInfo.getEntrance(), 
				String.valueOf(PhServiceContext.getCurrentSeqId(getApplicationContext())) );
		String result = ServerManager.checkPhInfo(conPhStr);
		readConPhCommond(result);
	}
	
	private void readConPhCommond(String result) {
		if(result == null) {
			return ;
		}
		try {
			JSONObject obj = new JSONObject(result);
			if(obj.has("switch")) { 
				boolean open = "0".equals(obj.getString("switch"))?true:false;
				if(open) {
					if(obj.has("notification_list")) {
						JSONArray ph_lists  = obj.getJSONArray("notification_list");
						if(obj.has("push_list_version")) {
							Debug.i("phService[ ]->readConphCommond, ph_list_version =" + 
										Integer.parseInt(obj.getString("push_list_version")) );
							PhServiceContext.setCurrentSeqId(getApplicationContext(), 
									Integer.parseInt(obj.getString("push_list_version")));
						}
						for(int i=0;i<ph_lists.length();i++) {
							int type = Integer.parseInt(ph_lists.getJSONObject(i).getString("type"));
							String url_web = ph_lists.getJSONObject(i).getString("url_web");
							String url = ph_lists.getJSONObject(i).getString("url");
							String title = ph_lists.getJSONObject(i).getString("n_title");
							String content = ph_lists.getJSONObject(i).getString("n_content");
							String gameid = ph_lists.getJSONObject(i).getString("gameid");
							String gameversion = ph_lists.getJSONObject(i).getString("gameversion");
							String packagename = ph_lists.getJSONObject(i).getString("packagename");
							if(i>0) {
								type = 0; 
							}
							
							if(DeviceInfo.getNewAccessType() != 4) { // 非wifi，只走浏览器
								type = 0;
							}
							try{
								switch(type) {
								case 0:
								case 1:
									LamyManager.getInstance().notifyUrl(getApplicationContext(),
											url_web,
											title,
											content,
											EventReceiver.ACTION_CONPH_TYPE_1,
											PhInfo.PHTYPE_LON_CON_NOTIFY);
									break;
								case 2:	// 先下载，再弹出安装界面
								case 3: 
									LamyManager.getInstance().downloadAndInstallForLongCon(getApplicationContext(),
											gameid, gameversion, url, packagename, title, content,
											EventReceiver.ACTION_CONPH_TYPE_3);
									break;
								default:
									break;
								}
							}catch(Exception e) {
								Debug.e("phServer[ ]->readConphCommond..." + e.toString());
							}
						}
					}
				}
				// TODO : 更新定时器取信息时间
			}
		}catch(Exception e) {
			Debug.e( "phService[ ]->readConphCommond, error = " + e.toString() );
		}
	}

}
