package com.candy.futon.util;

import android.view.animation.Animation;
import android.view.animation.Animation.AnimationListener;
import android.view.animation.TranslateAnimation;

import com.andy.canvasgame.ui.AView;
import com.candy.futon.view.HandPokerView;
import com.candy.futon.view.SlingPointerButtonGroupView;
import com.candy.futon.view.ViewPosition;

public class FirstSlingPointerHelper {

	private final static long MOVE_DURATION = 2000;
	
	public static void startAnimation(final SlingPointerButtonGroupView buttonGroup, final HandPokerView handPokerView){
		buttonGroup.getChilds().get(2).setAlpha(0);
		TranslateAnimation tr2Left = new TranslateAnimation(0, -ViewPosition.getInstance().SLING_POINTER_MOVE_X, 0, 0);
		tr2Left.setDuration(MOVE_DURATION);
		
		final TranslateAnimation tr2Right= new TranslateAnimation(-ViewPosition.getInstance().SLING_POINTER_MOVE_X, 0, 0, 0);
		tr2Right.setDuration(MOVE_DURATION);
		tr2Right.setStartOffset(500);
//		tr2Left.setFillAfter(true);
		
		tr2Left.setAnimationListener(new AnimationListener() {
			
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
				if(buttonGroup.getAlpha() == 0){
					return;
				}
				buttonGroup.startAnimation(tr2Right);
				buttonGroup.fakeSlingPokerView();
				buttonGroup.getChilds().get(0).setAlpha(0);
				buttonGroup.getChilds().get(2).setAlpha(AView.FULL_OPAQUE);
			}
		});
		tr2Right.setAnimationListener(new AnimationListener() {
			
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
				if(buttonGroup.getAlpha() == 0){
					return;
				}
				buttonGroup.fakeSlingPokerView();
				buttonGroup.onAnimationEnd();
			}
		});
		buttonGroup.startAnimation(tr2Left);
	}
	
}
