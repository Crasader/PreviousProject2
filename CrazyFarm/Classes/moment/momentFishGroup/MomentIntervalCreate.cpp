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
	for (auto var:gp.singleTypefishGroups)
	{
		for (int i = 0; i < var.fishCount;i++)
		{
			if (nNowTime > var.IntervalCreateTime*i)
			{
				if (var.fishID!=-1)
				{
					FishManage::getInstance()->createFishMonmentInterval(var.fishID, var.fishRoute, var.startPos);
					var.fishID = -1;
				}
				
			}
		}
		
	}




	return false;
}

void MomentIntervalCreate::init(float FFOneTime)
{
	initData();
	Audio::getInstance()->playBGM(FISHFLOCKBGM);
	gp = FishGroupData::getInstance()->getGroupBytag(m_groupTag);
	//FishManage::getInstance()->createFishGroup(m_groupTag);
}

void MomentIntervalCreate::initData()
{
	nNowTime = 0;
}