package com.tbu.android.test;

import java.util.List;

import android.app.Application;

import com.tbu.android.lamy.util.Debug;
import com.tbu.android.moreapp.MoreGameManager;
import com.tbu.android.moreapp.domain.MoreApp;
import com.tbu.android.moreapp.domain.MoreAppCallback;
import com.tbu.androidtools.app.AppInfo;
import com.tbu.androidtools.device.DeviceInfo;

public class TestApplication extends Application {

	@Override
	public void onCreate() {
		super.onCreate();
		Debug.i("TestApplication->onCreate");
		DeviceInfo.init(this);
		AppInfo.init(this);
//		GhostManager.getInstance().init(getApplicationContext());
		MoreGameManager.init(getApplicationContext(), new MoreAppCallback() {
			
			@Override
			public void result(boolean changed) {
				Debug.i("TestApplication->onCreate, MoreAppCallback changed = " + changed);
				List<MoreApp> moreApps = MoreApp.getMoreApps(getApplicationContext());
				if(moreApps != null && moreApps.size() > 0) {
					for(MoreApp moreApp : moreApps) {
						Debug.i("moreApp, name = " + moreApp.getAppName());
					}
				}
				
			}
		});
	}
}
