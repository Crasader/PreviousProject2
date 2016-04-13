#ifndef _AI_H_
#define _AI_H_
#include "cocos2d.h"
#include "PlayerWork.h"

using namespace cocos2d;
class Fish;
class AI {

public:
	AI(){ _currentFish = nullptr; }
    virtual PlayerWork nextStep(int currentCoins, Point currentPostion,int AiDoCounts )= 0;
    
    CC_SYNTHESIZE(int, maxTurrentLevel, MaxTurrentLevel);
    CC_SYNTHESIZE(float, reqSteps, ReqSteps);
	CC_SYNTHESIZE(Fish*, _currentFish, currentFish);
	protected:

	//升级炮塔策略通用
	PlayerWork getUpdataTurrentWork(int AiDoCounts);
    
};

#endif
