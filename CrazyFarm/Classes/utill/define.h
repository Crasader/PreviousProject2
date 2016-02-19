#pragma once
#include "cocos2d.h"
using namespace cocos2d;
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


#define CC_SYNTHESIZELOCALINT(KeyName, funName,initValue)\
public: int get##funName(void) const { return UserDefault::getInstance()->getIntegerForKey(KeyName,initValue); }\
public: void set##funName(int var){ UserDefault::getInstance()->setIntegerForKey(KeyName,var); }