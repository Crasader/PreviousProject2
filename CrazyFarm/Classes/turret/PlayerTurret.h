#pragma once
#include "cocos2d.h"
#include "turret/Turret.h"
USING_NS_CC;


class PlayerTurret : public Sprite{
public:
      virtual bool init();
	  CREATE_FUNC(PlayerTurret);
	  void initWithType(int type);
	  void setUpgradeButton();
	  void rorateTurret(float angle);
private:
		Turret* m_turret;
	  int turretType;
	  void upgradeTurret(Ref* psend);
	  void degradeTurret(Ref* psend);

};
