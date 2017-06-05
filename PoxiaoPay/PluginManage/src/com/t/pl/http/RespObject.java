package com.t.pl.http;

public class RespObject {
	private String errorCode;
	private String errorMessage;
	private String[] sequeens;
	private boolean secondConfirm;
	private int timeOut;

	public String getErrorCode() {
		return errorCode;
	}

	public void setErrorCode(String errorCode) {
		this.errorCode = errorCode;
	}

	public int getTimeOut() {
		return timeOut;
	}

	public void setTimeOut(int timeOut) {
		this.timeOut = timeOut;
	}

	public String getErrorMessage() {
		return errorMessage;
	}

	public void setErrorMessage(String errorMessage) {
		this.errorMessage = errorMessage;
	}

	public String[] getSequeens() {
		return sequeens;
	}

	public void setSequeens(String[] sequeens) {
		this.sequeens = sequeens;
	}

	public boolean isSecondConfirm() {
		return secondConfirm;
	}

	public void setSecondConfirm(boolean secondConfirm) {
		this.secondConfirm = secondConfirm;
	}

}
