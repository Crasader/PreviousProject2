#ifndef __BULLET_MANAGE_H__
#define __BULLET_MANAGE_H__
#include "bullet/Bullet.h"

class BulletManage{
public:
	static BulletManage* getInstance();
	Bullet* createBullet(TurretData turretdata, int rotation);
	Bullet* createBulletNoinPool(TurretData turretdata, int rotation);
	void removeBullet(Bullet* bullet);
	void initBulletManage();
	Vector<Bullet*> &getAllBullets();
	void ClearManage();
	int getBulletPoolSize(){ return bulletPool.size(); };
public:
	void moveBulletToCacheFromPool(Bullet*bullet);
private:
	Bullet* getFreeBulletInCache();
private:
	BulletManage();
	static BulletManage* _instance;
	std::vector<Bullet*> _cacheBullet;
	Vector<Bullet*> bulletPool;
};
#endif