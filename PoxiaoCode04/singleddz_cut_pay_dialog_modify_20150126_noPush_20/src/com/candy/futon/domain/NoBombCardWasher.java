package com.candy.futon.domain;

import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.List;

import com.andy.pokergames.ddz.ai.ddzai.domain.HandCard;
import com.andy.pokergames.ddz.ai.ddzai.domain.Poker;
import com.andy.pokergames.ddz.ai.ddzai.domain.PokerRank;
import com.andy.pokergames.ddz.ai.ddzai.domain.PokerRankCollection;
import com.andy.pokergames.ddz.ai.ddzai.uitl.PokerUtil;

public class NoBombCardWasher extends DefaultRandomCardWasher {

	public NoBombCardWasher(String defaultCardDataFile) {
		super(null);
	}
	
	@Override
	public List<Poker> getWashedPokerList() {
		List<Poker> result = super.getWashedPokerList();
		ArrayList<Poker> playersPoker = new ArrayList<Poker>(result.subList(0, 17));
		if(playersPoker.contains(Poker.BIG_JOKER) &&playersPoker.contains(Poker.SMALL_JOKER)){
			return getWashedPokerList();
		}
		 LinkedHashMap<PokerRank, PokerRankCollection> pokerCollections = PokerUtil.getPokerRankCollection(playersPoker, false);
		boolean foundBomb = false;
		 for(PokerRankCollection pokerRankCollection: pokerCollections.values()){
			if(pokerRankCollection.getPokerList().size() == HandCard.BOMB_POKER_COUNT){
				foundBomb = true;
				break;
			}
		}
		 if(foundBomb){
			 return getWashedPokerList();
		 }
		 return result;
	}

}
