package com.poixao.crazyfarm;

import android.app.Application;

import com.avos.avoscloud.AVAnalytics;
import com.avos.avoscloud.AVOSCloud;
import com.bugtags.library.Bugtags;
import com.tbu.android.pay.sky.third.SkyThirdPay;
import com.tbu.gameextend.android.GameExtend;

public class CrazyFarmApplication extends Application {

	@Override
	public void onCreate() {
		super.onCreate();
		GameExtend.init(getApplicationContext()); // 设备环境变量初始化
		
		AVOSCloud.initialize(this, 
				"FMmrXq8mMagQj6vDFnBtTaHr-gzGzoHsz", 
				"FoOVWWpQeL4IjJ7SJIOyk7if");
        AVAnalytics.enableCrashReport(this, true);
		
	SkyThirdPay.getInstance().initOnApplication(getApplicationContext());
	Bugtags.start("a03524eaf40ac0590023b0e3bc5534b6", this, Bugtags.BTGInvocationEventBubble);
	}
}
