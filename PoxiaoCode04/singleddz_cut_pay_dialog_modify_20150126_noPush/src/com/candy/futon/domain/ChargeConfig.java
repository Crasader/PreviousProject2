package com.candy.futon.domain;

public class ChargeConfig {

	/**
	 * 需要支付的费用
	 */
	public int mPay;
	
	/**
	 * 能获取到的银币数
	 */
	public int mOriginalCoin;
	
	/**
	 * 加送的银币数
	 */
	public int mExtraCoin;

	public final static ChargeConfig getDefaultChargeConfig(){
		return CHARGE_CONFIGS[CHARGE_CONFIGS.length - 1];
	}
	
	public final static ChargeConfig[] CHARGE_CONFIGS= new ChargeConfig[]{
		new ChargeConfig(8,32000,8000),
		new ChargeConfig(6,24000,6000),
		new ChargeConfig(4,16000,4000),
		new ChargeConfig(2,8000,2000)
	};
	
	public ChargeConfig(int pay, int coin, int extraCoin){
		this.mPay = pay;
		this.mOriginalCoin = coin;
		this.mExtraCoin = extraCoin;
	}
	
}
