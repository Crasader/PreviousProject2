package com.candy.futon.view;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Rect;
import android.view.MotionEvent;

import com.andy.canvasgame.service.GameConstantsService;
import com.andy.canvasgame.ui.AView;
import com.andy.canvasgame.util.MyGravity;
import com.andy.pokergames.ddz.ai.ddzai.domain.Poker;
import com.andy.pokergames.ddz.ai.ddzai.uitl.PokerUtil;

public class SelfPlayedHandCardView extends AView {

	private int MARGIN_BOTTOM = 172;
	
	private int MAX_WIDTH = 533;
	
	private int POKER_WIDTH;
	
	private int POKER_HEIGHT;
	
	private int MAX_POKER_WIDTH;
	
	private Context context;
	
	public SelfPlayedHandCardView(Context context){
		this.context = context;
		MARGIN_BOTTOM *= GameConstantsService.getInstance().getDensityScale();
		MAX_WIDTH *= GameConstantsService.getInstance().getDensityScale();
		PokerView pokerView = new PokerView(Poker.CLUBS_3, context, GameUIResource.SIZE_MIDDLE, 0, 0);
		POKER_WIDTH = pokerView.getBounds().width();
		POKER_HEIGHT =  pokerView.getBounds().height();
		MAX_POKER_WIDTH = (int) (POKER_WIDTH * 0.9);
		this.setBounds(new Rect());
		
	}
	
	public void setPokerList(List<Poker> pokerList){
		if(pokerList == null || pokerList.isEmpty()){
			setPokers(null);
			return;
		}
		ArrayList<Poker> temp = new ArrayList<Poker>(pokerList);
		Collections.reverse(temp);
		doSetPoker(temp.toArray(new Poker[]{}));
	}
	
	public void setPokers(Poker[] pokers){
		this.clearChilds();
		
		doSetPoker(pokers);
	}

	private void doSetPoker(Poker[] pokers) {
		if(pokers == null || pokers.length == 0){
			return;
		}
		int pokerWidth;
		if(pokers.length == 1){
			pokerWidth = POKER_WIDTH;
		}else{
			pokerWidth = (MAX_WIDTH - POKER_WIDTH)/(pokers.length -1);
		}
		if(pokerWidth > MAX_POKER_WIDTH){
			pokerWidth = MAX_POKER_WIDTH;
		}
		int totalWidth = pokerWidth * (pokers.length-1) + POKER_WIDTH;
		this.getBounds().set(0,0,totalWidth, POKER_HEIGHT);
		this.setGravity(MyGravity.BOTTOM|MyGravity.CENTER);
		this.setMargin(0, 0, 0, MARGIN_BOTTOM);
		int left = this.getBounds().left;
		int top = this.getBounds().top;
		for(int i = 0;i<pokers.length;i++){
			left = this.getBounds().left + i* pokerWidth;
			PokerView pokerView = new PokerView(pokers[i], context, GameUIResource.SIZE_MIDDLE, left, top);
			this.addChild(pokerView);
		}
	}
	
	@Override
	protected void doDraw(Canvas canvas) {
		// TODO Auto-generated method stub

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
