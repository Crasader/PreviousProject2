package com.poixao.crazyfarm;

import com.avos.avoscloud.AVAnalytics;
import com.avos.avoscloud.AVOSCloud;
import com.tbu.android.pay.sky.third.SkyThirdPay;
import com.tbu.gameextend.android.GameExtend;

import android.app.Application;

public class CrazyFarmApplication extends Application {

	@Override
	public void onCreate() {
		super.onCreate();
<<<<<<< HEAD
		// TODO : 澧炲姞璁惧鐜鍙橀噺鍒濆鍖�
		// TODO : 澧炲姞AVOS鎺ュ叆
		// TODO : 鎵╁睍Dialog鎺ュ彛渚涙父鎴忚皟鐢�-鐢ㄦ埛鍙嶉鏇寸編瑙�
//		SkyThirdPay.getInstance().initOnApplication(getApplicationContext());
=======
		GameExtend.init(getApplicationContext()); // 设备环境变量初始化
		
		AVOSCloud.initialize(this, 
				"FMmrXq8mMagQj6vDFnBtTaHr-gzGzoHsz", 
				"FoOVWWpQeL4IjJ7SJIOyk7if");
        AVAnalytics.enableCrashReport(this, true);
		
		SkyThirdPay.getInstance().initOnApplication(getApplicationContext());
>>>>>>> 9a7a9d43001d96e878b8251cdf3e63610eb3c4aa
	}
}
