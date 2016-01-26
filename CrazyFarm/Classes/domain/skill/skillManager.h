#pragma once
#include "cocos2d.h"
#include "core/GameLayer.h"
#include "config/ConfigSkill.h"
#include "utill/SkillButton.h"

using namespace cocos2d;

class skillManager {

public:
	static skillManager* getInstance();
    
    
	SkillConfigInfo getSkillInfoByID(int skillid);
	int getSKillNumById(int skillid);
	int getSkillPriceById(int skillid);
	void useSkillFreeze();
	void useSkillFreezeEnd();
	void useSkillSummon();
	void useSkillLock();
	void useSkillLockEnd();
	void useSkillLight();
	void useSkillLightEnd();
	void useSkillBoom();
	void setlayer(GameLayer*layer){ m_gamelayer = layer; }
	void addskillButton(int id, SkillButton* button){ map_id_skillbutton[id] = button; };
	SkillButton* getButtonByID(int id){ return map_id_skillbutton[id]; };
	std::map<int, SkillButton*> getSkillButtons(){ return map_id_skillbutton; };
private:
	skillManager();
    void init();
	GameLayer* m_gamelayer = nullptr;
	static skillManager* _instance;
	std::map<int, bool> map_skill_isUsingnow;
	std::map<int, SkillButton*> map_id_skillbutton;

};


