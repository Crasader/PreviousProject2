package com.tbu.androidtools.util.psspoint;

import java.util.Map;

/**
 * 计费点的一般抽象
* @author molo.xiao@gmail.com 
* @version 创建时间：2015-5-12 下午1:51:47
*
 */
public class PPoint {

	private int type;
	private String desc;
	private int moey;
	private String name;
	private Map<Integer, Integer> reward;

	public int getType() {
		return type;
	}

	public void setType(int type) {
		this.type = type;
	}

	public String getDesc() {
		return desc;
	}

	public void setDesc(String desc) {
		this.desc = desc;
	}

	public int getMoey() {
		return moey;
	}

	public void setMoey(int moey) {
		this.moey = moey;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public Map<Integer, Integer> getReward() {
		return reward;
	}

	public void setReward(Map<Integer, Integer> reward) {
		this.reward = reward;
	}

}
