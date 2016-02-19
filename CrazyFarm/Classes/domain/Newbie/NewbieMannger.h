#pragma once
#include "cocos2d.h"
#include "utill/define.h"
using namespace cocos2d;

class NewbieMannger{
public:
	static NewbieMannger* getInstance();
private:
	NewbieMannger();
	static NewbieMannger* _instance;

	const char* KEY_ISOVERTEACHMODE = "KEY_ISOVERTEACHMODE";

	const char* KEY_SHOOTCOUNTS = "KEY_SHOOTCOUNTS";
	const char* KEY_ISGETTHEFIRSTREWARD = "KEY_ISGETTHEFIRSTREWARD";
	CC_SYNTHESIZELOCALINT(KEY_ISGETTHEFIRSTREWARD, isGetFirstReward, 0);
	CC_SYNTHESIZELOCALINT(KEY_ISOVERTEACHMODE, isOverTeachMode, 0);
	CC_SYNTHESIZELOCALINT(KEY_SHOOTCOUNTS, NBShootCounts, 0);//15枪提示锁定技能
};

