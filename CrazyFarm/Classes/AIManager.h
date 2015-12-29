#ifndef _AIMANAGER_H_
#define _AIMANAGER_H_
#include "cocos2d.h"
#include "AI.h"
#include "AIMolo.h"

using namespace cocos2d;

class AIManager {

public:
    static AIManager* getInstance();
    
    AI* getAI(int aiType, int aiLevel, int maxTurrentLevel);
    
    
private:
    AIManager();
    void init();
    static AIManager* _instance;
    
};

#endif
