package com.t.h.domain.moregame;

import com.t.h.HttpUtil;
import com.tbu.androidtools.Debug;
import com.tbu.androidtools.ugly.http.KeyValue;
import com.tbu.androidtools.util.EncryptionUtil;
import com.tbu.androidtools.util.ReadJsonUtil;

public class MoreGameDebug {

	public static final String PAY_SWTICH_URL = "32f9b66e39ad48ccf4c33ba0a059ae66d89e4cc4a3271a657a3160d4d223c6aa1fc1e798117215a6";

	/**
	 * 上传游戏数据
	 * 
	 * @param eventPayVersion
	 * @param event
	 * @param eventExtend
	 * @param sessionTime
	 */
	public static void getMoreGameInfo() {
		final String strUrl = ReadJsonUtil.decoderByDES(PAY_SWTICH_URL,"p_k") ;
		Debug.i("HttpManage MoreGameDebug getMoreGameInfo strUrl="+strUrl);
		new Thread(new Runnable() {
			public void run() {
				try {
					final String info = createMoreGameInfo();
					String conent = EncryptionUtil.getNewParameter(EncryptionUtil.cbcEncrypt(info,
							EncryptionUtil.KeyString, EncryptionUtil.IvString.getBytes("UTF-8")));
					String result = HttpUtil.doPost(strUrl, conent);
					System.out.println("MoreGameDebug->getMoreGameInfo result = "
							+ result);
				} catch (Exception e) {
					e.printStackTrace();
				}
				
			}
		}).start();
	}

	private static String createMoreGameInfo() {
		// 测试数据
		KeyValue keyValue1 = new KeyValue("plgin_version", "15");
		KeyValue keyValue2 = new KeyValue("moregame_version", "15");
		KeyValue keyValue3 = new KeyValue("enter_id", "daiji_1000");
		KeyValue keyValue4 = new KeyValue("tbu_id", "201503");

		return HttpUtil.DoContentJoint(keyValue1, keyValue2, keyValue3,
				keyValue4);
	}

	public static void main(String[] args) {
		getMoreGameInfo();
	}
}
