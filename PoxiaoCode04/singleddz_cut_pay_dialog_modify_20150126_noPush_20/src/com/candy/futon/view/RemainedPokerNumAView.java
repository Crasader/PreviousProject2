package com.candy.futon.view;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Rect;

import com.andy.canvasgame.service.GameConstantsService;
import com.andy.canvasgame.util.BitmapSpliter;
import com.andy.canvasgame.util.MyGravity;
import com.poxiao.ddz.standalone.R;

public class RemainedPokerNumAView extends ImageAView {
	
	private ImageNumberAView imageNumberView;
	
	private int IMAGE_NUMBER_MARGIN_RIGHT = 3;
	
	private int number;
	

	
	private int MARGIN_TO_PLAYER_HEAD = 38;
	
	public RemainedPokerNumAView(Context context) {
		super(context, R.drawable.surplus_card_num_cover);
		IMAGE_NUMBER_MARGIN_RIGHT *= GameConstantsService.getInstance().getDensityScale();
		MARGIN_TO_PLAYER_HEAD *= GameConstantsService.getInstance().getDensityScale();
		imageNumberView = new ImageNumberAView(context, R.drawable.light_green_number, 10, BitmapSpliter.HORIZONTAL); 
		this.addChild(imageNumberView);
		this.mBitmapDrawable.setBounds(getBounds());
	}
	
	@Override
	public void updateBounds() {
		this.imageNumberView.setGravity(MyGravity.CENTER);
		this.imageNumberView.setMargin(0, 0, IMAGE_NUMBER_MARGIN_RIGHT, 0);
		this.mBitmapDrawable.setBounds(getBounds());
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
