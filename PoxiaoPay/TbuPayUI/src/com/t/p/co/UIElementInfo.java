package com.t.p.co;

import android.graphics.Rect;

/**
 * 计费界面单个元素的信息
 * 
 * @author doubi
 * 
 */
public class UIElementInfo {
	private ELEMENTTYPE imageType;
	private Rect Rect;
	private String defaultName;// 正常状态下的图片
	private String specialName;// 特殊状态下的图片
	private boolean isClicked = false;// 是否处于被点击状态,区分按钮多态

	// 元素类型枚举:按钮，图片
	public enum ELEMENTTYPE {
		CONFIRMBUTTON, CANCELBUTTON, IMAGE
	}

	public ELEMENTTYPE getType() {
		return imageType;
	}

	public void setType(ELEMENTTYPE type) {
		this.imageType = type;
	}

	public String getDefaultName() {
		return defaultName;
	}

	public void setDefaultName(String defaultName) {
		this.defaultName = defaultName;
	}

	public String getSpecialName() {
		return specialName;
	}

	public void setSpecialName(String specialName) {
		this.specialName = specialName;
	}

	public Rect getRect() {
		return Rect;
	}

	public void setRect(Rect rect) {
		Rect = rect;
	}

	public boolean isClicked() {
		return isClicked;
	}

	public void setClicked(boolean isClicked) {
		this.isClicked = isClicked;
	}

}
