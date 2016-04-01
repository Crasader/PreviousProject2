#include "domain/nobility/NobilityManager.h"
#include "config/ConfigSign.h"
#include "utill/dayUtil.h"
#include "domain/user/User.h"
NobilityManager* NobilityManager::_instance = NULL;

NobilityManager::NobilityManager(){
    this->init();
}


void NobilityManager::init(){

}

NobilityManager* NobilityManager::getInstance(){
    if(_instance == NULL){
        _instance = new NobilityManager();
    }
    return _instance;
}
int NobilityManager::RemainingNobilityday()
{
	return User::getInstance()->getNobilityDay();
}
bool NobilityManager::isNobility() {
	return (RemainingNobilityday() > 0);
}

