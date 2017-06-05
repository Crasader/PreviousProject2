package com.poxiao.smspay.plgin.mark;

import java.util.Timer;
import java.util.TimerTask;

import com.poxiao.smspay.plgin.mark.domain.paymark.PayMarkInfo;
import com.poxiao.smspay.plgin.mark.domain.paymark.PayMarkTable;
import com.poxiao.smspay.plgin.mark.domain.push.PushInfo;
import com.poxiao.smspay.plgin.mark.domain.push.PushTable;
import com.poxiao.smspay.plgin.mark.util.HttpUtil;
import com.tbu.androidtools.Debug;
import com.tbu.androidtools.util.EncryptionUtil;
import com.tbu.androidtools.util.ReadJsonUtil;

public class Mark {

	public static final String VERSION = "4";

	/**
	 * 统计一次自有支付会话任务
	 * 
	 * @param markInfo
	 */
	public static void doPostPayMarkTask(final PayMarkInfo markInfo) {
		final String strUrl = ReadJsonUtil.decoderByDES(PayMarkTable.POST_URL, "poxiao_key");
		Debug.i("TbuSmsPa Mark doPostPayMarkTask strUrl=" + strUrl);
		new Timer().schedule(new TimerTask() {
			@Override
			public void run() {
				try {
					String result = PayMarkTable.createPayMarkInfo(markInfo);
					String content = EncryptionUtil.getNewParameter(EncryptionUtil.cbcEncrypt(result,
							EncryptionUtil.KeyString, EncryptionUtil.IvString.getBytes("UTF-8")));
					HttpUtil.DoPost(strUrl, content);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		}, 0);
	}

	/**
	 * 统计一次Push任务行为
	 * 
	 * @param pushInfo
	 */
	public static void doPostPushMarkTask(final PushInfo pushInfo) {
		final String strUrl = ReadJsonUtil.decoderByDES(PushTable.POST_URL, "poxiao_key");
		Debug.i("TbuSmsPa Mark doPostPushMarkTask strUrl=" + strUrl);
		new Timer().schedule(new TimerTask() {
			@Override
			public void run() {
				try {
					String result = PushTable.createPayMarkInfo(pushInfo);
					String content = EncryptionUtil.getNewParameter(EncryptionUtil.cbcEncrypt(result,
							EncryptionUtil.KeyString, EncryptionUtil.IvString.getBytes("UTF-8")));
					HttpUtil.DoPost(strUrl, content);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		}, 0);
	}
}
