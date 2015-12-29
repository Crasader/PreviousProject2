#pragma once
#include "cocos2d.h"
#include "turret/Turret.h"
#include "AI.h"
USING_NS_CC;


class PlayerTurret : public Sprite{
public:
      virtual bool init();
	  CREATE_FUNC(PlayerTurret);
	  void initWithType(int type);
	  void setUpgradeButton();
	  void rorateTurret(float angle);
	  void setMaxLevel(int maxlevel);
	  void shoot(float);

	  //AI
	  void setAIinfo(AI info);
	  void doAIthing(float dt);
private:
	 Turret* m_turret;
	  int turretType;
	  void upgradeTurret(Ref* psend);
	  void degradeTurret(Ref* psend);
	  LabelAtlas* nMaxLevel;
	  

	  AI m_aiinfo;
	  CC_SYNTHESIZE(int, nMaxlevel, nMaxLevel);

};
