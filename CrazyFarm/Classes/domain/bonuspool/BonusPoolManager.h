/**
 * 奖金池管理
 */

#pragma once

#include "cocos2d.h"

using namespace cocos2d;


class BonusPoolManager {

public:
    static BonusPoolManager* getInstance();
    
    int getCoins();                 // TODO : 获取奖金池的数目
    bool addCoins(int coins);       // TODO : 增加奖金池的数目
    bool cleanCoins();              // TODO : 清空奖金池的数目
    
    // TODO : 获取奖励区间和奖励结果
    
private:
    BonusPoolManager();
    void init();
    static BonusPoolManager* _instance;
    
    const char* KEY_BONUSPOOL_COINS = "KEY_BONUSPOOL_COINS";
};

