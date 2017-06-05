package com.candy.futon.view;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Rect;

import com.andy.canvasgame.service.GameConstantsService;
import com.andy.canvasgame.ui.AView;
import com.andy.canvasgame.util.AViewUtil;
import com.andy.canvasgame.util.BitmapSpliter;
import com.andy.canvasgame.util.MyGravity;
import com.poxiao.ddz.standalone.R;

public class ClockAView extends ImageAView {
	
	private ImageNumberAView imageNumberView;
	
	private int IMAGE_NUMBER_MARGIN_RIGHT = 3;
	
	private int number;
	
	private boolean isLeft;
	
	private int MARGIN_TO_PLAYER_HEAD = 8;
	
	public ClockAView(Context context, PlayerView playerHeadView, AView parent, boolean isLeft) {
		
		super(context, R.drawable.clock);
		this.isLeft = isLeft;
		IMAGE_NUMBER_MARGIN_RIGHT *= GameConstantsService.getInstance().getDensityScale();
		MARGIN_TO_PLAYER_HEAD *= GameConstantsService.getInstance().getDensityScale();
		imageNumberView = new ImageNumberAView(context, R.drawable.light_dark_number, 10, BitmapSpliter.HORIZONTAL); 
		this.addChild(imageNumberView);
		if(this.isLeft){
			int top = playerHeadView.getBounds().top + (playerHeadView.getBounds().height() - this.getBounds().height())/2;
			this.setMargin(playerHeadView.getPlayerBgBounds().right, top, 0, 0);
			this.setMargin(MARGIN_TO_PLAYER_HEAD, 0, 0, 0);
		}else{
			int top = playerHeadView.getBounds().top + (playerHeadView.getBounds().height() - this.getBounds().height())/2;
			this.setParent(parent);
			this.setGravity(playerHeadView.getGravity());
			this.setMargin(0, top, parent.getBounds().right - playerHeadView.getPlayerBgBounds().left, 0);
			this.setMargin(0, 0, MARGIN_TO_PLAYER_HEAD, 0);
		}
		
		this.mBitmapDrawable.setBounds(getBounds());
	}
	
	@Override
	public void updateBounds() {
		this.imageNumberView.setGravity(MyGravity.CENTER);
		this.imageNumberView.setMargin(0, 0, IMAGE_NUMBER_MARGIN_RIGHT, 0);
	}
	
	public void setNumber(int number) {
		this.number = number;
		this.imageNumberView.setNumber(number);
		updateBounds();
	}
	
	@Override
	public void setGravity(int gravity) {
		super.setGravity(gravity);
		updateBounds();
	}

	@Override
	public void setMargin(int left, int top, int right, int bottom) {
		super.setMargin(left, top, right, bottom);
		updateBounds();
	}


	@Override
	protected void doDraw(Canvas canvas) {
		if(number == 0){
			return;
		}
		super.doDraw(canvas);
	}
	
	@Override
	protected void drawChild(Canvas canvas, Rect rect) {
		if(number == 0){
			return;
		}
		super.drawChild(canvas, rect);
	}
	

}
