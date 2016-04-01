#ifndef _NOBILITYMANAGER_H_
#define _NOBILITYMANAGER_H_
#include "cocos2d.h"
#include "server/HttpMsgDefine.h"
using namespace cocos2d;



class NobilityManager {

public:
    static NobilityManager* getInstance();
    bool isNobility();// 是否为贵族
	int  RemainingNobilityday();


private:
    NobilityManager();
    void init();
    static NobilityManager* _instance;
	CC_SYNTHESIZE(std::vector<RewardValue>, _nobilityRewadItems, NobilityRewadItems)

};

#endif
