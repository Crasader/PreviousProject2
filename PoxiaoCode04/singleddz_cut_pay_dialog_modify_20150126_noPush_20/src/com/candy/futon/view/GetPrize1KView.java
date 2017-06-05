package com.candy.futon.view;

import android.content.Context;
import android.graphics.Point;
import android.graphics.Rect;
import android.view.animation.Animation;
import android.view.animation.Animation.AnimationListener;
import android.view.animation.AnimationSet;
import android.view.animation.ScaleAnimation;
import android.view.animation.TranslateAnimation;

import com.andy.canvasgame.service.GameConstantsService;
import com.andy.canvasgame.ui.AView;
import com.andy.canvasgame.util.MyGravity;
import com.andy.canvasgame.view.BlankView;
import com.candy.futon.IFutonDdzApplication;
import com.candy.futon.domain.GameConfig;
import com.candy.futon.util.FireworkViewHelper;
import com.candy.futon.util.FireworkViewHelper.FireworkEndListener;
import com.poxiao.ddz.standalone.R;

public class GetPrize1KView extends BlankView {

	public static interface GetPrize1KViewAnimationFinishListener{
		public void onEnd();
	}
	
	private ImageAView closePrizeView;
	
	private ImageAView openPrizeView;
	
	private ImageAView add1KTextView;
	
	
	private static boolean inited = false;
	
	public static int MARGIN_BOTTOM = 120;
	
	private static long SCALE_DURATION = 1000;
	
	private static long MOVE_DURATION = 600;
	
	private int add1KTr2Y = 0;
	
	private Rect destRect;
	
	private static Point[] fireworkArchors = new Point[]{
		new Point(243,97), new Point(41,214),
		new Point(27,93), new Point(135,46)
	};
	
	public static Point[] FIREWORK_ARCHORS = new Point[fireworkArchors.length];
	
	
	public GetPrize1KView(Context context, AView parent, Rect destRect){
		this.destRect = destRect;
		openPrizeView = new ImageAView(context, R.drawable.anim_prize_open);
		closePrizeView = new ImageAView(context, R.drawable.anim_prize_closed);
		add1KTextView = new ImageAView(context, R.drawable.anim_prize_add_1k);
		if(!inited){
			MARGIN_BOTTOM *= GameConstantsService.getInstance().getDensityScale();
			for(int i=0;i<fireworkArchors.length;i++){
				fireworkArchors[i].x *= GameConstantsService.getInstance().getDensityScale();
				fireworkArchors[i].y *= GameConstantsService.getInstance().getDensityScale();
			}
		}
		closePrizeView.setAlpha(0);
		parent.addChild(closePrizeView);
		this.addChild(openPrizeView);
		this.addChild(add1KTextView);
		this.setBounds(new Rect(closePrizeView.getBounds()));
	}
	
	@Override
	public void updateBounds() {
		super.updateBounds();
		for(int i=0;i<FIREWORK_ARCHORS.length;i++){
			FIREWORK_ARCHORS[i] = new Point(fireworkArchors[i].x + getBounds().left, fireworkArchors[i].y + getBounds().top);
		}
		MyGravity.apply(MyGravity.CENTER, closePrizeView.getBounds().width(), closePrizeView.getBounds().height(), 
				this.getBounds(), closePrizeView.getBounds());
		openPrizeView.setGravity(MyGravity.CENTER);
		add1KTextView.setGravity(MyGravity.CENTER);
		add1KTr2Y = getBounds().top - add1KTextView.getBounds().top;
	}
	
	public void startSelfAnimation(final ImageAView fireworks[], final GetPrize1KViewAnimationFinishListener endListener){
		openPrizeView.setAlpha(0);
		closePrizeView.setAlpha(AView.FULL_OPAQUE);
		add1KTextView.setAlpha(0);
		this.setAlpha(AView.FULL_OPAQUE);
		for(int i=0;i<fireworks.length;i++){
			fireworks[i].setAlpha(0);
		}
		ScaleAnimation scaleAnimation = new ScaleAnimation(0.1f, 1f,0.1f,1f,this.getBounds().centerX(), this.getBounds().centerY());
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
				openPrizeAndStartFireWorks(fireworks, endListener);
				
				
			}

			
		});
		this.invalidate();
		closePrizeView.startAnimation(scaleAnimation);
		
	}
	protected void openPrizeAndStartFireWorks(ImageAView fireworks[], final GetPrize1KViewAnimationFinishListener endListener) {
		add1KTextView.setAlpha(AView.FULL_OPAQUE);
		openPrizeView.setAlpha(AView.FULL_OPAQUE);
		closePrizeView.setAlpha(0);
		openPrizeView.invalidate();
		TranslateAnimation tr = new TranslateAnimation(0, 0, 0, add1KTr2Y);
		tr.setDuration(MOVE_DURATION);
		add1KTextView.startAnimation(tr);
		FireworkViewHelper.updatePosition(fireworks, FIREWORK_ARCHORS);
		FireworkViewHelper.startFireworks(fireworks, new FireworkEndListener() {
			
			@Override
			public void onEnd() {
				closePrizeAndSendIt2Player(endListener);
			}
		});
	}

	protected void closePrizeAndSendIt2Player(final GetPrize1KViewAnimationFinishListener endListener) {
		add1KTextView.setAlpha(0);
		openPrizeView.setAlpha(0);
		closePrizeView.setAlpha(AView.FULL_OPAQUE);
		openPrizeView.invalidate();
		
//		ScaleAnimation scaleAnimation = new ScaleAnimation(1f, 0.2f, 1f, 0.2f,
//				Animation.RELATIVE_TO_SELF, 0.5f, Animation.RELATIVE_TO_SELF, 0.5f);
		ScaleAnimation scaleAnimation = new ScaleAnimation(1f, 0.2f, 1f,0.2f,this.getBounds().centerX(), this.getBounds().centerY());
		scaleAnimation.setDuration(SCALE_DURATION);
		
		int toXDelta, toYDelta;
		toXDelta = (int) ((destRect.left - closePrizeView.getBounds().left) * 1.2f);
		
		
		toYDelta = (int) ((destRect.top - closePrizeView.getBounds().top)/2f);
		TranslateAnimation tr = new TranslateAnimation(0, toXDelta, 0, toYDelta);
//		TranslateAnimation tr = new TranslateAnimation(Animation.RELATIVE_TO_SELF, 0f, Animation.ABSOLUTE, destRect.centerX(), 
//				Animation.RELATIVE_TO_SELF, 0f, Animation.ABSOLUTE, destRect.centerY());
		
		tr.setDuration(SCALE_DURATION);
		
		AnimationSet set = new AnimationSet(true);
		
		set.addAnimation(scaleAnimation);
		set.addAnimation(tr);
		
		
		tr.setAnimationListener(new AnimationListener() {
			
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
				GetPrize1KView.this.setAlpha(0);
				closePrizeView.setAlpha(0);
				GetPrize1KView.this.getParent().invalidate();
				if(endListener != null){
					endListener.onEnd();
				}
				
			}
		});
		
		closePrizeView.clearAnimation();
		closePrizeView.startAnimation(set);
		
	}
	
}

