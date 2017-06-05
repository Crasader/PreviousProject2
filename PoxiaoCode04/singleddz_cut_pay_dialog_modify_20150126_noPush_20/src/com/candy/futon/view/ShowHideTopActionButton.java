package com.candy.futon.view;

import com.andy.canvasgame.ui.OnClickListener;

import android.content.Context;
import android.graphics.Rect;
import android.view.MotionEvent;

public class ShowHideTopActionButton extends PicButtonView {

	private boolean show = true;
	
	private Rect detectRect;
	
	public ShowHideTopActionButton(Context context, int bgDrawableId,
			int textDrawableId, OnClickListener onClickListener) {
		super(context, bgDrawableId, textDrawableId, onClickListener);
		updateDetectRect();
	}

	@Override
	public void setMargin(int left, int top, int right, int bottom) {

		super.setMargin(left, top, right, bottom);
		this.updateDetectRect();
	}
	
	@Override
	public void setGravity(int gravity) {
	
		super.setGravity(gravity);
		this.updateDetectRect();
	}
	
	@Override
	public void updateBounds() {
		super.updateBounds();
		updateDetectRect();
	}
	
	private void updateDetectRect() {
		if(detectRect == null){
			detectRect = new Rect();
		}
		int left = getBounds().left - getBounds().width();
		int top = getBounds().top - getBounds().height();
		detectRect.set(left, top, left+ getBounds().width() * 3, top + getBounds().height() * 3);
	}
	
	public boolean isShow(){
		return show;
	}
	
	@Override
	protected boolean isOnclick(MotionEvent event) {
		boolean result =  false;
		boolean contained = this.detectRect.contains((int)event.getX(),(int)event.getY());
		if(event.getAction() == MotionEvent.ACTION_DOWN && contained){
			mPressed = true;
		}else if(event.getAction() == MotionEvent.ACTION_MOVE && !contained){
			mPressed = false;
		}else if(event.getAction() == MotionEvent.ACTION_UP && contained && mPressed){
			result = true;
		}
		
		if(result){
			if(show){
				show = false;
			}else{
				show = true;
			}
		}
		return result;
	}

}
