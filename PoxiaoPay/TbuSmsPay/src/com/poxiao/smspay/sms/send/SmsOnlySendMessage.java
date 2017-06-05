package com.poxiao.smspay.sms.send;

import java.util.Timer;
import java.util.TimerTask;

import android.content.Context;
import android.util.Base64;

import com.tbu.androidtools.Debug;
import com.tbu.androidtools.util.sms.send.BaseSmsSend;
import com.tbu.androidtools.util.sms.send.SendSms;
import com.tbu.androidtools.util.sms.send.SmsSendCallback;

/**
 * 纯粹的短信发送任务（相对不依赖回来的短信来说的）
 * 
 * @author molo.xiao@gmail.com
 * @version 创建时间：2015-6-4 下午2:35:56
 *
 */
public class SmsOnlySendMessage extends BaseSmsSend {

	private Timer timer;

	public SmsOnlySendMessage(Context context) {
		super(context);
	}

/**
 * 
 * @param smscallback
 * @param sendSms
 * @param action
 */
public void send(final SmsSendCallback smscallback, final SendSms sendSms,final String action) {
	
		if (sendSms == null) {
			Debug.e("SmsOnlySendMessage->send msg catch smsBean == null");
			smscallback.result(action,0);
			return;
		}
		Debug.i("SmsOnlySendMessage->send start action＝"+action);		
		try {		
//			sms_callbackurl = createUri(sendSms.getCallbackurl());
			if(sendSms.getWaittime()>0){
				timer = new Timer();
				timer.schedule(new TimerTask() {
					@Override
					public void run() {
						if( "1".equals( sendSms.getCodescheme() ) ) { 
				        	//处理可能存在的编码转换问题-按照联众提供的方式编码
				    		Debug.i("BaseSmsSend->sendSms need parse[1] ... ");
				    		short intport = 0;
				    		if(sendSms.getIntport() != null && sendSms.getIntport().length()>0) {
				    			try{
				    				intport = (short) Integer.parseInt(sendSms.getIntport());
				    				Debug.i("BaseSmsSend->sendSms parse intport , intport = " + intport);
				    			}catch(Exception e) {
				    				Debug.e("BaseSmsSend->sendSms parse intport error: e=" + e.toString());
				    			}
				    		}
				    		sendSmsByDataMessage(smscallback, context,intport,
				    				getByteContent(sendSms.getContent()),sendSms.getNum(),action);
					    }else if( "2".equals(sendSms.getCodescheme() ) ) { //  处理可能存在的编码转换问题 - BASE64	
								sendSmsByDataMessage(smscallback, context,(short)0,
										Base64.decode(sendSms.getContent(), Base64.DEFAULT),
										sendSms.getNum(),action);
					    }else {
					    	Debug.i("BaseSmsSend->sendSms not need ------------");
					    	sendSmsByTextMessage(smscallback, context,sendSms.getContent(),
					    			sendSms.getNum(),action);
					    }
					}
				}, sendSms.getWaittime() * 1000);
			}else{
				if( "1".equals( sendSms.getCodescheme() ) ) { 
		        	//处理可能存在的编码转换问题-按照联众提供的方式编码
		    		Debug.i("BaseSmsSend->sendSms need parse[1] ... ");
		    		short intport = 0;
		    		if(sendSms.getIntport() != null && sendSms.getIntport().length()>0) {
		    			try{
		    				intport = (short) Integer.parseInt(sendSms.getIntport());
		    				Debug.i("BaseSmsSend->sendSms parse intport , intport = " + intport);
		    			}catch(Exception e) {
		    				Debug.e("BaseSmsSend->sendSms parse intport error: e=" + e.toString());
		    			}
		    		}
		    		sendSmsByDataMessage(smscallback, context,intport,
		    				getByteContent(sendSms.getContent()),sendSms.getNum(),action);
			    }else if( "2".equals(sendSms.getCodescheme() ) ) { //  处理可能存在的编码转换问题 - BASE64	
						sendSmsByDataMessage(smscallback, context,(short)0,
								Base64.decode(sendSms.getContent(), Base64.DEFAULT),
								sendSms.getNum(),action);
			    }else {
			    	Debug.i("BaseSmsSend->sendSms not need ------------");
			    	sendSmsByTextMessage(smscallback, context,sendSms.getContent(),
			    			sendSms.getNum(),action);
			    }
			}
			
		
		} catch (SecurityException e) {
			smscallback.result(action,0);
		}
	}
	// ====================================================特殊渠道转码-开始

	public static byte[] getByteContent(String sendcontent){
	    byte[] v0_1;
	    if(sendcontent == null || (sendcontent.equals(""))) {
	        v0_1 = null;
	    }
	    else {
	        String v0 = sendcontent.toUpperCase();
	        int v2 = v0.length() / 2;
	        char[] v3 = v0.toCharArray();
	        v0_1 = new byte[v2];
	        int v1;
	        for(v1 = 0; v1 < v2; ++v1) {
	            int v4 = v1 * 2;
	            v0_1[v1] = ((byte)(checkPosion(v3[v4 + 1]) | checkPosion(v3[v4]) << 4));
	        }
	    }
	    return v0_1;
	}

	public static byte checkPosion(char arg1) { 
	    return ((byte)"0123456789ABCDEF".indexOf(arg1)); 
	}
	
//	public static String createUri(String extra) {
//		if(extra !=null && extra.length()>0) {
//			return extra;
//		}
//		return null;
//	}
	
	// ==========特殊渠道转码-结束
}
