package com.candy.futon.view;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Rect;
import android.graphics.drawable.BitmapDrawable;
import android.view.MotionEvent;

import com.andy.canvasgame.service.GameConstantsService;
import com.andy.canvasgame.ui.AView;
import com.andy.canvasgame.util.MyGravity;
import com.candy.futon.domain.GameConfig;
import com.poxiao.ddz.standalone.R;

public class TopExtraPokerAndActionView extends AView{

	public static int EXTRA_POKER_MARGIN_TOP = 10;
	
	public static int EXTRA_POKER_MARGIN_LEFT = 0;
	
	public static int LEFT_ACTION_MARGIN_LEFT = 30;
	
	public static int LEFT_ACTION_MARGIN_LEFT_WHILE_ONLY_2_ACTION = 40;
	
	public static int RIGHT_ACTION_MARGIN_RIGHT_WHILE_ONLY_2_ACTION = 46;
	
	public static int RIGHT_ACTION_MARGIN_RIGHT = 38;
	
	public static int LEFT_ACTION_MARGIN_LEFT2 = 115;
	
	public static int RIGHT_ACTION_MARGIN_RIGHT2 = 125;
	
	public static int ACTION_MARGIN_TOP = 10;
	
	public static int SHOW_HIDE_BUTTON_MARGIN_BOTTOM = 12;
	
	public static int MARGIN_TOP_WHILE_HIDE = -81;
	
	private static BitmapDrawable bgDrawable;
	
	public TopExtraPokerAndActionView(Context context, AView parent){
		
		
		
		if(bgDrawable == null){
			LEFT_ACTION_MARGIN_LEFT_WHILE_ONLY_2_ACTION *= GameConstantsService.getInstance().getDensityScale();
			RIGHT_ACTION_MARGIN_RIGHT_WHILE_ONLY_2_ACTION *= GameConstantsService.getInstance().getDensityScale();
			EXTRA_POKER_MARGIN_LEFT *= GameConstantsService.getInstance().getDensityScale();
			EXTRA_POKER_MARGIN_TOP *= GameConstantsService.getInstance().getDensityScale();
			LEFT_ACTION_MARGIN_LEFT *= GameConstantsService.getInstance().getDensityScale();
			RIGHT_ACTION_MARGIN_RIGHT *= GameConstantsService.getInstance().getDensityScale();
			LEFT_ACTION_MARGIN_LEFT2 *= GameConstantsService.getInstance().getDensityScale();
			RIGHT_ACTION_MARGIN_RIGHT2 *= GameConstantsService.getInstance().getDensityScale();
			SHOW_HIDE_BUTTON_MARGIN_BOTTOM *= GameConstantsService.getInstance().getDensityScale();
			MARGIN_TOP_WHILE_HIDE *= GameConstantsService.getInstance().getDensityScale();
			ACTION_MARGIN_TOP *= GameConstantsService.getInstance().getDensityScale();
			if(GameConfig.getInstance().noPromote){
				bgDrawable = new BitmapDrawable(context.getResources(), GameUIResource.getInstance().loadBitMap(context.getResources(), R.drawable.top_extra_poker_actions_no_promote));
			}else{
				bgDrawable = new BitmapDrawable(context.getResources(), GameUIResource.getInstance().loadBitMap(context.getResources(), R.drawable.top_extra_poker_actions));
			}
		}
		this.setBounds(new Rect(0,0, bgDrawable.getIntrinsicWidth(),bgDrawable.getIntrinsicHeight()));
		
		this.setParent(parent);
		this.setGravity(MyGravity.CENTER_HORIZONTAL|MyGravity.TOP);
		bgDrawable.setBounds(getBounds());
	}
	
	public void resetBg(Context context){
		if(GameConfig.getInstance().noPromote){
			bgDrawable = new BitmapDrawable(context.getResources(), GameUIResource.getInstance().loadBitMap(context.getResources(), R.drawable.top_extra_poker_actions_no_promote));
		}else{
			bgDrawable = new BitmapDrawable(context.getResources(), GameUIResource.getInstance().loadBitMap(context.getResources(), R.drawable.top_extra_poker_actions));
		}
		this.setBounds(new Rect(0,0, bgDrawable.getIntrinsicWidth(),bgDrawable.getIntrinsicHeight()));
		this.setGravity(MyGravity.CENTER_HORIZONTAL|MyGravity.TOP);
		bgDrawable.setBounds(getBounds());
		
	}
	
	@Override
	protected void doDraw(Canvas canvas) {
		bgDrawable.setBounds(getBounds());
		bgDrawable.setAlpha(mAlpha);
		bgDrawable.draw(canvas);
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
