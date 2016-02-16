#include "moment/MomentManager.h"
#include "moment/MomentEight.h"
#include "moment/momentFishGroup/MomentFive.h"
#include "moment/momentFishGroup/MomentSix.h"
#include "moment/MomentNine.h"
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

Moment* MomentManager::getNewMoment(float FFOneTime) {
    
	return getNewMomentByType(getCurrentType(), FFOneTime);
}

Moment* MomentManager::getNewMomentByType(int momentType, float FFOneTime) {
    if(momentType == 1) {
        Moment* moment = new MomentOne();
		moment->init(FFOneTime);
        return moment;
    }
	switch (momentType)
	{
	case 1:
	{
		Moment* moment = new MomentOne();
		moment->init(FFOneTime);
		return moment;
	}
	case 2:
	{
		Moment* moment = new MomentTwo();
		moment->init(FFOneTime);
		return moment;
	}
	case 3:
	{
		Moment* moment = new MomentThree();
		moment->init(FFOneTime);
		return moment;
	}
	case 4:
	{
		Moment* moment = new MomentFour();
		moment->init(FFOneTime);
		return moment;
	}
	case 5:
		{

			
				Moment* moment = new MomentFive();
				moment->init(FFOneTime);
				return moment;
			
		}
	case 6:
		{


			Moment* moment = new MomentSix();
			moment->init(FFOneTime);
			return moment;

		}
	case 8:
	{
		Moment* moment = new MomentEight();
		moment->init(FFOneTime);
		return moment;
	}
	case 9:
	{
		Moment* moment = new MomentNine();
		moment->init(FFOneTime);
		return moment;
	}
	default:
		break;
	}
    
    Moment* moment = new MomentOne();
	moment->init(FFOneTime);
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



