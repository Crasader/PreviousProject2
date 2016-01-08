#ifndef _AIHU_H_
#define _AIHU_H_
#include "cocos2d.h"
#include "PlayerWork.h"
#include "AI.h"
#include "FishManage.h"

using namespace cocos2d;

class AIHu : public AI {

public:
    virtual PlayerWork nextStep(int currentCoins, Point currentPostion);
    
    
private:
    float angle = 0;
};

#endif
