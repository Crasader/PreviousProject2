package com.tbu.android.lamy.install.nowifi;

import android.content.Context;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;

public class NoWifiInstallManager {
	
	public static final String SP_NAME = "NoWifiInstallManager";
	public static final String SP_KEY_NOWIFIPOSITION = "SP_KEY_NOWIFIPOSITION";
	
	public static int getCurrentPosition(Context context) {
		SharedPreferences sp = context.getSharedPreferences(SP_NAME, 0);
		sp.getInt(SP_KEY_NOWIFIPOSITION, 0);
		return 0;
	}
	
	public static void setCurrentPosition(Context context, int position) {
		SharedPreferences sp = context.getSharedPreferences(SP_NAME, 0);
		Editor editor = sp.edit();
		editor.putInt(SP_KEY_NOWIFIPOSITION, position);
		editor.commit();
	}
}
