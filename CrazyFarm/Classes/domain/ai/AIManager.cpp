#include "domain/ai/AIManager.h"
#include "data/GameData.h"
#include "domain/game/GameManage.h"
#include "utill/FunUtil.h"
#include "AIJun.h"
#include"AILei.h"
AIManager* AIManager::_instance = NULL;

AIManager::AIManager(){
    this->init();
}

void AIManager::init(){
	setNowCreateGoldFish(1);
}

AIManager* AIManager::getInstance(){
    if(_instance == NULL){
        _instance = new AIManager();
    }
    return _instance;
}

AI* AIManager::getAI( int maxTurrentLevel) {
    int who = getRand()%100;
    if(who < 40) {
		AI* molo = new AIHu();
        if(maxTurrentLevel > 0) {
            molo->setMaxTurrentLevel(maxTurrentLevel);
        }else {
            molo->setMaxTurrentLevel(1);
        }
        
        molo->setReqSteps(0.2f);
        return molo;
    }
	else if (who<60)
	{
		AI*hu = new AIJun();
		hu->setMaxTurrentLevel(maxTurrentLevel);
		hu->setReqSteps(0.2f);
		return hu;
	}
	else if (who < 80)
	{
		AI*hu = new AIMolo();
		hu->setMaxTurrentLevel(maxTurrentLevel);
		hu->setReqSteps(0.2f);
		return hu;
	}
	else
    {
		AI*jun = new AILei();
		jun->setMaxTurrentLevel(maxTurrentLevel);
		jun->setReqSteps(0.2f);
		return jun;
    }
}

bool AIManager::allowAiFire() {
    return aiFire;
}

void AIManager::setAiFire(bool allow) {
     aiFire = allow;
}

void  AIManager::MainUpdata(float dt)
{
	
}

void AIManager::addCreateGoldFish()
{
	const int maxvalue = 99999999;
	nNowCreateGoldFish++;
	auto turrets = GameManage::getInstance()->getGameLayer()->GetOtherTurret();
	for (auto var:turrets)
	{
		if (var->getTag()==-1)
		{
			break;
		}
		int lv = var->getTurrentMupltData().multiple;
		int goldfishneedcounts[5];//±ù¶³Ëø¶¨ÕÙ»½ºËµ¯¼¤¹â
		if (lv >= 1 && lv <= 10)
		{
			goldfishneedcounts[0] = maxvalue;
			goldfishneedcounts[1] = 7;
			goldfishneedcounts[2] = maxvalue;
			goldfishneedcounts[3] =maxvalue;
			goldfishneedcounts[4] = maxvalue;
			/*	goldfishneedcounts[0] = 10;
				goldfishneedcounts[1] = 13;
				goldfishneedcounts[2] = 22;
				goldfishneedcounts[3] = 4;
				goldfishneedcounts[4] = 4;*/
		}
		else if (lv > 10 && lv <= 30)
		{
			goldfishneedcounts[0] = 17;
			goldfishneedcounts[1] = 6;
			goldfishneedcounts[2] = 30;
			goldfishneedcounts[3] = maxvalue;
			goldfishneedcounts[4] = maxvalue;
		}
		else if (lv > 30 && lv <= 100)
		{
			goldfishneedcounts[0] = 13.5;
			goldfishneedcounts[1] = 6;
			goldfishneedcounts[2] = 27.5;
			goldfishneedcounts[3] = 35;
			goldfishneedcounts[4] = maxvalue;
		}
		else if (lv > 100 && lv <= 300)
		{
			goldfishneedcounts[0] = 11;
			goldfishneedcounts[1] = 4;
			goldfishneedcounts[2] = 23;
			goldfishneedcounts[3] = 25;
			goldfishneedcounts[4] = maxvalue;
		}
		else if (lv > 300 && lv <= 500)
		{
			goldfishneedcounts[0] = 9;
			goldfishneedcounts[1] = 4;
			goldfishneedcounts[2] = 13;
			goldfishneedcounts[3] = 17;
			goldfishneedcounts[4] = maxvalue;
		}
		else if (lv > 500 && lv <= 1000)
		{
			goldfishneedcounts[0] = 9;
			goldfishneedcounts[1] = 3;
			goldfishneedcounts[2] = 10;
			goldfishneedcounts[3] = 13;
			goldfishneedcounts[4] = 45;
		}
		for (int i = 0; i < 5;i++)
		{
			if (nNowCreateGoldFish % goldfishneedcounts[i] == 0)
			{
				skillManager::getInstance()->useSkillById(i + 1, var);
			}
		}/*
		if (nNowCreateGoldFish % goldfishneedcounts[0] == 0)
		{
			skillManager::getInstance()->useSkillFreeze(var);
		}
		if (nNowCreateGoldFish % goldfishneedcounts[1] == 0)
		{
			skillManager::getInstance()->useSkillLock(var);
			
		}
		if (nNowCreateGoldFish % goldfishneedcounts[2] == 0)
		{
			skillManager::getInstance()->useSkillSummon(var);
			
		}
		if (nNowCreateGoldFish % goldfishneedcounts[3] == 0)
		{
			skillManager::getInstance()->useSkillLight(var);
			
		}
		if (nNowCreateGoldFish % goldfishneedcounts[4] == 0)
		{
			skillManager::getInstance()->useSkillBoom(var);
		
		}*/
	}
}