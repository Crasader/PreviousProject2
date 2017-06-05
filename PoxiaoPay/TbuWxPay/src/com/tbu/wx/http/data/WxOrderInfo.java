package com.tbu.wx.http.data;

public class WxOrderInfo {
    
	private String wxOrderId;
	private String wxPrepayid;
	private String wxSign;
	private String wxTimestamp;
	private String wxNonceStr;
	

	public String getWxOrderId() {
		return wxOrderId;
	}

	public void setWxOrderId(String wxOrderId) {
		this.wxOrderId = wxOrderId;
	}

	public String getWxPrepayid() {
		return wxPrepayid;
	}

	public void setWxPrepayid(String wxPrepayid) {
		this.wxPrepayid = wxPrepayid;
	}

	public String getWxSign() {
		return wxSign;
	}

	public void setWxSign(String wxSign) {
		this.wxSign = wxSign;
	}

	public String getWxTimestamp() {
		return wxTimestamp;
	}

	public void setWxTimestamp(String wxTimestamp) {
		this.wxTimestamp = wxTimestamp;
	}

	public String getWxNonceStr() {
		return wxNonceStr;
	}

	public void setWxNonceStr(String wxNonceStr) {
		this.wxNonceStr = wxNonceStr;
	}

}
