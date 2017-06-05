package com.tbu.androidtools.device;

import com.tbu.androidtools.device.platform.mtk.MtkDoubleInfo;
import com.tbu.androidtools.device.platform.qualcomm.QualcommDoubleInfo;
import com.tbu.androidtools.util.StringUtils;

import android.content.Context;
import android.telephony.TelephonyManager;

/**
 * 获取手机的IMSI、IMEI、运营商信息。
 * 
 * @author molo.xiao@gmail.com
 * @version 创建时间：2015-5-6 上午10:41:35
 *
 */
public class PhoneInfoManager {

	public static final String DEFAULT_SI = "111111111111113";
	public static final String DEFAULT_IMSERIALNUMBER = "111111111111113";
	public static final String DEFAULT_EI = "222222222222222";

	public static final String ERROR_EI = "000000000000000";
	public static final String ERROR_SI = "000000000000000";

	/**
	 * @param tm
	 * @return
	 */
	public static String getimSerialNumber(TelephonyManager tm) {
		if (tm != null) {
			return tm.getSimSerialNumber();
		}
		return DEFAULT_IMSERIALNUMBER;
	}

	/**
	 * 
	 * @param tm
	 * @param context
	 * @return
	 */
	public static String getSI(TelephonyManager tm, Context context) {

		String si = tm.getSubscriberId();

		// 如果获取的si为空，则判断是否为高通平台机型。如果是，设置为第一个可用的si
		if (StringUtils.isBlank(si)) {
			QualcommDoubleInfo gaotongDoubleInfo = QualcommDoubleInfo
					.initQualcommDoubleim(context);
			if (gaotongDoubleInfo.getQualcommDoubleim()) {
				if (gaotongDoubleInfo.getsi_1() != null) {
					si = gaotongDoubleInfo.getsi_1();
				} else if (gaotongDoubleInfo.getsi_2() != null) {
					si = gaotongDoubleInfo.getsi_2();
				}
			}
		}

		// 如果获取的si为空，则继续判断是否为MTK平台机型。如果是，设置为第一个可用的si
		if (StringUtils.isBlank(si)) {
			MtkDoubleInfo mtkDoubleInfo = MtkDoubleInfo
					.initMtkDoubleim(context);
			if (mtkDoubleInfo.getMTKDoubleim()) {
				if (mtkDoubleInfo.getsi_1() != null) {
					si = mtkDoubleInfo.getsi_1();
				} else if (mtkDoubleInfo.getsi_2() != null) {
					si = mtkDoubleInfo.getsi_2();
				}
			}
		}

		return PhoneInfoManager.formatsi(si);
	}

	/**
	 * 格式化SI
	 * 
	 * @param si
	 * @return
	 */
	private static String formatsi(String si) {
		if (StringUtils.isBlank(si)) {
			// 如果仍然为空设置为默认值(此处的默认值主要是为了服务端统计看数据之用)
			si = DEFAULT_SI;
		} else if (si.length() < 15) {
			int len = si.length();
			int s = 15 - len;
			StringBuffer sb = new StringBuffer();
			for (int i = 0; i < s; i++) {
				sb.append("0");
			}
			si += sb.toString();
		} else if (si.length() > 15) {
			si = si.substring(0, 15);
		}
		return si;
	}

	/**
	 * 通过SI获取运营商信息 TODO : 各个头信息转化为定义项目而不是魔数
	 * 
	 * @param siInfo
	 * @return
	 */
	public static int getCarrierInfo(String siInfo) {
		int carrier = 0;
		String operPrefix = siInfo.substring(0, 5);
		if (operPrefix.equalsIgnoreCase("46000")
				|| operPrefix.equalsIgnoreCase("46002")
				|| operPrefix.equalsIgnoreCase("46007")) {
			// 因为移动网络编号46000下的IMSI已经用完，所以虚拟了一个46002编号，134/159号段使用了此编号 //中国移动
			carrier = 1;
		} else if (operPrefix.equalsIgnoreCase("46001")
				|| operPrefix.equalsIgnoreCase("46006")) {
			// 中国联通
			carrier = 2;
		} else if (operPrefix.equalsIgnoreCase("46003")
				|| operPrefix.equalsIgnoreCase("46005")
				|| operPrefix.equalsIgnoreCase("46011")) {
			// 中国电信
			carrier = 3;
		} else if (operPrefix.equalsIgnoreCase("46020")) {
			// 中国铁通
			carrier = 4;
		}

		return carrier;
	}

	/**
	 * 获取手机的EI号
	 * 
	 * @param tm
	 * @return
	 */
	public static String getEI(TelephonyManager tm) {
		String ei = tm.getDeviceId();
		return PhoneInfoManager.FormatImei(ei);
	}

	/**
	 * 格式化
	 * EI
	 * 
	 * @param ei
	 * @return
	 */
	private static String FormatImei(String ei) {
		if (StringUtils.isBlank(ei)) {
			ei = DEFAULT_EI;
		} else if (ei.length() < 15) {
			int len = ei.length();
			int s = 15 - len;
			StringBuffer sb = new StringBuffer();
			for (int i = 0; i < s; i++) {
				sb.append("0");
			}
			ei += sb.toString();
		} else if (ei.length() > 15) {
			ei = ei.substring(0, 15);
		}
		return ei;
	}
}
