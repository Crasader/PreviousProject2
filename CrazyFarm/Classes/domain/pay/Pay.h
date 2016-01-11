#ifndef _PAY_H_
#define _PAY_H_
#include "cocos2d.h"

using namespace cocos2d;

class Pay {

public:
    static Pay* getInstance();
    
private:
    Pay();
    void init();
    static Pay* _instance;
};

#endif
