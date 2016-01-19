#include "moment/MomentEight.h"
#include "utill/FunUtil.h"

void MomentEight::init()
{
	fInterval = 1.0f;
	momentEightItemType1 = ConfigMomentEight::getInstance()->getMomentEightItemByTypeId(1);
	momentEightItemType2 = ConfigMomentEight::getInstance()->getMomentEightItemByTypeId(2);
	momentEightItemType3 = ConfigMomentEight::getInstance()->getMomentEightItemByTypeId(3);
	momentEightItemType4 = ConfigMomentEight::getInstance()->getMomentEightItemByTypeId(4);
	momentEightItemType5 = ConfigMomentEight::getInstance()->getMomentEightItemByTypeId(5);
	fTemp1 = getRandonNumByAtoB(momentEightItemType1.interval_time_start, momentEightItemType1.interval_time_end);
	fTemp2 = getRandonNumByAtoB(momentEightItemType2.interval_time_start, momentEightItemType2.interval_time_end);
	fTemp3 = getRandonNumByAtoB(momentEightItemType3.interval_time_start, momentEightItemType3.interval_time_end);
	fTemp4 = getRandonNumByAtoB(momentEightItemType4.interval_time_start, momentEightItemType4.interval_time_end);
	fTemp5 = getRandonNumByAtoB(momentEightItemType5.interval_time_start, momentEightItemType5.interval_time_end);
}

bool MomentEight::updata(float dt)
{
	nNowTime += dt;
	fTemp1 -= dt;
	fTemp2 -= dt;
	fTemp3 -= dt;
	fTemp4 -= dt;
	fTemp5 -= dt;
	if (nNowTime > momentEightItemType1.life_time)
	{
		return true;
	}
	if (fTemp1 <= 0)
	{
		fTemp1 = getRandonNumByAtoB(momentEightItemType1.interval_time_start, momentEightItemType1.interval_time_end);
		int count = (int)getRandonNumByAtoB(momentEightItemType1.fish_startcount, momentEightItemType1.fish_endcount);
		for (int i = 0; i < count; i++)
		{
			auto item = getFishByRandVec(momentEightItemType1.momentEightItemPers);
			FishManage::getInstance()->createFishRand(item.fish_id);
		}
		
	}
	if (fTemp2 <= 0)
	{
		fTemp2 = getRandonNumByAtoB(momentEightItemType2.interval_time_start, momentEightItemType2.interval_time_end);
		int count = (int)getRandonNumByAtoB(momentEightItemType2.fish_startcount, momentEightItemType2.fish_endcount);
		for (int i = 0; i < count; i++)
		{
			auto item = getFishByRandVec(momentEightItemType2.momentEightItemPers);
			FishManage::getInstance()->createFishRand(item.fish_id);
		}
	}
	if (fTemp3 <= 0)
	{
		fTemp3 = getRandonNumByAtoB(momentEightItemType3.interval_time_start, momentEightItemType3.interval_time_end);
		int count = (int)getRandonNumByAtoB(momentEightItemType3.fish_startcount, momentEightItemType3.fish_endcount);
		for (int i = 0; i < count; i++)
		{
			auto item = getFishByRandVec(momentEightItemType3.momentEightItemPers);
			FishManage::getInstance()->createFishArrangeRand(item.fish_id);
		}
	}
	if (fTemp4 <= 0)
	{
		fTemp4 = getRandonNumByAtoB(momentEightItemType4.interval_time_start, momentEightItemType4.interval_time_end);
		int count = (int)getRandonNumByAtoB(momentEightItemType4.fish_startcount, momentEightItemType4.fish_endcount);
		for (int i = 0; i < count; i++)
		{
			auto item = getFishByRandVec(momentEightItemType4.momentEightItemPers);
			FishManage::getInstance()->createFishRand(item.fish_id);
		}
	}
	if (fTemp5 <= 0)
	{
		fTemp5 = getRandonNumByAtoB(momentEightItemType5.interval_time_start, momentEightItemType5.interval_time_end);
		int count = (int)getRandonNumByAtoB(momentEightItemType5.fish_startcount, momentEightItemType5.fish_endcount);
		for (int i = 0; i < count; i++)
		{
			auto item = getFishByRandVec(momentEightItemType5.momentEightItemPers);
			FishManage::getInstance()->createFishRand(item.fish_id);
		}
	}
	return false;

}

MomentEightItemPer MomentEight::getFishByRandVec(std::vector<MomentEightItemPer> momentEightItemPers)
{
	std::vector<MomentEightItemPer> vec;
	vec.resize(momentEightItemPers.size());
	for (int i = 0; i < momentEightItemPers.size();i++)
	{
		vec.at(i).fish_id = momentEightItemPers[i].fish_id;
		if (i == 0)
		{
			vec.at(0).per = 0;
		}
		else
		{
			int lastPer = (i == 0 ? 0 : vec[i - 1].per);
			vec.at(i).per = lastPer + momentEightItemPers[i].per;
		}
		
	}
	int randNum = rand() % 100 + 1;
	for (auto ite = vec.rbegin(); ite != vec.rend();ite++)
	{
		if (randNum > ite->per)
		{
			return *ite;
		}
	}
	return momentEightItemPers.at(0);
}