package com.d.event;

import java.util.Map;

/**
 * 事件返回结果
 * 
 * @author QZ
 *
 */
public class EventResult {

	private boolean hasBuy;
	private boolean payResult;
	private Map<Integer, Integer> reward;

	public boolean getPResult() {
		return payResult;
	}

	public void setPResult(boolean payResult) {
		this.payResult = payResult;
	}

	public Map<Integer, Integer> getReward() {
		return reward;
	}

	public void setReward(Map<Integer, Integer> reward) {
		this.reward = reward;
	}

	public boolean getHasBuy() {
		return hasBuy;
	}

	public void setHasBuy(boolean hasBuy) {
		this.hasBuy = hasBuy;
	}

}
