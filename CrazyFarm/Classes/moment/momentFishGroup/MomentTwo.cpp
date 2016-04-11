#include "MomentTwo.h"
#include "fish/FishGroupData.h"
#include "fish/FishAniMannage.h"
#include "domain/game/GameManage.h"
void MomentTwo::initData()
{
	MomentIntervalCreate::initData();
	m_groupTag = 1;
	fishMinSize = 100;
}
bool MomentTwo::updata(float dt)
{

	nNowTime += dt;
	auto fishcount = FishManage::getInstance()->getAllFishInPoolCount();
	if (fishcount < fishMinSize&&nNowTime>50)//50 == Óã³²Ê±¼ä todo:µ¥¶ÀÅäÖÃ
	{

		GameManage::getInstance()->getGameLayer()->onClearFishFinish();
		return true;
	}
	for (auto it = info.begin(); it != info.end();)
	{
		it->_time -= dt;
		if (it->_time < 0)
		{
			FishManage::getInstance()->createFishMonmentInterval(it->_fishid, it->_startPos, it->_endPos, it->_moveTime);
			it = info.erase(it);
		}
		else
		{
			it++;
		}
	}




	return false;
}
void MomentTwo::init(float ffonetime)
{
	initData();
	Audio::getInstance()->playBGM(FISHFLOCKBGM);
	//1
	for (int i = 0; i < 18; i++)
	{
		MomentIntervalCreateFishInfo temp;
		temp._fishid = 4;
		temp._startPos = Vec2(960 + FishAniMannage::getInstance()->getSpriteById(4)->getOriginalSize().width, 425);
		temp._endPos = Vec2(-FishAniMannage::getInstance()->getSpriteById(4)->getOriginalSize().width, 425);
		temp._moveTime = 25;
		temp._time = 1.51*i;
		info.push_back(temp);
	}
	//2
	for (int i = 0; i < 19; i++)
	{
		MomentIntervalCreateFishInfo temp;
		temp._fishid = 2;
		temp._startPos = Vec2(960 + FishAniMannage::getInstance()->getSpriteById(2)->getOriginalSize().width, 380);
		temp._endPos = Vec2(-FishAniMannage::getInstance()->getSpriteById(2)->getOriginalSize().width, 380);
		temp._moveTime = 25;
		temp._time = 1.33*i;
		info.push_back(temp);
	}
	//3
	for (int i = 0; i < 11; i++)
	{
		MomentIntervalCreateFishInfo temp;
		temp._fishid = 34;
		temp._startPos = Vec2(960 + FishAniMannage::getInstance()->getSpriteById(4)->getOriginalSize().width, 350);
		temp._endPos = Vec2(-FishAniMannage::getInstance()->getSpriteById(4)->getOriginalSize().width, 350);
		temp._moveTime = 30;
		temp._time = 2.27*i;
		info.push_back(temp);
	}
	//4
	for (int i = 0; i < 11; i++)
	{
		MomentIntervalCreateFishInfo temp;
		temp._fishid = 34;
		temp._startPos = Vec2(960 + FishAniMannage::getInstance()->getSpriteById(4)->getOriginalSize().width, 190);
		temp._endPos = Vec2(-FishAniMannage::getInstance()->getSpriteById(4)->getOriginalSize().width, 190);
		temp._moveTime = 25;
		temp._time = 2.27*i;
		info.push_back(temp);
	}
	//5
	for (int i = 0; i < 19; i++)
	{
		MomentIntervalCreateFishInfo temp;
		temp._fishid = 2;
		temp._startPos = Vec2(960 + FishAniMannage::getInstance()->getSpriteById(4)->getOriginalSize().width, 160);
		temp._endPos = Vec2(-FishAniMannage::getInstance()->getSpriteById(4)->getOriginalSize().width, 160);
		temp._moveTime = 25;
		temp._time = 1.33*i;
		info.push_back(temp);
	}


	//6
	for (int i = 0; i < 18; i++)
	{
		MomentIntervalCreateFishInfo temp;
		temp._fishid = 4;
		temp._startPos = Vec2(960 + FishAniMannage::getInstance()->getSpriteById(4)->getOriginalSize().width, 115);
		temp._endPos = Vec2(-FishAniMannage::getInstance()->getSpriteById(4)->getOriginalSize().width, 115);
		temp._moveTime = 25;
		temp._time = 1.51*i;
		info.push_back(temp);
	}
	//7
	for (int i = 0; i < 18; i++)
	{
		MomentIntervalCreateFishInfo temp;
		temp._fishid = 1;
		temp._startPos = Vec2(960 + FishAniMannage::getInstance()->getSpriteById(4)->getOriginalSize().width, 320);
		temp._endPos = Vec2(-FishAniMannage::getInstance()->getSpriteById(4)->getOriginalSize().width, 320);
		temp._moveTime = 25;
		temp._time = 1.51*i;
		info.push_back(temp);
	}
	//8
	for (int i = 0; i < 18; i++)
	{
		MomentIntervalCreateFishInfo temp;
		temp._fishid = 1;
		temp._startPos = Vec2(960 + FishAniMannage::getInstance()->getSpriteById(4)->getOriginalSize().width, 220);
		temp._endPos = Vec2(-FishAniMannage::getInstance()->getSpriteById(4)->getOriginalSize().width, 220);
		temp._moveTime = 25;
		temp._time = 1.51*i;
		info.push_back(temp);
	}
	//9
	for (int i = 0; i < 2; i++)
	{
		MomentIntervalCreateFishInfo temp;
		temp._fishid = 33;
		temp._startPos = Vec2(960 + FishAniMannage::getInstance()->getSpriteById(4)->getOriginalSize().width, 270);
		temp._endPos = Vec2(-FishAniMannage::getInstance()->getSpriteById(4)->getOriginalSize().width, 270);
		temp._moveTime = 25;
		temp._time = 1.76*i+1;
		info.push_back(temp);
	}
	//10
	for (int i = 0; i < 1; i++)
	{
		MomentIntervalCreateFishInfo temp;
		temp._fishid = 7;
		temp._startPos = Vec2(960 + FishAniMannage::getInstance()->getSpriteById(4)->getOriginalSize().width, 270);
		temp._endPos = Vec2(-FishAniMannage::getInstance()->getSpriteById(4)->getOriginalSize().width, 270);
		temp._moveTime = 25;
		temp._time = 0 + 5;
		info.push_back(temp);
	}
	//11
	for (int i = 0; i < 3; i++)
	{
		MomentIntervalCreateFishInfo temp;
		temp._fishid = 33;
		temp._startPos = Vec2(960 + FishAniMannage::getInstance()->getSpriteById(4)->getOriginalSize().width, 270);
		temp._endPos = Vec2(-FishAniMannage::getInstance()->getSpriteById(4)->getOriginalSize().width, 270);
		temp._moveTime = 25;
		temp._time = 1.76*i + 8;
		info.push_back(temp);
	}
	//12
	for (int i = 0; i < 1; i++)
	{
		MomentIntervalCreateFishInfo temp;
		temp._fishid = 43;
		temp._startPos = Vec2(960 + FishAniMannage::getInstance()->getSpriteById(4)->getOriginalSize().width, 270);
		temp._endPos = Vec2(-FishAniMannage::getInstance()->getSpriteById(4)->getOriginalSize().width, 270);
		temp._moveTime = 25;
		temp._time = 2.3*i + 16;
		info.push_back(temp);
	}
	//13
	for (int i = 0; i < 1; i++)
	{
		MomentIntervalCreateFishInfo temp;
		temp._fishid = 41;
		temp._startPos = Vec2(960 + FishAniMannage::getInstance()->getSpriteById(4)->getOriginalSize().width, 270);
		temp._endPos = Vec2(-FishAniMannage::getInstance()->getSpriteById(4)->getOriginalSize().width, 270);
		temp._moveTime = 25;
		temp._time = 2.3*i + 23;
		info.push_back(temp);
	}

}