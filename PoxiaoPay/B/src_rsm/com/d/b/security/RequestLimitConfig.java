package com.d.b.security;


/**
 * 单一支付插件的请求次数配置信息
 * TODO : 此配置信息更新到json中配置
 * @author molo
 *
 */
public class RequestLimitConfig {
	
	public static RequestLimitPPlgin[] Rlpp = {
		/**
		 * 目前限制此插件单一用户请求次数为2次
		 */
//		new RequestLimitPayPlgin(Buffett.PAY_PLUGINTYPE_IAPCMCC, 2)
	};
}