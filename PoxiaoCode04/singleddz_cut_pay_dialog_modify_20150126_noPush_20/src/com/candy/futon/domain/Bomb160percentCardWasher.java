package com.candy.futon.domain;

import java.util.ArrayList;
import java.util.List;

import com.andy.pokergames.ddz.ai.ddzai.domain.DefaultCardWasher;
import com.andy.pokergames.ddz.ai.ddzai.domain.Poker;
import com.andy.pokergames.ddz.ai.ddzai.domain.PokerRank;
import com.andy.pokergames.ddz.ai.ddzai.uitl.PokerData;

public class Bomb160percentCardWasher extends DefaultCardWasher{
	
	private final static int BOMB_PERCENTAGE = 20;
	
	private List<List<Poker>> pokerListData = null;
	
	private int pokerListIndex = 0;
	
	public Bomb160percentCardWasher(String defaultCardDataFile){
		super();
		this.pokerListData = PokerData.getBatchData(defaultCardDataFile);
		
	}
	
	@Override
	public List<Poker> getWashedPokerList() {
		if(this.pokerListData != null && !this.pokerListData.isEmpty()
				&& this.pokerListData.size()> pokerListIndex){
			return this.pokerListData.get(pokerListIndex++);
		}
		boolean playerOneBomb = getPercentageInt() > BOMB_PERCENTAGE/2;
		boolean playerTwoBomb = getPercentageInt() >BOMB_PERCENTAGE*2;
		boolean playerThreeBomb = getPercentageInt() >BOMB_PERCENTAGE*2;
		List<Poker> pokerList = super.getWashedPokerList();
		ArrayList<ArrayList<Poker>> randomBombs = getBombsByRandom(pokerList);
		if(playerOneBomb){
			ArrayList<Poker> bomb = randomBombs.get(0);
			pokerList.removeAll(bomb);
			pokerList.addAll(0, bomb);
		}
		if(playerTwoBomb){
			ArrayList<Poker> bomb = randomBombs.get(1);
			pokerList.removeAll(bomb);
			pokerList.addAll(25, bomb);
		}
		if(playerThreeBomb){
			ArrayList<Poker> bomb = randomBombs.get(2);
			pokerList.removeAll(bomb);
			pokerList.addAll(45,bomb);
		}
		return pokerList;
	}
	
	public ArrayList<ArrayList<Poker>> getBombsByRandom(List<Poker> pokerList){
		int[] rank = new int[3];
		rank[0] = getRandomBombRank();
		rank[1] = getRandomBombRank();
		while(rank[1] == rank[0]){
			rank[1] = getRandomBombRank();
		}
		rank[2] = getRandomBombRank();
		while(rank[2] == rank[1] || rank[2] == rank[0]){
			rank[2] = getRandomBombRank();
		}
		
		ArrayList<ArrayList<Poker>> result = new ArrayList<ArrayList<Poker>>();
		for(int i=0;i<3;i++){
			PokerRank pokerRank = PokerRank.getPokerRank(rank[i]);
			ArrayList<Poker> temp = new ArrayList<Poker>();
			for(Poker poker: pokerList){
				if(poker.getRank() == pokerRank.getRank() || (pokerRank == PokerRank.BIG_JOKER && poker.getRank() == PokerRank.SMALL_JOKER.getRank())){
					temp.add(poker);
				}
			}	
			result.add(temp);
		}
		return result;
	}

	private int getRandomBombRank() {
		int rank = (int) (Math.random() * 14 + 1);
		if(rank == 14){
			rank = PokerRank.BIG_JOKER.getRank();
		}
		return rank;
	}
	
	private int getPercentageInt(){
		return (int) (Math.random() * 100 + 1);
	}
	
}
