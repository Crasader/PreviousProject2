#pragma once
#include "cocos2d.h"
#include "core/GameLayer.h"
#include "config/ConfigSkill.h"

using namespace cocos2d;

class skillManager {

public:
	static skillManager* getInstance();
    
    
	SkillConfigInfo skillManager::getSkillInfoByID(int skillid);
	int getSKillNumById(int skillid);

	void useSkillFreeze();
	void useSkillFreezeEnd();
	void useSkillSummon();

	void setlayer(GameLayer*layer){ m_gamelayer = layer; }
private:
	skillManager();
    void init();
	GameLayer* m_gamelayer = nullptr;
	static skillManager* _instance;
	std::map<int, bool> map_skill_isUsingnow;

};


