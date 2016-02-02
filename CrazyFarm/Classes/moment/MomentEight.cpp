#include "moment/MomentEight.h"
#include "utill/FunUtil.h"

void MomentEight::init()
{
	life_time = ConfigMomentEight::getInstance()->getLifeTime();
	for (int i = 0; i < 5;i++)
	{
		momentEightItemType[i] = ConfigMomentEight::getInstance()->getMomentEightItemByTypeId(i + 1);
		for (auto &var : momentEightItemType[i])
		{
			var.fTempTime = getRandonNumByAtoB(var.interval_time_start, var.interval_time_end);
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
	for (int i = 0; i < 5; i++)
	{
		for (auto &var : momentEightItemType[i])
		{
			var.fTempTime -= dt;
			if (var.fTempTime <= 0)
			{
				var.fTempTime = getRandonNumByAtoB(var.interval_time_start, var.interval_time_end);
				int count = getintRandonNumByAtoB(var.fish_startcount, var.fish_endcount);
				for (int i = 0; i < count; i++)
				{
					auto item = getFishByRandVec(var.momentEightItemPers);
					FishManage::getInstance()->createFishByEightMonment(item);
				}
			}
		}
	}
	return false;
}

MomentEightItemPer MomentEight::getFishByRandVec(std::vector<MomentEightItemPer> momentEightItemPers)
{
	std::vector<MomentEightItemPer> vec;
	vec.resize(momentEightItemPers.size());
	for (int i = 0; i < momentEightItemPers.size(); i++)
	{
		vec.at(i).fish_id = momentEightItemPers[i].fish_id;
		vec.at(i).fishRoute = momentEightItemPers[i].fishRoute;
		int lastPer = (i == 0 ? 0 : vec[i - 1].per);
		vec.at(i).per = lastPer + momentEightItemPers[i].per;
	}
	int randNum = rand() % 100 + 1;
	for (auto ite = vec.begin(); ite != vec.end(); ite++)
	{
		if (randNum <=ite->per)
		{
			return *ite;
		}
	}
	return momentEightItemPers.at(0);
}