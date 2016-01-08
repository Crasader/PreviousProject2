#include "config/ConfigExp.h"

using namespace cocos2d;

ConfigExp* ConfigExp::_instance = NULL;

ConfigExp::ConfigExp(){
    this->init();
}

void ConfigExp::init(){
    // TODO : read file from json
}

ConfigExp* ConfigExp::getInstance(){
    if(_instance == NULL){
        _instance = new ConfigExp();
    }
    return _instance;
}

int ConfigExp::getLevelId(int exp) {
    // TODO : wait impl
    return 1;
}

LevelData ConfigExp::getLevelData(int exp) {
    LevelData levelData;
    levelData.levelId = getLevelId(exp);
    levelData.haveExp = 20;
    levelData.passNeedExp = 200;
    return levelData;
}

