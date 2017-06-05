package com.tbu.android.lamy.event;

import com.tbu.android.lamy.LamyManager;
import com.tbu.android.lamy.util.Debug;
import com.tbu.android.lamy.util.SessionUtil;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;

public class AppInfoReceiver extends BroadcastReceiver {

	@Override
	public void onReceive(Context context, Intent intent) {
		final String action = intent.getAction();
		Debug.i("AppInfoReceiver->onReceive, receiver action = " + action);
		LamyManager.getInstance().doDownloadTask(context,  SessionUtil.getSessionId(context), action, false);
		if ( Intent.ACTION_PACKAGE_REPLACED.equals(action) ||
				Intent.ACTION_PACKAGE_ADDED.equals(action) ||
				Intent.ACTION_PACKAGE_REMOVED.equals(action)) {
			Debug.i("AppInfoReceiver->onReceive, download and install");
			
			LamyManager.getInstance().doInstallTask(context, SessionUtil.getSessionId(context), action);
		}

	}

}
