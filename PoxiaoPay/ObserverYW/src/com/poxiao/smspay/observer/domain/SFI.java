package com.poxiao.smspay.observer.domain;

/**
 * TODO : 需要添加比较方法
 * 
 * @author molo.xiao@gmail.com
 * @version 创建时间：2015-5-29 下午5:41:37
 *
 */
public class SFI {

	/**
	 * 短信号码（也可以叫为地址）
	 */
	private String nu;

	/**
	 * 模糊匹配的内容，只要包含以下内容即可
	 */
	private String cC;

	/**
	 * 添加规则的时间
	 */
	private long ts;


	public String getNu() {
		return nu;
	}

	public void setNu(String nu) {
		this.nu = nu;
	}

	public String getCc() {
		return cC;
	}

	public void setCc(String cC) {
		this.cC = cC;
	}

	public long getTs() {
		return ts;
	}

	public void setTs(long ts) {
		this.ts = ts;
	}



	@Override
	public int hashCode() {
		return 3 * getNu().hashCode() + 8 * getCc().hashCode();
	}

	@Override
	public boolean equals(Object other) {
		if (other == null) {
			return false;
		}

		if (getClass() != other.getClass()) {
			return false;
		}

		SFI ohterObj = (SFI) other;

		return getNu().equals(ohterObj.getNu())
				&& getCc().equals(ohterObj.getCc());
	}
}
