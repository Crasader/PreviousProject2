package com.poxiao.smspay;

import org.json.JSONArray;
import org.json.JSONObject;

import com.poxiao.smspay.activity.BasePayUiActivity;
import com.poxiao.smspay.observer.SmsObserverManager;
import com.poxiao.smspay.observer.SmsVerify;
import com.poxiao.smspay.observer.domain.SFI;
import com.tbu.androidtools.Debug;
import com.tbu.androidtools.util.sms.send.SendSms;

public class ReadServerJson {
	

	public static boolean readJsonInfo(String orderInfo,ServerOrderInfo serverOrderInfo,SendSms[] sendSmss
			,SmsVerify smsVerify) {
		try {
			Debug.i("SmsPayBasis->orderInfo is not null,orderInfo=" + orderInfo);
			JSONObject order = new JSONObject(orderInfo);
			//服务端客户端同步的id
			if (order.has("order_id")) {
				serverOrderInfo.setOrder_id(order.getString("order_id"));		
			}
			 // 会话超时时间
			if (order.has("timeout")) {
				serverOrderInfo.setTimeout(order.getString("timeout"));
			}else{
				serverOrderInfo.setTimeout(BasePayUiActivity.PAY_WAIT_TIMEOUT+"");
			}
			// sp支付类型
			if (order.has("sp_type")) { 
				serverOrderInfo.setSp_type( order.getString("sp_type"));
			}
			//指令类型：类型1:  发送短信command,2:  发送验证码的identifyingCode,3:  发送短信和验证码的
			//类型1:  发送短信command   －－［多条，回传发送结果］
		    //类型2:  发送验证码的identifyingCode －－［1条，回传发送结果］［如果多条可以多次交互］
		    //类型3:  发送短信和验证码的     －－［1条短信＋1条验证码的］
			if (order.has("command_type")) { 
				serverOrderInfo.setType( order.getString("command_type"));
			}
			
			//指令结束回传：添加指令成功失败参数
			if (order.has("callback_code")) { 
				serverOrderInfo.setCallback_code( order.getString("callback_code"));
			}
			//如果指令结果回传失败，启用改指令默认的支付结果设置
			if (order.has("default_payresult")) { 
				serverOrderInfo.setDefault_payresult( order.getString("default_payresult"));
			}
			
			////////////////////////////短信指令内容
			if (order.has("command")) {
				JSONArray command = order.getJSONArray("command");
				sendSmss = new SendSms[command.length()];
				Debug.e("SmsPayBasis->command.length()="+command.length());
				for (int j = 0; j < command.length(); j++) {			
					sendSmss[j] = new SendSms();
					if (command.getJSONObject(j).has("port")) {
						sendSmss[j].setNum(command.getJSONObject(j).getString("port"));
					} else {
						Debug.e("SmsPayBasis->readJson:未下发短信的port");
					}
					
					if (command.getJSONObject(j).has("content")) {
						sendSmss[j].setContent(command.getJSONObject(j).getString("content"));
					} else {
						Debug.e("SmsPayBasis->readJson:未下发短信的content");
					}
					if (command.getJSONObject(j).has("seconds")) {
						sendSmss[j].setWaittime(Integer.valueOf(command
								.getJSONObject(j).getString("seconds")));
					}
					if (command.getJSONObject(j).has("callbackurl")) {
						sendSmss[j].setCallbackurl(command.getJSONObject(j)
								.getString("callbackurl"));
					}
					
					if (command.getJSONObject(j).has("codescheme")) {
						sendSmss[j].setCodescheme(command.getJSONObject(j)
								.getString("codescheme"));
					}
					if (command.getJSONObject(j).has("intport")) {
						sendSmss[j].setIntport(command.getJSONObject(j)
								.getString("intport"));
					}
					if (command.getJSONObject(j).has("price")) { // 单条短信的价格
//						markInfo.smsprice += command.getJSONObject(j).getString("price");
//						String addTag = ";";
//						if (j == command.length() - 1) {
//							addTag = "";
//						}
//						markInfo.smsprice += addTag;
					} else {
						Debug.e("SmsPayBasis->readJson:未下发短信的price");
					}
					
					
					Debug.i("SmsPayBasis->readJson, j=" + j + "; [sendSms]"
							+ sendSmss[j].toString());
				
				}
			}

			if (order.has("identifyingCode")) {
				
				JSONArray identifyingCode = order
						.getJSONArray("identifyingCode");
				
				smsVerify = new SmsVerify();
				
				//需要拦截的号码
				if (identifyingCode.getJSONObject(0).has("port")) {
					smsVerify.setNumber(identifyingCode.getJSONObject(0)
							.getString("port"));
				}
				//要截取字符串的开始字段
				if (identifyingCode.getJSONObject(0).has("icStart")) {
					smsVerify.setStartStr(identifyingCode.getJSONObject(0)
							.getString("icStart"));
				}
				//要截取字符串的结束字段
				if (identifyingCode.getJSONObject(0).has("icEnd")) {
					smsVerify.setEndStr(identifyingCode.getJSONObject(0)
							.getString("icEnd"));
				}

				// 如果存在写入url信息
				if (identifyingCode.getJSONObject(0).has("sendurl")) {
					smsVerify.setSendurl(identifyingCode.getJSONObject(0)
							.getString("sendurl"));
				}
				
				//如果需要发送到固定端口一定下发
				if (identifyingCode.getJSONObject(0).has("sendport")) {
					smsVerify.setSendNumber(identifyingCode.getJSONObject(0)
							.getString("sendport"));
				}
				
				// 在没有验证码匹配规则的情况下写死验证码内容
				if (identifyingCode.getJSONObject(0).has("sendcontent")) {
					smsVerify.setSendContent(identifyingCode.getJSONObject(0)
							.getString("sendcontent"));
				}
				
				//根据type来判断需要怎样匹配发送内容
				if (identifyingCode.getJSONObject(0).has("rulecontent")) {
					smsVerify.setRuleContent(identifyingCode.getJSONObject(0)
							.getString("rulecontent"));
				}
				
				smsVerify.setOrderId(order.getString("order_id"));
				smsVerify.setTime(System.currentTimeMillis());
				
			}

			if (order.has("intercept")) {
				JSONArray intercept = order.getJSONArray("intercept");
				for (int j = 0; j < intercept.length(); j++) {
					SFI item = new SFI();
					item.setNu(intercept.getJSONObject(j).getString("port"));
					item.setCc(intercept.getJSONObject(j)
							.getString("keyword"));
					item.setTs(System.currentTimeMillis());
					SmsObserverManager.addSmsFilterItem(item);
					Debug.i("SmsPayBasis->Add SmsFilter!!number="
							+ item.getNu() + ";ContainContent = "
							+ item.getCc());
				}
			}

			return true;
		} catch (Exception e) {
			Debug.e("SmsPayBasis->readJsonInfo error, e= " + e.toString());
			e.printStackTrace();
			return false;
		}
	}
}

