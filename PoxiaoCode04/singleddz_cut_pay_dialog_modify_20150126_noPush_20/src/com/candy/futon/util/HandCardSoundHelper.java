package com.candy.futon.util;

import android.content.Context;

import com.andy.canvasgame.service.SoundService;
import com.andy.pokergames.ddz.ai.ddzai.domain.CardType;
import com.andy.pokergames.ddz.ai.ddzai.domain.HandCard;
import com.andy.pokergames.ddz.ai.ddzai.domain.PokerRank;

public class HandCardSoundHelper {

	private HandCardSoundHelper(){
		
	}
	
	public static void playEffectByHandCard(Context context, HandCard handCard){
		if(handCard == null){
			SoundService.getInstance().play(context, "sbuchu.ogg", true);
			return;
		}
		
		if(handCard.getCardType() == CardType.ROCKET){
			SoundService.getInstance().play(context, "sroket.ogg", true);
		}else if(handCard.getCardType() == CardType.BOMB){
			SoundService.getInstance().play(context, "sbomb.ogg", true);
		}else if(handCard.getCardType() == CardType.TRIP_STRAIGHT_WING){
			SoundService.getInstance().play(context, "splane.ogg", true);
		}else{
			SoundService.getInstance().play(context, "schupai.ogg", true);
		}
	}
	
	public static void playSoundByHandCard(boolean isFollow, Context context, HandCard handCard, boolean gender){
		String fileName = null;
		if(handCard == null){
			fileName = "buyao" + ((int)(Math.random() * 4) + 1);
		}
		else if(handCard.getCardType() == CardType.SINGLE){
			int fileRank = getFileRank(handCard);
			fileName = String.valueOf(fileRank);
			if(handCard.getHandCardRank() == PokerRank.SMALL_JOKER.getRank() || handCard.getHandCardRank() == PokerRank.BIG_JOKER.getRank()){
				fileName = String.valueOf(handCard.getHandCardRank());
			}
		}else if(handCard.getCardType() == CardType.DUAL){
			int fileRank = getFileRank(handCard);
			fileName = "dui" + fileRank;
		}else if(handCard.getCardType() == CardType.TRIPLE){
			int fileRank = getFileRank(handCard);
			fileName = "tuple"+fileRank;
		}else if(handCard.getCardType() == CardType.BOMB){
			fileName = "zhadan";
		}else if(handCard.getCardType() == CardType.ROCKET){
			fileName = "wangzha";
		}else if(isFollow){
			fileName = "dani" + ((int)(Math.random() * 3) + 1);
		}else if(handCard.getCardType() == CardType.TRIP_ONE){
			if(handCard.getPokers().length == 4){
				fileName = "sandaiyi";
			}else{
				fileName = "sandaiyidui";
			}
		}else if(handCard.getCardType() == CardType.BOMB_DUAL){
			if(handCard.getPokers().length == 6){
				fileName = "sidaier";
			}else{
				fileName = "sidailiangdui";
			}
		}else if(handCard.getCardType() == CardType.SING_STRAIGHT){
			fileName = "shunzi";
		}else if(handCard.getCardType() == CardType.DUAL_STRAIGHT){
			fileName = "liandui";
		}else if(handCard.getCardType() == CardType.TRIP_STRAIGHT_WING){
			fileName = "feiji";
		}
		
		if(fileName == null){
			return;
		}
		fileName += ".ogg";
		SoundService.getInstance().play(context, fileName, gender);
	}

	private static int getFileRank(HandCard handCard) {
		int fileRank = (handCard.getHandCardRank() + 2);
		if(fileRank > 13){
			fileRank %= 13;
		}
		return fileRank;
	}
	
}
