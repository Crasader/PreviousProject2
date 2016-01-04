#ifndef _CONFIGEXP_H_
#define _CONFIGEXP_H_
#include "cocos2d.h"

using namespace cocos2d;

struct LevelData {
    int levelId;
    int haveExp;
    int passNeedExp;
};

class ConfigExp{
public:
	static ConfigExp* getInstance();

    
    LevelData getLevelData(int exp);

private:
	ConfigExp();
	void init();
	static ConfigExp* _instance;
    
    int getLevelId(int exp);

};

#endif
