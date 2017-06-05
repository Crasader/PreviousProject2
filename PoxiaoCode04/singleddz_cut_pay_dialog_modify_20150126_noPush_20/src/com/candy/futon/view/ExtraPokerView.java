package com.candy.futon.view;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Rect;
import android.graphics.drawable.BitmapDrawable;
import android.view.MotionEvent;

import com.andy.canvasgame.service.GameConstantsService;
import com.andy.canvasgame.ui.AView;
import com.andy.pokergames.ddz.ai.ddzai.domain.DdzTable;
import com.poxiao.ddz.standalone.R;

public class ExtraPokerView extends AView {

	private BitmapDrawable pokerCoverDrawable;
	
	private int left = 145;
	
	private int top = 14;
	
	private int innerPadding = 4;
	
	private DdzTable table;
	
	private Context context;
	
	private final static int EXTRA_CARD_NUM = 3;
	
	private Rect[] pokerRect = new Rect[EXTRA_CARD_NUM];
	
	public ExtraPokerView(Context context, DdzTable table){
		this.table = table;
		this.context = context;
		pokerCoverDrawable = new BitmapDrawable(context.getResources(), GameUIResource.getInstance().loadBitMap(context.getResources(), 
				R.drawable.back_card_bg));
		
		left = (int) (left * GameConstantsService.getInstance().getDensityScale());
		top = (int) (top * GameConstantsService.getInstance().getDensityScale());
		innerPadding =  (int) (innerPadding * GameConstantsService.getInstance().getDensityScale());
		int intrinsicWidth = pokerCoverDrawable.getIntrinsicWidth();
		int width = intrinsicWidth * EXTRA_CARD_NUM + (EXTRA_CARD_NUM -1)* innerPadding;
		int height = pokerCoverDrawable.getIntrinsicHeight();
		this.setBounds(new Rect(left, top, left+width,top+height));
		
		updatePokerRect();
		
	}
	
	private void updatePokerRect(){
		int intrinsicWidth = pokerCoverDrawable.getIntrinsicWidth();
		int height = pokerCoverDrawable.getIntrinsicHeight();
		for(int i=0;i<EXTRA_CARD_NUM;i++){
			pokerRect[i] = new Rect();
			int pokerLeft = getBounds().left + i*intrinsicWidth;
			if(i != 0){
				pokerLeft += i* innerPadding;
			}
			pokerRect[i].set(pokerLeft, getBounds().top, pokerLeft + intrinsicWidth, getBounds().top+ height);
			
		}
	}
	
	@Override
	public void setGravity(int gravity) {
		super.setGravity(gravity);
		updatePokerRect();
	}
	
	@Override
	public void setMargin(int left, int top, int right, int bottom) {
		super.setMargin(left, top, right, bottom);
		updatePokerRect();
	}
	
	public boolean checkPokerList(){
		if(table.getLoadExtraCards() == null || table.getLoadExtraCards().isEmpty()){
			this.clearChilds();
			return false;
		}
		if(this.mChilds == null || this.mChilds.isEmpty()){
			for(int i=0;i<EXTRA_CARD_NUM;i++){
				PokerView pokerView = new PokerView(table.getLoadExtraCards().get(i), context, GameUIResource.SIZE_SMALL, 0, 0);
				pokerView.getBounds().set(pokerRect[i]);
				this.addChild(pokerView);
			}
		}
		return true;
	}
	
	@Override
	protected void doDraw(Canvas canvas) {
		if(table.getLoad() != null && table.getLoad() == table.getPlayers()[0] && checkPokerList()){
			return;
		}
		for(int i=0;i<EXTRA_CARD_NUM;i++){
			this.pokerCoverDrawable.setBounds(pokerRect[i]);
			this.pokerCoverDrawable.setAlpha(mAlpha);
			this.pokerCoverDrawable.draw(canvas);
		}
	}
	
	@Override
	protected void drawChild(Canvas canvas, Rect rect) {
		if(table.getLoad() != null && table.getLoad() == table.getPlayers()[0] && checkPokerList()){
			super.drawChild(canvas, rect);
		}

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
