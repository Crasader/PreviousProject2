package com.poxiao.smspay.plgin.mark.domain.paymark;

import java.text.SimpleDateFormat;
import java.util.Date;

import com.poxiao.smspay.SmsPay;
import com.poxiao.smspay.plgin.mark.domain.KeyValue;
import com.poxiao.smspay.plgin.mark.util.MarkUtil;
import com.tbu.androidtools.Debug;
import com.tbu.androidtools.app.AppInfo;
import com.tbu.androidtools.device.DeviceInfo;

public class PayMarkTable {
	
	//TODO:上传路径需要修改
	
	public final static String POST_URL = "4e488421b349ce70e3d3330e9c980d5296673f1de3e48756e9192295c4ad274fc6c41e8f69464aeb";

	/**
	 * 构造统计数据 - 统计支付会话行为
	 * 
	 * @param markInfo
	 * @return
	 */
	public static String createPayMarkInfo(PayMarkInfo markInfo) {
		KeyValue keyValue1 = new KeyValue("gameid", AppInfo.getTId());
		KeyValue keyValue2 = new KeyValue("enterid", AppInfo.getEntrance());
		KeyValue keyValue3 = new KeyValue("paymoney",
				String.valueOf(markInfo.payMoney));
		KeyValue keyValue5 = new KeyValue("accesstype",
				String.valueOf(DeviceInfo.getNewAccessType()));
		KeyValue keyValue6 = new KeyValue("hdfactory", DeviceInfo.getProduct());

		KeyValue keyValue7 = new KeyValue("hdtype", DeviceInfo.getModle());
		KeyValue keyValue8 = new KeyValue("imei", DeviceInfo.getei());
		KeyValue keyValue9 = new KeyValue("imsi", DeviceInfo.getsi());
		KeyValue keyValue10 = new KeyValue("payplginversion",
				SmsPay.PAY_VERSION);
		KeyValue keyValue11 = new KeyValue("platformversion",
				DeviceInfo.getPlatformVersion());
		KeyValue keyValue12 = new KeyValue("thirdapp",
				DeviceInfo.getSafeAppState()); ////第三方软件安装情况

		KeyValue keyValue20 = new KeyValue("orderid", markInfo.orderid);
		KeyValue keyValue21 = new KeyValue("toappresult",
				String.valueOf(markInfo.toAppResult));
		KeyValue keyValue22 = new KeyValue("timeout",
				String.valueOf(markInfo.timeOut == true ? 1 : 0)); // TODO :
		int sessionTime = (int) ((System.currentTimeMillis() - markInfo.createTime) / 1000);
		KeyValue keyValue23 = new KeyValue("sessiontime",
				String.valueOf(sessionTime));
		
		Date nowTime = new Date(markInfo.createTime);
		Debug.i("payMarkTable:nowTime = " + nowTime);
		SimpleDateFormat time = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss:SSS");
		KeyValue keyValue25 = new KeyValue("client_create_time",
				time.format(nowTime));
		KeyValue keyValue29 = new KeyValue("orderreqtime",
				String.valueOf(markInfo.orderreqtime));
		KeyValue keyValue30 = new KeyValue("smsprice", markInfo.smsprice); // 上传短信价格
		KeyValue keyValue31 = new KeyValue("sptype", markInfo.pay_platform); // 服务端下发的sp支付类型
		
		return MarkUtil.DoContentJoint(keyValue1, keyValue2, keyValue3,
				keyValue5, keyValue6, keyValue7, keyValue8,
				keyValue9, keyValue10, keyValue11, keyValue12, keyValue20,
				keyValue21, keyValue22, keyValue23, keyValue25,
				keyValue29, keyValue30,
				keyValue31);
	}
}
