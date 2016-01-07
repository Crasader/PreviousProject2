#ifndef _MOMENTMANAGER_H_
#define _MOMENTMANAGER_H_
#include "cocos2d.h"

#include "moment/Moment.h"
#include "moment/MomentOne.h"

using namespace cocos2d;

class MomentManager {

public:
    static MomentManager* getInstance();
    
    Moment* getNewMoment();
    
private:
    MomentManager();
    void init();
    static MomentManager* _instance;
    
};

#endif
