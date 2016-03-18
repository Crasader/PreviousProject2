#include "moment/momentFishGroup/MomentIntervalCreate.h"
#include "fish/FishManage.h"
#include "domain/game/GameManage.h"
bool MomentIntervalCreate::updata(float dt)
{
	nNowTime += dt;
	auto fishcount = FishManage::getInstance()->getAllFishInPoolCount();
	if (fishcount < fishMinSize&&nNowTime>45)//45 == Óã³²Ê±¼ä todo:µ¥¶ÀÅäÖÃ
	{
		
		GameManage::getInstance()->getGameLayer()->onClearFishFinish();
		return true;
	}
	for (auto it = info.begin(); it != info.end();)
	{
		it->_time -= dt;
		if (it->_time < 0)
		{
			FishManage::getInstance()->createFishMonmentInterval(it->_fishid,it->_route,it->_startPos);
			it = info.erase(it);
		}
		else
		{
			it++;
		}
	}




	return false;
}

void MomentIntervalCreate::init(float FFOneTime)
{
	initData();
	Audio::getInstance()->playBGM(FISHFLOCKBGM);
	gp = FishGroupData::getInstance()->getGroupBytag(m_groupTag);
	for (auto var : gp.singleTypefishGroups)
	{
		for (int i = 0; i < var.fishCount; i++)
		{
			MomentIntervalCreateFishInfo temp;
			temp._fishid = var.fishID;
			temp._startPos = var.startPos;
			temp._route = var.fishRoute;
			temp._time = var.IntervalCreateTime*i;
			info.push_back(temp);
		}

	}
	//FishManage::getInstance()->createFishGroup(m_groupTag);
}

void MomentIntervalCreate::initData()
{
	nNowTime = 0;
}