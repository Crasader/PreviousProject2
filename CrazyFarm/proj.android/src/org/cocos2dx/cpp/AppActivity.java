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
import android.view.WindowManager;
import android.widget.EditText;
import android.widget.Toast;

import com.avos.avoscloud.AVAnalytics;
import com.poixao.crazyfarm.Constants;
import com.poixao.crazyfarm.R;
import com.tencent.mm.sdk.modelmsg.SendMessageToWX;
import com.tencent.mm.sdk.modelmsg.WXMediaMessage;
import com.tencent.mm.sdk.modelmsg.WXTextObject;
import com.tencent.mm.sdk.modelmsg.WXWebpageObject;
import com.tencent.mm.sdk.modelpay.PayReq;
import com.tencent.mm.sdk.openapi.IWXAPI;
import com.tencent.mm.sdk.openapi.WXAPIFactory;



public class AppActivity extends Cocos2dxActivity  {
	
	private static Activity activity;

	private  static IWXAPI msgApi;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		AppActivity.activity = this;
//		TbuWxPay.getInstance().initOnFirstActivity(this);
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON,
				WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);

		// 将该app注册到微信
		msgApi = WXAPIFactory.createWXAPI(this,Constants.APP_ID, false);
		msgApi.registerApp(Constants.APP_ID);//写死
		
	}
	
	public static void SKYpay(final int price, final String orderId) {
//		Log.i("TBU_DEBUG", "AppActivity->pay: price = " + price + ";orderId = " + orderId);
//		final SkyOrderInfo skyOrderInfo = new SkyOrderInfo(
//				orderId, 
//				price, 
//				"万炮捕鱼", 
//				SkyOrderInfo.PAY_TYPE_ITEM, 
//				"道具购买");
//		
//		AppActivity.activity.runOnUiThread(new Runnable() {
//			
//			@Override
//			public void run() {
//				Log.i("TBU_DEBUG", "[ON UI THREAD]AppActivity->pay: price = " + price + ";orderId = " + orderId);
//				SkyThirdPay.getInstance().pay(activity, skyOrderInfo, new PayCallback(){
//					@Override
//					public void result(final int code, final String msg) {
//						Log.i("TBU_DEBUG", "code = " + code + ";msg = " + msg);
//						JniPayCallbackHelper.payResultCallBack(code,msg);		
//					}
//				});
//				
//			}
//			
//		});
		
	}
	public static void WXpay(final String prepayId, final String nonceStr, final String timeStamp, final String sign) {
		Log.e("TBU_DEBUG", "pay wx coming ...");
		AppActivity.activity.runOnUiThread(new Runnable() {
			
			@Override
			public void run() {
				PayReq request = new PayReq();
				request.appId = Constants.APP_ID;//商户号和APPID写死
				request.partnerId = Constants.PARTNER_ID;
				request.packageValue = "Sign=WXPay";
				request.prepayId= prepayId;
				request.nonceStr= nonceStr;
				request.timeStamp= timeStamp;
				request.sign= sign;
				msgApi.sendReq(request);
				Log.e("TBU_DEBUG", "pay wx end "+request.toString());
				
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
	
	public  static void shareToWx(){
		((AppActivity)AppActivity.activity).shareWebPage("192.168.1.1", "您的好友邀请您一起捞鱼哦", "捕呀捕,捕到一个大逗比", true);
		
	}
	
	public void shareWebPage(String webpageUrl, String title,
			String description, boolean friends) {
		WXWebpageObject webpage = new WXWebpageObject();
		webpage.webpageUrl = webpageUrl;
		WXMediaMessage msg = new WXMediaMessage(webpage);
		msg.title = title;
		msg.description = description;
		SendMessageToWX.Req req = new SendMessageToWX.Req();
		req.transaction = buildTransaction("webpage");
		req.message = msg;
		req.scene = friends ? SendMessageToWX.Req.WXSceneTimeline
				: SendMessageToWX.Req.WXSceneSession;
		req.scene = SendMessageToWX.Req.WXSceneSession;
		msgApi.sendReq(req);

//		WXTextObject textObj = new WXTextObject();
//		textObj.text = title;
//		
//		WXMediaMessage msg = new WXMediaMessage();
//		msg.mediaObject = textObj;
//		msg.description = title;
//		
//		SendMessageToWX.Req req = new SendMessageToWX.Req();
//		req.transaction = buildTransaction("text");
//		req.message = msg;
//		req.scene = friends ? SendMessageToWX.Req.WXSceneTimeline
//				: SendMessageToWX.Req.WXSceneSession;
//		req.scene = SendMessageToWX.Req.WXSceneSession;
//		msgApi.sendReq(req);

	}

	private String buildTransaction(final String type) {
		return (type == null) ? String.valueOf(System.currentTimeMillis())
				: type + System.currentTimeMillis();
	}

	
	protected void onPause() {
	    super.onPause();
	    AVAnalytics.onPause(this);

	}

	protected void onResume() {
	    super.onResume();
	    AVAnalytics.onResume(this);
	}


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
		runOnUiThread(new Runnable() {	
			@Override
			public void run() {
				Toast.makeText(AppActivity.this, "提交成功", Toast.LENGTH_LONG).show();
				
			}
		});
	}
	
	public static  boolean isWXAppInstalled() {
		return msgApi.isWXAppInstalled();
	}

	
}
