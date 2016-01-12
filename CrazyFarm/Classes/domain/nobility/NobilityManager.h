#ifndef _PAY_H_
#define _PAY_H_
#include "cocos2d.h"

using namespace cocos2d;

class NobilityManager {

public:
    static NobilityManager* getInstance();
    
private:
    NobilityManager();
    void init();
    static NobilityManager* _instance;
};

#endif
