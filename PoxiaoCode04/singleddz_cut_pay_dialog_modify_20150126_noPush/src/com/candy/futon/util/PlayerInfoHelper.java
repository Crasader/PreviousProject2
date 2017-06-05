package com.candy.futon.util;

import com.candy.futon.IFutonDdzApplication;
import com.candy.futon.domain.GameRoom;
import com.candy.futon.domain.PlayerInfo;

public class PlayerInfoHelper {

	public static boolean isPointAvaliable(IFutonDdzApplication application, GameRoom gameRoom){
		PlayerInfo playerInfo = application.getPlayerInfo();
		if(playerInfo.getPoint() < gameRoom.minPoint){
			return false;
		}
		return true;
	}
	
	
	
	private PlayerInfoHelper(){
		
	}
	
}
