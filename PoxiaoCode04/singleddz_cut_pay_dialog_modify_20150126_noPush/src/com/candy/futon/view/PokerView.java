package com.candy.futon.view;

import java.util.concurrent.ConcurrentHashMap;

import android.content.Context;
import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Rect;
import android.graphics.drawable.BitmapDrawable;
import android.view.MotionEvent;

import com.andy.canvasgame.service.GameConstantsService;
import com.andy.canvasgame.ui.AView;
import com.andy.canvasgame.ui.OnClickListener;
import com.andy.pokergames.ddz.ai.ddzai.domain.Poker;
import com.andy.pokergames.ddz.ai.ddzai.domain.Suit;
import com.poxiao.ddz.standalone.R;

public class PokerView extends AView{

	private static BitmapDrawable mBgDrawable_1;

	private static BitmapDrawable mBgDrawable_2;
	
	private static BitmapDrawable mBgDrawable_3;
	
	private static BitmapDrawable mJoker_1;
	
	private static BitmapDrawable mJoker_2;
	
	private static BitmapDrawable mJoker_3;
	
	private static BitmapDrawable mSmallJoker_1;
	
	private static BitmapDrawable mSmallJoker_2;
	
	private static BitmapDrawable mSmallJoker_3;
	
	private static BitmapDrawable mBgDrawable_touched;
	
	private static ConcurrentHashMap<String, BitmapDrawable> mDrawableCache;
	
	private Poker mPoker;
	
	private int mSize;
	
	private Resources mResources;
	
	private final static int POKER_NUM_PADDING_LEFT_1 = 3;
	
	private final static int POKER_NUM_PADDING_TOP_1 = 5;
	
	private final static int POKER_NUM_PADDING_LEFT_2 = 1;
	
	private final static int POKER_NUM_PADDING_TOP_2 = 6;
	
	private final static int POKER_NUM_PADDING_LEFT_3 = 2;
	
	private final static int POKER_NUM_PADDING_TOP_3 = 6;
	
	private final static int SUIT_PADDING_LEFT_1 = 8;
	
	private final static int SUIT_PADDING_TOP_1 = 32;
	
	private final static int SUIT_PADDING_LEFT_2 = 6;
	
	private final static int SUIT_PADDING_TOP_2 = 32;
	
	private final static int SUIT_PADDING_LEFT_3 = 5;
	
	private final static int SUIT_PADDING_TOP_3 = 32;
	
	private Rect mPokerNumBounds = new Rect();
	
	private Rect mSuitBounds = new Rect();
	
	private OnClickListener mOnClickListener;
	
	private boolean isTouched = false;
	
	private boolean isFirstTouch = false;

	public interface FirstTouchListener {
        /**
         * Called when a view has been clicked.
         *
         * @param v The view that was clicked.
         */
        void onFirstTouch(AView v);
    }
	
	private FirstTouchListener firstTouchListener  = null;
	
	public static void initDrawables(Resources resources){
		if(mBgDrawable_1 == null){
			mBgDrawable_1 = new BitmapDrawable(resources, GameUIResource.getInstance().loadBitMap(resources, R.drawable.poker_bg_1));
			mBgDrawable_2 = new BitmapDrawable(resources, GameUIResource.getInstance().loadBitMap(resources, R.drawable.poker_bg_2));
			mBgDrawable_3 = new BitmapDrawable(resources, GameUIResource.getInstance().loadBitMap(resources, R.drawable.poker_bg_2));
			mJoker_1 = new BitmapDrawable(resources, GameUIResource.getInstance().loadBitMap(resources, R.drawable.joker_1));
			mJoker_2 = new BitmapDrawable(resources, GameUIResource.getInstance().loadBitMap(resources, R.drawable.joker_2));
			mJoker_3 = new BitmapDrawable(resources, GameUIResource.getInstance().loadBitMap(resources, R.drawable.joker_2));
			mSmallJoker_1 = new BitmapDrawable(resources, GameUIResource.getInstance().loadBitMap(resources, R.drawable.small_joker_1));
			mSmallJoker_2 = new BitmapDrawable(resources, GameUIResource.getInstance().loadBitMap(resources, R.drawable.small_joker_2));
			mSmallJoker_3 = new BitmapDrawable(resources, GameUIResource.getInstance().loadBitMap(resources, R.drawable.small_joker_2));
			mDrawableCache = new ConcurrentHashMap<String, BitmapDrawable>();
			mBgDrawable_touched = new BitmapDrawable(resources, GameUIResource.getInstance().loadBitMap(resources, R.drawable.poker_bg_1_touched));
		}
	}
	
