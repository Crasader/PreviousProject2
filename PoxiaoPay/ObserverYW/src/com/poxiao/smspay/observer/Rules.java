package com.poxiao.smspay.observer;

import com.tbu.androidtools.device.DeviceInfo;

public class Rules {

	public static boolean isAllowObserver() {
		Debug.i("DeviceInfo.sdk = " + DeviceInfo.getSdk());
		if (DeviceInfo.getSdk() < 19) {
			return true;
		}
		return false;
	}
}
