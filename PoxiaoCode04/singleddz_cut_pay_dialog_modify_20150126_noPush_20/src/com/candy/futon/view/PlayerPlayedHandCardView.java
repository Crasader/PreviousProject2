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

public class PlayerPlayedHandCardView extends AView{

	public final static int LEFT = 1;
	
	public final static int RIGHT = 2;
	
	private int location;
	
	private int PADDING_BETWEEN_ROW = 32;
	
	private int PADDING_BETWEEN_COLUMN = 28;
	
	private int MARGIN_X = 120;
	
	private int MARGIN_Y = 108;
	
	private int POKER_WIDTH;
	
	private int POKER_HEIGHT;
	
	private Context context;
	
	private int PADDING_BETWEEN_HANDCARD = 20;
	
	private int MAX_POKER_WIDTH;
	
	private int width;
	
	public PlayerPlayedHandCardView(Context context, AView parent, int location){
		this.location = location;
		this.context = context;
		this.setParent(parent);
		PADDING_BETWEEN_COLUMN *= GameConstantsService.getInstance().getDensityScale();
		
		PADDING_BETWEEN_ROW *= GameConstantsService.getInstance().getDensityScale();
		MARGIN_X *= GameConstantsService.getInstance().getDensityScale();
		MARGIN_Y *= GameConstantsService.getInstance().getDensityScale();
		PADDING_BETWEEN_HANDCARD *= GameConstantsService.getInstance().getDensityScale();
		PokerView pokerView = new PokerView(Poker.CLUBS_3, context, GameUIResource.SIZE_MIDDLE, 0, 0);
		POKER_WIDTH = pokerView.getBounds().width();
		POKER_HEIGHT =  pokerView.getBounds().height();
		
		MAX_POKER_WIDTH = (int) (POKER_WIDTH*0.9);
		
		width = GameConstantsService.getInstance().getScreenWidth() / 2 - MARGIN_X - PADDING_BETWEEN_HANDCARD;
		this.setBounds( new Rect(0,0, width, POKER_HEIGHT));
		if(location == LEFT){
			this.setGravity(MyGravity.LEFT|MyGravity.TOP);
			this.setMargin(MARGIN_X, MARGIN_Y, 0, 0);
		}else if(location == RIGHT){
			this.setGravity(MyGravity.RIGHT|MyGravity.TOP);
			this.setMargin(0, MARGIN_Y, MARGIN_X, 0);
		}else{
			throw new IllegalArgumentException();
		}
	}
	
	public void setPokerList(List<Poker> pokerList){
		this.clearChilds();
		if(pokerList == null || pokerList.isEmpty()){
			setPokers(null);
			return;
		}
		ArrayList<Poker> temp = new ArrayList<Poker>(pokerList);
		Collections.reverse(temp);
		doSetPokers(temp.toArray(new Poker[]{}));
	}
	
	public void setPokers(Poker[] pokersT){
		this.clearChilds();

		doSetPokers(pokersT);
	}

	private void doSetPokers(Poker[] pokers) {
		if(pokers == null || pokers.length == 0){
			return;
		}
		int columnPadding;
		if(pokers.length == 1){
			columnPadding = POKER_WIDTH;
		}else{
			columnPadding = (width - POKER_WIDTH)/ (pokers.length -1);
		}
		if(columnPadding < PADDING_BETWEEN_COLUMN){
			columnPadding = PADDING_BETWEEN_COLUMN;
		}else if(columnPadding > MAX_POKER_WIDTH){
			columnPadding = MAX_POKER_WIDTH;
		}
		List<PokerView> pokerViews = new ArrayList<PokerView>();
		
		int marginX,top;
		int rowCount = 0;
		int columnCount = 0;
		int pokerViewCountOnOneRow = (getBounds().width() - POKER_WIDTH) /PADDING_BETWEEN_COLUMN + 1;
		int maxColumn = pokers.length/pokerViewCountOnOneRow;
		if(pokers.length % pokerViewCountOnOneRow != 0){
			maxColumn += 1;
		}
		if(pokers.length == pokerViewCountOnOneRow)
		{
			maxColumn += 1;
		}
		if(location == LEFT){
			marginX = getBounds().left;
		}else{
			marginX = getRightMarginX(pokers, columnPadding, columnCount,
					pokerViewCountOnOneRow, maxColumn);
		}
		top = getBounds().top;
		
		
		
		
		for(int i = 0;i<pokers.length;i++){
			if(location == LEFT && (marginX + POKER_WIDTH) > getBounds().right){
				marginX = getBounds().left;
				top += PADDING_BETWEEN_ROW;
			}else if(location == RIGHT && (marginX + POKER_WIDTH) > getBounds().right){
				marginX = getRightMarginX(pokers, columnPadding, columnCount,
						pokerViewCountOnOneRow, maxColumn);
				top += PADDING_BETWEEN_ROW;
				rowCount += 1;
			}
			if(rowCount == 0){
				columnCount += 1;
			}
			PokerView pokerView;
			
			pokerView = new PokerView(pokers[i], context, GameUIResource.SIZE_MIDDLE, marginX, top);
			marginX += columnPadding;
			
			pokerViews.add(pokerView);
		}
		
		
		
		int totalHeight = top - getBounds().top + POKER_HEIGHT;
		if(totalHeight > getBounds().height()){
			getBounds().set(getBounds().left, getBounds().top, getBounds().right, getBounds().top + totalHeight);
		}
		for(int i = 0;i<pokerViews.size();i++){
			this.addChild(pokerViews.get(i));
		}
		
	}

	private int getRightMarginX(Poker[] pokers, int columnPadding,
			int columnCount, int pokerViewCountOnOneRow, int maxColumn) {
		int marginX;
		if(columnCount + 1== maxColumn){
			marginX = getBounds().right - (pokers.length%pokerViewCountOnOneRow -1) * columnPadding - POKER_WIDTH;
		}else{
			marginX = getBounds().right - (pokerViewCountOnOneRow -1) * columnPadding - POKER_WIDTH;
		}
		return marginX;
	}

	@Override
	protected void doDraw(Canvas canvas) {
		
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
