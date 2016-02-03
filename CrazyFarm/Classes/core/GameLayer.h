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
enum TouchType
{
	TouchInNormal,
	TouchInLock,
	TouchInBoom,
	TouchInAutoShoot,
	TouchInLight
};

class GameLayer: public cocos2d::Layer{
public:
	virtual bool init();
	CREATE_FUNC(GameLayer);
	void loadNewMonent();
	void RefreShmyPlayerTurret();
	
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
	void beginLight();
	void endLight();
	void LightUpdata(float dt);
	bool lightTouchEvent(Touch *touch, Event  *event);
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
	void onBoomCatchFish(Point pos); 
private:
	bool boomTouchEvent(Touch *touch, Event  *event);
	
//�Զ�����
public:
	void beginAutoShoot();
	void endAutoShoot();
private:
	Point autoShootPos;
	bool AutoShootTouchEvent(Touch *touch, Event  *event);
////////////����
public:
	void onFreezeBegin();
	void onFreezeEnd();
////�㳱����
	void onClearFish();
	void onClearFishUpdata(float dt);
private:
	

	//�����
	bool onTouTurret(Point pos);
	void removePlayerInfo();
	void calculateFreeChair();
	PlayerTurret* myTurret;
	Vector<PlayerTurret*> otherTurrets;
	std::vector<RoomPlayer> players;
	int m_index = -1;
	EventListenerTouchOneByOne* touchListener;
	bool isShoot = true;
//����¼�
	void changeTouchFunByTouchType(TouchType type);
	TouchType m_touchType;
	TouchType m_lasttouchType;
	Sprite* game_bg;
};
#endif