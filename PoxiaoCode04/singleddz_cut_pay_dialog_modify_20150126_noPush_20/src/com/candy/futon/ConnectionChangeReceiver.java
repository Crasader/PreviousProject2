package com.candy.futon;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.util.Log;

import com.andy.canvasgame.util.NetWorkUtil;

public class ConnectionChangeReceiver extends BroadcastReceiver {
	private static final String TAG = "ConnectionChangeReceiver";

	@Override
	public void onReceive(Context context, Intent intent) {
		Log.d(TAG, "网络状态改变");

		boolean success = NetWorkUtil.isNetworkAvilable(context);

		
	}

	
}
