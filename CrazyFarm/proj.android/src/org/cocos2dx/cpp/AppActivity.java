package org.cocos2dx.cpp;

import java.io.File;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.DialogInterface.OnClickListener;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;


import android.widget.Toast;

//import com.bugtags.library.Bugtags;
import com.avos.avoscloud.AVAnalytics;
import com.poixao.crazyfarm.R;
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
	   // Bugtags.onPause(this);
	}

	protected void onResume() {
	    super.onResume();
	    AVAnalytics.onResume(this);
	   // Bugtags.onResume(this);
	}
//	 public boolean dispatchTouchEvent(MotionEvent event) {
//	        //注：回调 3
//	        Bugtags.onDispatchTouchEvent(this, event);
//	        return super.dispatchTouchEvent(event);
//	    }

	public  static void showFeedDialogOnUiThread() {
		AppActivity.activity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				((AppActivity) AppActivity.activity).showFeedDialog();
			}
		});
	}
	
	private void showFeedDialog() {
		LayoutInflater inflater = getLayoutInflater();
		   View layout = inflater.inflate(R.layout.feedback_dialog,
		     (ViewGroup) findViewById(R.id.dialog));
		final EditText et = (EditText)layout.findViewById(R.id.etname);

		   new AlertDialog.Builder(this).setTitle("用户反馈").setView(layout)
		     .setPositiveButton("确定", new OnClickListener() {
				@Override
				public void onClick(DialogInterface dialog, int which) {
					String text =et.getText().toString().trim(); 
					sayWhat("" + text);
					JniPayCallbackHelper.sendFeedback(text);	
				}
		     	}
		     )
		     .show();
	}
	
	private void sayWhat(final String what) {
		// TODO  : 填写对话框回调
		runOnUiThread(new Runnable() {	// TODO : 以下部分为测试，调试完成可以关闭
			@Override
			public void run() {
				Toast.makeText(AppActivity.this, "提交成功", Toast.LENGTH_LONG).show();
				
			}
		});
	}
}
