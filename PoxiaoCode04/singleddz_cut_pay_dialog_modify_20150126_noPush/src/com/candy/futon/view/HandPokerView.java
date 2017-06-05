package com.candy.futon.view;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedHashSet;
import java.util.List;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Rect;
import android.util.Log;
import android.view.MotionEvent;

import com.andy.canvasgame.service.GameConstantsService;
import com.andy.canvasgame.service.SoundService;
import com.andy.canvasgame.ui.AView;
import com.andy.canvasgame.ui.OnClickListener;
import com.andy.canvasgame.util.MyGravity;
import com.andy.pokergames.ddz.ai.ddzai.domain.CardType;
import com.andy.pokergames.ddz.ai.ddzai.domain.DdzAIPlayer;
import com.andy.pokergames.ddz.ai.ddzai.domain.DdzTableState;
import com.andy.pokergames.ddz.ai.ddzai.domain.HandCard;
import com.andy.pokergames.ddz.ai.ddzai.domain.Poker;
import com.andy.pokergames.ddz.ai.ddzai.uitl.HandCardUtil;
import com.candy.futon.GameEngine;
import com.candy.futon.view.PokerView.FirstTouchListener;
import com.poxiao.ddz.standalone.R;

public class HandPokerView extends AView{

	private final static String TAG = "HandPokerView";
	
	private DdzAIPlayer player;
	
	private List<Poker> pokerList = new ArrayList<Poker>();
	
	private HashMap<Poker, AView> pokerViewMap = new HashMap<Poker,AView>();
	
	private Context mContext;
	
	private Bitmap pokerBg;
	
	private int SELECT_POKER_PADDING_BOTTOM = 20;
	
	private LinkedHashSet<Poker> pickedPokers = new LinkedHashSet<Poker>();
	
	private int flingStartX;
	
	private int pokerViewWidth;
	
	private int POKER_VIEW_MAX_WIDTH = 60;
	
	private HandPokerChangedListener onChangeListener;
	
	private boolean loadGen = false;
	
	private final static String[] PIANO_SOUNDS = new String[]{
		"x1.ogg","x2.ogg","x3.ogg","x4.ogg","x5.ogg","x6.ogg",
		"x7.ogg","x8.ogg","x9.ogg","xa.ogg","xb.ogg","xc.ogg",
	};
	
	public interface HandPokerChangedListener{
		public void onChange();
	}
	
	private FirstTouchListener firstTouchListener = new FirstTouchListener() {
		
		@Override
		public void onFirstTouch(AView v) {
			int index = mChilds.indexOf(v);
			if(index == -1 ){
				return;
			}
			index %= PIANO_SOUNDS.length;
			SoundService.getInstance().play(mContext, PIANO_SOUNDS[index], true);
		}
	};
	
	public void syncPokerList(){
		pokerList.clear();
		if(player.getPokerList() == null || player.getPokerList().isEmpty()){
			return;
		}
		pokerList.addAll(player.getPokerList());
	}
	
	public HandPokerView(AView parent, Context context, DdzAIPlayer player){
		mContext = context;
		this.setParent(parent);
		this.setBounds(new Rect());
		SELECT_POKER_PADDING_BOTTOM *= GameConstantsService.getInstance().getDensityScale();
		POKER_VIEW_MAX_WIDTH *= GameConstantsService.getInstance().getDensityScale();
		pokerBg = GameUIResource.getInstance().loadBitMap(context.getResources(), R.drawable.joker_1);
		this.player = player;
	}
	
	public void setPlayer(DdzAIPlayer player){
		this.player = player;
	}
	
