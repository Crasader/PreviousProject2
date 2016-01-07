#include "moment/MomentManager.h"


MomentManager* MomentManager::_instance = NULL;

MomentManager::MomentManager(){
    this->init();
}

void MomentManager::init(){
}

MomentManager* MomentManager::getInstance(){
    if(_instance == NULL){
        _instance = new MomentManager();
        _instance->momentOrders = ConfigMomentOrder::getInstance()->LoadConfig();
    }
    return _instance;
}

Moment* MomentManager::getNewMoment() {
    
    return getNewMomentByType(getCurrentType());
}

Moment* MomentManager::getNewMomentByType(int momentType) {
    if(momentType == 1) {
        Moment* moment = new MomentOne();
        moment->init();
        return moment;
    }
	switch (momentType)
	{
	case 1:
	{
		Moment* moment = new MomentOne();
		moment->init();
		return moment;
	}
	case 2:
	{
		Moment* moment = new MomentTwo();
		moment->init();
		return moment;
	}
	case 3:
	{
		Moment* moment = new MomentThree();
		moment->init();
		return moment;
	}
	case 4:
	{
		Moment* moment = new MomentFour();
		moment->init();
		return moment;
	}
	default:
		break;
	}
    
    Moment* moment = new MomentOne();
    moment->init();
    return moment;
}

int MomentManager::getCurrentType() {
    if(momentOrders.size() > 0) {
        if(currentPos < momentOrders.size()) {
        }else {
            currentPos = 0;
        }
        int type = momentOrders[currentPos].moment_id;
        currentPos++;
        return type;
    }
    return 1;
}



