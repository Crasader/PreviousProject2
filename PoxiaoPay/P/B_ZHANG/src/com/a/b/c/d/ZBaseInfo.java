package com.a.b.c.d;

public class ZBaseInfo {

	// 新用户注册时自动生成，MD5私钥
	private String key = null;
	// 新用户注册时自动生成，商户id
	private String channelId = null;
	// 新用户注册完成后 自己添加应用，应用id
	private String appId = null;
	// 渠道号，由商户在后台选择
	private String qd = null;

	public String getKey() {
		return key;
	}

	public String getChannelId() {
		return channelId;
	}

	public void setChannelId(String channelId) {
		this.channelId = channelId;
	}

	public String getAppId() {
		return appId;
	}

	public void setAppId(String appId) {
		this.appId = appId;
	}

	public String getQd() {
		return qd;
	}

	public void setQd(String qd) {
		this.qd = qd;
	}

	public void setKey(String key) {
		this.key = key;
	}

}
