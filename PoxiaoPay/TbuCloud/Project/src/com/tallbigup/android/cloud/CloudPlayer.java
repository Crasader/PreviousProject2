package com.tallbigup.android.cloud;

import com.avos.avoscloud.AVUser;

public class CloudPlayer extends AVUser {

	public CloudPlayer(String username, String password) {
		super.setUsername(username);
		super.setPassword(password);
	}

	public void setNickName(String nickName) {
		this.put("nickName", nickName);
	}

	public String getNickName() {
		return this.getString("nickName");
	}

	public void setIMSI(String IMSI) {
		this.put("IMSI", IMSI);
	}

	public String getIMSI() {
		return this.getString("IMSI");
	}

	public void setIMEI(String IMEI) {
		this.put("IMEI", IMEI);
	}

	public String getIMEI() {
		return this.getString("IMEI");
	}

	public void setEnterId(String enterId) {
		this.put("enterId", enterId);
	}

	/**
	 * 渠道号
	 * 
	 * @return
	 */
	public String getEnterId() {
		return this.getString("enterId");
	}

	public void setGameVersionCode(String gameVersionCode) {
		this.put("gameVersionCode", gameVersionCode);
	}

	/**
	 * 游戏版本号
	 * 
	 * @return
	 */
	public String getGameVersionCode() {
		return this.getString("gameVersionCode");
	}

	/**
	 * 厂商
	 * 
	 * @param hsman
	 */
	public void setHsman(String hsman) {
		this.put("hsman", hsman);
	}

	public String getHsman() {
		return this.getString("hsman");
	}

	/**
	 * 机型
	 * 
	 * @param hstype
	 */
	public void setHstype(String hstype) {
		this.put("hstype", hstype);
	}

	public String getHstype() {
		return this.getString("hstype");
	}

	/**
	 * 运营商
	 * 
	 * @param carrier
	 */
	public void setCarrier(String carrier) {
		this.put("carrier", carrier);
	}

	public String getCarrier() {
		return this.getString("carrier");
	}

	/**
	 * 网络访问类型
	 * 
	 * @param nettype
	 */
	public void setNettype(String nettype) {
		this.put("nettype", nettype);
	}

	public String getNettype() {
		return this.getString("nettype");
	}

}
