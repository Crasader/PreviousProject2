#include "core/GameLayer.h"
#include "net/Net.h"
#include "utill/FunUtil.h"


bool GameLayer::init(){
	if (!Layer::init())
	{
		return false;
	}
	//add game bg to this layer
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* game_bg = Sprite::create("lobby_bg.jpg");
	game_bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(game_bg);
	//TODO ��Ϸ���Ľ���
	createTurret(0);
	//TODO ������
	schedule(schedule_selector(GameLayer::createFish), 1, 100, 0);
	scheduleUpdate();
	addTouchEvent();

	return true;
}


void GameLayer::createFish(float dt){
	Fish* fish = FishManage::getInstance()->createFishSingle();
	FishManage::getInstance()->decideFishPos(fish);
	fish->move(1);
	this->addChild(fish);
}

void GameLayer::createTurret(int type){
	//����һ���������ڲ���
	Size visibleSize = Director::getInstance()->getVisibleSize();
	myTurret = Turret::create();
	myTurret->initWithType(0);
	myTurret->setAnchorPoint(ccp(0.5, 0.5));
	myTurret->setPosition(ccp(visibleSize.width / 2, myTurret->getBoundingBox().size.height / 2));
	this->addChild(myTurret, 2);
}



void GameLayer::shoot(float degree){
	//����һ���ӵ����ڲ���
	auto bullet = BulletManage::getInstance()->createBullet(rand()%8, 90);
	bullet->setRotation(degree);
	bullet->setPosition(myTurret->getPosition());
	this->addChild(bullet);
}


void GameLayer::addTouchEvent(){
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

bool GameLayer::onTouchBegan(Touch *touch, Event  *event)
{
	float degree = getTurretRotation(myTurret->getPosition(), touch->getLocation());
	rotateTurret(degree);
	shoot(degree);
	return true;
}

void GameLayer::onTouchMoved(Touch *touch, Event  *event)
{
	//TODO ��Ҫ�����ӵ����
	//float degree = getTurretRotation(myTurret->getPosition(), touch->getLocation());
	//rotateTurret(degree);
	//shoot(degree);

}

void  GameLayer::onTouchEnded(Touch *touch, Event  *event)
{
	//��ʱ��������
}


float GameLayer::getTurretRotation(Point start_pos, Point pos){
	//��������֮��ĽǶ�
	double len_y = pos.y - start_pos.y;
	double len_x = pos.x - start_pos.x;

	double tan_yx = tan_yx = abs(len_y) / abs(len_x);
	float angle = 0;
	if (len_y > 0 && len_x < 0) {
		angle = atan(tan_yx) * 180 / M_PI - 90;
	}
	else if (len_y > 0 && len_x > 0) {
		angle = 90 - atan(tan_yx) * 180 / M_PI;
	}
	else if (len_y < 0 && len_x < 0) {
		angle = -atan(tan_yx) * 180 / M_PI - 90;
	}
	else if (len_y < 0 && len_x > 0) {
		angle = atan(tan_yx) * 180 / M_PI + 90;
	}
	return angle;
}

void GameLayer::rotateTurret(float degree){
	auto rotate = RotateTo::create(0.1, degree);
	myTurret->runAction(rotate);
}

void GameLayer::update(float dt){
	//TODO ��ײ�߼�
	//step1 ��ȡ�ӵ��б�
	auto allBullets = BulletManage::getInstance()->getAllBullets();
	//step2 ��ȡ����б�
	auto allFish = FishManage::getInstance()->getAllFishInPool();
	//step3 ��ײ���
	Vector<Fish*>::iterator it;
	Vector<Bullet*> bulletNeedRemove;
	for (it = allFish.begin(); it != allFish.end(); it++){
		Vector<Bullet*>::iterator it2;
		for (it2 = allBullets.begin(); it2 != allBullets.end();){
			Fish* fish = *it;
			Bullet* bullet = *it2;
			if (collision(fish,bullet)){
				//������ײ,�Ƴ��ӵ�
				bulletNeedRemove.pushBack(bullet);
				bullet->removeFromParent();
				it2 = allBullets.erase(it2);
				//TODO������
				createNet(bullet->getType(), bullet->getPosition());
			}
			else{
				it2++;
			}
			if (bulletNeedRemove.size() > 0){
				for (Bullet* bullet : bulletNeedRemove){
					BulletManage::getInstance()->removeBullet(bullet);
				}
			}
		}
	}
}


void GameLayer::createNet(int type, Point pos){
	Net* fishNet = Net::create();
	fishNet->setPosition(pos);
	fishNet->initNetByType(type);
	this->addChild(fishNet, 3);
	fishNet->checkCatchFish();
}

