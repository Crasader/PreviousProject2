package com.t.bfft;

import android.app.Activity;

import com.tbu.androidtools.Debug;
import com.tbu.androidtools.util.psspoint.PPoint;
import com.tbu.androidtools.util.psspoint.PPointUtil;

/**
 * 
 * @author molo.xiao@gmail.com
 * @version 创建时间：2015-5-6 上午11:09:31
 *
 */
public class OrderInfo {
	// 订单价格
	private int price;
	// 订单产品名称
	private String productName;
	// 订单信息描述
	private String orderDesc;
	// 订单产品编号
	private int pPointNum;
	// 订单序列号
	private String sequence;
	// 订单号
	private String orderId;
	
	private String phoneNum;
	
	private String proviceId;
	
	private int showUiId;

	private String linkId;
	

	public int getpPointNum() {
		return pPointNum;
	}

	public void setpPointNum(int pPointNum) {
		this.pPointNum = pPointNum;
	}

	public int getShowUiId() {
		return showUiId;
	}

	public void setShowUiId(int showUiId) {
		this.showUiId = showUiId;
	}

	public String getLinkId() {
		return linkId;
	}

	public void setLinkId(String linkId) {
		this.linkId = linkId;
	}

	public String getPhoneNum() {
		return phoneNum;
	}

	public void setPhoneNum(String phoneNum) {
		this.phoneNum = phoneNum;
	}

	public String getProviceId() {
		return proviceId;
	}

	public void setProviceId(String proviceId) {
		this.proviceId = proviceId;
	}

	public int getPrice() {
		return price;
	}

	public void setPrice(int price) {
		this.price = price;
	}

	public String getProductName() {
		return productName;
	}

	public void setProductName(String productName) {
		this.productName = productName;
	}

	public String getOrderDesc() {
		return orderDesc;
	}

	public void setOrderDesc(String orderDesc) {
		this.orderDesc = orderDesc;
	}

	public int getPPointNum() {
		return pPointNum;
	}

	public void setPPointNum(int pPointNum) {
		this.pPointNum = pPointNum;
	}

	public String getSequence() {
		return sequence;
	}

	public void setSequence(String sequence) {
		this.sequence = sequence;
	}

	public String getOrderId() {
		return orderId;
	}

	public void setOrderId(String orderId) {
		this.orderId = orderId;
	}

	public static OrderInfo getOrderInfo(Activity context, int pCode,
			String sequence, String orderId, String phone, String prov_id,
			int isShowId, String linkId) {
		OrderInfo orderInfo = new OrderInfo();
		PPoint pPoint = PPointUtil.getPPointById(context, pCode);
		if (pPoint != null) {
			orderInfo.setPrice(pPoint.getMoey());
			orderInfo.setProductName(pPoint.getName());
			orderInfo.setOrderDesc(pPoint.getDesc());
			orderInfo.setPhoneNum(phone);
			orderInfo.setProviceId(prov_id);
		} else {
			Debug.e("OrderInfo->Could not get P Point By PPointUtil");
		}
		orderInfo.setLinkId(linkId);
		orderInfo.setShowUiId(isShowId);
		orderInfo.setOrderId(orderId);
		orderInfo.setPPointNum(pCode);
		orderInfo.setSequence(sequence);
		return orderInfo;
	}
}
