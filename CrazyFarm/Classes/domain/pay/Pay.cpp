#include "domain/pay/Pay.h"


Pay* Pay::_instance = NULL;

Pay::Pay(){
    this->init();
}

void Pay::init(){
}

Pay* Pay::getInstance(){
    if(_instance == NULL){
        _instance = new Pay();
    }
    return _instance;
}

