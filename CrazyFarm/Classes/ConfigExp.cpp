#include "ConfigExp.h"

using namespace cocos2d;

ConfigExp* ConfigExp::_instance = NULL;

ConfigExp::ConfigExp(){
    this->init();
}

void ConfigExp::init(){
    
}

ConfigExp* ConfigExp::getInstance(){
    if(_instance == NULL){
        _instance = new ConfigExp();
    }
    return _instance;
}

int ConfigExp::getLevel(int exp) {
    // TODO : wait impl
    return 1;
}

char* ConfigExp::getLevelDesc(int exp) {
    // TODO : wait impl
    return "0/200";
}

