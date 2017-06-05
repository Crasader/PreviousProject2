package com.candy.futon.view;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.PorterDuff;
import android.graphics.PorterDuffXfermode;
import android.graphics.Rect;
import android.graphics.drawable.NinePatchDrawable;



public class ProgressAView extends NinePatchAView{

	protected NinePatchDrawable ninePatchProgressDrawable;
	
	private Rect progressRect = new Rect();

	private Paint paint = new Paint();
	
	public ProgressAView(Context context, int drawId, int progressDrawableId, int width) {
		super(context, drawId);
		this.getBounds().set(0,0,width, this.getBounds().height());
		Bitmap bitmap = get9PatchBg(context, progressDrawableId);
		ninePatchProgressDrawable = new NinePatchDrawable(context.getResources(), bitmap, bitmap.getNinePatchChunk(), new Rect(), null);
		ninePatchProgressDrawable.getPaint().setXfermode(new PorterDuffXfermode(PorterDuff.Mode.SRC_IN));  
		paint.setFilterBitmap(false);
		
	}
	
	public void setProgress(int progress){
		if(progress <=0){
			this.invalidate();
		}else{
			if(progress > 100){
				progress = progress - 100;
			}
			progressRect.set(getBounds().left, getBounds().top, (int) (getBounds().left + getBounds().width() * (progress * 1.0/100)), getBounds().bottom);
			this.invalidate();
		}
	}

	@Override
	protected void doDraw(Canvas canvas) {
		super.doDraw(canvas);
		int sc = canvas.saveLayer(getBounds().left, getBounds().top, getBounds().right, getBounds().bottom, null,  
                Canvas.MATRIX_SAVE_FLAG | Canvas.CLIP_SAVE_FLAG  
                        | Canvas.HAS_ALPHA_LAYER_SAVE_FLAG  
                        | Canvas.FULL_COLOR_LAYER_SAVE_FLAG  
                        | Canvas.CLIP_TO_LAYER_SAVE_FLAG);  
        canvas.drawRect(progressRect, paint);  
		ninePatchProgressDrawable.setBounds(getBounds()); 
		ninePatchProgressDrawable.draw(canvas);
        canvas.restoreToCount(sc); 
	}
}