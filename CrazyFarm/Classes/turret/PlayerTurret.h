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
	int turrent_ui_id; // ��ʾui
	double net_per; // ������ϵ��
	double catch_per; // �������ϵ��
	int ui_type; // 1����;2����
	int net_type;  // 1,1����;2,2��;3,����
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
	  //�������
	  void beginLockShoot();
	  void endLockShoot();
	  void rorateAndShootOnlock(float dt);
	  void shootOnLock(float dt);
	  ///�Զ����
	  void beginAutoShoot();
	  void endAutoShoot();
	  void rorateAndShootOnAuto(float dt);
	  void shootOnAuto(float dt);


	  float getRarote(){ return m_turret->getRotation(); }
	  //�ո���
	  void getCoinByFish(Fish* fish);
	  //AI
	  void setAIinfo(AI* info);
	  void doAIthing(float dt);
	  void stopAI();
	  //�Ʋ�
	  void onBankrupt();
	  void onAIResurgenceCallBack(Node* sender, void* data);
	  void update(float delta); 
	 
	  ///����������Ϣ
	  void refreshTurretInfo();
	  void setLockFish(Fish* fish);
	  Fish*getLockFish(){ return lockFish; };
	  //��ʾ�����Ϣ
	  bool onTurretTouch(Point pos);
	  bool isTurretBeTouch(Point pos);
	  void showRobotInfo();
	  void showPlayerInfo();
	  void changeTurrentCallback(Ref*psend); //����
	  void autoShootCallback(Ref*psend);//�Զ�����
	  void onPlayerUpgrade();//�������
	  Turrent getTurrentMupltData(){ return m_turretdata; };
	  //�������Ľ��
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
