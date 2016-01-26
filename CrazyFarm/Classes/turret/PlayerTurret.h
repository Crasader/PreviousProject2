#pragma once
#include "cocos2d.h"
#include "turret/Turret.h"
#include "domain/ai/AI.h"
#include "domain/user/user.h"
#include "domain/room/RoomPlayer.h"
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
	  void shoot(float);
	  //锁定射击
	  void beginLockShoot();
	  void endLockShoot();
	  void rorateAndShootOnlock(float dt);
	  void shootOnLock(float dt);
	  ///自动射击
	  void beginAutoShoot();
	  void endAutoShoot();
	  void rorateAndShootOnAuto(float dt);
	  void shootOnAuto(float dt);


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
	  void update(float delta); 
	 
	  ///更新炮塔信息
	  void refreshTurretInfo();
	  void setLockFish(Fish* fish);
	  Fish*getLockFish(){ return lockFish; };
	  //显示玩家信息
	  bool onTurretTouch(Point pos);
	  bool isTurretBeTouch(Point pos);
	  void showRobotInfo();
	  void showPlayerInfo();
	  void changeTurrentCallback(Ref*psend); //换炮
	  void autoShootCallback(Ref*psend);//自动开炮
	  void onPlayerUpgrade();//玩家升级
	  Turrent getTurrentMupltData(){ return m_turretdata; };
	  //攻击消耗金币
	  void costMoney();
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
	  Fish* lockFish = nullptr;
	  CC_SYNTHESIZE(Point, targetPos, TargetPos);
	  Sprite* aniFishNode=NULL;
};
