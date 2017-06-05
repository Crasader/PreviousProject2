package com.tbu.androidtools.util.spcode;

/**
 * tbu的计费点和运营商计费点编码的对应关系类
 * 
 * @author QZ
 *
 */
public class SpCodeMap {
	
	private int pId;// 
	private String type;// 运营商类型
	private String spPoint;// 运营商计费点编码

	public int getPId() {
		return pId;
	}

	public void setPId(int pId) {
		this.pId = pId;
	}

	public String getType() {
		return type;
	}

	public void setType(String type) {
		this.type = type;
	}

	public String getSpPoint() {
		return spPoint;
	}

	public void setSpPoint(String spPoint) {
		this.spPoint = spPoint;
	}

}
