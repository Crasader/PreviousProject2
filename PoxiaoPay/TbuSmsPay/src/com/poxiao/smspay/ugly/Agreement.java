package com.poxiao.smspay.ugly;

/**
 * 
 * @author molo
 * @hide
 */
public class Agreement {
	/**
	 * 只有支付成功获得指令
	 */
	public static final String RESULT_SUCCESS = "0";
	/**
	 * 支付类型-没有获取到通道
	 */
	public static final int PAY_TYPE_NOTALLOWPAY = 0;
	
	/**
	 * 支付类型-发送短信
	 */
	public static final int PAY_TYPE_SENDSMS = 1;
	
	/**
	 * 支付类型-发送HTTP请求
	 */
	public static final int PAY_TYPE_SENDHTTPREQUEST = 2;
	
	/**
	 * 支付类型-发送短信获取验证码再发送计费
	 */
	public static final int PAY_TYPE_SENDSMS_ANDNEED_BACKINFO = 3;
	
	/**
	 * 支付类型-发送短信，但发送短信内容需要编码
	 */
	public static final int PAY_TYPE_SENDSMS_ANDNEEDDES = 4;
	
	/**
	 * 支付类型-直接发送道具
	 */
	public static final int PAY_TYPE_SUCCESS = 5;
	
	/**
	 * 服务端发送此字符串，表示直接给道具。
	 */
	public static final String SUCCESS_PAY_INFO = "10000";
	
	/**
	 * 解析服务端协议类型-还未启用
	 * @param strJson
	 * @return
	 */
	public static int getPayType(String strJson) {
		// TODO : 等待实现
		if(strJson == null) {
			return Agreement.PAY_TYPE_NOTALLOWPAY;
		}else if(strJson.trim().length() <= 0) {
			return Agreement.PAY_TYPE_NOTALLOWPAY;
		}
		
	 	if(Agreement.SUCCESS_PAY_INFO.equals(strJson)) {
	 		return Agreement.PAY_TYPE_SUCCESS;
	 	}
		
		// TODO : 等待分析其它Type类型
		
		return Agreement.PAY_TYPE_NOTALLOWPAY;
	}
	
	// TODO : 等待添加几个类型的数据获取方式
}
