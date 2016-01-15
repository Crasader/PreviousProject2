#include "moment/MomentEight.h"


void MomentEight::init()
{
	fInterval = 1.0f;
	fTemp = fInterval;

}

bool MomentEight::updata(float dt)
{
	nNowTime += dt;
	fTemp -= dt;
	if (nNowTime>100)
	{
		return true;
	}
	if (fTemp <= 0)
	{
		fTemp = fInterval;
		FishManage::getInstance()->createFishRand();		
	}
	return false;

}