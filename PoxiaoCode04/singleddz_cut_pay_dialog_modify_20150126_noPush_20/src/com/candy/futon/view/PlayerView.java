package com.candy.futon.view;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Rect;
import android.graphics.drawable.BitmapDrawable;
import android.util.Log;
import android.view.MotionEvent;

import com.andy.canvasgame.service.GameConstantsService;
import com.andy.canvasgame.ui.AView;
import com.andy.canvasgame.ui.OnClickListener;
import com.andy.canvasgame.util.MyGravity;
import com.andy.pokergames.ddz.ai.ddzai.domain.DdzAIPlayer;
import com.candy.futon.domain.PlayerInfo;
import com.poxiao.ddz.standalone.R;

public class PlayerView extends AView{
	
	private final static String TAG = "PlayerView";
	
	private static BitmapDrawable mPlayerBgDrawable;

	private static BitmapDrawable mFarmerDrawable;
	
	private static BitmapDrawable mLoadDrawable;
	
	private BitmapDrawable mHeadDrawable;
	
	private static Paint paint;
	
	private DdzAIPlayer player;
	
	private DdzAIPlayer currentPlayer;
	
	private Context context;
	
	private Rect bgRect = new Rect();
	
	private Rect headRect = new Rect();
	
	private Rect textRect = new Rect();
	
	private final static int MARGIN_X = 12;
	
	private final static int MARGIN_TOP = 56;
	
	private final static int MARGIN_BOTTOM = 146;
	
	private OnClickListener mOnClickListener;
	
	private Paint getPaint(){
		if(paint == null){
			paint = new Paint();
			paint.setTextAlign(Paint.Align.LEFT);
			paint.setAntiAlias(true);
//			paint.setFakeBoldText(true);
			paint.setColor(0xFFFFFFFF);
			paint.setShadowLayer(8, 8, 8, Color.DKGRAY);
			paint.setTextSize(22f * GameConstantsService.getInstance().getDensityScale());
		}
		return paint;
	}
	
	private BitmapDrawable getPlayerBgDrawable(){
		if(mPlayerBgDrawable == null){
			mPlayerBgDrawable = new BitmapDrawable(context.getResources(), GameUIResource.getInstance().loadBitMap(context.getResources(), R.drawable.head_box));
		}
		return mPlayerBgDrawable;
	}
	
	public Rect getPlayerBgBounds(){
		return bgRect;
	}
	
	private BitmapDrawable getFaramerDrawable(){
		if(mFarmerDrawable == null){
			mFarmerDrawable = new BitmapDrawable(context.getResources(), GameUIResource.getInstance().loadBitMap(context.getResources(), R.drawable.farmer));
		}
		return mFarmerDrawable;
	}
	
	private BitmapDrawable getLoadDrawable(){
		if(mLoadDrawable == null){
			mLoadDrawable = new BitmapDrawable(context.getResources(), GameUIResource.getInstance().loadBitMap(context.getResources(), R.drawable.load));
		}
		return mLoadDrawable;
	}

