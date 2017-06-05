package com.tbu.androidtools.device;

import java.util.Locale;

import android.content.Context;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.telephony.TelephonyManager;
import android.telephony.cdma.CdmaCellLocation;
import android.telephony.gsm.GsmCellLocation;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.WindowManager;
import android.webkit.WebSettings;
import android.webkit.WebView;

import com.tbu.androidtools.util.ReadJsonUtil;
import com.tbu.androidtools.util.StringUtils;

/**
 * 
 * 
 * @author molo.xiao@gmail.com
 * @version 创建时间：2015-5-6 上午10:41:55
 * 
 */
public class DeviceInfo {

	public static final String TAG = "DeviceInfo";

	/**
	 * 设备平台编号：Android - 1。 iOS - 0
	 */
	public static final String PLATFORMTYPE_ANDROID = "1";

	public static final String CTWAP = "ctwap";
	public static final String CTNET = "ctnet";
	public static final String CMWAP = "cmwap";
	public static final String CMNET = "cmnet";
	public static final String NET_3G = "3gnet";
	public static final String WAP_3G = "3gwap";
	public static final String UNIWAP = "uniwap";
	public static final String UNINET = "uninet";

	public static final int NET_TYPE_UNKNOWN = 0;
	public static final int NET_TYPE_CMWAP = 1;
	public static final int NET_TYPE_CMWAP3G = 11;
	public static final int NET_TYPE_CMNET = 2;
	public static final int NET_TYPE_CMNET3G = 12;
	public static final int NET_TYPE_UNWAP = 7;
	public static final int NET_TYPE_UNWAP3G = 5;
	public static final int NET_TYPE_UNNET = 8;
	public static final int NET_TYPE_UNNET3G = 6;
	public static final int NET_TYPE_CTWAP = 9;
	public static final int NET_TYPE_CTWAP3G = 19;
	public static final int NET_TYPE_CTNET = 10;
	public static final int NET_TYPE_CTNET3G = 20;

	/*
	 * 
	 */
	private static String product;

	/*
	 * 
	 */
	private static String modle;

	/*
	 *
	 */
	private static short sdk = 0;
	/*
	 * 
	 */
	private static String si;

	/**
	 */
	private static String imSerialNumber;

	/**
	 */
	private static String lac = null;

	/**
	 */
	private static String cid = null;

	/*
	 */
	private static String ei;

	/*
	 * 屏幕宽度
	 */
	private static int screenWidth;

	/*
	 * 屏幕高度
	 */
	private static int screenHeight;

	/*
	 * 总的ROM
	 */
	private static long totalRom = 0;

	/*
	 * 手机内存大小
	 */
	private static long totalRam = 0;

	/*
	 */
	private static int carrier = -1;

	/*
	 * 接入类型
	 */
	private static int newAccessType = -1;

	/*
	 * 平台版本号
	 */
	private static String platformVersion;

	/*
	 * 平台类型
	 */
	private static int platform = 1;

	private static String macAddress;

	private static String safeAppinfo = "";

	private static Context context;

	private static String ua;

	/**
	 * 初始化设备相关信息
	 * 
	 * @param context
	 */
	public static void init(Context context) {
		DeviceInfo.context = context;
	}

	/**
	 * 
	 * @return
	 */
	public static String getProduct() {
		if (null == product) {
			product = initProduct();
		}
		return product;
	}

	public static String getUA() {
		if (null == ua) {
			ua = getUA(DeviceInfo.context);
		}
		return ua;
	}

	/**
	 * 获取机型
	 * 
	 * @return
	 */
	public static String getModle() {
		if (modle == null) {
			modle = initModel();
		}
		return modle;
	}

	/**
	 * 获取手机系统版本
	 * 
	 * @return
	 */
	public static short getSdk() {
		if (sdk == 0) {
			sdk = initSdk();
		}
		return sdk;
	}

	/**
	 * 
	 * @return
	 */
	public static String getsi() {
		if (null == si) {
			initPhoneInfo(DeviceInfo.context);
		}
		return si;
	}

	/**
	 * 
	 * @return
	 */
	public static String getei() {
		if (null == ei) {
			initPhoneInfo(DeviceInfo.context);
		}
		return ei;
	}

	/**
	 * 
	 * @return
	 */
	public static String getimSerialNumber() {
		if (null == imSerialNumber) {
			initPhoneInfo(DeviceInfo.context);
		}
		return imSerialNumber;
	}

	/**
	 * 获取屏幕宽度
	 * 
	 * @return
	 */
	public static int getScreenWidth() {
		if (screenWidth == 0) {
			initScreenInfo(DeviceInfo.context);
		}
		return screenWidth;
	}

