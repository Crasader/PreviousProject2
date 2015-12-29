#pragma once

struct playerInfo
{
	int  nId;
	int  nLevel;
	int  nCoin;
	int	 nDiamond;
	bool nIsVip = false;

	
};

enum 
{
	kTagCoinFrame0 = 0,
	kTagCoinFrame1 = 1,
	kTagCoinFrame2 = 2,
	kTagCoinFrame3 = 3,
};