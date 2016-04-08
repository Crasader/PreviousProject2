#pragma once
#include "cocos2d.h"
#include "utill/define.h"
#include "server/HttpMsgDefine.h"
using namespace cocos2d;

struct NBRewardItem
{
	int itemId;
	int num;
};


class NewbieMannger{
public:
	static NewbieMannger* getInstance();
	void resetInfo();
private:
	NewbieMannger();
	static NewbieMannger* _instance;


	CC_SYNTHESIZE(std::vector<RewardValue>, _NBRewards, NBRewards);
	CC_SYNTHESIZE(bool, _isAllowdedGetFirstReward, isAllowdedGetFirstReward);


	
	const char* KEY_ISOVERTEACHMODE = "KEY_ISOVERTEACHMODE";
	const char* KEY_SHOOTCOUNTS = "KEY_SHOOTCOUNTS";
	const char* KEY_ISGETTHEFIRSTREWARD = "KEY_ISGETTHEFIRSTREWARD";
	const char* KEY_ISTEACHUPGRADETURRENT = "KEY_ISTEACHUPGRADETURRENT";
	const char* KEY_ISSHOWLOCKTIP = "KEY_ISSHOWLOCKTIP";


	CC_SYNTHESIZELOCALINT(KEY_ISSHOWLOCKTIP, isShowLockTip, 0);
	CC_SYNTHESIZELOCALINT(KEY_ISGETTHEFIRSTREWARD, isGetFirstReward, 0);
	CC_SYNTHESIZELOCALINT(KEY_ISOVERTEACHMODE, isOverTeachMode, 0);
	CC_SYNTHESIZELOCALINT(KEY_SHOOTCOUNTS, NBShootCounts, 0);//40枪提示锁定技能
	CC_SYNTHESIZELOCALINT(KEY_ISTEACHUPGRADETURRENT, isTeachUpgradeTurrent, 0);//升级炮塔引导

};

