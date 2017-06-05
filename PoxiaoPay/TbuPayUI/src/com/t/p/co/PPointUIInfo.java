package com.t.p.co;

import java.util.List;
/**
 * 单点的信息
 * 
 * @author doubi
 * 
 */
public class PPointUIInfo {


	private int pIndex;
	private String type;
	private List<UIElementInfo> elementInfos;// 单点包含多个元素


	public int getPIndex() {
		return pIndex;
	}

	public void setPIndex(int pIndex) {
		this.pIndex = pIndex;
	}

	public List<UIElementInfo> getElementInfos() {
		return elementInfos;
	}

	public void setElementInfos(List<UIElementInfo> elementInfos) {
		this.elementInfos = elementInfos;
	}

	public String getType() {
		return type;
	}

	public void setType(String type) {
		this.type = type;
	}
	
	
}
