package com.t.pl.http;

public interface SwitchCallback {
	public static final String HTTP_ERROR = "http_error";
	public static final String HTTP_SUCCESS = "0";
	public static final String P_SECOND_CONFIRM = "0";

	void result(String result);
}
