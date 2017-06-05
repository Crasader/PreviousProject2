package com.candy.futon.view;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Rect;
import android.graphics.drawable.BitmapDrawable;
import android.view.MotionEvent;

import com.andy.canvasgame.service.GameConstantsService;
import com.andy.canvasgame.ui.AView;
import com.andy.canvasgame.util.BitmapSpliter;
import com.poxiao.ddz.standalone.R;

/**
 * 底分和倍数View
 * @author Andy
 *
 */
public class BetAndMagView extends AView{
	
	public static int MARGIN_TOP = -36;
	
	public static int MARGIN_LEFT = 12;
	
	public static int MARGIN_RIGHT = 36;

	private BitmapDrawable titleDrawable;
	
	private ImageNumberAView imageNumberView;
	
	private static BitmapDrawable xDrawable;
	
	private static Rect sizeRect;
	
	private static int TITLE_NUMBER_MARGIN = 2;
	
	private Rect titleRect = new Rect();
	
	private Rect xRect = new Rect();
	
	private Rect numberRect = new Rect();
	
	private int number = 0;
	
	private static boolean init = false;
	
	private boolean isBet = false;
	
	public BetAndMagView(Context context, int titleId){
		
		if(!init){
			TITLE_NUMBER_MARGIN *= GameConstantsService.getInstance().getDensityScale();
			MARGIN_TOP *= GameConstantsService.getInstance().getDensityScale();
			MARGIN_LEFT *= GameConstantsService.getInstance().getDensityScale();
			MARGIN_RIGHT *= GameConstantsService.getInstance().getDensityScale();
			init = true;
			
		}
		if(titleId == R.drawable.bet_point){
			isBet = true;
		}
		imageNumberView = new ImageNumberAView(context, R.drawable.bet_and_mag_num, 10, BitmapSpliter.HORIZONTAL);
		imageNumberView.setNumber(number);
		this.addChild(imageNumberView);	
		titleDrawable = new BitmapDrawable(context.getResources(), GameUIResource.getInstance().loadBitMap(context.getResources(), titleId));
		if(sizeRect == null){
			sizeRect = new Rect();
			sizeRect.set(0, 0, titleDrawable.getIntrinsicWidth() + TITLE_NUMBER_MARGIN + imageNumberView.getBounds().width() * 2, imageNumberView.getBounds().height());
		}
		xDrawable = new BitmapDrawable(context.getResources(), GameUIResource.getInstance().loadBitMap(context.getResources(), R.drawable.bet_and_mag_x));
		this.setBounds(new Rect(sizeRect));
		
	}
	
	@Override
	public void setGravity(int gravity) {
		// TODO Auto-generated method stub
		super.setGravity(gravity);
		calcDrawableBounds();
		
	}
	
	private void calcDrawableBounds() {
		titleRect.set(getBounds().left, getBounds().top, getBounds().left + titleDrawable.getIntrinsicWidth(), 
				getBounds().top + titleDrawable.getIntrinsicHeight());
		int xRectLeft= titleRect.right + TITLE_NUMBER_MARGIN;
		int numRectTop = getBounds().centerY() - (xDrawable.getIntrinsicHeight()/2);
		xRect.set(xRectLeft, numRectTop,
				xRectLeft + xDrawable.getIntrinsicWidth(),
				numRectTop + xDrawable.getIntrinsicHeight());
		numberRect.set(xRect.right, numRectTop, xRect.right+ this.imageNumberView.getBounds().width(),
				numRectTop + this.imageNumberView.getBounds().height());
		titleDrawable.setBounds(titleRect);
		this.imageNumberView.getBounds().set(numberRect);
		
	}
	

	@Override
	public void setMargin(int left, int top, int right, int bottom) {
		// TODO Auto-generated method stub
		super.setMargin(left, top, right, bottom);
		calcDrawableBounds();
	}
	
	@Override
	protected void doDraw(Canvas canvas) {
		if(number == 0){
			return;
		}
		titleDrawable.draw(canvas);
		if(!isBet){
			xDrawable.setBounds(xRect);
			xDrawable.draw(canvas);
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

	public void setNumber(int number) {
		this.number = number;
		this.imageNumberView.setNumber(this.number);
		calcDrawableBounds();
	}

	@Override
	protected void drawChild(Canvas canvas, Rect rect) {
		if(this.number == 0){
			return;
		}
		super.drawChild(canvas, rect);
	}
	
	@Override
	protected void drawChild(Canvas canvas) {
		if(this.number == 0){
			return;
		}
		super.drawChild(canvas);
	}
	
	
}
