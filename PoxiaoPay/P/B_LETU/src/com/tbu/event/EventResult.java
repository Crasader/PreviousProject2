package com.tbu.event;

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

	public boolean getPayResult() {
		return payResult;
	}

	public void setPayResult(boolean payResult) {
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
