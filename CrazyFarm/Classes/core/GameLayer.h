#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__
#include "cocos2d.h"
#include "fish/FishManage.h"
#include "bullet/BulletManage.h"
#include "turret/PlayerTurret.h"
#include "net/Net.h"
#include "domain/room/RoomManager.h"
#include "domain/magnate/MagnateManager.h"
USING_NS_CC;

class GameLayer: public cocos2d::Layer{
public:
	virtual bool init();
	CREATE_FUNC(GameLayer);
	void loadNewMonent();
	void RefreShmyPlayerTurret();
	
	static float getTurretRotation(Point pos1,Point pos2);//��ȡ������Ҫ��ת�ĽǶ�
	void createNet(Bullet *bullet);//������
	PlayerTurret* GetMyTurret(){ return myTurret; }
private:
	void createTurret();//����������������
	void addTouchEvent();
	bool onTouchBegan(Touch *touch, Event  *event);
	void onTouchMoved(Touch *touch, Event  *event);
	void onTouchEnded(Touch *touch, Event  *event);
	//�����ӵ�

	void createFish(float dt);//������
	void createFishGroup(float dt);//������Ⱥ
	

	void rotateTurret(float degree, PlayerTurret* turret);//��ת����

	void AiUpdata(float dt);
	void onExit();
	//Updata
	void collisionUpdate(float dt);
	void update(float dt);

 //����
public:
	void beginLock();
	void endLock();
private:
   
	void LockUpdata(float dt);
	bool lockTouchEvent(Touch *touch, Event  *event);
	CC_SYNTHESIZE(bool, bIsOnSkillLock, bisOnSkillLock);
//�˵�
public:
	void beginSkillBoom();
	void endSkillBoom(); 
private:
	bool boomTouchEvent(Touch *touch, Event  *event);


	void calculateFreeChair();
	PlayerTurret* myTurret;
	Vector<PlayerTurret*> otherTurrets;
	std::vector<RoomPlayer> players;
	int m_index = -1;
	EventListenerTouchOneByOne* touchListener;
	bool isShoot = true;
};
#endif