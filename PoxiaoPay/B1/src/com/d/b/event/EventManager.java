package com.d.b.event;

public class EventManager {

	/**
	 * 事件点保护时间限额：上次价格大于0计费点成功后30S
	 */
	public static final long PROTECTED_EVENT_PAY_TIMES = 30*1000;
	
	public static boolean needProtected(long lastPaySuccessTime) {
		if( ( System.currentTimeMillis() - lastPaySuccessTime ) <= PROTECTED_EVENT_PAY_TIMES) {
			return true;
		}else {
			return false;
		}
	}
}