	public PokerView(Poker poker, Context context, int size, int left, int top){
		mPoker = poker;
		mSize = size;
		mResources = context.getResources();
		BitmapDrawable bgDrawable = null;
		if(size == GameUIResource.SIZE_LARGE){
			bgDrawable = mBgDrawable_1;
		}else if(size == GameUIResource.SIZE_MIDDLE){
			bgDrawable = mBgDrawable_2;
		}else if(size == GameUIResource.SIZE_SMALL){
			bgDrawable = mBgDrawable_3;
		}else{
			throw new IllegalArgumentException();
		}
		this.setBounds(new Rect(left,top, left+(bgDrawable.getIntrinsicWidth()), top+bgDrawable.getIntrinsicHeight()));
	}
	
	private BitmapDrawable getNumDrawable(){
		String color = "black";
		if(mPoker.getSuit() == Suit.DIAMONDS || mPoker.getSuit() == Suit.HEARTS){
			color = "red";
		}
		String key = mPoker.getRank() +"_"+ color +"_" + mSize;
		BitmapDrawable drawable = mDrawableCache.get(key);
		if(drawable == null){
			Bitmap numBitmap = GameUIResource.getInstance().getPokerBitmap(mResources, mPoker, mSize);
			drawable = new BitmapDrawable(mResources, numBitmap);
			mDrawableCache.put(key, drawable);
		}
		return drawable;
	}
	
	private BitmapDrawable getSuitDrawable(){
		String key = mPoker.getSuit() + "_" + mSize;
		BitmapDrawable drawable = mDrawableCache.get(key);
		if(drawable == null){
			Bitmap suitBitmap = GameUIResource.getInstance().getSuitBitmap(mResources, mPoker.getSuit(), mSize);
			drawable = new BitmapDrawable(mResources, suitBitmap);
			mDrawableCache.put(key, drawable);
		}
		return drawable;
	}
	
	private BitmapDrawable getBgDrawable(){
		if(mSize == GameUIResource.SIZE_LARGE){
			return mBgDrawable_1;
		}else if(mSize == GameUIResource.SIZE_MIDDLE){
			return mBgDrawable_2;
		}else{
			return mBgDrawable_3;
		}
	}

	private void calcPokerNumBounds(){
		int paddingLeft = 0;
		int paddingTop = 0;
		if(mSize == GameUIResource.SIZE_LARGE){
			paddingLeft = POKER_NUM_PADDING_LEFT_1;
			paddingTop = POKER_NUM_PADDING_TOP_1;
		}else if(mSize == GameUIResource.SIZE_MIDDLE){
			paddingLeft = POKER_NUM_PADDING_LEFT_2;
			paddingTop = POKER_NUM_PADDING_TOP_2;
		}else if(mSize == GameUIResource.SIZE_SMALL){
			paddingLeft = POKER_NUM_PADDING_LEFT_3;
			paddingTop = POKER_NUM_PADDING_TOP_3;
		}
		if(GameConstantsService.getInstance().getDensityScale() != 1.0f){
			paddingLeft = (int) (paddingLeft * GameConstantsService.getInstance().getDensityScale());
			paddingTop = (int) (paddingTop * GameConstantsService.getInstance().getDensityScale());
		}
		BitmapDrawable pokerNumDrawable = this.getNumDrawable();
		int left = getBounds().left + paddingLeft;
		int top = getBounds().top + paddingTop;
		mPokerNumBounds.set(left, top, left+pokerNumDrawable.getIntrinsicWidth(), top + pokerNumDrawable.getIntrinsicHeight());
	}
	
