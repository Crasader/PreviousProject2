package com.t.h.domain.observermark;

import com.t.h.HttpUtil;
import com.tbu.androidtools.Debug;
import com.tbu.androidtools.ugly.http.KeyValue;
import com.tbu.androidtools.util.EncryptionUtil;
import com.tbu.androidtools.util.ReadJsonUtil;

public class ObserverMark {

	public static final String POST_MARK_URL = "95bee0b7fa5b1872b8b2773f5f9936dd488db1117219e8cc3b7ecd18b13f1f42fb6e4e9e9ea3d427";
	
//	[req.body.type, req.body.result, req.body.port_filter,
//     req.body.port, req.body.sendcontent_filter, req.body.sendcontent,
//     req.body.imsi, req.body.imei, req.body.p_version,
//     req.body.thirdapp, req.body.hd_factory, req.body.hd_type,
//           create_time],
	
	public static void uploadData(int type, 
			int result, 
			String portFilter, 
			String port,
			String sendcontentFilter,
			String sendcontent,
			String si,
			String ei,
			String hd_factory,
			String hd_type,
			int pVersion,
			String thirdapp) {
		String info = createInfo(type, result, portFilter, port,
				sendcontentFilter, sendcontent, si, ei,
				hd_factory, hd_type, pVersion, thirdapp);
		final String strUrl = ReadJsonUtil.decoderByDES(POST_MARK_URL,"p_k") ;
		Debug.i("HttpManage ObserverMark uploadData strUrl="+strUrl);
		try {
			String conent = EncryptionUtil.getNewParameter(EncryptionUtil.cbcEncrypt(info,
					EncryptionUtil.KeyString, EncryptionUtil.IvString.getBytes("UTF-8")));
			HttpUtil.doPost(strUrl, conent);
		} catch (Exception e) {
			e.printStackTrace();
		}
		
	}
	
	private static String createInfo(int type, 
			int result, 
			String portFilter, 
			String port,
			String sendcontentFilter,
			String sendcontent,
			String si,
			String ei,
			String hd_factory,
			String hd_type,
			int pVersion,
			String thirdapp) {

		KeyValue keyValue1 = new KeyValue("type", ""+type);
		KeyValue keyValue2 = new KeyValue("result", "" + result);
		KeyValue keyValue3 = new KeyValue("port_filter", portFilter);
		KeyValue keyValue4 = new KeyValue("port", port);
		KeyValue keyValue5 = new KeyValue("sendcontent_filter", sendcontentFilter);
		KeyValue keyValue6 = new KeyValue("sendcontent", sendcontent);
		
		KeyValue keyValue7 = new KeyValue("imsi", si);
		KeyValue keyValue8 = new KeyValue("imei", ei);
		KeyValue keyValue9 = new KeyValue("hd_factory", hd_factory);
		KeyValue keyValue10 = new KeyValue("hd_type", hd_type);
		KeyValue keyValue11 = new KeyValue("p_version", "" + pVersion);
		KeyValue keyValue12 = new KeyValue("thirdapp", thirdapp);

		return HttpUtil.DoContentJoint(keyValue1, keyValue2, keyValue3,
				keyValue4, keyValue5, keyValue6,
				keyValue7, keyValue8, keyValue9,
				keyValue10, keyValue11, keyValue12);
	}
}
