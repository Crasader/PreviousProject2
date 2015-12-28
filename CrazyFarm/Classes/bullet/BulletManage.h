#ifndef __BULLET_MANAGE_H__
#define __BULLET_MANAGE_H__
#include "bullet/Bullet.h"

class BulletManage{
public:
	static BulletManage* getInstance();
	Bullet* createBullet(int type, int rotation);
	void removeBullet(Bullet* bullet);
	Vector<Bullet*> getAllBullets();
private:
	BulletManage();
	static BulletManage* _instance;
	Vector<Bullet*> bulletPool;
};
#endif