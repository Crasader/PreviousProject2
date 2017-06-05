package com.candy.futon.view;

import android.content.Context;

import com.andy.canvasgame.service.GameConstantsService;
import com.andy.canvasgame.ui.AView;
import com.andy.canvasgame.util.MyGravity;

public class CoinView extends ImageAView {

	private int MARGIN_TOP = 5;
	
	public CoinView(Context context, int drawId, AView playerView, AView parent, boolean isLeft) {
		
		super(context, drawId);
		this.setParent(parent);
		MARGIN_TOP *= GameConstantsService.getInstance().getDensityScale();
		int marginTop = playerView.getBounds().bottom + MARGIN_TOP;
		if(isLeft){
			this.setMargin(playerView.getBounds().left, marginTop, 0, 0);
		}else{
			this.setGravity(MyGravity.RIGHT | MyGravity.TOP);
			this.setMargin(0, marginTop, parent.getBounds().right - playerView.getBounds().right, 0);
		}
	}
	
	

}
