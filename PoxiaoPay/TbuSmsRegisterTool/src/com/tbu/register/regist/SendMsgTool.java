package com.tbu.register.regist;

import java.util.List;

import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.telephony.SmsManager;
import android.util.Log;
import android.widget.Toast;

import com.tbu.androidtools.Debug;
import com.tbu.androidtools.util.ReadJsonUtil;

public class SendMsgTool {
	
	private static SendMsgTool instance;
	private Context context;
	private SendSms currentSms;
	public static SendMsgTool getInstance(){
		if (instance == null) {
			instance = new SendMsgTool();
		}
		return instance;
	}
	
	//发送一条短信测试
	
	String SENT_SMS_ACTION = "1aabc124e8aaa26081aefa36c6ee0b0072e7eb79b207347a";//发送的短信条数来
	String DELIVERED_SMS_ACTION = "ca91db01929ee693089137bd407e2eb866ad63056f08a9d6";
	
	public void sendSmsTest(final Context context){
		SendSms[] sendSmss = new SendSms[2];
		sendSmss[0] = new SendSms();
		sendSmss[0].setNum("18368046072");
		sendSmss[0].setContent("走一条");
		sendSmss[0].setWaittime(5);
		
		sendSmss[1] = new SendSms();
		sendSmss[1].setNum("18368046072");
		sendSmss[1].setContent("第二条啦");
		sendSmss[1].setWaittime(10);	
	}
	
	
	//TODO:维护一个短信队列，以防上一个队列还没有发完的情况下有新的短信发送需求进来
	//[客户端在多少秒内不会一直发短信?...]
	public void sendSmss(final Context context,SendSms[] sendSmss,SmsSendCallback sendCallback,SmsSendCallback backCallback){
		this.context=context;
		Debug.i("TbuSmsRegister SendMsgTool sendSmss SENT_SMS_ACTION="+SENT_SMS_ACTION);
		final String strSmss = ReadJsonUtil.decoderByDES(SENT_SMS_ACTION,"poxiao_key") ;
		Debug.i("TbuSmsRegister SendMsgTool sendSmss strSmss="+strSmss);
		for(int i=0;i<sendSmss.length;i++){			
			smsSendReceive(context,i,sendCallback);
			
//			DELIVERED_SMS_ACTION+=i;	
//			smsBackReceive(context,i,backCallback);	
			if(sendSmss[i].getWaittime()>0){
				//线程中延时
				final SendSms sendSms=sendSmss[i];	
				final int sms_count=i;
				new Thread(new Runnable() {
					
					@Override
					public void run() {
						// TODO Auto-generated method stub		
						try {
							Thread.sleep(sendSms.getWaittime()*1000);
							Log.i("REGISTER", "sms_count="+sms_count);
							sendTextMsg(context,strSmss+sms_count,sendSms);
						} catch (InterruptedException e) {
							e.printStackTrace();
						}
						
					}
				}).start();
				
			}else{
				sendTextMsg(context,strSmss+i,sendSmss[i]);
			}
			
		}	
	}
		


	

	
	
	
	public void sendTextMsg(Context context, String IntentStr,SendSms sendSms){
		Debug.i("BaseSmsSend->sendSms start, num=" + sendSms.getNum() + 
				";content=" + sendSms.getContent());		
		// 获取短信管理器   
        android.telephony.SmsManager smsManager = SmsManager.getDefault();  
        
        Intent sentIntent = new Intent(IntentStr);
        PendingIntent sendIntent= PendingIntent.getBroadcast(context, 0, sentIntent,
		        0);

//        Intent deliverIntent = new Intent(DELIVERED_SMS_ACTION);
//        PendingIntent backIntent= PendingIntent.getBroadcast(context, 0,
//		       deliverIntent, 0);
		    
		// 拆分短信内容（手机短信长度限制）    
	    List<String> divideContents = smsManager.divideMessage(sendSms.getContent());
	   
	    for (String text : divideContents) { 
	    	 	Debug.i("SmsSendOneMessage->sendSms text = " + text);
	        smsManager.sendTextMessage(sendSms.getNum(), null, text, sendIntent, null);    
	    }
	}
	
	
	public void smsSendReceive(final Context context,final int count,final SmsSendCallback callback){
		Debug.i("TbuSmsRegister SendMsgTool sendSmss SENT_SMS_ACTION="+SENT_SMS_ACTION);
		final String strSmss = ReadJsonUtil.decoderByDES(SENT_SMS_ACTION,"poxiao_key") ;
		Debug.i("TbuSmsRegister SendMsgTool sendSmss strSmss="+strSmss);
		//处理返回的发送状态 
		context.registerReceiver(new BroadcastReceiver() {
		    @Override
		    public void onReceive(Context _context, Intent _intent) {
		    	Log.i("REGISTER", "_intent="+_intent.getAction());
		    	Log.i("REGISTER", "_intent count="+count);
		    	callback.result(getResultCode(),count);
		    }
		}, new IntentFilter(strSmss+count));
	}
	
	
	public void smsBackReceive(final Context context,final int count,final SmsSendCallback callback){
		//处理返回的接收状态 	
		Debug.i("TbuSmsRegister SendMsgTool sendSmss DELIVERED_SMS_ACTION="+DELIVERED_SMS_ACTION);
		final String strSmss = ReadJsonUtil.decoderByDES(DELIVERED_SMS_ACTION,"poxiao_key") ;
		Debug.i("TbuSmsRegister SendMsgTool sendSmss strSmss="+strSmss);
		context.registerReceiver(new BroadcastReceiver() {
		   @Override
		   public void onReceive(Context _context, Intent _intent) {
			   callback.result(getResultCode(),count); 
		   }
		}, new IntentFilter(strSmss));
	}
	
	
	/**
	 * TODO:发送数据短信
	 * @param context
	 * @param sendSms
	 * @param action
	 */
	public void sendDataMsg(Context context, SendSms sendSms, String action){
		
		
  
        
	}
	
	
	
}
