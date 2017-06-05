package com.candy.futon.view;


import android.content.Context;

import com.andy.canvasgame.service.GameConstantsService;
import com.andy.canvasgame.ui.OnClickListener;
import com.andy.canvasgame.util.AViewUtil;
import com.andy.canvasgame.util.BitmapSpliter;
import com.andy.canvasgame.util.MyGravity;
import com.candy.futon.activitys.GameActivity;
import com.candy.futon.domain.GameConfig;
import com.candy.futon.util.BaoxiangUtil;
import com.poxiao.ddz.standalone.R;

public class BaoxiangView extends ImageAView {

	private PicButtonView baoxiangBtn;
	private ImageNumberAView currentNum;
	private ImageNumberAView maxNum;
	private ImageNumberAView baoxiangNum;
	private ImageAView numBg;
	private ImageAView gangView;
	
	private int numMarginTop = 30;
	private int numMarginLeft = 15;
	
	public BaoxiangView(Context context, OnClickListener onClickListener) {
		super(context, R.drawable.baoxiang_box);
		baoxiangBtn = new PicButtonView(context, R.drawable.baoxiang_normal, -1, onClickListener);
		baoxiangBtn.setHoverDrawable(R.drawable.baoxiang_hover);
		currentNum = new ImageNumberAView(context, R.drawable.baoxiang_progress_num, 10, BitmapSpliter.HORIZONTAL);
		maxNum = new ImageNumberAView(context, R.drawable.baoxiang_progress_num, 10, BitmapSpliter.HORIZONTAL);
		baoxiangNum = new ImageNumberAView(context, R.drawable.baoxiang_number, 10, BitmapSpliter.HORIZONTAL);
		
		numBg = new ImageAView(context, R.drawable.baoxiang_num_bg);
		this.addChild(baoxiangBtn);
		addChild(currentNum);
		addChild(maxNum);
		addChild(numBg);
		numBg.addChild(baoxiangNum);
		gangView =new ImageAView(context, R.drawable.baoxiang_text_gang);
		addChild(gangView);
		numMarginLeft *= GameConstantsService.getInstance().getDensityScale();
		numMarginTop *= GameConstantsService.getInstance().getDensityScale();
		
	}
	
	@Override
	public void updateBounds() {
		baoxiangNum.setNumber(BaoxiangUtil.getBaoxiangCount(GameActivity.getInstance()));
		currentNum.setNumber(GameConfig.getInstance().getCurrentReceivePrizeCurrent(GameActivity.getInstance()));
		maxNum.setNumber(5);
		numBg.setGravity(MyGravity.RIGHT|MyGravity.TOP);
		baoxiangNum.setGravity(MyGravity.CENTER);
		baoxiangBtn.setGravity(MyGravity.BOTTOM|MyGravity.RIGHT);
		
		currentNum.setGravity(MyGravity.LEFT|MyGravity.TOP);
		currentNum.setMargin(numMarginLeft, numMarginTop, 0, 0);
		gangView.getBounds().set(0, 0, gangView.getBounds().width(), gangView.getBounds().height());
		maxNum.getBounds().set(0,0, maxNum.getBounds().width(), maxNum.getBounds().height());
		AViewUtil.toRightOf(gangView, currentNum, this);
		AViewUtil.toRightOf(maxNum, gangView, this);
		
		invalidate();
	}

	

}
