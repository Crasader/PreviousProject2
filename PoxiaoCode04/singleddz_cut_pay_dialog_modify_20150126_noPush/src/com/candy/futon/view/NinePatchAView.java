package com.candy.futon.view;

import android.content.Context;
import android.graphics.Bitmap;

import com.andy.canvasgame.view.AbstractNinePatchAView;

public class NinePatchAView extends AbstractNinePatchAView {

	public NinePatchAView(Context context, int drawId) {
		super(context, drawId);
		
	}

	@Override
	protected Bitmap get9PatchBg(Context context, int ninePatchId) {
		return GameUIResource.getInstance().loadBitMapWithOutScale(context.getResources(), ninePatchId);
	}

}
