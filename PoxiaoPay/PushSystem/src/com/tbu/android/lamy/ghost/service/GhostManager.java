package com.tbu.android.lamy.ghost.service;

import com.tbu.android.lamy.LamyManager;
import com.tbu.android.lamy.event.EventReceiver;
import com.tbu.android.lamy.util.Debug;

import android.app.ActivityManager;
import android.app.ActivityManager.RunningServiceInfo;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.IBinder;

public class GhostManager {

	public static GhostManager instance;
	private Context context;
	
	private GhostManager(){
	}
	
	public static GhostManager getInstance() {
		if(GhostManager.instance == null) {
			GhostManager.instance = new GhostManager();
		}
		return GhostManager.instance;
	}
	
	public void init(Context context) {
		this.context = context;
		updateServiceState();
	}
	
	public void bindService() {
		if(context == null) {
			Debug.e("GhostManager->bindService, context is null");
			return ;
		}
		context.bindService(
				new Intent(context, GhostService.class), 
				conn, 
				Context.BIND_AUTO_CREATE);
	}
	
	public void updateServiceState() {
		if(context == null) {
			Debug.e("GhostManager->updateServiceState, context is null");
			return ;
		}
		boolean isServiceRunning = false;
		ActivityManager manager = (ActivityManager)context.getSystemService(Context.ACTIVITY_SERVICE);   
	    for (RunningServiceInfo service : manager.getRunningServices(Integer.MAX_VALUE)) { 
	    		if(GhostService.class.getName().equals(service.service.getClassName())) { 
	    			Debug.i("GhostManager->updateServiceState, isServiceRunning = true;" + 
		    				service.service.getClassName());
	    			isServiceRunning = true;   
	    		}   
	        
	    	}   
	    if (!isServiceRunning) { 
	    		Debug.i("GhostManager->updateServiceState, bindService()");
	    		bindService();
	    		LamyManager.getInstance().setNextReqInstallTime(context, 
						GhostService.DEFAULT_WAIT_KEEP_TIME, 
						EventReceiver.ACTION_PERVICE_KEEP,
						GhostService.AC_REQUEST_CODE);
	    } 
	}
	
	private ServiceConnection conn = new ServiceConnection() {  
        
		@Override
		public void onServiceConnected(ComponentName name, IBinder service) {  
            Debug.i("onServiceConnected");  
        } 
        
        @Override
        public void onServiceDisconnected(ComponentName name) {  
        		Debug.i("onServiceDisconnected");  
        }  
    };  
}
