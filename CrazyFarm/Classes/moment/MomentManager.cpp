#include "moment/MomentManager.h"
#include "moment/MomentEight.h"

MomentManager* MomentManager::_instance = NULL;

MomentManager::MomentManager(){
    this->init();
}

void MomentManager::init(){
}

MomentManager* MomentManager::getInstance(){
    if(_instance == NULL){
        _instance = new MomentManager();
        _instance->momentOrderItems = ConfigMomentOrder::getInstance()->LoadConfig();
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
	case 8:
	{
		Moment* moment = new MomentEight();
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
    if(momentOrderItems.size() > 0) {
        if(currentPos < momentOrderItems.size()) {
        }else {
            currentPos = 0;
        }
        MomentOrderItem momentOrderItem = momentOrderItems.at(currentPos);
        int random = rand()%100;
        int currentCount = 0;
        for(int i=0; i<momentOrderItem.momentOrderBaseItems.size(); i++) {
            currentCount += momentOrderItem.momentOrderBaseItems.at(i).per;
            if(random <= currentCount) {
                int moment_id = momentOrderItem.momentOrderBaseItems.at(i).moment_id;
                currentPos++;
                return moment_id;
            }
        }
    }
    return 1;
}



