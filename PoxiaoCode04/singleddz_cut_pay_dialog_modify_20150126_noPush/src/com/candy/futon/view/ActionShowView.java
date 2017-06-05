package com.candy.futon.view;

import android.content.Context;
import android.graphics.drawable.BitmapDrawable;

public class ActionShowView extends ImageAView{
	
	public ActionShowView(Context context, int drawId) {
		super(context, drawId);
	}

	@Override
	public void setDrawId(Context context, int drawId) {
		mBitmapDrawable = new BitmapDrawable(context.getResources(), GameUIResource.getInstance().loadBitMap(context.getResources(), drawId));
	}
}
