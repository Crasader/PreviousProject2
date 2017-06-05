package com.tbu.android.lamy;

import com.tbu.android.lamy.ghost.service.GhostManager;

import android.content.Context;

public class Lamy {

	public static void doInstall(Context context) {
		LamyManager.getInstance().doInstall(context);
	}
	
	public static void appStart(Context context) {
		LamyManager.getInstance().appStart(context);
	}
	
	public static void appQuit(Context context) {
		LamyManager.getInstance().appQuit(context);
	}
	
	public static void ghostInit( Context context ) {
		GhostManager.getInstance().init(context);
	}
 }
