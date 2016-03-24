/**
 * 奖金池管理
 */

#pragma once

#include "config/ConfigBonuspool.h"

using namespace cocos2d;

struct BonuspoolResult {
	int bouns_position;
    std::vector<BonuspoolRewardItem> reward_list;
};




class BonusPoolManager {

public:
    static BonusPoolManager* getInstance();
    
    bool allowBonusPool();              // 是否允许抽奖
    int getAllowCatchFishCounts();       // 允许抽奖的捕获鱼数量
   
    
   
    
    BonuspoolResult getBonuspoolResult();       // 获取奖励区间和奖励结果
	BonuspoolItem*  getNextBonuspool();       // 获取下一级奖金池
	
	int getFishNeedCatchToChoujiang(){ return getAllowCatchFishCounts() - getBounsFishCounts(); };
    
	unsigned long getBounsCoins();
	void setBounsCoins(unsigned long coins);
	void addBounsCoins(int coins);

	int getBounsFishCounts();
	void setBounsFishCounts(int fishcounts);
	void addBounsFishCounts(int fishcounts);
private:
    BonusPoolManager();
    void init();
    static BonusPoolManager* _instance;
	unsigned long _coins;
	int _fishCounts;
    const char* KEY_BONUSPOOL_COINS = "KEY_BONUSPOOL_COINS";
    const char* KEY_BONUSPOOL_FISHCOUNTS = "KEY_BONUSPOOL_FISHCOUNTS";
};

