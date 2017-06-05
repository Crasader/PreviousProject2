package com.candy.futon.util;

import android.view.animation.Animation;
import android.view.animation.Animation.AnimationListener;
import android.view.animation.TranslateAnimation;

import com.andy.canvasgame.ui.AView;
import com.candy.futon.view.PlayResultPointImageNumberAView;

public class PlayResultPointAnimationHelper {

	public interface PlayResultPointAnimationListener{
		
		public void onEnd();
		
	}
	
	private static long DURATION = 1000;
	
	public static void startAnimation(PlayResultPointImageNumberAView[] views, int yDelta, final PlayResultPointAnimationListener listener){
		boolean firstOne = true;
		for(PlayResultPointImageNumberAView view:views){
			view.setAlpha(AView.FULL_OPAQUE);
			TranslateAnimation tr = new TranslateAnimation(0,0,0,yDelta);
			tr.setDuration(DURATION);
			if(firstOne){
				firstOne = false;
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
						listener.onEnd();
					}
				});
			}
			view.startAnimation(tr);
			view.invalidate();
		}
	}
	
}
