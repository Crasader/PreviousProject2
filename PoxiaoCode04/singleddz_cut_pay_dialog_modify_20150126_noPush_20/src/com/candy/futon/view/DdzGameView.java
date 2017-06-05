package com.candy.futon.view;

import android.content.Context;
import android.util.AttributeSet;
import android.view.MotionEvent;
import android.view.SurfaceHolder;

import com.andy.canvasgame.ui.GameView;
import com.candy.futon.GameEngine;

public class DdzGameView extends GameView {

	public DdzGameView(Context context) {
		super(context);
	}

	public DdzGameView(Context context, AttributeSet attrs) {
		super(context, attrs);
	}
	
	public DdzGameView(Context context, AttributeSet attrs, int defStyle) {
		super(context, attrs, defStyle);
	}
	
	@Override
	public void surfaceDestroyed(SurfaceHolder holder) {
		super.surfaceDestroyed(holder);
	}
	
	
	
	@Override
	public boolean onTouchEvent(MotionEvent event) {
		
		GameEngine.getInstance().updateLastActionTimeMilli();
		return super.onTouchEvent(event);
	}
}
