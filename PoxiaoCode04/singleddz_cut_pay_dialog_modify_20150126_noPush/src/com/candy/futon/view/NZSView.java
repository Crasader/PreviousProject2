package com.candy.futon.view;

import android.content.Context;
import android.graphics.Point;
import android.graphics.Rect;
import android.view.animation.AlphaAnimation;
import android.view.animation.Animation;
import android.view.animation.Animation.AnimationListener;
import android.view.animation.ScaleAnimation;

import com.andy.canvasgame.service.GameConstantsService;
import com.andy.canvasgame.ui.AView;
import com.andy.canvasgame.util.MyGravity;
import com.andy.canvasgame.view.BlankView;
import com.poxiao.ddz.standalone.R;

public class NZSView extends BlankView{

	private ImageAView nzsRenView;
	
	private ImageAView nzsTextView;
	
	private ImageAView[] nzsTears = new ImageAView[TEARS_ID.length];
	
	private final static int[] TEARS_ID = new int[]{R.drawable.nzs_tears_1, R.drawable.nzs_tears_2};
	
	private static Point[] TEARS_POINT = new Point[]{new Point(75, 88), new Point(79,89)};
	
	private static int NZS_TEXT_MARGIN_BOTTOM = 6;
	
	private static boolean inited = false;
	
	public static int MARGIN_BOTTOM = 129;
	
	private static long SCALE_DURATION = 1500;
	
	private RoomChangeView roomChangeView;
	
	private int tearIndex;
	
	private final static int MAX_CRY_COUNT = 8;
	
	public NZSView(Context context){
		if(!inited){
			inited = true;
			for(int i=0;i<TEARS_POINT.length;i++){
				TEARS_POINT[i].x *= GameConstantsService.getInstance().getDensityScale();
				TEARS_POINT[i].y *= GameConstantsService.getInstance().getDensityScale();
			}
			MARGIN_BOTTOM *= GameConstantsService.getInstance().getDensityScale();
			NZS_TEXT_MARGIN_BOTTOM *= GameConstantsService.getInstance().getDensityScale();
		}
		nzsRenView = new ImageAView(context, R.drawable.nzs_suiren);
		nzsTextView = new ImageAView(context, R.drawable.nzs_text);
		this.addChild(nzsRenView);
		this.addChild(nzsTextView);
		
		for(int i=0;i<TEARS_POINT.length;i++){
			nzsTears[i] = new ImageAView(context, TEARS_ID[i]);
			this.addChild(nzsTears[i]);
			nzsTears[i].setAlpha(0);
		}
		
		int width = Math.max(nzsRenView.getBounds().width(), nzsTextView.getBounds().width());
		roomChangeView = new RoomChangeView(context, width);
		this.addChild(roomChangeView);
		this.setBounds(new Rect(0,0, Math.max(width, roomChangeView.getBounds().width()), nzsRenView.getBounds().height() + roomChangeView.getBounds().height()));
		
	}
	
	@Override
	public void updateBounds() {
		super.updateBounds();
		nzsRenView.setGravity(MyGravity.BOTTOM|MyGravity.CENTER_HORIZONTAL);
		nzsTextView.setGravity(MyGravity.BOTTOM|MyGravity.CENTER_HORIZONTAL);
		nzsTextView.setMargin(0, 0, 0, NZS_TEXT_MARGIN_BOTTOM);
		for(int i=0;i<TEARS_POINT.length;i++){
			int left = nzsRenView.getBounds().left + TEARS_POINT[i].x;
			int top = nzsRenView.getBounds().top + TEARS_POINT[i].y;
			nzsTears[i].getBounds().set(left, 
					top, left+ nzsTears[i].getBounds().width(), top+nzsTears[i].getBounds().height());
			
		}
		
		roomChangeView.setGravity(MyGravity.TOP|MyGravity.CENTER_HORIZONTAL);
		roomChangeView.updateBounds();
		
	}
	
	public void setRoomChangeParam(boolean roomUp, int from, int to){
		roomChangeView.setParam(roomUp, from, to);
		roomChangeView.setGravity(MyGravity.TOP|MyGravity.CENTER_HORIZONTAL);
		roomChangeView.updateBounds();
	}
	
	public void startSelfAnimation(){
		this.tearIndex = 0;
		this.setAlpha(AView.FULL_OPAQUE);
		
		ScaleAnimation scaleAnimation = new ScaleAnimation(0.1f, 1f,0.1f,1f,nzsRenView.getBounds().centerX(), nzsRenView.getBounds().centerY());
		scaleAnimation.setDuration(SCALE_DURATION);
		
		
		scaleAnimation.setAnimationListener(new AnimationListener() {
			
			@Override
			public void onAnimationStart(Animation animation) {
				// TODO Auto-generated method stub
				
			}
			
			@Override
			public void onAnimationRepeat(Animation animation) {
				// TODO Auto-generated method stub
				
			}
			
			@Override
			public void onAnimationEnd(Animation animation) {
				cray();
			}
		});
		this.invalidate();
		ScaleAnimation textScale = new ScaleAnimation(0.1f, 1f,0.1f,1f, nzsRenView.getBounds().centerX(), nzsRenView.getBounds().centerY());
		textScale.setDuration(SCALE_DURATION);
		nzsTextView.startAnimation(textScale);
		nzsRenView.startAnimation(scaleAnimation);
		
	}

	protected void cray() {
		for(int i=0;i<nzsTears.length;i++){
			nzsTears[i].setAlpha(0);
		}
		AlphaAnimation alphaAnimation = new AlphaAnimation(1f, 1f);
		alphaAnimation.setDuration(200);
		alphaAnimation.setAnimationListener(new AnimationListener() {
			
			@Override
			public void onAnimationStart(Animation animation) {
				// TODO Auto-generated method stub
				
			}
			
			@Override
			public void onAnimationRepeat(Animation animation) {
				// TODO Auto-generated method stub
				
			}
			
			@Override
			public void onAnimationEnd(Animation animation) {
				
				tearIndex += 1;
				if(tearIndex > MAX_CRY_COUNT){
					NZSView.this.setAlpha(0);
					NZSView.this.getParent().invalidate();
					return;
				}
				cray();
			}
		});
		int index = tearIndex % TEARS_POINT.length;
		
		nzsTears[index].setAlpha(AView.FULL_OPAQUE);
		nzsTears[index].startAnimation(alphaAnimation);
		this.invalidate();
	}
	
}
