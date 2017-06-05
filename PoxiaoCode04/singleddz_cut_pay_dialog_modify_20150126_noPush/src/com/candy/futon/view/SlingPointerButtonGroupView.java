package com.candy.futon.view;

import java.util.List;

import android.graphics.Canvas;
import android.util.Log;
import android.view.MotionEvent;

import com.andy.canvasgame.ui.AView;
import com.andy.canvasgame.view.ButtonGroupView;
import com.candy.futon.domain.GameConfig;

public class SlingPointerButtonGroupView extends ButtonGroupView {

	private HandPokerView handPokerView;
	
	public SlingPointerButtonGroupView(List<AView> buttonList,
			int paddingBetweenButton, int layoutDirection) {
		super(buttonList, paddingBetweenButton, layoutDirection);
		// TODO Auto-generated constructor stub
	}
	
	@Override
	protected void doDraw(Canvas canvas) {
		Log.d("SlingPointerButtonGroupView","map2Rect:" + mMap2Rect);
		int start = getBounds().centerX();
		int end = (int) mMap2Rect.centerX();
		if(handPokerView != null){
			handPokerView.onSelectPoker(start, end);
		}
	}

	public void setHandPokerView(HandPokerView handPokerView) {
		this.handPokerView = handPokerView;
	}
	
	public void fakeSlingPokerView(){
		int start = getBounds().centerX();
		int end = (int) mMap2Rect.centerX();
		if(handPokerView != null){
			handPokerView.onFakeFling(start, end);
		}
	}
	
	@Override
	protected boolean doOnTouchEvent(MotionEvent event) {
		if(this.mCurrentAnimation != null && mCurrentAnimation.hasStarted()){
			onAnimationEnd();
		}
		return false;
	}

	public void onAnimationEnd() {
		this.setAlpha(0);
		this.invalidate();
		handPokerView.rePick();
		handPokerView.deSelectPoker();
		GameConfig.getInstance().showSlingCardAnimation = false;
	}
	
}
