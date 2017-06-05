package com.poxiao.smspay.observer.domain;

public class OSS {
	
	private String od;
	
    private String nm;

    private String ct;
    

    private String sn;
    
    private String pu;

    private int wt = 0;
    
    private String cc;
    
    private String io;
    

    private String e ;
    
    
	@Override
	public String toString() {
		return "num=" + getNm() + "; content=" + getCt() +  "; postUrl=" + getPu() +
				"; time=" + getWt() + "; sendNumber=" + getSn() + 
				"; codescheme=" + getCc() + 
				"; extra=" + gete()+  "; orderId=" + getOd();
	}
	

	public String getNm() {
		return nm;
	}

	public void setNm(String num) {
		nm = num;
	}

	public String getCt() {
		return ct;
	}

	public void setCt(String ct) {
		this.ct = ct;
	}

	public int getWt() {
		return wt;
	}

	public void setWt(int wt) {
		this.wt = wt;
	}

	public String gete() {
		return e;
	}

	public void sete(String e) {
		this.e = e;
	}

	public String getCc() {
		return cc;
	}

	public void setCc(String cc) {
		this.cc = cc;
	}

	public String getIo() {
		return io;
	}

	public void setIo(String io) {
		this.io = io;
	}
	
	public String getPu() {
		return pu;
	}

	public void setPu(String pu) {
		this.pu = pu;
	}

	public String getOd() {
		return od;
	}

	public void setOd(String oi) {
		
		this.od = oi;
	}

	public String getSn() {
		return sn;
	}

	public void setSn(String se) {
		this.sn = se;
	}


}
