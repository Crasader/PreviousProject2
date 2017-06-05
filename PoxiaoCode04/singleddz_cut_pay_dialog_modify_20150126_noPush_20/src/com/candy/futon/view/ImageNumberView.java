package com.candy.futon.view;

import java.util.ArrayList;

import android.content.Context;
import android.content.res.TypedArray;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.util.AttributeSet;
import android.view.View;

import com.andy.canvasgame.util.BitmapSpliter;
import com.poxiao.ddz.standalone.R;

public class ImageNumberView extends View {
	
	private int numberDrawableId;
	
	private int number;
	
	private int numberInDrawable = 10;
	
	private int direction = BitmapSpliter.HORIZONTAL;
	
	private Bitmap[] numberBitmaps;
	
	private Bitmap addBitmap;
	
	private Bitmap subBitmap;
	
	private boolean showAddIcon;
	
	private ArrayList<Integer> numbers = new ArrayList<Integer>();
	
	private Paint paint;
	
	public ImageNumberView(Context context) {
		super(context);
	}

	public ImageNumberView(Context context, AttributeSet attrs){
		super(context, attrs);
		TypedArray a = context.obtainStyledAttributes(attrs,
				R.styleable.ImageNumberView);
			 
		final int N = a.getIndexCount();
		for (int i = 0; i < N; ++i)
		{
		    int attr = a.getIndex(i);
		    
		    if(attr== R.styleable.ImageNumberView_numberDrawableId){
		    	 this.numberDrawableId = a.getResourceId(attr, 0);
		    }else if(attr==R.styleable.ImageNumberView_number){
		    	 this.number = a.getInteger(attr, 0);
		    }else if(attr==R.styleable.ImageNumberView_numberInDrawable){
		    	this.numberInDrawable = a.getInteger(attr, 10);
		    }else if(attr==R.styleable.ImageNumberView_drawableDirection){
		    	this.direction = a.getInteger(attr, BitmapSpliter.HORIZONTAL);
		    }

		}
		a.recycle();
		init();
		paint = new Paint();
		paint.setAntiAlias(true);
	}
	
	private void init(){
		
		if(numberDrawableId == 0){
			return ;
		}
		numbers.clear();
		String temp = String.valueOf(Math.abs(number));
		for(int i=0;i<temp.length();i++){
			numbers.add(Integer.parseInt(String.valueOf(temp.charAt(i))));
		}
		Bitmap[] bitmapArray = GameUIResource.getInstance().loadBitmapArrayByDensity(getResources(), numberDrawableId, numberInDrawable, direction);
		addBitmap = GameUIResource.getInstance().loadBitMap(getResources(), R.drawable.add);
		subBitmap = GameUIResource.getInstance().loadBitMap(getResources(), R.drawable.sub);
		int size = numbers.size();
		numberBitmaps = new Bitmap[size];
		for(int i=0;i<size;i++){
			numberBitmaps[i] = bitmapArray[numbers.get(i)];
		}
	}
	
	@Override
	protected void onDraw(Canvas canvas) {
		super.onDraw(canvas);
		if(numberDrawableId == 0){
			return;
		}
		int left =0;
		int top = 0;
		
		Bitmap addOrSub = null;
		if(showAddIcon && number>0){
			addOrSub = addBitmap;
		}else if(number<0){
			addOrSub = subBitmap;
		}
		
		if(addOrSub != null){
			int tempTop = (numberBitmaps[0].getHeight() - addOrSub.getHeight())/2;
			canvas.drawBitmap(addOrSub, left, tempTop, paint);
			left += addOrSub.getWidth();
		}
		
		for(int i=0;i<numberBitmaps.length;i++){
			canvas.drawBitmap(numberBitmaps[i], left, top, paint);
			left += numberBitmaps[i].getWidth();
		}
	}
	
	

	public void setNumberDrawableId(int numberDrawableId) {
		this.numberDrawableId = numberDrawableId;
		init();
	}

	public void setNumber(int number) {
		this.number = number;
		init();
	}

	public void setShowAddIcon(boolean showAddIcon) {
		this.showAddIcon = showAddIcon;
	}
	
	

}
