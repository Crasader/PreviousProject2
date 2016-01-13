#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__
#include "cocos2d.h"
#include "fish/FishManage.h"
#include "bullet/BulletManage.h"
#include "turret/PlayerTurret.h"
#include "net/Net.h"
#include "RoomManager.h"

USING_NS_CC;

class GameLayer: public cocos2d::Layer{
public:
	virtual bool init();
	CREATE_FUNC(GameLayer);
	void loadNewMonent();
private:
	void createTurret();//����������������
	void addTouchEvent();
	bool onTouchBegan(Touch *touch, Event  *event);
	void onTouchMoved(Touch *touch, Event  *event);
	void onTouchEnded(Touch *touch, Event  *event);
	//�����ӵ�

	void createFish(float dt);//������
	void createFishGroup(float dt);//������Ⱥ
	void createNet(Bullet *bullet);//������
	float getTurretRotation(Point pos1,Point pos2);//��ȡ������Ҫ��ת�ĽǶ�
	void rotateTurret(float degree, PlayerTurret* turret);//��ת����

	void AiUpdata(float dt);
	void onExit();
	void collisionUpdate(float dt);
	void update(float dt);
    
	void calculateFreeChair();
	PlayerTurret* myTurret;
	Vector<PlayerTurret*> otherTurrets;
	std::vector<RoomPlayer> players;
	int m_index = -1;
	
};
#endif