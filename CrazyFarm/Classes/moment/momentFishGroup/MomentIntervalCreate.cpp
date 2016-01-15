#include "moment/momentFishGroup/MomentIntervalCreate.h"
#include "fish/FishManage.h"

bool MomentIntervalCreate::updata(float dt)
{
	nNowTime += dt;
	//if (nNowTime>60)   
	//{
	//	return true;
	//}
	auto fishcount = FishManage::getInstance()->getAllFishInPoolCount();
	if (fishcount < fishMinSize&&nNowTime>30)
	{
		return true;
	}

	return false;
}

void MomentIntervalCreate::init()
{
	initData();
	FishManage::getInstance()->createFishGroup(m_groupTag);
}

void MomentIntervalCreate::initData()
{
	nNowTime = 0;
}