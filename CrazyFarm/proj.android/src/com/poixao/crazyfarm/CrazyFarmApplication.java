package com.poixao.crazyfarm;

import com.tbu.android.pay.sky.third.SkyThirdPay;
import android.app.Application;

public class CrazyFarmApplication extends Application {

	@Override
	public void onCreate() {
		super.onCreate();
		// TODO : 增加设备环境变量初始化
		// TODO : 增加AVOS接入
		// TODO : 扩展Dialog接口供游戏调用-用户反馈更美观
		SkyThirdPay.getInstance().initOnApplication(getApplicationContext());
	}
}
