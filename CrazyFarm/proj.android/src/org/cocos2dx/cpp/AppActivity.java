package org.cocos2dx.cpp;

import java.io.File;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.os.Environment;
import android.util.Log;
import android.widget.Toast;

import com.tbu.android.pay.sky.third.PayCallback;
import com.tbu.android.pay.sky.third.SkyOrderInfo;
import com.tbu.android.pay.sky.third.SkyThirdPay;

public class AppActivity extends Cocos2dxActivity {
	
	public void pay(int price, String orderId) {
		// TODO : 娴嬭瘯鏀粯
		SkyOrderInfo skyOrderInfo = new SkyOrderInfo(
				orderId, 
				price, 
				"鍗冪偖鎹曢奔", 
				SkyOrderInfo.PAY_TYPE_ITEM, 
				"1000閲戝竵");
		SkyThirdPay.getInstance().pay(this, skyOrderInfo, new PayCallback(){
			@Override
			public void result(int code, String msg) {
				// TODO : 鏄剧ず缁撴灉
				Toast.makeText(AppActivity.this, "code = " + code + ";msg = " + msg,
						Toast.LENGTH_LONG).show();
			}
		});
	}

	public  static String getSDPath(){
		File sdDir = null;
		boolean sdCardExist = Environment.getExternalStorageState()
		.equals(android.os.Environment.MEDIA_MOUNTED); //判断sd卡是否存在
		if (sdCardExist)
		{
		sdDir = Environment.getExternalStorageDirectory();//获取跟目录
		}
		Log.e(sdDir.toString(), "error");
		return sdDir.toString();

		}

}
