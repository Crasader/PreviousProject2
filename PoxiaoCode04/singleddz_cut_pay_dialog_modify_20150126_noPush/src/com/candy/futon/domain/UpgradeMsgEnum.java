package com.candy.futon.domain;

public enum UpgradeMsgEnum {
	
	NET_ERROR(404,"无法连接至更新服务器"),
	DOWN_ABORT(500,"下载失败"),
	SUCCESS(200,"成功读取服务器响应"),
	GENERIC_ERROR(501,"更新出现异常，请稍后再试");
	
	private int code;
	private String msg;
	private UpgradeMsgEnum(int code, String msg){
		this.code = code;
		this.msg = msg;
	}
	public int getCode() {
		return code;
	}
	public String getMsg() {
		return msg;
	}
	
}
