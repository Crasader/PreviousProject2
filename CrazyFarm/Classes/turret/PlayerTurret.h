#pragma once
#include "cocos2d.h"
#include "turret/Turret.h"
#include "AI.h"
#include "user.h"
#include "RoomPlayer.h"
#include "fish/Fish.h"
#include "config/ConfigTurrent.h"
USING_NS_CC;
class PlayerTurret : public Sprite{
public:
      virtual bool init();
	  CREATE_FUNC(PlayerTurret);
	  void initWithDate(User* user,int index);
	  void initWithDate(RoomPlayer* user);
	  void createPlayerCoin(User* user, int index);
	  void createPlayerCoin(RoomPlayer* user);

	  void initWithType(int type);
	  void setUpgradeButton();
	  void rorateTurret(float angle);
	  void setMaxLevel(int maxlevel);
	  void shoot(float);
	 
	  // ’∏Ó”„
	  void getCoinByFish(Fish* fish);
	  //AI
	  void setAIinfo(AI* info);
	  void doAIthing(float dt);
private:
	Turrent  m_turretdata;
	  int turretType;
	  void upgradeTurret(Ref* psend);
	  void degradeTurret(Ref* psend);

	  LabelAtlas* nCurLevel;
	  LabelAtlas*m_CoinLabel;
	  LabelAtlas*m_DiamondLabel;
	  AI* m_aiinfo;
	  CC_SYNTHESIZE(int, nMaxlevel, nMaxLevel);
	  bool isRobot = true;

	  Turret* m_turret;
	  int nChairNoIndex = -1;

};
