#ifndef _AILEI_H_
#define _AILEI_H_
#include "cocos2d.h"
#include "PlayerWork.h"
#include "domain/ai/AI.h"
#include "fish/FishManage.h"

using namespace cocos2d;

///只打黄金鱼，没有就不打了
class AILei : public AI {

public:
    virtual PlayerWork nextStep(int currentCoins, Point currentPostion);
    
    
private:
    float angle = 0;
};

#endif
