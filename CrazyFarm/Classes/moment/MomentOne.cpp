#include "moment/MomentOne.h"


void MomentOne::init()
{
	oneMomentList = ConfigOnemoment::getInstance()->LoadConfig("config/config_onemoment_1.json");
    nNowTime = 0;

}

bool MomentOne::updata(float dt)
{
	nNowTime += dt;
	if (nNowTime>oneMomentList.life_time)    //TODO : need update 60s by config
	{
		return true;
	}

	for (auto iter = oneMomentList.oneMoments.begin(); iter != oneMomentList.oneMoments.end();)
	{
		if (nNowTime>(iter->start_time))
		{
			auto k = *iter;
			
			FishManage::getInstance()->createFishByOneMonet(*iter);
			iter = oneMomentList.oneMoments.erase(iter);
			
		}
		else
		{
			return false;
		}
	}
    return false;

}