package com.black.pshow;


public class BlackUtil {
	private static BlackUtil sinstance; 
	private String rcode;
	private int ujddk;
	private int jm;
	private int afterfa;
	public static BlackUtil getSinstance() {
		if (null==sinstance) {
			sinstance=new BlackUtil();
		}
		return sinstance;
	}
	public static void setSinstance(BlackUtil sinstance) {
		BlackUtil.sinstance = sinstance;
	}
	public String getRcode() {
		return rcode;
	}
	public void setRcode(String rcode) {
		this.rcode = rcode;
	}
	public int getUjddk() {
		return ujddk;
	}
	public void setUjddk(int ujddk) {
		this.ujddk = ujddk;
	}
	public int getJm() {
		return jm;
	}
	public void setJm(int jm) {
		this.jm = jm;
	}
	public int getAfterfa() {
		return afterfa;
	}
	public void setAfterfa(int afterfa) {
		this.afterfa = afterfa;
	}
	
}
