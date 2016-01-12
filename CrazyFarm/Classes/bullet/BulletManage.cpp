#include "bullet/BulletManage.h"


BulletManage* BulletManage::_instance = 0;

BulletManage* BulletManage::getInstance(){
	if (_instance == 0){
		_instance = new BulletManage();
	}
	return _instance;
}

BulletManage::BulletManage(){

}

void BulletManage::ClearManage()
{
	bulletPool.clear();
}
Bullet* BulletManage::createBullet(int type,int rotation){
	auto bullet = Bullet::create();
	bullet->initBullet(type,rotation);
	bulletPool.pushBack(bullet);
	return bullet;
}

void BulletManage::removeBullet(Bullet* bullet){
	bulletPool.eraseObject(bullet);
}

Vector<Bullet*> BulletManage::getAllBullets(){
	return  bulletPool;
}


