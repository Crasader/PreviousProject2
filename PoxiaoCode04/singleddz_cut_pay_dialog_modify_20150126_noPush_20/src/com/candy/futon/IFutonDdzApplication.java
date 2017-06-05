package com.candy.futon;

import com.candy.futon.activitys.GameActivity;
import com.candy.futon.dialog.ChargeDialog;
import com.candy.futon.domain.IPlayerGenerator;
import com.candy.futon.domain.PlayerInfo;

public interface IFutonDdzApplication {
	public PlayerInfo getPlayerInfo();
	
	public void addCoin2Hero(int coin);
	
	public void addCoin2Hero(int coin, boolean playAnimation);
	
	public Class<? extends GameActivity> getGameActivityClass();
	
	public Class<? extends ChargeDialog> getChargeDialogClass();
	
	public IPlayerGenerator getPlayerGenerator();
	
	public int getGameId();
	
	public String getPromoteNotAvaliableString();
	
	public String getPromoteDownloadProgressString();
	
	public String getPromoteDownloadCompleteString();
	
	public String getPromoteDownloadStartString();
	
	public String getPromoteDownloadErrorString();
}
