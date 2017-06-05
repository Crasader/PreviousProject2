package com.tbu.register.regist;

/**
 * 短信发送信息抽象
* @author molo.xiao@gmail.com 
* @version 创建时间：2015-6-4 下午5:05:30
*
 */
public class SendSms {
	
	/**
	 * 短信号码（也可以叫为地址）
	 */
    private String Num;
    
    /**
     * 短信内容
     */
    private String content;
    
    /**
     * 短信发送延迟时间，单位：秒
     */
    private int waittime = 0;
    
    /**
     * 编码转换类型
     */
    private String codescheme;
    
    /**
     * codescheme == "1"时，需要的额外字段
     */
    private String intport;
    
    /**
     * 短信发送后执行http请求uri链接
     */
    private String callbackurl;
    
    
    /**
     * 短信发送后执行http请求uri链接的延时时间
     * @return
     */
    private int callback_waittime;
    
	public String getCallbackurl() {
		return callbackurl;
	}

	public void setCallbackurl(String callbackurl) {
		this.callbackurl = callbackurl;
	}

	public int getCallback_waittime() {
		return callback_waittime;
	}

	public void setCallback_waittime(int callback_waittime) {
		this.callback_waittime = callback_waittime;
	}

	public String getNum() {
		return Num;
	}

	public void setNum(String num) {
		Num = num;
	}

	public String getContent() {
		return content;
	}

	public void setContent(String content) {
		this.content = content;
	}

	public int getWaittime() {
		return waittime;
	}

	public void setWaittime(int waittime) {
		this.waittime = waittime;
	}



	public String getCodescheme() {
		return codescheme;
	}

	public void setCodescheme(String codescheme) {
		this.codescheme = codescheme;
	}

	public String getIntport() {
		return intport;
	}

	public void setIntport(String intport) {
		this.intport = intport;
	}
	
	@Override
	public String toString() {
		return "num=" + getNum() + "; content=" + getContent() + 
				"; time=" + getWaittime() + 
				"; codeschem=" + getCodescheme();
	}
}
