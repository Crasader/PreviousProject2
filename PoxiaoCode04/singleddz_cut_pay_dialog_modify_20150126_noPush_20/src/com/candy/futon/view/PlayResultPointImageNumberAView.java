package com.candy.futon.view;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.drawable.BitmapDrawable;

import com.andy.canvasgame.view.AbstractImageNumberAView;
import com.candy.futon.util.BitmapDrawableUtil;
import com.poxiao.ddz.standalone.R;

public class PlayResultPointImageNumberAView extends AbstractImageNumberAView {

	
	
	public PlayResultPointImageNumberAView(Context context, int numberDrawId, int numberInBitmap, int direction){
		super(context, numberDrawId, numberInBitmap, direction);
	}
	
	

	@Override
	protected BitmapDrawable initSubDrawable(Context context) {
		return BitmapDrawableUtil.getBitmapDrawable(context, R.drawable.sliver_blue_sub);
	}



	@Override
	protected BitmapDrawable initAddDrawable(Context context) {
		return BitmapDrawableUtil.getBitmapDrawable(context, R.drawable.yello_add);
	}



	@Override
	protected void initNumberDrawables(Context context) {
		showAddIcon = true;
		Bitmap[] bitmapArray = GameUIResource.getInstance().loadBitMapArray(context.getResources(), numberDrawId, numberInBitmap, direction);
		numberDrawables = new BitmapDrawable[bitmapArray.length];
		for(int i=0;i<bitmapArray.length;i++){
			numberDrawables[i] = new BitmapDrawable(context.getResources(), bitmapArray[i]);
		}
	}

}
