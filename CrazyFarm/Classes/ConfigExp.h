#ifndef _CONFIGEXP_H_
#define _CONFIGEXP_H_
#include "cocos2d.h"

using namespace cocos2d;

class ConfigExp{
public:
	static ConfigExp* getInstance();
    
    int getLevel(int exp);
    char* getLevelDesc(int exp);

private:
	ConfigExp();
	void init();
	static ConfigExp* _instance;

};

#endif
