package com.candy.futon.view;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.drawable.BitmapDrawable;
import android.util.Log;

import com.andy.canvasgame.view.AbstractImageAView;
import com.candy.futon.util.BitmapDrawableUtil;

public class ImageAView extends AbstractImageAView {
	
	public ImageAView(Context context, int drawId){
		super(context, drawId);
	}
	
	@Override
	protected BitmapDrawable initBitmapDrawable(Context context, int drawId) {
		return BitmapDrawableUtil.getBitmapDrawable(context, drawId);
	}

}
