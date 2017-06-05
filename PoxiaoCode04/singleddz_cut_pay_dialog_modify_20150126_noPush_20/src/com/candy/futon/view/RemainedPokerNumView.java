package com.candy.futon.view;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.Rect;
import android.graphics.drawable.BitmapDrawable;
import android.view.MotionEvent;

import com.andy.canvasgame.service.GameConstantsService;
import com.andy.canvasgame.ui.AView;
import com.andy.canvasgame.util.MyGravity;
import com.poxiao.ddz.standalone.R;

public class RemainedPokerNumView extends AView{

	private int MARGIN_TO_PLAYER_HEAD = 38;
	
	private int FONT_SIZE = 20;
	
	private BitmapDrawable mPokerCoverDrawable;

	private static Paint paint;

	private Rect textRect = new Rect();
	
	private String pokerNumText = null;
	
	private BitmapDrawable mSurplusDrawable;
	
	private Paint getPaint(){
		if(paint == null){
			paint = new Paint();
			paint.setTextAlign(Paint.Align.LEFT);
			paint.setAntiAlias(true);
			paint.setFakeBoldText(true);
			paint.setColor(0xFFFFFFFF);
			paint.setTextSize(FONT_SIZE * GameConstantsService.getInstance().getDensityScale());
		}
		return paint;
	}
	
	public RemainedPokerNumView(Context context, AView playerHeadView){
		MARGIN_TO_PLAYER_HEAD *= GameConstantsService.getInstance().getDensityScale();
		FONT_SIZE *= GameConstantsService.getInstance().getDensityScale();
		mPokerCoverDrawable = new BitmapDrawable(context.getResources(), GameUIResource.getInstance().loadBitMap(context.getResources(), R.drawable.surplus_card_num_cover));
		mSurplusDrawable = new BitmapDrawable(context.getResources(), GameUIResource.getInstance().loadBitMap(context.getResources(), R.drawable.surplus_card_num_bg));
		int left = playerHeadView.getBounds().centerX() - mSurplusDrawable.getIntrinsicWidth()/2;
		int top = playerHeadView.getBounds().bottom + MARGIN_TO_PLAYER_HEAD;
		this.setBounds(new Rect(left, top, left + mSurplusDrawable.getIntrinsicWidth(), top + mSurplusDrawable.getIntrinsicHeight()));
		Rect rect = new Rect();
		MyGravity.apply(MyGravity.CENTER, mPokerCoverDrawable.getIntrinsicWidth(), mPokerCoverDrawable.getIntrinsicHeight(),
				getBounds(), rect);
		mPokerCoverDrawable.setBounds(rect);
		mSurplusDrawable.setBounds(getBounds());
		
	}
	
	public void setPokerNumText(String pokerNum){
		this.pokerNumText = pokerNum;
		if(this.pokerNumText == null){
			return;
		}
		textRect.set(0, 0, (int)getPaint().measureText(this.pokerNumText), (int)getPaint().getFontSpacing());
	}
	
	@Override
	protected void doDraw(Canvas canvas) {
		if(pokerNumText == null){
			return;
		}
		if(pokerNumText.equals("2") || pokerNumText.equals("1") ){
			mSurplusDrawable.setAlpha(mAlpha);
			mSurplusDrawable.draw(canvas);
		}
		mPokerCoverDrawable.setAlpha(mAlpha);
		mPokerCoverDrawable.draw(canvas);
		canvas.drawText(pokerNumText, this.getBounds().centerX() - textRect.centerX(), this.getBounds().bottom - textRect.height(), getPaint());
	}

	@Override
	protected boolean doOnTouchEvent(MotionEvent event) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public void onDestroy() {
		// TODO Auto-generated method stub
		
	}

}
