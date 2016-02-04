package org.cocos2dx.cpp;

import java.io.File;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.app.Activity;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.widget.Toast;

import com.avos.avoscloud.AVAnalytics;
import com.tbu.android.pay.sky.third.PayCallback;
import com.tbu.android.pay.sky.third.SkyOrderInfo;
import com.tbu.android.pay.sky.third.SkyThirdPay;

public class AppActivity extends Cocos2dxActivity {
	
	private static Activity activity;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		AppActivity.activity = this;
	}
	
	public static void pay(final int price, final String orderId) {
		Log.i("TBU_DEBUG", "AppActivity->pay: price = " + price + ";orderId = " + orderId);
		final SkyOrderInfo skyOrderInfo = new SkyOrderInfo(
				orderId, 
				price, 
				"万炮捕鱼", 
				SkyOrderInfo.PAY_TYPE_ITEM, 
				"道具购买");
		
		AppActivity.activity.runOnUiThread(new Runnable() {
			
			@Override
			public void run() {
				Log.i("TBU_DEBUG", "[ON UI THREAD]AppActivity->pay: price = " + price + ";orderId = " + orderId);
				SkyThirdPay.getInstance().pay(activity, skyOrderInfo, new PayCallback(){
					@Override
					public void result(final int code, final String msg) {
						Log.i("TBU_DEBUG", "code = " + code + ";msg = " + msg);
						if(code != 0) {
							AppActivity.activity.runOnUiThread(new Runnable() {
								@Override
								public void run() {
									Toast.makeText(AppActivity.activity, "支付失败:" + msg, 
											Toast.LENGTH_LONG).show();
									
								}
							});
						}
						JniPayCallbackHelper.payResultCallBack(code,msg);						
					}
				});
				
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
	
	protected void onPause() {
	    super.onPause();
	    AVAnalytics.onPause(this);
	}

	protected void onResume() {
	    super.onResume();
	    AVAnalytics.onResume(this);
	}

}
