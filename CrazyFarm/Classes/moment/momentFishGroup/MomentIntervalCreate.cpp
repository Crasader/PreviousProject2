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
	if (fishcount < fishMinSize&&nNowTime>45)//45 == Óã³²Ê±¼ä
	{
		Audio::getInstance()->playBGM(GAMEBGM);
		return true;
	}

	return false;
}

void MomentIntervalCreate::init(float FFOneTime)
{
	initData();
	Audio::getInstance()->playBGM(FISHFLOCKBGM);
	FishManage::getInstance()->createFishGroup(m_groupTag);
}

void MomentIntervalCreate::initData()
{
	nNowTime = 0;
}