	public void onPokerListChanged(){
		if(player.isLoad()){
			this.loadGen = true;
		}
		syncPokerList();
		this.clearChilds();
		this.pokerViewMap.clear();
		int pokerCount = pokerList.size();
		if(pokerCount <= 0){
			return;
		}
		pokerViewWidth = getPokerViewWidth(pokerCount);
		int pokerViewTotalWidth = pokerViewWidth * (pokerCount -1) + pokerBg.getWidth();
		
		MyGravity.apply(MyGravity.BOTTOM|MyGravity.CENTER, pokerViewTotalWidth, pokerBg.getHeight() + SELECT_POKER_PADDING_BOTTOM, getParent().getBounds(), this.getBounds());
		
		for(int i=0;i<pokerCount;i++){
			int left = i * pokerViewWidth + this.getBounds().left;
			int top = this.getBounds().top + SELECT_POKER_PADDING_BOTTOM;
			final Poker poker = pokerList.get(pokerCount - 1 - i);
			PokerView pokerView = new PokerView(poker, mContext, GameUIResource.SIZE_LARGE, left, top);
			pokerView.setOnClickListener(new OnClickListener() {
				
				@Override
				public void onClick(AView v, MotionEvent e) {
					int beginCount = pickedPokers.size();
					clickPoker(poker);
					if(pickedPokers.size() > beginCount){
						autoUpSingleStraight();
					}
					if(onChangeListener != null){
						onChangeListener.onChange();
					}
				}
			});
			pokerView.setFirstTouchListener(firstTouchListener);
			if(player.getTable().getLoadExtraCards().contains(poker)){
				pokerView.setTouched(true);
			}
			this.addChild(pokerView);
			pokerViewMap.put(poker, pokerView);
		}
	}
	
	
	
	protected void autoUpSingleStraight() {
		if(player.getTable().getTableState() != DdzTableState.PLAY){
			return;
		}
		if(pickedPokers.size() == 0){
			return;
		}
		Poker[] pokerArray = pickedPokers.toArray(new Poker[]{});
		GameEngine.getInstance().clickCardHint(pokerArray);
	}

	protected void clickPoker(Poker poker) {
		if(player.getTable().getLoad() == null){
			return;
		}
		AView pokerView = pokerViewMap.get(poker);
		if(pokerView == null){
			return;
		}
		if(pickedPokers.contains(poker)){
			pickedPokers.remove(poker);
			pokerView.setMargin(0, SELECT_POKER_PADDING_BOTTOM, 0, 0);
		}else{
			pickedPokers.add(poker);
			pokerView.setMargin(0, 0, 0, SELECT_POKER_PADDING_BOTTOM);
		}
		this.invalidate();
	}
	
	public void chosePokers(Poker[] pokers){
		for(Poker poker: pokers){
			AView pokerView = pokerViewMap.get(poker);
			if(pokerView == null){
				return;
			}
			if(pickedPokers.contains(poker)){
				continue;
			}
			pickedPokers.add(poker);
			pokerView.setMargin(0, 0, 0, SELECT_POKER_PADDING_BOTTOM);
		}
		this.invalidate();
		
	}

	public void rePick(){
		pickedPokers.clear();
		if(mChilds == null){
			return;
		}
		synchronized (childLock) {
			int childLen = mChilds.size();
			int top = this.getBounds().top + SELECT_POKER_PADDING_BOTTOM;
			for(int i=childLen-1;i>=0;i--){
				AView child = mChilds.get(i);
				
				child.getBounds().set(child.getBounds().left, top, child.getBounds().left + child.getBounds().width(), child.getBounds().height() + top);
			}
		}
		this.invalidate();
	}
	
	public List<Poker> getPickedPokers(){
		return new ArrayList<Poker>(pickedPokers);
	}
	
	public void playPokers(List<Poker> pokers){
		
		for(Poker poker: pokers){
			AView view = this.pokerViewMap.get(poker);
			if(view == null){
				continue;
			}
			this.pokerList.remove(poker);
			this.pickedPokers.remove(poker);
			this.pokerViewMap.remove(poker);
			this.removeChild(view);
		}
		synchronized (childLock) {
			int childLen = mChilds.size();
			
			pokerViewWidth = getPokerViewWidth(childLen);
			int pokerViewTotalWidth = pokerViewWidth * (childLen -1) + pokerBg.getWidth();
			
			MyGravity.apply(MyGravity.BOTTOM|MyGravity.CENTER, pokerViewTotalWidth, pokerBg.getHeight() + SELECT_POKER_PADDING_BOTTOM, getParent().getBounds(), this.getBounds());
			
			for(int i=childLen-1;i>=0;i--){
				AView child = mChilds.get(i);
				int left = i * pokerViewWidth + this.getBounds().left;
				int top = this.getBounds().top + SELECT_POKER_PADDING_BOTTOM;
				child.getBounds().set(left, top, left + child.getBounds().width(), top + child.getBounds().height());
			}
		}
	}

