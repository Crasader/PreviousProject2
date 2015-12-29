#ifndef _AI_H_
#define _AI_H_
#include "cocos2d.h"
#include "PlayerWork.h"

using namespace cocos2d;

class AI {

public:
    
    PlayerWork nextStep(int currentCoins);
    
    CC_SYNTHESIZE(int, maxTurrentLevel, MaxTurrentLevel);
    CC_SYNTHESIZE(int, reqSteps, ReqSteps);
    
private:
    
};

#endif
