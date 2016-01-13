#pragma once
#include "cocos2d.h"
#include "turret/Turret.h"
#include "AI.h"
#include "user.h"
#include "RoomPlayer.h"
#include "fish/Fish.h"
#include "config/ConfigTurrent.h"
USING_NS_CC;

struct TurretData
{
	int turrent_id;
	int turrent_ui_id; // 显示ui
	double net_per; // 打击面积系数
	double catch_per; // 捕获概率系数
	int ui_type; // 1火焰;2冰冻
	int net_type;  // 1,1张网;2,2张;3,三张
	TurretData(){};
	void init(int id, int uiid, double netPer, double catchper, int uiType, int netType){ turrent_id = id, turrent_ui_id = uiid, net_per = netPer, catch_per = catchper; ui_type = uiType, net_type = netType; }
};



class PlayerTurret : public Sprite{
public:
      virtual bool init();
	  CREATE_FUNC(PlayerTurret);
	  void initWithDate(User* user,int index);
	  void initWithDate(RoomPlayer* user);
	  void createPlayerCoin(User* user, int index);
	  void createPlayerCoin(RoomPlayer* user);

	  void initTurretWithType();
	  void initTurretWithTypeForRobot();
	  void setUpgradeButton();
	  void rorateTurret(float angle);
	  void setMaxLevel(int maxlevel);
	  void shoot(float);
	  float getRarote(){ return m_turret->getRotation(); }
	  //收割鱼
	  void getCoinByFish(Fish* fish);
	  //AI
	  void setAIinfo(AI* info);
	  void doAIthing(float dt);
	  void stopAI();
	  //破产
	  void onBankrupt();
	  void onAIResurgenceCallBack(Node* sender, void* data);
	  std::string getNetImgPath(int ui_type, int net_type);
	  void update(float delta); 
private:
	Turrent  m_turretdata;
	  int turretType;
	  void upgradeTurret(Ref* psend);
	  void degradeTurret(Ref* psend);
	  void onExit();
	  LabelAtlas* nCurLevel;
	  LabelAtlas*m_CoinLabel;
	  LabelAtlas*m_DiamondLabel;
	  AI* m_aiinfo;
	  CC_SYNTHESIZE(int, nMaxlevel, nMaxLevel);
	  bool isRobot = true;
	  TurretData turretdata;
	  Turret* m_turret;
	  int nChairNoIndex = -1;
	  int nNowMoney;
	  RoomPlayer* m_robotData;

};
