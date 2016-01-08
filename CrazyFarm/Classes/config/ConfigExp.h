#ifndef _CONFIGEXP_H_
#define _CONFIGEXP_H_

#include "cocos2d.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

using namespace cocos2d;

struct LevelData {
    int levelId;
    int haveExp;
    int passNeedExp;
};

struct LevelExp {
    int level_id;
    int require_exp;
};

class ConfigExp{
public:
	static ConfigExp* getInstance();

    bool LoadConfig();
    LevelData getLevelData(int exp);

private:
	ConfigExp();
	static ConfigExp* _instance;
    
    int getLevelId(int exp);
    int getLevelExp(int levelId);
    std::vector<LevelExp> levelExps;
};

#endif
