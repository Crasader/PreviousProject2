package com.t.bfft;

import java.util.Map;

public class OrderResultInfo {
	
	// resultCode的定义
	public static final int P_SUCCESS = 0;// 成功
	public static final int P_FAIL = 1;// 失败
	public static final int P_NOT_FIND = -2;// 找不到计费点
	public static final int P_CANCEL = -3;// 取消
	public static final int CLICK_CONFIRM = 3;// 点击确定
	public static final int CLICK_CANCEL = 4;// 点击取消
	public static final int PAY_FAIL_END = 2;// 支付失败且结束本次计费
	public static final int PAY_CANCEL_END=-4;// 支付取消且结束本次计费
	
	// errorMsg的定义(如有需要可继续补充)
	public static final String ERROR_CODE_MONTHLY_PAYMENT = "999";// 包月计费点已经购买

	// 订单价格
	private int price;
	// 订单支付结果 0 支付成功 ,1支付失败,-3取消支付,-2获取计费点失败,3点击确定,4点击取消
	private int resultCode;
	// 失败错误码
	private String errorCode;
	// 失败错误信息
	private String errorMsg;
	// 订单序列号
	private String sequence;
	// 计费点编号
	private int pPoint;
	// 计费点奖励
	private Map<Integer, Integer> reward;

	public int getPri() {
		return price;
	}

	public void setPri(int pri) {
		this.price = pri;
	}

	public int getResultCode() {
		return resultCode;
	}

	public void setResultCode(int resultCode) {
		this.resultCode = resultCode;
	}

	public String getErrorCode() {
		return errorCode;
	}

	public void setErrorCode(String errorCode) {
		this.errorCode = errorCode;
	}

	public String getErrorMsg() {
		return errorMsg;
	}

	public void setErrorMsg(String errorMsg) {
		this.errorMsg = errorMsg;
	}

	public String getSequence() {
		return sequence;
	}

	public void setSequence(String sequence) {
		this.sequence = sequence;
	}

	public int getPPoint() {
		return pPoint;
	}

	public void setPPoint(int pPoint) {
		this.pPoint = pPoint;
	}

	public Map<Integer, Integer> getReward() {
		return reward;
	}

	public void setReward(Map<Integer, Integer> reward) {
		this.reward = reward;
	}

}