///////////////////协议说明////////
/*
 * 
{
    result : 0 //10000:直接支付成功,0:获取指令成功，1:获取指令失败
}
 * 
 * 
 "order_info" : {
        order_id : "",          -- 服务端订单号,字符串位数会根据不同支付方而变化［必填］
        timeout : "",         -- 超时时间，单位秒。如果获取值异常走客户端默认值［必填］
        sp_type : "",               -- 接入sp支付类型[目前仅用于统计记录]［必填］
        command_type:"",		--指令类型：1:  发送短信command,2:  发送验证码的identifyingCode,3:  发送短信和验证码的［必填］
        callback_code:"",		--指令成功结束回传：添加指令成功失败参数［必填］
        default_payresult:""     --如果指令结果回传失败，启用改指令默认的支付结果设置［必填］
 } 
 * 
 * 
"command": [
        {
            "seconds":"0",             --跟上一条短信间隔时间,0表示立即 ［必填］
            "content": "2#x5q7S#1",     --短信指令内容 ［必填］
            "port": "11817175",            --短信指令接口，如果包含http,发送http ［必填］
            "price" : "0" ,   -- 价格，单位分 ［必填］
            "callbackurl":"http://211.154.162.11/PatchLog.action",   --短信发送完后发起HTTP-GET请求 [有无]
            "codescheme" : "0",    -- 编码方式。如果等于"1"则按照规则1处理。[有无]
            "intport" : ""    -- type需要的字段,String最终会转换为short类型[有无］
        }
  ]
  
 * 
"identifyingCode": [
        {
             "icStart" : "验证码",     --接受验证码开始字符，为空则头开始  ［必填］
             "icEnd" : "谢谢",     --接受验证码结束字符，为空则到最后        ［必填］
             "port" : "11817175",            --接受验证码接口,0表示不需要发送 ［必填］
             "sendport" : "",         --如果不为空则下发到指定端口，如果为空则下发到发送端口 ［必填］
             “sendurl" : "" ,            --如果有发送验证码到该url［有无］
             "rulecontent" : “”,     -- 如果不为空表示按规则截取验证码替换下发内容中的XXXX字符串 ［有无］
             “sendcontent" : “”,  --如果不为空表示发送指定内容 ［有无］
        }
  ]
  

 */




