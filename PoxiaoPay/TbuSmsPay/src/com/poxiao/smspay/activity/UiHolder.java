package com.poxiao.smspay.activity;

import android.os.Handler;

import com.poxiao.smspay.TbuSessionCallback;

public interface UiHolder {

	void startPxPayTimer(int timeNum) ;
	
	Handler getHandler();
	
	void setTbuSessionCallback(TbuSessionCallback tbuSessionCallback);
}
