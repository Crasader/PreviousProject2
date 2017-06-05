package com.candy.futon.util;

import android.view.animation.AlphaAnimation;
import android.view.animation.Animation;
import android.view.animation.Animation.AnimationListener;

import com.candy.futon.view.ImageNumberAView;

public class CoinChangeAnimationHelper {
	
	private static final long STEP_DURATION = 50;
	
	private static final long TOTAL_TIME = 2000;
	
	private static final long PREFER_COUNT = TOTAL_TIME/ STEP_DURATION;
	
	private static int preferedStepCoin;
	
	public static void startAnimation(final ImageNumberAView numberView, final int currentCoin, final int deltaCoin, final AnimationListener listener){
		
		if(deltaCoin > 0 && numberView.getNumber()>= currentCoin + deltaCoin){
			numberView.setNumber(currentCoin + deltaCoin);
			numberView.invalidate();
			listener.onAnimationEnd(null);
			return;
		}
		
		if(deltaCoin<0 && numberView.getNumber()<= currentCoin+deltaCoin){
			numberView.setNumber(currentCoin + deltaCoin);
			numberView.invalidate();
			listener.onAnimationEnd(null);
			return;
		}
		AlphaAnimation anim = new AlphaAnimation(1f, 1f);
		anim.setDuration(STEP_DURATION);
		anim.setAnimationListener(new AnimationListener() {
			
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
				startAnimation(numberView, currentCoin, deltaCoin, listener);
			}
		});
		preferedStepCoin =  (int) (deltaCoin/PREFER_COUNT);
		if(deltaCoin> 0 && numberView.getNumber() + preferedStepCoin > currentCoin + deltaCoin){
			preferedStepCoin = currentCoin + deltaCoin - numberView.getNumber();
		}else if(deltaCoin< 0 && numberView.getNumber() + preferedStepCoin < currentCoin + deltaCoin){
			preferedStepCoin = currentCoin + deltaCoin - numberView.getNumber();
		}
		numberView.setNumber(numberView.getNumber() + preferedStepCoin);
		numberView.startAnimation(anim);
		numberView.invalidate();
		listener.onAnimationEnd(null);
	}
	
	private CoinChangeAnimationHelper(){
		
	}
	
}
