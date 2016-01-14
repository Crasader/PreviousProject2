/**
 * 奖金池管理
 */

#pragma once

#include "cocos2d.h"

using namespace cocos2d;


class BonusPoolManager {

public:
    static BonusPoolManager* getInstance();
    
    // TODO : 获取奖金鱼配置信息
    // TODO : 根据金币数获取奖励区间
    
private:
    BonusPoolManager();
    void init();
    static BonusPoolManager* _instance;
    
    
};

