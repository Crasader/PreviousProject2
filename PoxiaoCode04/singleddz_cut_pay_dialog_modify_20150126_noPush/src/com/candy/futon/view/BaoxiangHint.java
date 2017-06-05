package com.candy.futon.view;

import android.content.Context;
import android.view.animation.AlphaAnimation;
import android.view.animation.Animation;
import android.view.animation.Animation.AnimationListener;

import com.andy.canvasgame.service.GameConstantsService;
import com.andy.canvasgame.ui.AView;
import com.andy.canvasgame.util.AViewUtil;
import com.andy.canvasgame.util.MyGravity;
import com.andy.canvasgame.view.LimitTextAView;
import com.poxiao.ddz.standalone.R;

public class BaoxiangHint extends ImageAView {

	private int TEXT_HEIGHT = 18;
	private LimitTextAView firstLine;
	private LimitTextAView secondLine;
	
	private String hintStr;
	
	private int strEndIndex;
	
	public BaoxiangHint(Context context) {
		super(context, R.drawable.baoxiang_hint_box);
		TEXT_HEIGHT *= GameConstantsService.getInstance().getDensityScale();
		firstLine = new LimitTextAView();
		firstLine.setLimitHeight(TEXT_HEIGHT);
		secondLine = new LimitTextAView();
		secondLine.setLimitHeight(TEXT_HEIGHT);
		addChild(firstLine);
		addChild(secondLine);
		
	}
	
	@Override
	public void updateBounds() {
		firstLine.setText(hintStr.substring(0, hintStr.length()/2));
		strEndIndex = hintStr.length()/2;
		if(firstLine.getBounds().width() + 2 * 8*GameConstantsService.getInstance().getDensityScale() >getBounds().width()){
			while(firstLine.getBounds().width() + 2 * 8*GameConstantsService.getInstance().getDensityScale() >getBounds().width()){
				strEndIndex -=1;
				firstLine.setText(hintStr.substring(0,strEndIndex));
			}
		}else{
			while(firstLine.getBounds().width() + 2 * 8*GameConstantsService.getInstance().getDensityScale() +4 <getBounds().width()){
				strEndIndex +=1;
				firstLine.setText(hintStr.substring(0,strEndIndex));
			}
			strEndIndex -=1;
		}
		firstLine.setText(hintStr.substring(0,strEndIndex));
		secondLine.setText(hintStr.substring(strEndIndex));
		firstLine.setGravity(MyGravity.LEFT|MyGravity.TOP);
		firstLine.setMargin((int)(8*GameConstantsService.getInstance().getDensityScale()), (int)(12*GameConstantsService.getInstance().getDensityScale()), 0, 0);
		AViewUtil.below(secondLine, firstLine, MyGravity.LEFT);
		invalidate();
	}
	
	public void setHintStr(String hintStr) {
		this.hintStr = hintStr;
		updateBounds();
		setAlpha(AView.FULL_OPAQUE);
		for(AView view:mChilds){
			view.setAlpha(AView.FULL_OPAQUE);
		}
		AlphaAnimation alphaAnimation = new AlphaAnimation(1.0f, 0f);
		alphaAnimation.setDuration(1000);
		alphaAnimation.setStartOffset(2000);
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
				setAlpha(0);
				getParent().invalidate();
				
			}
		});
		startAnimation(alphaAnimation);
		
	}
	
	@Override
	public void startAnimation(Animation ani) {
		for(AView view:mChilds){
			view.startAnimation(ani);
		}
		super.startAnimation(ani);
	}

}
