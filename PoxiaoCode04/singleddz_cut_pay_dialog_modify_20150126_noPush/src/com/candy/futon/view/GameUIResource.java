package com.candy.futon.view;

import android.content.res.Resources;
import android.graphics.Bitmap;

import com.andy.canvasgame.ui.UIResource;
import com.andy.canvasgame.util.BitmapSpliter;
import com.andy.pokergames.ddz.ai.ddzai.domain.Poker;
import com.andy.pokergames.ddz.ai.ddzai.domain.Suit;
import com.poxiao.ddz.standalone.R;

public class GameUIResource extends UIResource {
	
	private static GameUIResource instance;
	
	private Bitmap[] suits_1;
	
	private Bitmap[] poker_num_black_1;
	
	private Bitmap[] poker_num_red_1;
	
	private Bitmap[] suits_2;
	
	private Bitmap[] poker_num_black_2;
	
	private Bitmap[] poker_num_red_2;
	
	private Bitmap[] suits_3;
	
	private Bitmap[] poker_num_black_3;
	
	private Bitmap[] poker_num_red_3;
	
	public final static int SIZE_LARGE = 1;
	
	public final static int SIZE_MIDDLE = 2;
	
	public final static int SIZE_SMALL = 3;
	
	private final static int SUIT_COUNT = 4;
	
	private final static int POKER_NUM_COUNT = 13;
	

	
	/**
	 * 获得花色的图片
	 * @param resources
	 * @param suit 花色
	 * @param size 尺寸
	 * @return
	 */
	public Bitmap getSuitBitmap(Resources resources, Suit suit, int size){
		int index = 0;
		if(suit == Suit.HEARTS){
			index = 3;
		}else if(suit == Suit.DIAMONDS){
			index = 1;
		}else if(suit == Suit.CLUBS){
			index = 2;
		}else if(suit == Suit.SPADES){
			index = 0;
		}else{
			throw new IllegalArgumentException();
		}
		Bitmap[] bitmapArray = null;
		if(size == SIZE_LARGE){
			if(suits_1 == null){
				suits_1 = loadBitMapArray(resources, R.drawable.suit_1, SUIT_COUNT, BitmapSpliter.HORIZONTAL);
			}
			bitmapArray = suits_1;
		}else if(size == SIZE_MIDDLE){
			if(suits_2 == null){
				suits_2 = loadBitMapArray(resources, R.drawable.suit_2, SUIT_COUNT, BitmapSpliter.HORIZONTAL);
			}
			bitmapArray = suits_2;
		}else if(size == SIZE_SMALL){
			if(suits_3 == null){
				suits_3 = loadBitMapArray(resources, R.drawable.suit_2, SUIT_COUNT, BitmapSpliter.HORIZONTAL);
			}
			bitmapArray = suits_3;
		}else{
			throw new IllegalArgumentException();
		}
		return bitmapArray[index];
	}
	
	/**
	 * 获取牌值图片
	 * @param resources
	 * @param poker 牌
	 * @param size 尺寸
	 * @return
	 */
	public Bitmap getPokerBitmap(Resources resources, Poker poker, int size){
		int index = 0;
		index = poker.getRank() + 1;
		if(index >= POKER_NUM_COUNT){
			index -= POKER_NUM_COUNT;
		}
		Bitmap[] bitmapArray = null;
		if(size == SIZE_LARGE){
			if(poker.getSuit() == Suit.HEARTS || poker.getSuit() == Suit.DIAMONDS){
				if(poker_num_red_1 == null){
					poker_num_red_1 = loadBitMapArray(resources, R.drawable.poker_num_red_1 , POKER_NUM_COUNT,  BitmapSpliter.VERTICAL);
				}
				bitmapArray = poker_num_red_1;
			}else{
				if(poker_num_black_1 == null){
					poker_num_black_1 = loadBitMapArray(resources, R.drawable.poker_num_black_1, POKER_NUM_COUNT,  BitmapSpliter.VERTICAL);
				}
				bitmapArray = poker_num_black_1;
			}
		}else if(size == SIZE_MIDDLE){
			if(poker.getSuit() == Suit.HEARTS || poker.getSuit() == Suit.DIAMONDS){
				if(poker_num_red_2 == null){
					poker_num_red_2 = loadBitMapArray(resources, R.drawable.poker_num_red_2 , POKER_NUM_COUNT,  BitmapSpliter.VERTICAL);
				}
				bitmapArray = poker_num_red_2;
			}else{
				if(poker_num_black_2 == null){
					poker_num_black_2 = loadBitMapArray(resources, R.drawable.poker_num_black_2, POKER_NUM_COUNT,  BitmapSpliter.VERTICAL);
				}
				bitmapArray = poker_num_black_2;
			}
		}else if(size == SIZE_SMALL){
			if(poker.getSuit() == Suit.HEARTS || poker.getSuit() == Suit.DIAMONDS){
				if(poker_num_red_3 == null){
					poker_num_red_3 = loadBitMapArray(resources, R.drawable.poker_num_red_2 , POKER_NUM_COUNT,  BitmapSpliter.VERTICAL);
				}
				bitmapArray = poker_num_red_3;
			}else{
				if(poker_num_black_3 == null){
					poker_num_black_3 = loadBitMapArray(resources, R.drawable.poker_num_black_2, POKER_NUM_COUNT,  BitmapSpliter.VERTICAL);
				}
				bitmapArray = poker_num_black_3;
			}
		}else{
			throw new IllegalArgumentException();
		}
		return bitmapArray[index];
		
	}
	
	
	public static GameUIResource getInstance(){
		if(instance == null){
			instance =  new GameUIResource();
		}
		return instance;
	}
	
	private GameUIResource(){
		
	}

	private void releaseBitmapArray(Bitmap[] array){
		if(array == null){
			return;
		}
		for(int i=0;i<array.length;i++){
			array[i].recycle();
		}
	}
	
	@Override
	public void releaseAll() {
		super.releaseAll();
		releaseBitmapArray(suits_1);
		releaseBitmapArray(suits_2);
		releaseBitmapArray(suits_3);
		releaseBitmapArray(poker_num_black_1);
		releaseBitmapArray(poker_num_black_2);
		releaseBitmapArray(poker_num_black_3);
		releaseBitmapArray(poker_num_red_1);
		releaseBitmapArray(poker_num_red_2);
		releaseBitmapArray(poker_num_red_3);
		
	}
}
