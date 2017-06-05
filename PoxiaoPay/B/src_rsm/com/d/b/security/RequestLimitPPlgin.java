package com.d.b.security;

/**
 * 单一支付插件限制请求次数
 * @author molo
 *
 */
public class RequestLimitPPlgin {

	/**
	 * 支付插件名称
	 */
	private String plginName;
	
	/**
	 * 支付插件单一游戏限制请求次数
	 */
	private int limitTimes;

	public RequestLimitPPlgin(String plginName, int limitTimes) {
		super();
		this.plginName = plginName;
		this.limitTimes = limitTimes;
	}

	public String getPlginName() {
		return plginName;
	}

	public int getLimitTimes() {
		return limitTimes;
	}
}