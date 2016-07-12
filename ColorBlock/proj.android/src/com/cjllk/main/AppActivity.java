package com.cjllk.main;

import org.cocos2dx.lib.Cocos2dxActivity;

import com.a.c.AppApplication;
import com.tbu.androidtools.Debug;

import android.os.Bundle;


public class AppActivity extends Cocos2dxActivity {
		
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		AppApplication.getInstance().initOnFirstActivity(AppActivity.this);
		PayService.init(this);
		NetWorkService.init(this);
		Debug.e("init end");
	}
}
