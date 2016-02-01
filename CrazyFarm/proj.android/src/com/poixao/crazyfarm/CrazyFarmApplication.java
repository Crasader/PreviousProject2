package com.poixao.crazyfarm;

import com.tbu.android.pay.sky.third.SkyThirdPay;
import android.app.Application;

public class CrazyFarmApplication extends Application {

	@Override
	public void onCreate() {
		super.onCreate();
		// TODO : 澧炲姞璁惧鐜鍙橀噺鍒濆鍖�
		// TODO : 澧炲姞AVOS鎺ュ叆
		// TODO : 鎵╁睍Dialog鎺ュ彛渚涙父鎴忚皟鐢�-鐢ㄦ埛鍙嶉鏇寸編瑙�
//		SkyThirdPay.getInstance().initOnApplication(getApplicationContext());
	}
}
