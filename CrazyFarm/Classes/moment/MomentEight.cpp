#include "moment/MomentEight.h"
#include "utill/FunUtil.h"

void MomentEight::init()
{
	life_time = ConfigMomentEight::getInstance()->getLifeTime();
	momentEightItemTypes = ConfigMomentEight::getInstance()->getMomentEightItemTypes();
	for (int i = 1; i < momentEightItemTypes.size() + 1;i++)
	{
		auto &items = momentEightItemTypes[i];
		for (auto &item:items)
		{
			item.fTempTime = getRandonNumByAtoB(item.interval_time_start, item.interval_time_end);
		}
	}
}

bool MomentEight::updata(float dt)
{
	nNowTime += dt;
	if (nNowTime > life_time)
	{
		return true;
	}
	for (int i = 1; i < momentEightItemTypes.size() + 1; i++)
	{
		for (auto &item : momentEightItemTypes[i])
		{
			item.fTempTime -= dt;
			if (item.fTempTime <= 0)
			{
				item.fTempTime = getRandonNumByAtoB(item.interval_time_start, item.interval_time_end);
				for (auto fishitem:item.momentEightItemFishs)
				{
					FishManage::getInstance()->addMomentEightItemFishs(fishitem);
				}

			}
		}
	}
	return false;
}
//
//MomentEightItemPer MomentEight::getFishByRandVec(std::vector<MomentEightItemPer> momentEightItemPers)
//{
//	std::vector<MomentEightItemPer> vec;
//	vec.resize(momentEightItemPers.size());
//	for (int i = 0; i < momentEightItemPers.size(); i++)
//	{
//		vec.at(i).fish_id = momentEightItemPers[i].fish_id;
//		vec.at(i).fishRoute = momentEightItemPers[i].fishRoute;
//		int lastPer = (i == 0 ? 0 : vec[i - 1].per);
//		vec.at(i).per = lastPer + momentEightItemPers[i].per;
//	}
//	int randNum = rand() % 100 + 1;
//	for (auto ite = vec.begin(); ite != vec.end(); ite++)
//	{
//		if (randNum <=ite->per)
//		{
//			return *ite;
//		}
//	}
//	return momentEightItemPers.at(0);
//}