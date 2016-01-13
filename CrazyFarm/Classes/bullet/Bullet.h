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
	void initBullet(int ui_type, int net_type, float rotation);
	int getType();
	CC_SYNTHESIZE(PlayerTurret*, pPlayerTurret, PlayerTurret);
	void getCoinForFish(Vector<Fish*> fishs);
	int getUitype(){ return m_ui_type; };
	int getNetType(){ return m_net_type; };
private:
	int bulletSpeed;
	int bulletType;
	int bulletRotation;
	int m_ui_type; 
	int m_net_type;

	string getSrcByType(int ui_type, int net_type);
	int getSpeedByType(int type);
	void update(float);
	bool checkHeightBorder(float y);//y边界检查
	bool checkWidthBorder(float x);//x边界检查
	Point getNextPostion(Point pos, float speed, float degree);
};
#endif