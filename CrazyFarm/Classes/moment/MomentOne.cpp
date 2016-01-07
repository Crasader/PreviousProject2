#include "moment/MomentOne.h"


void MomentOne::init()
{
	m_oneMoment = ConfigOnemoment::getInstance()->LoadConfig("config/config_onemoment_1.json");

}

bool MomentOne::updata(float dt)
{
	nNowTime += dt;
	if (nNowTime>60)    //TODO : need update 60s by config
	{
		return true;
	}

	for (auto iter = m_oneMoment.begin(); iter != m_oneMoment.end();)
	{
		if (nNowTime>(iter->start_time))
		{
			
			FishManage::getInstance()->createFishByOneMonet(iter->fishgroup_id,iter->end_time-iter->start_time,Vec2(iter->start_position_x,iter->start_position_y),Vec2(iter->end_position_x,iter->end_position_y),iter->move_type);
			iter = m_oneMoment.erase(iter);
			
		}
		else
		{
			return false;
		}
	}

}