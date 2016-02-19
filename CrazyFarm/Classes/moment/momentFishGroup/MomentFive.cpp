#include "MomentFive.h"
#include "fish/FishGroupData.h"

void MomentFive::init(float FFOneTime)
{
	datas.push_back(MomentFiveData(8, 1,Vec2(-270,342)));
	datas.push_back(MomentFiveData(9, 5, Vec2(-270, 200)));
	datas.push_back(MomentFiveData(7, 10, Vec2(-270, 342)));
	datas.push_back(MomentFiveData(6, 15, Vec2(-270, 200)));
	datas.push_back(MomentFiveData(4, 20, Vec2(-270, 342)));
	
}

bool MomentFive::updata(float dt)
{
	nNowTime += dt;
	if (datas.size()<=0&&nNowTime>(20+25+10))
	{
		return true;
	}
	for (auto iter = datas.begin(); iter != datas.end();)
	{
		if (iter->startTime<nNowTime)
		{
			FishManage::getInstance()->createCycleFish(24, 160, iter->fishID, iter->pos, Vec2(1500, 0), 25);
			iter = datas.erase(iter);

		}
		else
		{
			return false;
		}
	}
	return true;

}