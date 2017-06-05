package com.candy.futon.view;

import android.content.Context;
import android.graphics.Point;
import android.graphics.Rect;
import android.text.method.MovementMethod;
import android.view.animation.Animation;
import android.view.animation.Animation.AnimationListener;
import android.view.animation.AlphaAnimation;
import android.view.animation.AnimationSet;
import android.view.animation.DecelerateInterpolator;
import android.view.animation.LinearInterpolator;
import android.view.animation.RotateAnimation;
import android.view.animation.ScaleAnimation;
import android.view.animation.TranslateAnimation;

import com.andy.canvasgame.service.GameConstantsService;
import com.andy.canvasgame.ui.AView;
import com.andy.canvasgame.util.MyGravity;
import com.andy.canvasgame.view.BlankView;
import com.poxiao.ddz.standalone.R;

public class NiZhenBangView extends BlankView{

	private ImageAView bgView;
	
	private ImageAView lightView;
	
	private ImageAView textView;
	
	private ImageAView[] snowFlakeViews = new ImageAView[12];
	
	private static int[] snowIds = new int[]{R.drawable.snow_flake_purple, R.drawable.snow_flake_red};
	
	private static int BG_PADDING_BOTTOM = 50;
	
	public static int MARGIN_BOTTOM = 70;
	
	public static boolean inited = false;
	
	private static long SCALE_DURATION = 1500;

	private static long ROTATE_DURATION = 1000;
	
	private static long SNOW_DURATION = 1500;
	
	
	private static long FADE_OUT_ANIMATION = 500;
	
	private RoomChangeView roomChangeView;
	
	private static Point[] fireworkArchors = new Point[]{
		new Point(259, 159), new Point(50,54),
		new Point(193,149), new Point(207,0)
	};
	
	
	public static Point[] FIREWORK_ARCHORS = new Point[fireworkArchors.length];
	
	public NiZhenBangView(Context context){
		
		if(!inited){
			inited = true;
			MARGIN_BOTTOM *= GameConstantsService.getInstance().getDensityScale();
			BG_PADDING_BOTTOM *= GameConstantsService.getInstance().getDensityScale();
			for(int i=0;i<fireworkArchors.length;i++){
				fireworkArchors[i].x *= GameConstantsService.getInstance().getDensityScale();
				fireworkArchors[i].y *= GameConstantsService.getInstance().getDensityScale();
			}
		}
		
		bgView = new ImageAView(context, R.drawable.nzb_bg);
		lightView = new ImageAView(context, R.drawable.nzb_light);
		textView = new ImageAView(context, R.drawable.nzb_text);
		this.addChild(bgView);
		this.addChild(lightView);
		this.addChild(textView);
		
		roomChangeView = new RoomChangeView(context, bgView.getBounds().width());
		this.addChild(roomChangeView);
		int width = Math.max(bgView.getBounds().width(), roomChangeView.getBounds().width());
		this.setBounds(new Rect(0,0,width, bgView.getBounds().height() + roomChangeView.getBounds().height() + BG_PADDING_BOTTOM));

		int j =0;
		for(int i=0;i<snowFlakeViews.length;i++){
			if(j >= snowIds.length){
				j = 0;
			}
			snowFlakeViews[i] = new ImageAView(context, snowIds[j]);
			j += 1;
			this.addChild(snowFlakeViews[i]);
		}
		
		
		
	}
	
