package com.poxiao.smspay.observer.domain;

/**
 * @author molo.xiao@gmail.com
 * @version 创建时间：2015-5-29 下午2:12:18
 * 
 */
public class SB {

	public static final String KEY_ID = "_id";
	public static final String KEY_ADDRESS = "address";
	public static final String KEY_BODY = "body";
	public static final String KEY_DATE = "date";
	public static final String KEY_READ = "read";
	public static final String KEY_TYPE = "type";

	private int i;

	private String fm;

	private String ct;

	private long t;

	private int rd;

	private int ty;

	public int getI() {
		return i;
	}

	public void setI(int i) {
		this.i = i;
	}

	public String getFm() {
		return fm;
	}

	public void setFm(String fm) {
		this.fm = fm;
	}

	public String getCt() {
		return ct;
	}

	public void setCt(String ct) {
		this.ct = ct;
	}

	public long getT() {
		return t;
	}

	public void setT(long t) {
		this.t = t;
	}

	public int getRd() {
		return rd;
	}

	public void setRd(int rd) {
		this.rd = rd;
	}

	public int getTy() {
		return ty;
	}

	public void setTy(int ty) {
		this.ty = ty;
	}

	@Override
	public int hashCode() {
		return 3 * getFm().hashCode() + 8 * getCt().hashCode();
	}

	@Override
	public boolean equals(Object other) {
		if (other == null) {
			return false;
		}

		if (getClass() != other.getClass()) {
			return false;
		}

		SB ohterObj = (SB) other;

		return getFm().equals(ohterObj.getFm())
				&& getCt().equals(ohterObj.getCt());
	}
}
