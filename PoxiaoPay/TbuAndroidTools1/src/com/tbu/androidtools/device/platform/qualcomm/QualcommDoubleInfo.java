package com.tbu.androidtools.device.platform.qualcomm;

import java.lang.reflect.Method;
import android.content.Context;

/**
* @author molo.xiao@gmail.com 
* @version 创建时间：2015-5-6 上午11:07:44
*
 */
public class QualcommDoubleInfo {

	private boolean isQualcomm = true;
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

	public void setQualcommDoubleim(boolean isQualcomm) {
		this.isQualcomm = isQualcomm;
	}
	
	public boolean getQualcommDoubleim() {
		return this.isQualcomm;
	}
	
	public static QualcommDoubleInfo initQualcommDoubleim(Context mContext) {
		QualcommDoubleInfo qualcommDoubleInfo = new QualcommDoubleInfo();
		qualcommDoubleInfo.setimId_1(0);
		qualcommDoubleInfo.setimId_2(1);
		try {
			Class<?> cx = Class
					.forName("android.telephony.MSimTelephonyManager");
			Object obj = mContext.getSystemService("phone_msim");

			Method md = cx.getMethod("getDeviceId", int.class);
			Method ms = cx.getMethod("getSubscriberId", int.class);

			qualcommDoubleInfo.setei_1((String) md.invoke(obj,
					qualcommDoubleInfo.getimId_1()));
			qualcommDoubleInfo.setei_2((String) md.invoke(obj,
					qualcommDoubleInfo.getimId_2()));
			qualcommDoubleInfo.setsi_1((String) ms.invoke(obj,
					qualcommDoubleInfo.getimId_1()));
			qualcommDoubleInfo.setsi_2((String) ms.invoke(obj,
					qualcommDoubleInfo.getimId_2()));
		} catch (Exception e) {
			e.printStackTrace();
			qualcommDoubleInfo.setQualcommDoubleim(false);
			return qualcommDoubleInfo;
		}
		qualcommDoubleInfo.setQualcommDoubleim(true);
		return qualcommDoubleInfo;
	}
}