	private void calcSuitBounds(){
		int paddingLeft = 0;
		int paddingTop = 0;
		if(mSize == GameUIResource.SIZE_LARGE){
			paddingLeft = SUIT_PADDING_LEFT_1;
			paddingTop = SUIT_PADDING_TOP_1;
		}else if(mSize == GameUIResource.SIZE_MIDDLE){
			paddingLeft = SUIT_PADDING_LEFT_2;
			paddingTop = SUIT_PADDING_TOP_2;
		}else if(mSize == GameUIResource.SIZE_SMALL){
			paddingLeft = SUIT_PADDING_LEFT_3;
			paddingTop = SUIT_PADDING_TOP_3;
		}
		if(GameConstantsService.getInstance().getDensityScale() != 1.0f){
			paddingLeft = (int) (paddingLeft * GameConstantsService.getInstance().getDensityScale());
			paddingTop = (int) (paddingTop * GameConstantsService.getInstance().getDensityScale());
		}
		BitmapDrawable drawable = this.getSuitDrawable();
		int left = getBounds().left + paddingLeft;
		int top = getBounds().top + paddingTop;
		mSuitBounds.set(left, top, left+drawable.getIntrinsicWidth(), top + drawable.getIntrinsicHeight());
	}
	
	@Override
	protected void doDraw(Canvas canvas) {
		if(mPoker == Poker.BIG_JOKER || mPoker == Poker.SMALL_JOKER){
			drawJoker(canvas);
			return;
		}
		//绘制牌面背景
		BitmapDrawable bgDrawable = getBgDrawable();
		bgDrawable.setAlpha(mAlpha);
		bgDrawable.setBounds(getBounds());
		bgDrawable.draw(canvas);
		
		BitmapDrawable pokerNumDrawable = getNumDrawable();
		calcPokerNumBounds();
		pokerNumDrawable.setAlpha(mAlpha);
		pokerNumDrawable.setBounds(mPokerNumBounds);
		pokerNumDrawable.draw(canvas);
		
		BitmapDrawable suitDrawable = getSuitDrawable();
		calcSuitBounds();
		suitDrawable.setAlpha(mAlpha);
		suitDrawable.setBounds(mSuitBounds);
		suitDrawable.draw(canvas);
		
		drawTouchedBg(canvas);
	}

	private void drawTouchedBg(Canvas canvas) {
		if(isTouched){
			mBgDrawable_touched.setAlpha(mAlpha);
			mBgDrawable_touched.setBounds(getBounds());
			mBgDrawable_touched.draw(canvas);
		}
	}


	private void drawJoker(Canvas canvas) {
		BitmapDrawable drawable = null;
		if(mPoker == Poker.BIG_JOKER){
			if(mSize == GameUIResource.SIZE_LARGE){
				drawable = mJoker_1;
			}else if(mSize == GameUIResource.SIZE_MIDDLE){
				drawable = mJoker_2;
			}else if(mSize == GameUIResource.SIZE_SMALL){
				drawable = mJoker_3;
			}
		}else if(mPoker == Poker.SMALL_JOKER){
			if(mSize == GameUIResource.SIZE_LARGE){
				drawable = mSmallJoker_1;
			}else if(mSize == GameUIResource.SIZE_MIDDLE){
				drawable = mSmallJoker_2;
			}else if(mSize == GameUIResource.SIZE_SMALL){
				drawable = mSmallJoker_3;
			}
		}
		drawable.setBounds(getBounds());
		drawable.setAlpha(mAlpha);
		drawable.draw(canvas);
		
		drawTouchedBg(canvas);
	}
	
	@Override
	protected boolean doOnTouchEvent(MotionEvent event) {
		if(mOnClickListener != null && isOnclick(event)){
			mOnClickListener.onClick(this, event);
			return true;
		}
		return false;
	}
	
	@Override
	protected boolean isOnclick(MotionEvent event){
		boolean contained = this.getBounds().contains((int)event.getX(),(int)event.getY());
		if(contained && !isFirstTouch){
			isFirstTouch = true;
			if(firstTouchListener != null){
				firstTouchListener.onFirstTouch(this);
			}
		}else if(!contained){
			isFirstTouch = false;
		}
		
		if(event.getAction() == MotionEvent.ACTION_DOWN && contained){
			mPressed = true;
		}else if(event.getAction() == MotionEvent.ACTION_MOVE && !contained){
			mPressed = false;
		}else if(event.getAction() == MotionEvent.ACTION_UP && contained && mPressed){
			return true;
		}
		return false;
	}

	@Override
	public void onDestroy() {
	}

	public void setOnClickListener(OnClickListener onClickListener) {
		this.mOnClickListener = onClickListener;
	}

	public void setTouched(boolean isTouched) {
		this.isTouched = isTouched;
	}

	public boolean isTouched() {
		return isTouched;
	}

	public void setFirstTouchListener(FirstTouchListener firstTouchListener) {
		this.firstTouchListener = firstTouchListener;
	}
	
	
}
