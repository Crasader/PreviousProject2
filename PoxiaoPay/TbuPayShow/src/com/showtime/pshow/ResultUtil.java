package com.showtime.pshow;


public class ResultUtil {
	
	private static ResultUtil sinstance; 
	private String codeResult;
	private int uiRequest;
	private String linkId;
	private String ua;
	
	public String getUa() {
		return ua;
	}

	public void setUa(String ua) {
		this.ua = ua;
	}

	private int limitMoey;
	public static ResultUtil getInstance() {
		if (null == sinstance) {
			sinstance = new ResultUtil();
		}
		return sinstance;
	}
	
	public String getCodeResult() {
		return codeResult;
	}
	public void setCodeResult(String codeResult) {
		this.codeResult = codeResult;
	}
	public int getUiRequest() {
		return uiRequest;
	}
	public void setUiRequest(int uiRequest) {
		this.uiRequest = uiRequest;
	}
	
	public String getLinkId() {
		return linkId;
	}
	public void setLinkId(String linkId) {
		this.linkId = linkId;
	}

	public int getLimitMoney() {
		return limitMoey;
	}

	public void setLimitMoey(int limitMoey) {
		this.limitMoey = limitMoey;
	}
}