	@Override
	public void updateBounds() {
		super.updateBounds();
		
		
		
		roomChangeView.setGravity(MyGravity.TOP|MyGravity.CENTER_HORIZONTAL);
		roomChangeView.updateBounds();
		
		
		MyGravity.apply(MyGravity.CENTER_HORIZONTAL|MyGravity.BOTTOM, bgView.getBounds().width(), bgView.getBounds().height(), 
				getBounds(), bgView.getBounds());
		bgView.setMargin(0, 0, 0, BG_PADDING_BOTTOM);
		MyGravity.apply(MyGravity.CENTER_HORIZONTAL|MyGravity.BOTTOM, lightView.getBounds().width(), lightView.getBounds().height(), 
				getBounds(), lightView.getBounds());
		MyGravity.apply(MyGravity.CENTER_HORIZONTAL|MyGravity.BOTTOM, textView.getBounds().width(), textView.getBounds().height(), 
				bgView.getBounds(), textView.getBounds());
		int startX = getBounds().left;
		int startY = getBounds().top;
		
		int endX = getBounds().right - snowFlakeViews[0].getBounds().width();
		int endY = getBounds().top + roomChangeView.getBounds().height() * 2;
		
		for(int i=0;i<snowFlakeViews.length;i++){
			int x = (int) (startX + (endX - startX) * Math.random());
			int y = (int) (startY + (endY- startY) * Math.random());
			Rect rect = snowFlakeViews[i].getBounds();
			snowFlakeViews[i].getBounds().set(x,y ,rect.width()+x, rect.height() + y);
		}
		
	}
	
	public void startSelfAnimation(){
		this.setAlpha(AView.FULL_OPAQUE);
		ScaleAnimation scaleAnimation = new ScaleAnimation(0.1f, 1f,0.1f,1f,this.getBounds().centerX(), this.getBounds().centerY());
		this.lightView.setAlpha(0);
		this.bgView.setAlpha(AView.FULL_OPAQUE);
		this.textView.setAlpha(AView.FULL_OPAQUE);
		for(int i=0;i<snowFlakeViews.length;i++){
			snowFlakeViews[i].setAlpha(0);
		}
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
				rotateAndSnow();
			}
		});
		this.invalidate();
		textView.setAnimation(scaleAnimation);
		bgView.startAnimation(scaleAnimation);
		
	}

	protected void rotateAndSnow() {
		RotateAnimation rotateAnimation = new RotateAnimation(0.0f, 360.0f, lightView.getBounds().centerX(), lightView.getBounds().centerY()); 
		rotateAnimation.setRepeatCount(3);
		rotateAnimation.setDuration(ROTATE_DURATION);
		rotateAnimation.setInterpolator(new LinearInterpolator());
		rotateAnimation.setAnimationListener(new AnimationListener() {
			
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
				NiZhenBangView.this.setAlpha(0);
				NiZhenBangView.this.getParent().invalidate();
			}
		});
		lightView.setAlpha(AView.FULL_OPAQUE);
		lightView.startAnimation(rotateAnimation);
		
		
		for(int i=0;i<snowFlakeViews.length;i++){
			
			
			
			
			final int index = i;
			final long delay = (long) (2000 * Math.random());
			AlphaAnimation fadeInAnimation = new AlphaAnimation(0f, 1f);
			fadeInAnimation.setDuration(delay);
			fadeInAnimation.setAnimationListener(new AnimationListener() {
				
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
					AnimationSet set = new AnimationSet(true);
					AlphaAnimation alphaAnim = new AlphaAnimation(1f, 0f);
					alphaAnim.setDuration(SNOW_DURATION);
					int endY = getBounds().bottom - snowFlakeViews[index].getBounds().bottom;
					
					TranslateAnimation tr = new TranslateAnimation(0f, 0f, 0f, endY);
					tr.setDuration(SNOW_DURATION);
					tr.setInterpolator(new DecelerateInterpolator());
					snowFlakeViews[index].setAlpha(AView.FULL_OPAQUE);
					
					set.addAnimation(tr);
					set.addAnimation(alphaAnim);
					snowFlakeViews[index].startAnimation(set);
				}
			});
			snowFlakeViews[i].startAnimation(fadeInAnimation);
		}
		this.invalidate();
		
	}
	
	public void setRoomChangeParam(boolean roomUp, int from, int to){
		roomChangeView.setParam(roomUp, from, to);
		roomChangeView.setGravity(MyGravity.TOP|MyGravity.CENTER_HORIZONTAL);
		roomChangeView.updateBounds();
	}
	
}
