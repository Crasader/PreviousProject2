#ifndef _MOMENTMANAGER_H_
#define _MOMENTMANAGER_H_
#include "cocos2d.h"

#include "config/ConfigMomentOrder.h"

#include "moment/Moment.h"
#include "moment/MomentOne.h"
#include "moment/MomentTwo.h"
#include "moment/MomentThree.h"
#include "moment/MomentFour.h"

using namespace cocos2d;

class MomentManager {

public:
    static MomentManager* getInstance();
    
    Moment* getNewMoment();
    
private:
    MomentManager();
    void init();
    static MomentManager* _instance;
    
    std::vector<MomentOrderItem> momentOrderItems;
    int currentPos = 0;
    
    Moment* getNewMomentByType(int momentType);
    int getCurrentType();
    
};

#endif
