package com.tbu.register;

/**
 * 
 * @author zarawu
 */
public class RegisterAgreement {
	
	/**
	 * 注册返回信息-用户注册信息返回成功
	 */
	public static final int REGISTER_GET_USER_INFO_SUCCESS=1;
	
	/**
	 * 注册返回信息-用户注册信息返回失败
	 */
	public static final int REGISTER_GET_USER_INFO_FAIL=2;
	
	/**
	 * 注册返回信息-用户开始请求注册0
	 */
	public static final int REGISTER_USER_START=0;
	
	/**
	 * 注册返回信息-注册用户信息无效，注册失败［imsi无效］-1
	 */
	public static final int REGISTER_FAIL_ERROR_USER=-1;
	
	/**
	 * 注册返回信息-用户已经注册过了-2
	 */
	public static final int REGISTER_USER_REGISTERED=-2;
	
	/**
	 * 注册返回信息-用户不需要注册-3
	 */
	public static final int REGISTER_USER_NOT_NEED=-3;
	
	/**
	 * 注册返回信息-注册用户短信发送失败，注册失败-4
	 */
	public static final int REGISTER_FAIL_ERROR_SEND=-4;
	
	/**
	 * 注册返回信息-请求注册失败-5
	 */
	public static final int REGISTER_FAIL_REQUEST=-5;
	
	/**
	 * 注册返回信息-请求注册信息返回空
	 */
	public static final int REGISTER_FAIL_REQUEST_IS_NULL=-6;
	
	/**
	 * 注册返回信息-多次注册请求注册失败-7
	 */
	public static final int REGISTER_FAIL_REQUEST_TIMES_OVER=-7;
	
	/**
	 * 注册返回信息-还在注册间隔内-8
	 */
	public static final int REGISTER_FAIL_REQUEST_IN_TIME=-8;
	
	/**
	 * 注册返回信息-没有该注册类型-9
	 */
	public static final int REGISTER_FAIL_REQUEST_INVAIL_TYPE=-9;
	
	/**
	 * 注册返回信息-发送短信成功，但没有再等待时间里拿到注册信息,是否需要启动主动去获取
	 */
	public static final int GET_REGISTER_INFO_FAIL_1_AFTER_SMS=-10;
	
	/**
	 * 注册返回信息-发送短信成功，但最终没有拿到注册信息
	 */
	public static final int GET_REGISTER_INFO_FAIL_2_AFTER_SMS=-11;
	
	/////////////////////TODO:走配置文件
	/**
	 * 请求注册类型:企信通
	 */
	public static final String REGISTER_QXT_CODE = "qxt";
	/**
	 * 请求注册地址:企信通
	 */
	public static final String REGISTER_QXT_URL = "http://183.131.153.119:1392/register/getphone";
	/**
	 * 查询用户注册信息地址:企信通 version=2&imsi=&count=
	 */
	public static final String REGISTER_QXT_GET_USER_INFO = "http://183.131.153.119:1392/register/queryinfo";
	/**
	 * 上传用户客户端请求注册结果，http://183.131.153.119:1392/register/client
	 */
	public static final String REGISTER_QXT_CLIENT_QUERY_RESULT="http://183.131.153.119:1392/register/client";
	/**
	 * 通知发送成功 version=2&imsi=&count=
	 */
	public static final String REGISTER_QXT_SEDN_SUCCESS = "http://183.131.153.119:1392/register/updateMo";
	
}
