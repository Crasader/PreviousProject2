package com.poxiao.smspay.plgin.mark.domain.paymark;

public class PayMarkInfo {
	public String gameId;
	public String gameVersion;
	public int payMoney;
	public int payPoint;
	public String orderid;
	public boolean timeOut;
	public long createTime;
	public int toAppResult;		//返回应用的支付结果
	public int orderreqtime;	 //请求计费代码用时
	public int ordertime;		 //订单下发超时时间
	public String pay_platform;	 //接入sp支付类型
	public String smsprice;	     //接入sp支付价格
}
