package com.tbu.androidtools.util.sms.send;

import java.util.List;
import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.telephony.SmsManager;
import android.util.Base64;

import com.tbu.androidtools.Debug;

/**
 * 发送短信的抽象类
* @author molo.xiao@gmail.com 
* @version 创建时间：2015-6-4 下午2:36:41
*
 */
public abstract class BaseSmsSend {
	public static int count = 0;
	
	private SmsReceiver smsReceiver;
	protected Context context;
	protected String action;
//	protected String sms_callbackurl;
	public  SmsSendCallback callback;
	
	public BaseSmsSend(Context context) {
		this.context = context;
		BaseSmsSend.count++;
	}

	
	
	public void sendSmsByDataMessage(SmsSendCallback callback,Context context,short disPort,byte[] content,String number,String action){
		Debug.i("BaseSmsSend->sendSms not need parse ... ");
		
		this.callback=callback;
		this.action=action;	
		//注册短信
		registerSmsReceiver();
		Intent itSend = new Intent(action);
        final PendingIntent sentPI = PendingIntent.getBroadcast(
                context.getApplicationContext(), 0, itSend, 0);
        
		android.telephony.SmsManager smsManager = SmsManager.getDefault(); 	
		smsManager.sendDataMessage(number, null, 
				disPort, content, sentPI, null);
	}
	
	public void sendSmsByTextMessage(SmsSendCallback callback,Context context,String content,String number,String action){
		Debug.i("BaseSmsSend->sendSms not need parse ... ");	
		
		this.callback=callback;
		this.action=action;	
		//注册短信
		registerSmsReceiver();
		Intent itSend = new Intent(action);// 发送intent
        final PendingIntent sentPI = PendingIntent.getBroadcast(
                context.getApplicationContext(), 0, itSend, 0);
        
		android.telephony.SmsManager smsManager = SmsManager.getDefault();  
		// 拆分短信内容（手机短信长度限制）    
	    List<String> divideContents = smsManager.divideMessage(content);
	   
	    for (String text : divideContents) { 
	    	 	Debug.i("SmsSendOneMessage->sendSms text = " + text);
	        smsManager.sendTextMessage(number, null, text, sentPI, null);    
	    }
	}
	
	
	public void registerSmsReceiver() {
		Debug.i("SmsOnlySendMessage->registerSmsReceiver start");
		if(smsReceiver == null) {
			smsReceiver = new SmsReceiver();
			try{
				context.registerReceiver(smsReceiver, new IntentFilter(action));
			}catch(Exception e) {
				Debug.e("SmsOnlySendMessage->registerSmsReceiver, e= " + e.toString());
			}
			Debug.i("SmsOnlySendMessage->registerSmsReceiver, Success!!");
		}else {
			Debug.e("SmsOnlySendMessage->registerSmsReceiver not needed");
		}
	}
	
	public void unRegisterSmsReceiver() {
		if(smsReceiver != null) {
			context.unregisterReceiver(smsReceiver);
			smsReceiver= null;
			Debug.i("SmsOnlySendMessage->unRegisterSmsReceiver, Success!! ");
		}
	}
	
	private class SmsReceiver extends BroadcastReceiver {
		@Override
		public void onReceive(Context context, Intent intent) {
			String actionName = intent.getAction();
            int resultCode = getResultCode();
            Debug.i("SmsOnlySendMessage->SmsReceiver->onReceive(), intent.getAction()[SENT_SMS_ACTION] = "
            			+ actionName + ";resultCode=" + resultCode);
            unRegisterSmsReceiver();
            callback.result(actionName,resultCode);
		}
	}
	
	
	/**
	 * 短信发送状态监听的Action参数-针对第一条短信发送的情况
	 */
//	private final static String SENT_SMS_ACTION_ONE = "SENT_SMS_ACTION_ONE";
	
