package com.candy.futon.util;

import android.content.Context;

import com.andy.pokergames.ddz.ai.ddzai.domain.DdzAIPlayer;
import com.andy.pokergames.ddz.ai.ddzai.domain.DdzTable;
import com.candy.futon.domain.GameRoom;
import com.candy.futon.domain.PlayerInfo;

public class RoundInfoHelper {

	public static void calcRoundInfo(Context context, DdzTable table, GameRoom gameRoom, PlayerInfo[] playerInfos, DdzAIPlayer winner, DdzAIPlayer selfPlayer){
		table.getRoundInfo().setBasePoint(gameRoom.basePoint);
		table.getRoundInfo().setBaseMag(gameRoom.baseMag);
		table.getRoundInfo().setTeaFee(gameRoom.teaFee);
		int magination = table.getRoundInfo().getMagination();
		if(magination > gameRoom.maxMag){
			magination = gameRoom.maxMag;
		}
		int point = table.getRoundInfo().getBasePoint() * table.getRoundInfo().getCallLoadPoint() * magination;
		boolean isLoadWin = false;
		if(winner.isLoad()){
			point *= -1;
			isLoadWin = true;
		}
		int teaFee = table.getRoundInfo().getTeaFee();
		table.getRoundInfo().setLoadWin(isLoadWin);
		int loadPoint = 0;
		
		
		PlayerInfo loadPlayerInfo = null;
		for(int i=0;i<playerInfos.length;i++){
			if(table.getPlayers()[i].isLoad()){
				loadPlayerInfo = playerInfos[i];
			}
		}
		int loadIndex = 0;
		if(isLoadWin){
			
			if(Math.abs(point) * 2 > loadPlayerInfo.getPoint()){
				point = - (loadPlayerInfo.getPoint())/2;
			}
			int realPoint = 0;
			for(int i=0;i<playerInfos.length;i++){
				if(!table.getPlayers()[i].isLoad()){
					int tempPoint = point - teaFee;
					if(playerInfos[i].getPoint() < Math.abs(tempPoint)){
						tempPoint = - playerInfos[i].getPoint();
					}
					playerInfos[i].setPoint(playerInfos[i].getPoint() + tempPoint);
					updateRoundInfoPoint(table, i, tempPoint);
					realPoint += tempPoint;
					playerInfos[i].setLose(playerInfos[i].getLose() + 1);
				}else{
					loadIndex = i;
					playerInfos[i].setWin(playerInfos[i].getWin() + 1);
				}
			}
			playerInfos[loadIndex].setPoint(playerInfos[loadIndex].getPoint() - realPoint - 3 * teaFee);
			updateRoundInfoPoint(table, loadIndex,  - realPoint - 3 * teaFee);
		}else{
			loadPoint = -2 * point - teaFee;
			if(loadPlayerInfo.getPoint() <Math.abs(loadPoint)){
				loadPoint = - loadPlayerInfo.getPoint();
			}
			int realLoadPoint = 0;
			
			for(int i=0;i<playerInfos.length;i++){
				if(!table.getPlayers()[i].isLoad()){
					int farmerPoint = (-loadPoint - teaFee)/2;
					if(farmerPoint > playerInfos[i].getPoint()){
						farmerPoint = playerInfos[i].getPoint();
					}
					realLoadPoint += farmerPoint;
					playerInfos[i].setPoint(playerInfos[i].getPoint() + farmerPoint - teaFee);
					updateRoundInfoPoint(table, i, farmerPoint - teaFee);
					playerInfos[i].setWin(playerInfos[i].getWin() + 1);
					
				}else{
					loadIndex = i;
					
					playerInfos[i].setLose(playerInfos[i].getLose() + 1);
				}
			}
			playerInfos[loadIndex].setPoint(playerInfos[loadIndex].getPoint() - realLoadPoint - teaFee);
			updateRoundInfoPoint(table, loadIndex, - realLoadPoint - teaFee);
			
		}
		
		for(PlayerInfo playerInfo: playerInfos){
			PlayerInfo.savePlayerInfo(context, playerInfo);
		}
		
		table.getRoundInfo().setLeftPlayer(table.getNextPlayer(table.getNextPlayer(selfPlayer)).getName());
		table.getRoundInfo().setRightPlayer(table.getNextPlayer(selfPlayer).getName());
	}
	
	private static void updateRoundInfoPoint(DdzTable mTable, int i, int tempPoint) {
		if(i==0){
			mTable.getRoundInfo().setPlayerPoint(tempPoint);
		}else if(i==1){
			mTable.getRoundInfo().setRightPlayerPoint(tempPoint);
		}else if(i==2){
			mTable.getRoundInfo().setLeftPlayerPoint(tempPoint);
		}
	}
	
	private RoundInfoHelper(){
		
	}
	
}
