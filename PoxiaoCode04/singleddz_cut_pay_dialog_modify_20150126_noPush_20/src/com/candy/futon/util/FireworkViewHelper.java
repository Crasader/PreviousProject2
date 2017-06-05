package com.candy.futon.util;

import android.graphics.Point;
import android.graphics.Rect;
import android.view.animation.AlphaAnimation;
import android.view.animation.Animation;
import android.view.animation.Animation.AnimationListener;
import android.view.animation.LinearInterpolator;
import android.view.animation.ScaleAnimation;

import com.andy.canvasgame.ui.AView;
import com.candy.futon.view.ImageAView;
import com.poxiao.ddz.standalone.R;

public class FireworkViewHelper {

	private static long SCALE_DURATION = 1000;
	
	private static long FADE_OUT_DURATION = 500;
	
	public static int[] FIRE_WORK_DRAW_ID = new int[]{R.drawable.firework_blue, R.drawable.fireworks_orange};
	
	public interface FireworkEndListener{
		public void onEnd();
	}
	
	/**
	 * 已points坐标为中心点，重新设置fireworks的bound rect
	 * @param fireworks
	 * @param points
	 */
	public static void updatePosition(ImageAView[] fireworks, Point[] points){
		for(int i=0;i<fireworks.length && i< points.length;i++){
			ImageAView firework = fireworks[i];
			
			Point point = points[i];
			Rect rect = firework.getBounds();
			int left, top;
			left = point.x - rect.width() /2;
			top = point.y - rect.height() /2;
			firework.getBounds().set(left, top, left+rect.width(), top + rect.height());
		}
	}
	
	public static void startFireworks(ImageAView[] fireworks, FireworkEndListener listener){
		startFirework(fireworks, 0, listener);
	}
	
	private static void startFirework(final ImageAView[] fireworks, final int index, final FireworkEndListener listener){
		if(index >= fireworks.length){
			return;
		}
		ImageAView firework = fireworks[index];
		firework.setAlpha(AView.FULL_OPAQUE);
		ScaleAnimation scaleAnimation = new ScaleAnimation(0.1f, 1f, 0.1f, 1f, firework.getBounds().centerX(), firework.getBounds().centerY());
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
				AlphaAnimation fadeOutAnim = new AlphaAnimation(1f, 0f);
				fadeOutAnim.setInterpolator(new LinearInterpolator());
				fadeOutAnim.setDuration(FADE_OUT_DURATION);
				
				
				fadeOutAnim.setAnimationListener(new AnimationListener() {
					
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
						
						ImageAView firework = fireworks[index];
						firework.setAlpha(0);
						firework.invalidate();
						if(index == fireworks.length - 1){
							listener.onEnd();
						}
					}
				});
				
				ImageAView firework = fireworks[index];
				firework.startAnimation(fadeOutAnim);
				startFirework(fireworks, index + 1, listener);
			}
		});
		firework.startAnimation(scaleAnimation);
	}
	
}
