package com.candy.futon.view;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Rect;
import android.graphics.drawable.BitmapDrawable;
import android.view.MotionEvent;

import com.andy.canvasgame.ui.AView;
import com.andy.canvasgame.util.BitmapSpliter;
import com.andy.pokergames.ddz.ai.ddzai.domain.PokerRank;
import com.poxiao.ddz.standalone.R;

public class CardNumberTitle extends AView {

	private BitmapDrawable drawable;
	
	public CardNumberTitle(Context context, PokerRank rank){
		Bitmap[] array = GameUIResource.getInstance().loadBitMapArray(context.getResources(), R.drawable.card_remainder_card_num_title, 
				PokerRank.values().length - 1, BitmapSpliter.VERTICAL);
		int index = PokerRank.values().length - 1 -  rank.ordinal();
		drawable = new BitmapDrawable(context.getResources(), array[index]);
		this.setBounds(new Rect(0,0,drawable.getIntrinsicWidth(), drawable.getIntrinsicHeight()));
	}
	
	@Override
	protected void doDraw(Canvas canvas) {
		drawable.setBounds(getBounds());
		drawable.draw(canvas);
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
