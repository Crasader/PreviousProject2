package com.candy.futon.view;

import android.graphics.Canvas;
import android.graphics.Paint.FontMetrics;
import android.graphics.Rect;

import com.andy.canvasgame.service.GameConstantsService;
import com.andy.canvasgame.view.LimitTextAView;
import com.andy.canvasgame.view.TextAView;


public class MarqueeTextAView extends LimitTextAView {

	private int offsetX;
	
	private long lastDrawTime;
	
	private Rect wholeLineRect = new Rect();

	private final static int UPDATE_INTERVAL = 50;
	
	private int left, right;
	
	private String defaultMarquee = "游戏累计玩5局就送3000银币，还有机会赢实物大奖，点击此处领取奖励";
	
	private boolean forward;
	
	@Override
	protected void doDraw(Canvas canvas) {
		if(text == null){
			return;
		}
		if(left == 0 && right == 0){
			left = getBounds().left;
			right = getBounds().right;
		}
		if(System.currentTimeMillis() - lastDrawTime >UPDATE_INTERVAL){
			lastDrawTime = System.currentTimeMillis();
			if (offsetX > (getBounds().width() + 10)) {  
				offsetX = -((right- left)) - 10;  
	        } else {  
	        	offsetX += 2;  
	        }
			
		}
		FontMetrics fm = getPaint().getFontMetrics();  
		getPaint().setAlpha(getAlpha());
		
		int sc = canvas.saveLayer(left, getBounds().top, right, getBounds().bottom, null,  
                Canvas.MATRIX_SAVE_FLAG | Canvas.CLIP_SAVE_FLAG  
                        | Canvas.HAS_ALPHA_LAYER_SAVE_FLAG  
                        | Canvas.FULL_COLOR_LAYER_SAVE_FLAG  
                        | Canvas.CLIP_TO_LAYER_SAVE_FLAG);  
		canvas.drawText(text, left - offsetX, getBounds().bottom - fm.descent, getPaint());
		canvas.restoreToCount(sc); 
		invalidateRect(wholeLineRect);
	}
	
	@Override
	public void setText(String text) {
		// TODO Auto-generated method stub
		super.setText(text + "     "+defaultMarquee);
		offsetX = 0;
		forward = true;
	}
	
	public void updateBounds() {
		super.updateBounds();
		wholeLineRect.set(0,getBounds().top, GameConstantsService.getInstance().getScreenWidth(),getBounds().bottom);
	};
	
	@Override
	public void setGravity(int gravity) {
		// TODO Auto-generated method stub
		super.setGravity(gravity);
		wholeLineRect.set(0,getBounds().top, GameConstantsService.getInstance().getScreenWidth(),getBounds().bottom);
	}
	
	@Override
	public void setMargin(int left, int top, int right, int bottom) {
		// TODO Auto-generated method stub
		super.setMargin(left, top, right, bottom);
		wholeLineRect.set(0,getBounds().top, GameConstantsService.getInstance().getScreenWidth(),getBounds().bottom);
	}
	
	public void setLeftRight(int left, int right){
		this.left = left;
		this.right = right;
	}
}
