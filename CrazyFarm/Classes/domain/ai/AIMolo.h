#ifndef _AIMOLO_H_
#define _AIMOLO_H_
#include "cocos2d.h"
#include "PlayerWork.h"
#include "domain/ai/AI.h"
#include "fish/FishManage.h"

using namespace cocos2d;

class AIMolo : public AI {

public:
	virtual PlayerWork nextStep(int currentCoins, Point currentPostion, int AiDoCounts, bool isUsingSkillLockOrLight = false, float bulletWidth = 0);
    
    
private:
    float angle = 0;

};

#endif