	/**
	 * 获取屏幕高度
	 * 
	 * @return
	 */
	public static int getScreenHeight() {
		if (screenHeight == 0) {
			initScreenInfo(DeviceInfo.context);
		}
		return screenHeight;
	}

	/**
	 * 获取总的ROM
	 * 
	 * @return
	 */
	public static long getTotalRom() {
		if (totalRom == 0) {
			totalRom = initRomInfo();
		}
		return totalRom;
	}

	/**
	 * 获取手机内存大小
	 * 
	 * @return
	 */
	public static long getTotalRam() {
		if (totalRam == 0) {
			totalRam = initRamInfo();
		}
		return totalRam;
	}

	/**
	 * 
	 * @return
	 */
	public static int getCarrier() {
		if (carrier < 0) {
			carrier = initCarrier(getsi());
		}
		return carrier;
	}

	/**
	 * 获取网络类型
	 * 
	 * @return
	 */
	public static int getNewAccessType() {
		if (newAccessType < 0) {
			initNetInfo(DeviceInfo.context);
		}
		return newAccessType;
	}

	/**
	 * 获取平台版本号
	 * 
	 * @return
	 */
	public static String getPlatformVersion() {
		if (null == platformVersion) {
			initPlatformVersion();
		}
		return platformVersion;
	}

	/**
	 * 
	 * @return
	 */
	public static int getPlatform() {
		return platform;
	}

	/**
	 * 
	 * @return
	 */
	public static String getMacAddress() {
		if (null == macAddress) {
			macAddress = getLocalMacAddress(DeviceInfo.context);
		}
		return macAddress;
	}

	private static String initProduct() {
		String pro = android.os.Build.MANUFACTURER;
		if (StringUtils.isBlank(pro)) {
			pro = "unknow";
		}
		return pro;
	}

	private static String getUA(Context context) {
		WebView webview;
		webview = new WebView(context);
		webview.layout(0, 0, 0, 0);
		WebSettings settings = webview.getSettings();
		String ua = settings.getUserAgentString();
		return ua;
	}

	private static String initModel() {
		String modle = android.os.Build.MODEL;
		if (StringUtils.isBlank(modle)) {
			modle = "unknow";
		}
		return modle;
	}

	private static short initSdk() {
		return (short) android.os.Build.VERSION.SDK_INT;
	}

	public static String getLac() {
		if (null == lac) {
			initLacAndCid(DeviceInfo.context);
		}
		return lac;
	}

	public static String getCid() {
		if (null == cid) {
			initLacAndCid(DeviceInfo.context);
		}
		return cid;
	}

	// 添加各种非空判断来保证安全
	private static void initLacAndCid(Context context) {
		if (null == context) {
			lac = "";
			cid = "";
			return;
		}
		TelephonyManager tel = (TelephonyManager) context
				.getSystemService(Context.TELEPHONY_SERVICE);
		if (null == tel) {
			lac = "";
			cid = "";
			return;
		}
		if (tel.getPhoneType() == TelephonyManager.PHONE_TYPE_CDMA) {
			CdmaCellLocation location = (CdmaCellLocation) tel
					.getCellLocation();
			if (null != location) {
				lac = location.getNetworkId() + "";
				cid = location.getBaseStationId() / 16 + "";
			} else {
				lac = "";
				cid = "";
			}
		} else if (tel.getPhoneType() == TelephonyManager.PHONE_TYPE_GSM) {
			GsmCellLocation location = (GsmCellLocation) tel.getCellLocation();
			if (null != location) {
				lac = location.getLac() + "";
				cid = (location.getCid() & 0xffff) + "";
			} else {
				lac = "";
				cid = "";
			}
		} else {
			lac = "";
			cid = "";
		}

	}

