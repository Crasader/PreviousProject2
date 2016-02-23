#include "moment/MomentManager.h"
#include "moment/MomentEight.h"
#include "moment/momentFishGroup/MomentFive.h"
#include "moment/momentFishGroup/MomentSix.h"
#include "moment/MomentNine.h"
#include "utill/FunUtil.h"
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

Moment*MomentManager::getNewMoment(float FFOneTime)
{
	if (nowMomentType>80)
	{
		return getNewMomentByType(9,FFOneTime);
	}
	else if (nowMomentType == 9)
	{
		return getNewMomentGroupfish(FFOneTime);
	}
	else
	{
		return getNewMomentEight(15+rand()%10);
	}

}

Moment* MomentManager::getNewMomentEight(float FFOneTime) {
    
	return getNewMomentByType(getCurrentMomentEight(), FFOneTime);
}

Moment* MomentManager::getNewMomentGroupfish(float FFOneTime) {

	return getNewMomentByType(getCurrentMomentFishGroup(), FFOneTime);
}


Moment* MomentManager::getNewMomentByType(int momentType, float FFOneTime) {
	Moment* moment;
    if (momentType>80)
	{
		moment = new MomentEight();
		((MomentEight*)moment)->setMomentEightType(momentType - 80);
		moment->init(FFOneTime);
		if (nowMomentType == -1)
		{
			((MomentEight*)moment)->clearFish();
		}
    }
	switch (momentType)
	{
	case 1:
	{
		moment = new MomentOne();
		moment->init(FFOneTime);
		break;
	
	}
	case 2:
	{
		moment = new MomentTwo();
		moment->init(FFOneTime);
		break;
	}
	case 3:
	{
		moment = new MomentThree();
		moment->init(FFOneTime);
		break;
	}
	case 4:
	{
		moment = new MomentFour();
		moment->init(FFOneTime);
		break;
	}
	case 5:
		{
			moment = new MomentFive();
			moment->init(FFOneTime);
			break;
		}
	case 6:
		{


			moment = new MomentSix();
			moment->init(FFOneTime);
			break;

		}
	case 9:
	{
		moment = new MomentNine();
		moment->init(FFOneTime);
		break;
	}
	default:
		break;
	}
	nowMomentType = momentType;
	return moment;
}


int MomentManager::getCurrentMomentEight()
{
	return 81;
	int size = momentEightVec.size();
	if (size>1)
	{
		
	}
	else
	{
		momentEightVec.clear();
		momentEightVec.push_back(81);
		momentEightVec.push_back(82); 
		momentEightVec.push_back(83);
		upsetVector(momentEightVec);
	}
	int curValue = momentEightVec.back();
	momentEightVec.pop_back();
	return curValue;
}

int MomentManager::getCurrentMomentFishGroup()
{
	
	int size = momentFishGroupVec.size();
	if (size > 1)
	{
		
	}
	else
	{
		momentFishGroupVec.clear();
		momentFishGroupVec.push_back(2);
		momentFishGroupVec.push_back(5);
		momentFishGroupVec.push_back(4);
		upsetVector(momentFishGroupVec);
	}
	int curValue = momentFishGroupVec.back();
	momentFishGroupVec.pop_back();
	return curValue;
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



