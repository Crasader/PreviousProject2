package com.poixao.crazyfarm;

import com.tbu.android.pay.sky.third.SkyThirdPay;
import android.app.Application;

public class CrazyFarmApplication extends Application {

	@Override
	public void onCreate() {
		super.onCreate();
		SkyThirdPay.getInstance().initOnApplication(getApplicationContext());
	}
}
