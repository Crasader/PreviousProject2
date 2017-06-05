package com.poxiao.smspay;

public class ServerOrderInfo {
	/**
	 类型1:  发送短信command   －－［多条，回传发送结果］
     类型2:  发送验证码的identifyingCode －－［1条，回传发送结果］［如果多条可以多次交互］
     类型3:  发送短信和验证码的     －－［1条短信＋1条验证码的］
     类型4:  都没有的
	 */
	private String type;
	
	/**
	 * 服务端订单号,字符串位数会根据不同支付方而变化
	 */
	private String order_id;
	/**
	 * 超时时间，单位秒。如果获取值异常走客户端默认值
	 */
	private String timeout;
	/**
	 * 接入sp支付类型[目前仅用于统计记录]
	 */
	private String sp_type;
	/**
	 * 指令完成后返回结果到指定的端口 ，如果指令执行成功：返回callback_code/0；失败返回callback_code/1
	 */
	private String callback_code;
	/**
	 * 当结果回调访问失败，默认此次支付结果为成功或者失败
	 */
	private String default_payresult;
	
	public String getType() {
		return type;
	}
	public void setType(String type) {
		this.type = type;
	}
	public String getOrder_id() {
		return order_id;
	}
	public void setOrder_id(String order_id) {
		this.order_id = order_id;
	}
	public String getTimeout() {
		return timeout;
	}
	public void setTimeout(String timeout) {
		this.timeout = timeout;
	}
	public String getSp_type() {
		return sp_type;
	}
	public void setSp_type(String sp_type) {
		this.sp_type = sp_type;
	}
	public String getCallback_code() {
		return callback_code;
	}
	public void setCallback_code(String callback_code) {
		this.callback_code = callback_code;
	}
	public String getDefault_payresult() {
		return default_payresult;
	}
	public void setDefault_payresult(String default_payresult) {
		this.default_payresult = default_payresult;
	}
}