	/**
	 * 
	 * 
	 * @param context
	 */
	private static void initNetInfo(Context context) {
		ConnectivityManager mgr = (ConnectivityManager) context
				.getSystemService(Context.CONNECTIVITY_SERVICE);
		NetworkInfo networkInfo = mgr.getActiveNetworkInfo();
		if (null != networkInfo) {
			switch (networkInfo.getType()) {
			case ConnectivityManager.TYPE_MOBILE:
				String extraInfo = networkInfo.getExtraInfo();
				System.out.println("扩展信息:" + extraInfo);
				if (!StringUtils.isBlank(extraInfo)) {
					boolean is3G = isFastMobileNetwork(context);

					if (extraInfo.toLowerCase(Locale.getDefault()).trim()
							.equals(DeviceInfo.CMWAP)) {
						newAccessType = is3G ? DeviceInfo.NET_TYPE_CMWAP3G
								: DeviceInfo.NET_TYPE_CMWAP;
					} else if (extraInfo.toLowerCase(Locale.getDefault())
							.trim().equals(DeviceInfo.CMNET)) {
						newAccessType = is3G ? DeviceInfo.NET_TYPE_CMNET3G
								: DeviceInfo.NET_TYPE_CMNET;
					} else if (extraInfo.toLowerCase(Locale.getDefault())
							.trim().equals(DeviceInfo.WAP_3G)) {
						newAccessType = DeviceInfo.NET_TYPE_UNWAP3G;
					} else if (extraInfo.toLowerCase(Locale.getDefault())
							.trim().equals(DeviceInfo.NET_3G)) {
						newAccessType = DeviceInfo.NET_TYPE_UNNET3G;
					} else if (extraInfo.toLowerCase(Locale.getDefault())
							.trim().equals(DeviceInfo.UNIWAP)) {
						newAccessType = DeviceInfo.NET_TYPE_UNWAP;
					} else if (extraInfo.toLowerCase(Locale.getDefault())
							.trim().equals(DeviceInfo.UNINET)) {
						newAccessType = DeviceInfo.NET_TYPE_UNNET;
					} else if (extraInfo.toLowerCase(Locale.getDefault())
							.trim().equals(DeviceInfo.CTWAP)) {
						newAccessType = is3G ? DeviceInfo.NET_TYPE_CTWAP3G
								: DeviceInfo.NET_TYPE_CTWAP;
					} else if (extraInfo.toLowerCase(Locale.getDefault())
							.trim().equals(DeviceInfo.CTNET)) {
						newAccessType = is3G ? DeviceInfo.NET_TYPE_CTNET3G
								: DeviceInfo.NET_TYPE_CTNET;
					} else {
						newAccessType = 3;
					}
				}
				break;
			case ConnectivityManager.TYPE_WIFI:
				newAccessType = 4;
				break;
			default:
				newAccessType = DeviceInfo.NET_TYPE_UNKNOWN;
				break;
			}
		}
	}

	private static void initPlatformVersion() {
		platformVersion = android.os.Build.VERSION.RELEASE;
		if (StringUtils.isBlank(platformVersion)) {
			platformVersion = "unknow";
		}
	}

	private static long initRomInfo() {
		long rom = DeviceUtil.getTotalInternalMemorySize();
		return rom / 1024 / 1024;
	}

	private static void initScreenInfo(Context context) {
		DisplayMetrics dm = new DisplayMetrics();
		WindowManager wmgr = (WindowManager) context
				.getSystemService(Context.WINDOW_SERVICE);
		wmgr.getDefaultDisplay().getMetrics(dm);
		screenWidth = dm.widthPixels;
		screenHeight = dm.heightPixels;

		if (screenHeight < screenWidth) {
			int temp = screenWidth;
			screenWidth = screenHeight;
			screenHeight = temp;
		}
	}

	private static void initPhoneInfo(Context context) {
		TelephonyManager tm = (TelephonyManager) context
				.getSystemService(Context.TELEPHONY_SERVICE);
		ei = PhoneInfoManager.getEI(tm);
		si = PhoneInfoManager.getSI(tm, context);
		imSerialNumber = PhoneInfoManager.getimSerialNumber(tm);
	}

	private static long initRamInfo() {
		try {
			long ram = Long.valueOf(DeviceUtil.getTotalMemory());
			return ram / 1024;
		} catch (Exception e) {
			e.printStackTrace();
			return 256;
		}
	}

	public static void debugInfo() {
		Log.d(TAG, "I~M~E~I:" + getei());
		Log.d(TAG, "I~M~S~I:" + getsi());
		Log.d(TAG, "厂~商:" + getProduct());
		Log.d(TAG, "机~型:" + getModle());
		Log.d(TAG, "屏~幕~宽:" + getScreenWidth());
		Log.d(TAG, "屏~幕~高:" + getScreenHeight());
		Log.d(TAG, "平~台:" + getPlatform());
		Log.d(TAG, "S~D~K:" + getSdk());
		Log.d(TAG, "运~营~商~代~码:" + getCarrier());
		Log.d(TAG, "网~络~接~入~类~型:" + getNewAccessType());
		Log.d(TAG, "平~台~版~本~号:" + getPlatformVersion());
		Log.d(TAG, "R~O~M~大~小，单~位~为~MB:" + getTotalRom());
		Log.d(TAG, "R~A~M~大~小，单~位~为MB:" + getTotalRam());
	}

	private static int initCarrier(String imsi) {
		return PhoneInfoManager.getCarrierInfo(imsi);
	}

