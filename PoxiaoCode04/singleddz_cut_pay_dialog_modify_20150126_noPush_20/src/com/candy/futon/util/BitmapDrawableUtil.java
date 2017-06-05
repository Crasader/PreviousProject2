package com.candy.futon.util;

import android.content.Context;
import android.graphics.drawable.BitmapDrawable;

import com.candy.futon.view.GameUIResource;

public class BitmapDrawableUtil {

	public static BitmapDrawable getBitmapDrawable(Context context, int drawId){
		return new BitmapDrawable(context.getResources(), GameUIResource.getInstance().loadBitMap(context.getResources(), drawId));
	}
	private BitmapDrawableUtil(){
		
	}
	
}
