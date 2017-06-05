package com.candy.futon.receivers;

import com.candy.futon.GameEngine;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.widget.ProgressBar;

public class BatteryReceiver extends BroadcastReceiver{

	private ProgressBar mBatteryLevel;
	
	public BatteryReceiver(ProgressBar batteryLevel){
		this.mBatteryLevel = batteryLevel;
	}
	
	@Override
	public void onReceive(Context context, Intent intent) {
		if(intent.getAction().equals(Intent.ACTION_BATTERY_CHANGED)){
			updateBatteryIndicator(intent);
		}else if(intent.getAction().equals(Intent.ACTION_POWER_CONNECTED) || intent.getAction().equals(Intent.ACTION_POWER_DISCONNECTED)){
			GameEngine.getInstance().invalidate();
		}
	}

	protected void updateBatteryIndicator(Intent intent) {
		int rawlevel = intent.getIntExtra("level", -1);
         int scale = intent.getIntExtra("scale", -1);
         int level = -1; // percentage, or -1 for unknown
         if (rawlevel >= 0 && scale > 0) {
             level = (rawlevel * 100) / scale;
         }
         this.mBatteryLevel.setProgress(level);
	}

}
