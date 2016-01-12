#ifndef _NOBILITYMANAGER_H_
#define _NOBILITYMANAGER_H_
#include "cocos2d.h"

using namespace cocos2d;

struct NobilityRewadItem  {
    int item_id;
    int num;
};

class NobilityManager {

public:
    static NobilityManager* getInstance();
    
    
    bool isNobility();// 是否为贵族
    std::vector<NobilityRewadItem> getNobilityRewadItems(); // TODO : 获取单日奖励列表
    bool addNewDay(std::string day);                        // 添加一个新的签到日期
    bool isGetRewardToday();                                // 今日是否领取过礼物
    
private:
    NobilityManager();
    void init();
    static NobilityManager* _instance;
    std::vector<NobilityRewadItem> nobilityRewadItems;
    
    std::string startDay;
    int steps;
};

#endif
