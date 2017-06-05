package com.tbu.androidtools.util.event;

import java.util.Map;

/**
 * tbu的事件分离机制与道具发放机制
 * 
 * @author QZ
 *
 */
public class TbuEvent {
	
	private int eventId;
	private int pId;
	private boolean eventState;
	/**
	 * 是否包含N秒保护（即如果在N秒内连续触发，则直接给免费）
	 */
	private boolean isProtected = false;
	
	private Map<Integer, Integer> reward;

	public int getEventId() {
		return eventId;
	}

	public void setEventId(int eventId) {
		this.eventId = eventId;
	}

	public int getPyId() {
		return pId;
	}

	public void setPId(int pId) {
		this.pId = pId;
	}

	public boolean getEventState() {
		return eventState;
	}

	public void setEventState(boolean state) {
		this.eventState = state;
	}

	public Map<Integer, Integer> getReward() {
		return reward;
	}

	public void setReward(Map<Integer, Integer> reward) {
		this.reward = reward;
	}

	public boolean isProtected() {
		return isProtected;
	}

	public void setProtected(boolean isProtected) {
		this.isProtected = isProtected;
	}
	
	
}
