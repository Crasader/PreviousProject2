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
	void beginLock();	
	void endLock();
	static float getTurretRotation(Point pos1,Point pos2);//获取炮塔需要旋转的角度
	void createNet(Bullet *bullet);//打开渔网
	PlayerTurret* GetMyTurret(){ return myTurret; }
private:
	void createTurret();//按照类型生成炮塔
	void addTouchEvent();
	bool onTouchBegan(Touch *touch, Event  *event);
	void onTouchMoved(Touch *touch, Event  *event);
	void onTouchEnded(Touch *touch, Event  *event);
	//发射子弹

	void createFish(float dt);//产生鱼
	void createFishGroup(float dt);//产生鱼群
	

	void rotateTurret(float degree, PlayerTurret* turret);//旋转炮塔

	void AiUpdata(float dt);
	void onExit();
	//Updata
	void collisionUpdate(float dt);
	void update(float dt);

	
	
    //锁定
	
	void LockUpdata(float dt);
	bool lockTouchEvent(Touch *touch, Event  *event);
	CC_SYNTHESIZE(bool, bIsOnSkillLock, bisOnSkillLock);
	void calculateFreeChair();
	PlayerTurret* myTurret;
	Vector<PlayerTurret*> otherTurrets;
	std::vector<RoomPlayer> players;
	int m_index = -1;
	EventListenerTouchOneByOne* touchListener;
	bool isShoot = true;
};
#endif