#ifndef _AIMOLO_H_
#define _AIMOLO_H_
#include "cocos2d.h"
#include "PlayerWork.h"
#include "AI.h"

using namespace cocos2d;

class AIMolo : public AI {

public:
    PlayerWork nextStep(int currentCoins);
    
    
private:
    float angle = 0;
};

#endif
