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
	SkillConfigInfo getSkillInfoByitemId(int itemID);
	int isSatisfyBuySkill(int skillid); //返回值1：VIP等级不够 2：炮塔等级不够 0: 满足
	int getSKillNumById(int skillid);
	int getSkillPriceById(int skillid);

	void robotUseSkillFreeze(PlayerTurret*turret);
	void useSkillFreeze(PlayerTurret*turret);
	void useSkillFreezeEnd(PlayerTurret*turret);

	void useSkillSummon(PlayerTurret*turret);
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
	CC_SYNTHESIZE(bool, isUseSkillNow, IsUseSkillNow);
	std::map<int, bool> map_skill_isUsingnow;
	std::map<int, SkillButton*> map_id_skillbutton;

};


