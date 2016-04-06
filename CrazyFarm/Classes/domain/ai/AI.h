#ifndef _AI_H_
#define _AI_H_
#include "cocos2d.h"
#include "PlayerWork.h"

using namespace cocos2d;
class Fish;
class AI {

public:
	AI(){ _currentFish = nullptr; }
    virtual PlayerWork nextStep(int currentCoins, Point currentPostion) = 0;
    
    CC_SYNTHESIZE(int, maxTurrentLevel, MaxTurrentLevel);
    CC_SYNTHESIZE(float, reqSteps, ReqSteps);
	CC_SYNTHESIZE(Fish*, _currentFish, currentFish);
private:
    
};

#endif
