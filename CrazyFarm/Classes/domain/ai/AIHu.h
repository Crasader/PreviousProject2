#ifndef _AIHU_H_
#define _AIHU_H_
#include "cocos2d.h"
#include "PlayerWork.h"
#include "domain/ai/AI.h"
#include "fish/FishManage.h"

using namespace cocos2d;

///������Ļ�������㲻ͣ��
class AIHu : public AI {

public:
	virtual PlayerWork nextStep(int currentCoins, Point currentPostion, int AiDoCounts);
    
    
private:
    float angle = 0;
};

#endif