	private int getPokerViewWidth(int childLen) {
		int pokerViewWidth;
		if(childLen == 1){
			pokerViewWidth = pokerBg.getWidth();
		}else{
			pokerViewWidth = (getParent().getBounds().width() - pokerBg.getWidth()) / (childLen -1);
		}
		if(pokerViewWidth > POKER_VIEW_MAX_WIDTH){
			pokerViewWidth = POKER_VIEW_MAX_WIDTH;
		}
		return pokerViewWidth;
	}
	
	@Override
	protected void doDraw(Canvas canvas) {
		
	}
	
	@Override
	protected boolean isOnclick(MotionEvent event){
		return false;
	}
	
	public boolean onFakeFling(int startX, int endX){
		
		int start, end;
		if(startX > endX){
			start = endX;
			end = startX;
		}else{
			start = startX;
			end = endX;
		}
		start = (start - getBounds().left) / pokerViewWidth;
		end = (end - getBounds().left) /pokerViewWidth;
		if(start == end){
			return false;
		}
		Log.d(TAG, "on Fake fling:" + start +" "+ end);
		if(start >= mChilds.size()){
			return false;
		}
		List<Poker> flingPokers = new ArrayList<Poker>();
		boolean isAllDown = true;
		synchronized (childLock) {
			int childLen = mChilds.size();
			for(int i=start;i<=end && i<childLen;i++){
				Poker poker = pokerList.get(childLen - 1 -i);
				if(pickedPokers.contains(poker)){
					isAllDown = false;
				}
				flingPokers.add(poker);
			}
		}
		if(isAllDown){
			HandCard handCard = GameEngine.getInstance().flingCardHint(flingPokers);
			if(handCard!= null){
				for(Poker poker: handCard.getPokers()){
					clickPoker(poker);
				}
				return true;
			}
		}
		for(Poker poker:flingPokers){
			clickPoker(poker);
		}
		return true;
		
	}
	
	public void onSelectPoker(int startX, int endX){
		int start, end;
		if(startX > endX){
			start = endX;
			end = startX;
		}else{
			start = startX;
			end = endX;
		}
		start = (start - getBounds().left) / pokerViewWidth;
		end = (end - getBounds().left) /pokerViewWidth;
		if(end > mChilds.size()){
			return;
		}
		synchronized (childLock) {
			int childLen = mChilds.size();
			for(int i=0;i<childLen;i++){
				PokerView pokerView = (PokerView)mChilds.get(i);
				if(i>=start && i<=end){
					pokerView.setTouched(true);
					pokerView.invalidate();
				}else if(pokerView.isTouched()){
					pokerView.setTouched(false);
					pokerView.invalidate();
				}
			}
		}
	}
	
	

	@Override
	protected boolean doOnTouchEvent(MotionEvent event) {
		if(mChilds == null){
			return false;
		}
		boolean contained = this.getBounds().contains((int)event.getX(),(int)event.getY());
		
		if(contained && loadGen){
			loadGen = false;
			for(Poker poker: player.getTable().getLoadExtraCards()){
				PokerView pokerView = (PokerView)pokerViewMap.get(poker);
				if(pokerView != null){
					pokerView.setTouched(false);
					pokerView.invalidate();
				}
			}
		}
		
		if(event.getAction() == MotionEvent.ACTION_DOWN && contained){
			mPressed = true;
			flingStartX = (int) event.getX();
		}else if(event.getAction() == MotionEvent.ACTION_MOVE && contained && mPressed){
			onSelectPoker(flingStartX, (int)event.getX());
		}else if(event.getAction() == MotionEvent.ACTION_MOVE && !contained){
			deSelectPoker();
			mPressed = false;
		}else if(event.getAction() == MotionEvent.ACTION_UP && contained && mPressed){
			deSelectPoker();
			mPressed = false;
			boolean result = onFakeFling(flingStartX, (int)event.getX());
			if(result && onChangeListener != null){
				onChangeListener.onChange();
			}
			return result;
		}
		return false;
	}

	public void deSelectPoker() {
		
		synchronized (childLock) {
			int childLen = mChilds.size();
			for(int i=0;i<childLen;i++){
				PokerView pokerView = (PokerView)mChilds.get(i);
				if(pokerView.isTouched()){
					pokerView.setTouched(false);
					pokerView.invalidate();
				}
			}
		}
	}
	
	

	public void setOnChangeListener(HandPokerChangedListener onChangeListener) {
		this.onChangeListener = onChangeListener;
	}

	@Override
	public void onDestroy() {
		// TODO Auto-generated method stub
		
	}

}
