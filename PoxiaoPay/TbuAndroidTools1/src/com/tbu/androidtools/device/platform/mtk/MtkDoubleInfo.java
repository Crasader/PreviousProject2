package com.tbu.androidtools.device.platform.mtk;

import java.lang.reflect.Field;
import java.lang.reflect.Method;
import android.content.Context;
import android.telephony.TelephonyManager;

/**
 * 
* @author molo.xiao@gmail.com 
* @version 创建时间：2015-5-6 上午11:07:51
*
 */
public class MtkDoubleInfo {
	private boolean isMTK = true;
	private int imId_1;
	private int imId_2;
	
	private String si_1;
	private String si_2;
	private String ei_1;
	private String ei_2;
	
	public void setimId_1(int imId_1) {
		this.imId_1 = imId_1;
	}
	
	public void setimId_2(int imId_2) {
		this.imId_2 = imId_2;
	}
	
	public int getimId_1() {
		return this.imId_1;
	}
	
	public int getimId_2() {
		return this.imId_2;
	}

	public void setei_1(String ei_1) {
		this.ei_1 = ei_1;
	}

	public void setei_2(String ei_2) {
		this.ei_2 = ei_2;
	}

	public void setsi_1(String si_1) {
		this.si_1 = si_1;
	}

	public void setsi_2(String si_2) {
		this.si_2 = si_2;
	}
	
	public String getei_1() {
		return this.ei_1;
	}

	public String getei_2() {
		return this.ei_2;
	}

	public String getsi_1() {
		return this.si_1;
	}

	public String getsi_2() {
		return this.si_2;
	}

	public void setMTKDoubleim(boolean isMTK) {
		this.isMTK = isMTK;
	}
	
	public boolean getMTKDoubleim() {
		return this.isMTK;
	}
	
	public static MtkDoubleInfo initMtkDoubleim(Context mContext) {
		MtkDoubleInfo mtkDoubleInfo = new MtkDoubleInfo();
		try {
			TelephonyManager tm = (TelephonyManager) mContext
					.getSystemService(Context.TELEPHONY_SERVICE);
			Class<?> c = Class.forName("com.android.internal.telephony.Phone");
			Field fields1 = c.getField("GEMINI_SIM_1");
			fields1.setAccessible(true);
			mtkDoubleInfo.setimId_1((Integer) fields1.get(null));
			Field fields2 = c.getField("GEMINI_SIM_2");
			fields2.setAccessible(true);
			mtkDoubleInfo.setimId_2((Integer) fields2.get(null));
			Method m = TelephonyManager.class.getDeclaredMethod(
					"getSubscriberIdGemini", int.class);
			mtkDoubleInfo.setsi_1((String) m.invoke(tm,
					mtkDoubleInfo.getimId_1()));
			mtkDoubleInfo.setsi_2((String) m.invoke(tm,
					mtkDoubleInfo.getimId_2()));

			Method m1 = TelephonyManager.class.getDeclaredMethod(
					"getDeviceIdGemini", int.class);
			mtkDoubleInfo.setei_1((String) m1.invoke(tm,
					mtkDoubleInfo.getimId_1()));
			mtkDoubleInfo.setei_2((String) m1.invoke(tm,
					mtkDoubleInfo.getimId_2()));
		} catch (Exception e) {
			mtkDoubleInfo.setMTKDoubleim(false);
			return mtkDoubleInfo;
		}
		mtkDoubleInfo.setMTKDoubleim(true);
		return mtkDoubleInfo;
	}
}
