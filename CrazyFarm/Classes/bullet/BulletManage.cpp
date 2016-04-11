#include "bullet/BulletManage.h"
#include "domain/game/GameManage.h"

BulletManage* BulletManage::_instance = 0;

BulletManage* BulletManage::getInstance(){
	if (_instance == 0){
		_instance = new BulletManage();
	}
	return _instance;
}

BulletManage::BulletManage(){

}
void BulletManage::initBulletManage()
{
	_cacheBullet.clear();
	bulletPool.clear(); 
	for (int i = 0; i < 200;i++)
	{
		auto bullet = Bullet::create();
		bullet->retain();
		_cacheBullet.push_back(bullet);
		bullet->setTag(-1);
		bullet->setVisible(false);	
	}
}
void BulletManage::moveBulletToCacheFromPool(Bullet*bullet)
{
	bulletPool.eraseObject(bullet);
	bullet->setVisible(false);
	bullet->stopAllActions();
	bullet->unscheduleAllCallbacks();
	bullet->removeFromParentAndCleanup(false);
	bullet->setTag(-1);
	_cacheBullet.push_back(bullet);
}

Bullet* BulletManage::getFreeBulletInCache()
{
	if (_cacheBullet.size() <= 0)
	{
		return nullptr;
	}
	auto bullet = _cacheBullet.back();
	_cacheBullet.pop_back(); 
	if (bullet->getParent())
	{
		bullet->removeFromParentAndCleanup(false);
	}
	bullet->setTag(1);
	bullet->setVisible(true);
	
	return bullet;
}
void BulletManage::ClearManage()
{
	bulletPool.clear();
}
Bullet* BulletManage::createBullet(TurretData turretdata, int rotation){
	/*auto bullet = Bullet::create();*/
	auto bullet = getFreeBulletInCache();
	bullet->initBullet(turretdata, rotation);
	bulletPool.pushBack(bullet);
	return bullet;
}

Bullet* BulletManage::createBulletNoinPool(TurretData turretdata, int rotation){
	/*auto bullet = Bullet::create();*/
	auto bullet = getFreeBulletInCache();
	bullet->initBullet(turretdata, rotation);
	return bullet;
}

void BulletManage::removeBullet(Bullet* bullet){
	bulletPool.eraseObject(bullet);
}

Vector<Bullet*> &BulletManage::getAllBullets(){
	return  bulletPool;
}


