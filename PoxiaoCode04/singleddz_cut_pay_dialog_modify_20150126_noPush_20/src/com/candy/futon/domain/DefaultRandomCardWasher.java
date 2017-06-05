package com.candy.futon.domain;

import java.util.List;

import com.andy.pokergames.ddz.ai.ddzai.domain.DefaultCardWasher;
import com.andy.pokergames.ddz.ai.ddzai.domain.Poker;
import com.andy.pokergames.ddz.ai.ddzai.uitl.PokerData;

public class DefaultRandomCardWasher extends DefaultCardWasher {

	private List<List<Poker>> pokerListData = null;
	
	private int pokerListIndex = 0;
	
	public DefaultRandomCardWasher(String defaultCardDataFile){
		super();
		this.pokerListData = PokerData.getBatchData(defaultCardDataFile);
		
	}
	
	@Override
	public List<Poker> getWashedPokerList() {
		if(this.pokerListData != null && !this.pokerListData.isEmpty()
				&& this.pokerListData.size()> pokerListIndex){
			return this.pokerListData.get(pokerListIndex++);
		}
		return super.getWashedPokerList();
	}
}
