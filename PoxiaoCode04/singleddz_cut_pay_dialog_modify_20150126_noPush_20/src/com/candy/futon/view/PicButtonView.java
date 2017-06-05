package com.candy.futon.view;

import android.content.Context;

import com.andy.canvasgame.ui.OnClickListener;
import com.andy.canvasgame.view.AbstractPicButtonView;
import com.candy.futon.util.BitmapDrawableUtil;

/**
 * 图片按钮
 * @author Andy
 *
 */
public class PicButtonView extends AbstractPicButtonView {

	
	
	/**
	 * 
	 * @param context
	 * @param bgDrawableId
	 * @param textDrawableId 小于0表示没有这个图
	 * @param onClickListener
	 */
	public PicButtonView(Context context, int bgDrawableId, int textDrawableId, OnClickListener onClickListener){
		super(context, bgDrawableId, textDrawableId, onClickListener);
	}
	
	
	@Override
	public void setButtonBgDrawable(int bgDrawId){
		this.mButtonBgDrawable = BitmapDrawableUtil.getBitmapDrawable(mContext, bgDrawId);
	}
	
	@Override
	public void setDisableDrawable(int drawId){
		if(drawId == 0){
			mButtonDisableDrawable = null;
		}else{
			mButtonDisableDrawable = BitmapDrawableUtil.getBitmapDrawable(mContext, drawId);
		}
	}
	
	@Override
	public void setTextDrawable(int drawId){
		this.mTextDrawable = BitmapDrawableUtil.getBitmapDrawable(mContext, drawId);
		this.updateBounds();
	}
	
	@Override
	public void setTextDiableDrawable(int drawId){
		this.mTextDisableDrawable = BitmapDrawableUtil.getBitmapDrawable(mContext, drawId);
		this.updateBounds();
	}
	
	@Override
	public void setHoverDrawable(int drawId){
		if(drawId == 0){
			mButtonHoverDrawable = null;
		}else{
			mButtonHoverDrawable = BitmapDrawableUtil.getBitmapDrawable(mContext, drawId);
		}
	}
	
	
}