	public PlayerView(AView parent, DdzAIPlayer player, DdzAIPlayer currentPlayer, PlayerInfo playerInfo, Context context){
		this.setParent(parent);
		this.player = player;
		this.context = context;
		this.currentPlayer = currentPlayer;
		BitmapDrawable bgDrawable = this.getPlayerBgDrawable();
		textRect.set(0, 0, (int)getPaint().measureText(player.getName()), (int)getPaint().getFontSpacing());
		int width = textRect.width()>bgDrawable.getIntrinsicWidth()?textRect.width():bgDrawable.getIntrinsicWidth();
		this.setBounds(new Rect(0,0, width, bgDrawable.getIntrinsicHeight()));
		
		int marginx = (int) (MARGIN_X * GameConstantsService.getInstance().getDensityScale());
		int marginTop = (int) (MARGIN_TOP * GameConstantsService.getInstance().getDensityScale());
		int marginBottom = (int) (MARGIN_BOTTOM * GameConstantsService.getInstance().getDensityScale());
		if(player == currentPlayer){
			this.setGravity(MyGravity.BOTTOM|MyGravity.LEFT);
			this.setMargin(marginx, 0, 0, marginBottom);
			bgRect.set(getBounds().left, getBounds().top, getBounds().left + bgDrawable.getIntrinsicWidth(), getBounds().top +bgDrawable.getIntrinsicHeight());
			textRect.set(getBounds().left, getBounds().bottom - textRect.height(), getBounds().left + textRect.width(), getBounds().bottom);
		}else if(player == currentPlayer.getTable().getNextPlayer(currentPlayer)){
			this.setGravity(MyGravity.TOP|MyGravity.RIGHT);
			this.setMargin(0, marginTop, marginx, 0);
			bgRect.set(getBounds().right - bgDrawable.getIntrinsicWidth(), getBounds().top, getBounds().right, getBounds().top +bgDrawable.getIntrinsicHeight());
			textRect.set(getBounds().right - textRect.width(), getBounds().bottom - textRect.height(), getBounds().right, getBounds().bottom);
		}else{
			this.setGravity(MyGravity.TOP|MyGravity.LEFT);
			this.setMargin(marginx, marginTop, 0, 0);
			bgRect.set(getBounds().left, getBounds().top, getBounds().left + bgDrawable.getIntrinsicWidth(), getBounds().top +bgDrawable.getIntrinsicHeight());
			textRect.set(getBounds().left, getBounds().bottom - textRect.height(), getBounds().left + textRect.width(), getBounds().bottom);
		}
		Log.d(TAG, "textRect"+ textRect);
		Log.d(TAG, "bounds"+this.getBounds());
		getFaramerDrawable();
		getLoadDrawable();
		this.mHeadDrawable = new BitmapDrawable(context.getResources(), GameUIResource.getInstance().loadBitMap(context.getResources(), playerInfo.getHeadDrawId()));
		
		
		
	}
	
	@Override
	protected void doDraw(Canvas canvas) {
		BitmapDrawable bgDrawable = this.getPlayerBgDrawable();
		
		bgDrawable.setBounds(bgRect);
		bgDrawable.setAlpha(mAlpha);
		bgDrawable.draw(canvas);
		
		BitmapDrawable headDrawable;
		if(player.getTable().getLoad() == null){
			headDrawable = this.mHeadDrawable;
		}
		else if(player.isLoad()){
			headDrawable = getLoadDrawable();
		}else{
			headDrawable = getFaramerDrawable();
		}
		headRect.set(bgRect.centerX() - (headDrawable.getIntrinsicWidth()/2),
				bgRect.centerY() - headDrawable.getIntrinsicHeight()/2,
				bgRect.centerX() + headDrawable.getIntrinsicWidth()/2,
				bgRect.centerY() + headDrawable.getIntrinsicHeight()/2);
		headDrawable.setBounds(headRect);
		headDrawable.setAlpha(mAlpha);
		headDrawable.draw(canvas);
//		FontMetrics fm = getPaint().getFontMetrics();  
//		canvas.drawText(player.getName(), textRect.left, textRect.bottom - fm.descent, getPaint());
	}

	@Override
	protected boolean doOnTouchEvent(MotionEvent event) {
		if(isOnclick(event)){
			if(this.mOnClickListener != null){
				this.mOnClickListener.onClick(this, event);
			}
			return true;
		}
		return false;
	}

	@Override
	public void onDestroy() {
		mFarmerDrawable = null;
		mLoadDrawable = null;
		mPlayerBgDrawable = null;
	}

	public void setPlayer(DdzAIPlayer player, DdzAIPlayer currentPlayer, PlayerInfo playerInfo){
		this.player = player;
		this.currentPlayer = currentPlayer;
		this.mHeadDrawable = new BitmapDrawable(context.getResources(), GameUIResource.getInstance().loadBitMap(context.getResources(), playerInfo.getHeadDrawId()));
	}
	
	public void setOnClickListener(OnClickListener onClickListener) {
		this.mOnClickListener = onClickListener;
	}
}
