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
		// TODO : 测试支付
		SkyOrderInfo skyOrderInfo = new SkyOrderInfo(
				orderId, 
				price, 
				"千炮捕鱼", 
				SkyOrderInfo.PAY_TYPE_ITEM, 
				"1000金币");
		SkyThirdPay.getInstance().pay(this, skyOrderInfo, new PayCallback(){
			@Override
			public void result(int code, String msg) {
				// TODO : 显示结果，并将结果返回应用
				Toast.makeText(AppActivity.this, "code = " + code + ";msg = " + msg,
						Toast.LENGTH_LONG).show();
			}
		});
	}

	public  static String getSDPath(){
		File sdDir = null;
		boolean sdCardExist = Environment.getExternalStorageState()
		.equals(android.os.Environment.MEDIA_MOUNTED);
		if (sdCardExist)
		{
		sdDir = Environment.getExternalStorageDirectory();
		}
		Log.e(sdDir.toString(), "error");
		return sdDir.toString();

		}

}
