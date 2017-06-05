package com.poxiao.smspay;

/**
 * 
* @author molo.xiao@gmail.com 
* @version 创建时间：2015-6-4 下午3:22:22
*
 */
public interface TbuPayCallBack {
	
	public static final String RESULT_CODE_KEY = "RESULT_CODE_KEY";
	public static final String RESULT_MESSAGE_KEY = "RESULT_MESSAGE_KEY";
	
	/**
	 * 没有获取到通道
	 */
	public static final int RESULT_CODE_FAIL_GETCODE = 100;
	
	/**
	 * 支付时遇到错误
	 */
	public static final int RESULT_CODE_FAIL_ERROR = 101;
	
	/**
	 * 支付时服务端信息解析错误-大部分可能是json协议对应有误
	 */
	public static final int RESULT_CODE_FAIL_READJSON = 102;
	
	/**
	 * 支付时超时
	 */
	public static final int RESULT_CODE_FAIL_TIMEOUT = 103;
	
	/**
	 * 支付时短信发送失败
	 */
	public static final int RESULT_CODE_FAIL_SENDSMS = 104;
	
	/**
	 * 发送验证码时失败
	 */
	public static final int RESULT_CODE_FAIL_VERIFY = 105;
	
	/**
	 * 解析服务端下发的指令失败
	 */
	public static final int RESULT_CODE_FAIL_PARSE_SERVERORDER = 106;
	
	/**
	 * 访问下一条指令失败走默认失败结果
	 */
	public static final int RESULT_CODE_FAIL_DEFAULT_RESULT=107;
	
	/**
	 * 进行网络类型的付费时遇到错误
	 */
	public static final int RESULT_CODE_FAIL_ONHTTPPAY = 121;
	
	/**
	 * 支付过程中本地会话参数传递异常
	 */
	public static final int RESULT_CODE_FAIL_AGU = 131;
	
	/**
	 * 进行订单请求时错误
	 */
	public static final int RESULT_CODE_FAIL_ORDERREQ = 141;
	
	/**
	 * 支付成功
	 */
	public static final int RESULT_CODE_SUCCESS = 0;
		
	/**
	 * 
	 * @param resultCode
	 * @param resultMsg
	 */
    public void PayResult(int resultCode, String resultMsg);
}