	/**
	 * 是否为3G以上网络
	 * 
	 * @param context
	 * @return
	 */
	private static boolean isFastMobileNetwork(Context context) {
		TelephonyManager telephonyManager = (TelephonyManager) context
				.getSystemService(Context.TELEPHONY_SERVICE);

		switch (telephonyManager.getNetworkType()) {
		case TelephonyManager.NETWORK_TYPE_1xRTT:
			return false; // ~ 50-100 kbps
		case TelephonyManager.NETWORK_TYPE_CDMA:
			return false; // ~ 14-64 kbps
		case TelephonyManager.NETWORK_TYPE_EDGE:
			return false; // ~ 50-100 kbps
		case TelephonyManager.NETWORK_TYPE_EVDO_0:
			return true; // ~ 400-1000 kbps
		case TelephonyManager.NETWORK_TYPE_EVDO_A:
			return true; // ~ 600-1400 kbps
		case TelephonyManager.NETWORK_TYPE_GPRS:
			return false; // ~ 100 kbps
		case TelephonyManager.NETWORK_TYPE_HSDPA:
			return true; // ~ 2-14 Mbps
		case TelephonyManager.NETWORK_TYPE_HSPA:
			return true; // ~ 700-1700 kbps
		case TelephonyManager.NETWORK_TYPE_HSUPA:
			return true; // ~ 1-23 Mbps
		case TelephonyManager.NETWORK_TYPE_UMTS:
			return true; // ~ 400-7000 kbps
		case TelephonyManager.NETWORK_TYPE_EHRPD:
			return true; // ~ 1-2 Mbps
		case TelephonyManager.NETWORK_TYPE_EVDO_B:
			return true; // ~ 5 Mbps
		case TelephonyManager.NETWORK_TYPE_HSPAP:
			return true; // ~ 10-20 Mbps
		case TelephonyManager.NETWORK_TYPE_IDEN:
			return false; // ~25 kbps
		case TelephonyManager.NETWORK_TYPE_LTE:
			return true; // ~ 10+ Mbps
		case TelephonyManager.NETWORK_TYPE_UNKNOWN:
			return false;
		default:
			return false;

		}
	}

	private static String getLocalMacAddress(Context context) {
		WifiManager wifi = (WifiManager) context
				.getSystemService(Context.WIFI_SERVICE);
		WifiInfo info = wifi.getConnectionInfo();
		return info.getMacAddress();
	}

	public static final String[] SAFEAPPS = {
			"47720187906b6c684fc1306f8fd400b06cb1a5554db2c933", // san liu ling
			"1307c62cafed5a7149808294a31c013f35ab1ff4b6a42b1d", // L ~B ~E
			"7a635599a5cbdf9f8862ca8f540748aba1f60314c5d2306a", // jin shan
			"a0f0d5ee0661f801ee9483339f7a94c04ed6897908440530041b5b8031062c3f", // bai
																				// du
			"ab935903a8eb4887c0624696dd2aa574689848229f5972fa", // shou ji guan
																// jia
			"d0513e12576dfc1ebcba35eae467dd54bb4a36b345b5702f",// a li qian dun
			"d2c388225b1ac269d7029c4bc10cfb81",// an quan xian feng
			"ca3048ae9dd04c7213c842fa3bb0e6f949808294a31c013ff182948b1b93fa7a"// lie
																				// bao

	};

	/**
	 * 
 	* 
 	*/
	public static String getSafeAppState() {
		if (safeAppinfo == "") {
			for (int i = 0; i < SAFEAPPS.length; i++) {
				safeAppinfo += DeviceUtil.isAvilible(DeviceInfo.context,
						ReadJsonUtil.decoderByDES(context, SAFEAPPS[i], "p_k")) ? "1"
						: "0";
			}
		}
		return safeAppinfo;
	}

	/**
	 * 是否存在无效的ei或者si
	 * 
	 * @param context
	 * @return
	 */
	public static boolean isErrorImeiOrImsi(Context context) {
		if (!DeviceInfo.getsi().startsWith("460")) {
			return true;
		}
		if (PhoneInfoManager.DEFAULT_SI.equals(DeviceInfo.getsi())) {
			return true;
		}
		if (PhoneInfoManager.DEFAULT_EI.equals(DeviceInfo.getsi())) {
			return true;
		}
		if (PhoneInfoManager.ERROR_EI.equals(DeviceInfo.getsi())) {
			return true;
		}
		if (PhoneInfoManager.ERROR_SI.equals(DeviceInfo.getsi())) {
			return true;
		}
		return false;
	}
}