	/**
	 * 短信发送状态监听的Action参数-针对第二条短信发送的情况
	 */
//	private final static String SENT_SMS_ACTION_TWO = "SENT_SMS_ACTION_TWO";
	
	
//	public void sendSms(SmsSendCallback callback,Context context, SendSms sendSms, String action) {
//		//注册短信
//		registerSmsReceiverOne();
//		this.callback=callback;
//		
//		
//		Debug.i("BaseSmsSend->sendSms start, num=" + 
//		sendSms.getNum() + ";content=" + sendSms.getContent());	
//		
//		Intent itSend = new Intent(action);// 发送intent
//        final PendingIntent sentPI = PendingIntent.getBroadcast(
//                context.getApplicationContext(), 0, itSend, 0);
//        
//		// 获取短信管理器   
//        android.telephony.SmsManager smsManager = SmsManager.getDefault();  
//        if( "1".equals( sendSms.getCodescheme() ) ) { //处理可能存在的编码转换问题-按照联众提供的方式编码
//        		Debug.i("BaseSmsSend->sendSms need parse[1] ... ");
//        		short intport = 0;
//        		if(sendSms.getIntport() != null && sendSms.getIntport().length()>0) {
//        			try{
//        				intport = (short) Integer.parseInt(sendSms.getIntport());
//        				Debug.i("BaseSmsSend->sendSms parse intport , intport = " + intport);
//        			}catch(Exception e) {
//        				Debug.e("BaseSmsSend->sendSms parse intport error: e=" + e.toString());
//        			}
//        		}
//            smsManager.sendDataMessage(sendSms.getNum(), null, 
//            		intport, getByteContent(sendSms.getContent()), sentPI, null);
//            sendSmsByDataMessage(intport,getByteContent(sendSms.getContent()),sendSms.getNum(),action);
//        }else if( "2".equals( sendSms.getCodescheme() ) ) { //  处理可能存在的编码转换问题 - BASE64
//    			Debug.i("BaseSmsSend->sendSms need parse [2]... ");
//    			smsManager.sendDataMessage(sendSms.getNum(), null, 
//    					(short)0, Base64.decode(sendSms.getContent(), Base64.DEFAULT), sentPI, null);
 		
//    			sendSmsByDataMessage((short)0,Base64.decode(sendSms.getContent(), Base64.DEFAULT),sendSms.getNum(),action);
//        }else {
//        	sendSmsByTextMessage(sendSms.getContent(),sendSms.getNum(),action);
//        }
        
//	}
	
	/**
	 * 处理短信发送状态逻辑-第一条
	* @author molo.xiao@gmail.com 
	* @version 创建时间：2015-6-4 下午4:11:02
	*
	 */
//	private class SmsReceiverOne extends BroadcastReceiver {
//
//		@Override
//		public void onReceive(Context context, Intent intent) {
//			String actionName = intent.getAction();
//            int resultCode = getResultCode();
//            Debug.i("SmsOnlySendMessage->SmsReceiverOne->onReceive(), intent.getAction()[SENT_SMS_ACTION] = "
//            			+ actionName + ";resultCode=" + resultCode);
//            if (actionName.equals(action1)) {
//            	callback.result(resultCode);   
//            }
//		}
//	}
	

	
	/**
	 * 处理短信发送状态逻辑-第二条
	* @author molo.xiao@gmail.com 
	* @version 创建时间：2015-6-4 下午4:11:02
	*
	 */
//	private class SmsReceiverTwo extends BroadcastReceiver {
//
//		@Override
//		public void onReceive(Context context, Intent intent) {
//			String actionName = intent.getAction();
//            int resultCode = getResultCode();
//            Debug.i("SmsOnlySendMessage->SmsReceiverTwo->onReceive(), intent.getAction()[SENT_SMS_ACTION] = "
//            			+ actionName + ";resultCode=" + resultCode);
//            if (actionName.equals(action2)) {   
//            	callback.result(resultCode);
//            }
//		}
//	}
	
//	public void registerSmsReceiverOne() {
//		Debug.i("SmsOnlySendMessage->registerSmsReceiverOne start");
//		if(smsReceiverOne == null) {
//			smsReceiverOne = new SmsReceiverOne();
//			try{
//				context.registerReceiver(smsReceiverOne, new IntentFilter(action1));
//			}catch(Exception e) {
//				Debug.e("SmsOnlySendMessage->registerSmsReceiverTwo, e= " + e.toString());
//			}
//			Debug.i("SmsOnlySendMessage->registerSmsReceiverOne, Success!!");
//		}else {
//			Debug.e("SmsOnlySendMessage->registerSmsReceiverOne not needed");
//		}
//	}
//	
//	public void unRegisterSmsReceiverOne() {
//		if(smsReceiverOne != null) {
//			context.unregisterReceiver(smsReceiverOne);
//			smsReceiverOne = null;
//			Debug.i("SmsOnlySendMessage->unRegisterSmsReceiverOne, Success!! ");
//		}
//	}
//	
//	public void registerSmsReceiverTwo() {
//		if(smsReceiverTwo == null) {
//			smsReceiverTwo = new SmsReceiverTwo();
//			try{
//			context.registerReceiver(smsReceiverTwo, new IntentFilter(action2));
//			}catch(Exception e) {
//				Debug.e("SmsOnlySendMessage->registerSmsReceiverTwo, e= " + e.toString());
//			}
//			Debug.i("SmsOnlySendMessage->registerSmsReceiverTwo, Success!! ");
//		}else {
//			Debug.e("SmsOnlySendMessage->registerSmsReceiverTwo not needed");
//		}
//	}
//	
//	public void unRegisterSmsReceiverTwo() {
//		if(smsReceiverTwo != null) {
//			context.unregisterReceiver(smsReceiverTwo);
//			smsReceiverTwo = null;
//			Debug.i("SmsOnlySendMessage->unRegisterSmsReceiverTwo, Success!! ");
//		}
//	}
	

}
