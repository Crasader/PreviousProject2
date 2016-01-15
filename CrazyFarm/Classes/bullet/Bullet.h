#ifndef __BULLET_H__
#define __BULLET_H__
#include "cocos2d.h" 
#include "turret/PlayerTurret.h"
#include "fish/Fish.h"
using namespace cocos2d;
using namespace std;

#define BULLETTYPE_1 0
#define BULLETTYPE_2 1
#define BULLETTYPE_3 2
#define BULLETTYPE_4 3
#define BULLETTYPE_5 4
#define BULLETTYPE_6 5
#define BULLETTYPE_7 6
#define BULLETTYPE_8 7

class Bullet:public Sprite{
public:
	virtual bool init();
	CREATE_FUNC(Bullet);
	void initBullet(TurretData turretdata, float rotation);

	CC_SYNTHESIZE(PlayerTurret*, pPlayerTurret, PlayerTurret);
	void getCoinForFish(Vector<Fish*> fishs);
	TurretData getTurretdata(){ return m_turretdata; };

	void moveToLockfish(float time,Fish*fish);
private:
	int bulletSpeed;
	int bulletRotation;

	TurretData m_turretdata;
	string getSrcByType(int ui_type, int net_type);
	int getSpeedByType(int type);
	void update(float);
	bool checkHeightBorder(float y);//y边界检查
	bool checkWidthBorder(float x);//x边界检查
	Point getNextPostion(Point pos, float speed, float degree);
};
#endif