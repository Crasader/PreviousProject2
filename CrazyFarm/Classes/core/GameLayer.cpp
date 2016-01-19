#include "core/GameLayer.h"
#include "net/Net.h"
#include "utill/FunUtil.h"
#include "utill/AnimationUtil.h"
#include "utill/CircleMoveTo.h"
#include "domain/user/User.h"
#include "domain/ai/AIManager.h"
#include "fish/FishGroupData.h"
#include "data/GameData.h"
#include "config/ConfigRoom.h"
#include "fish/FishArrangeOne.h"
#include "domain/skill/skillManager.h"
#include "utill/CCircle.h"
#include "domain/gameConfig/gameConfig.h"

#define kTagBaseturret 10
#define BOOMRADIUS 300


bool GameLayer::init(){
	if (!Layer::init())
	{
		return false;
	}
	FishManage::getInstance()->setlayer(this);
	skillManager::getInstance()->setlayer(this);
	//add game bg to this layer
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* game_bg = Sprite::create("ani/water/aniWater1.jpg");
	game_bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(game_bg);
	game_bg->runAction(RepeatForever::create(AnimationUtil::getInstance()->getAnimate("aniWater")));
	//TODO 游戏核心界面
	
	//TODO 产生鱼
	/*schedule(schedule_selector(GameLayer::createFish), 0.3f,CC_REPEAT_FOREVER, 20.0f);
	schedule(schedule_selector(GameLayer::createFishGroup), 180.0f, CC_REPEAT_FOREVER, 2.0f);*/
	scheduleUpdate();
	addTouchEvent();	
    auto roominfo = ConfigRoom::getInstance()->getRoombyId(GameData::getInstance()->getRoomID());
	players = RoomManager::getInstance()->initRoomConfig(roominfo.unlock_turrent_level);
	calculateFreeChair();
	createTurret();
	schedule(schedule_selector(GameLayer::collisionUpdate), 1.0 / 60.0f, CC_REPEAT_FOREVER, 0);

	loadNewMonent();

	//for (int i = 0; i < 10;i++)
	//{
	//	FishManage::getInstance()->createFishRand(52);
	//}
	setbisOnSkillLock(false);

	GameData::getInstance()->setShotCount(0);
	GameData::getInstance()->setevent(MagnateManager::getInstance()->getDiamandMagnateEvent());
	return true;
}





void GameLayer::createFish(float dt){
	if (FishManage::getInstance()->getAllFishInPoolCount() < 30) {
		int create = rand() % 100;
		if (create < 80) {
			Fish* fish = FishManage::getInstance()->createFishSingle();
			FishManage::getInstance()->decideFishPos(fish);
			fish->move(3);
			this->addChild(fish);
		}
	}
}


void GameLayer::createFishGroup(float dt)
{
	auto gp = FishGroupData::getInstance()->getGroupBytag(rand()%3+1);
	for (int i = 0; i < gp.singleTypefishGroups.size();i++)
	{
		auto singlegp = gp.singleTypefishGroups[i];
		for (int j = 0; j < singlegp.fishCount;j++)
		{
			runAction(Sequence::create(DelayTime::create(j*singlegp.IntervalCreateTime), CallFunc::create([=]{
				Fish* fish = FishManage::getInstance()->createFishSingle(singlegp.fishID);
				fish->setRoute(singlegp.fishRoute);
				fish->setPosition(singlegp.startPos);
				addChild(fish);
			}), nullptr));
		}
		
	}
	
}

void GameLayer::createTurret(){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto vec = players;
	auto user = User::getInstance();

	myTurret = PlayerTurret::create();
	const Point turretPos[4] =
	{
		Vec2(visibleSize.width *0.3, myTurret->getBoundingBox().size.height / 2),
		Vec2(visibleSize.width *0.7, myTurret->getBoundingBox().size.height / 2),
		Vec2(visibleSize.width *0.7, visibleSize.height - myTurret->getBoundingBox().size.height / 2),
		Vec2(visibleSize.width *0.3, visibleSize.height - myTurret->getBoundingBox().size.height / 2)
	};
	
	myTurret->initWithDate(user, m_index);
	myTurret->setAnchorPoint(ccp(0.5, 0.5));
	myTurret->setPosition(turretPos[m_index]);
	this->addChild(myTurret, 2);

	for (auto player:vec)
	{
		auto otherTurret = PlayerTurret::create();
		otherTurret->setAnchorPoint(ccp(0.5, 0.5));
		otherTurret->setPosition(turretPos[player.getRoomPosition()]);
		otherTurret->initWithDate(&player);
		otherTurrets.pushBack(otherTurret);
		addChild(otherTurret, 2, kTagBaseturret+player.getRoomPosition());
		
	}
	
}




void GameLayer::addTouchEvent(){
	touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

bool GameLayer::onTouchBegan(Touch *touch, Event  *event)
{
	const float shootInterval = GameConfig::getInstance()->getShootData().shootInterval;
	if (!isShoot)
	{
		return true;
	}
	float degree = getTurretRotation(myTurret->getPosition(), touch->getLocation());
	rotateTurret(degree, myTurret);
	GameData::getInstance()->setShotCount(1+(GameData::getInstance()->getShotCount()));
	runAction(Sequence::create(DelayTime::create(0.1f), CallFunc::create([&]{
		CCLOG("turret rotate%f", myTurret->getRarote());
		myTurret->shoot(myTurret->getRarote()); 
	}), nullptr));
	isShoot = false;
	runAction(Sequence::create(DelayTime::create(shootInterval), CallFunc::create([&]{
		isShoot = true;
	}), nullptr));
	return true;
}

bool GameLayer::lockTouchEvent(Touch *touch, Event  *event)
{
	auto pos = touch->getLocation();
	auto fish = FishManage::getInstance()->getFishByPosInPool(pos);
	if (fish)
	{
		myTurret->setLockFish(fish);
	}
	return false;
}


void GameLayer::onTouchMoved(Touch *touch, Event  *event)
{


}

void  GameLayer::onTouchEnded(Touch *touch, Event  *event)
{
	
}


float GameLayer::getTurretRotation(Point start_pos, Point pos){
	//计算两点之间的角度
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

void GameLayer::rotateTurret(float degree,PlayerTurret* turret){
	turret->rorateTurret(degree);
}

void GameLayer::update(float dt){
	FishManage::getInstance()->UpdateWhenController(dt);
}


void GameLayer::createNet(Bullet *bullet){
	Net* fishNet = Net::create();
	fishNet->setBullet(bullet);
	fishNet->setPosition(bullet->getPosition());
	fishNet->setRotation(bullet->getRotation());
	fishNet->initNetByType();
	this->addChild(fishNet, 3);
}


void GameLayer::calculateFreeChair()
{
	std::map<int, bool> findFreeTable;
	for (int i = 0; i < 4; i++)
	{
		findFreeTable[i] = true;
	}
	for (auto player : players)
	{
		findFreeTable[player.getRoomPosition()] = false;
	}
	for (int i = 0; i < 4; i++)
	{
		if (findFreeTable[i])
		{
			m_index = i;
			break;
		}

	}
	

}

void GameLayer::AiUpdata(float dt)
{
	
}

void GameLayer::collisionUpdate(float dt)
{


	//TODO 碰撞逻辑
	//step1 获取子弹列表
	auto allBullets = BulletManage::getInstance()->getAllBullets();
	//step2 获取鱼的列表
	auto allFish = FishManage::getInstance()->getAllFishInPool();
	//step3 碰撞检查
	Vector<Bullet*> bulletNeedRemove;
	for (auto bullet:allBullets)
	{
		for (auto fish:allFish)
		{
			if (collision(fish, bullet)){
				//发生碰撞,移除子弹
				bulletNeedRemove.pushBack(bullet);
				bullet->removeFromParent();
				//TODO打开渔网
				createNet(bullet);
				break;
			}
		}
	}


	//Vector<Fish*>::iterator it;
	//Vector<Bullet*> bulletNeedRemove;
	//for (Vector<Bullet*>::iterator it2 = allBullets.begin(); it2 != allBullets.end();)
	//{
	//	for (auto it = allFish.begin(); it != allFish.end(); it++)
	//	{
	//		Fish* fish = *it;
	//		Bullet* bullet = *it2;
	//		if (collision(fish, bullet)){
	//			//发生碰撞,移除子弹
	//			/*bulletNeedRemove.pushBack(bullet);*/
	//			bullet->removeFromParent();
	//			it2 = allBullets.erase(it2);
	//			//TODO打开渔网
	//			createNet(bullet);
	//			break;

	//		}
	//	}
	//	if (++it2 != allBullets.end())
	//	{
	//		
	//	}
	//	else
	//	{
	//		break;
	//	}
	//	
	//}/*if (bulletNeedRemove.size() > 0){

				for (Bullet* bullet : bulletNeedRemove){
					bullet->retain();
					BulletManage::getInstance()->removeBullet(bullet);
					}
				
/*for (it = allFish.begin(); it != allFish.end(); it++){
	for (Vector<Bullet*>::iterator it2 = allBullets.begin(); it2 != allBullets.end();){


	}
	}*/

	FishManage::getInstance()->removeFishWhichSwimOut();
}

void GameLayer::onExit()
{
	Layer::onExit();
	FishManage::getInstance()->cleanVector();
	BulletManage::getInstance()->ClearManage();
	myTurret = nullptr;
	otherTurrets.clear();
}

void GameLayer::loadNewMonent()
{
	FishManage::getInstance()->LoadOnement();
}

void GameLayer::RefreShmyPlayerTurret()
{
	myTurret->refreshTurretInfo();
}

void GameLayer::beginLock()
{
	myTurret->beginLockShoot();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::lockTouchEvent, this);
}
void GameLayer::endLock()
{
	myTurret->endLockShoot();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
}


void GameLayer::beginSkillBoom()
{
	skillManager::getInstance()->getButtonByID(4)->setEnable(false);
	touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::boomTouchEvent, this);
}
void GameLayer::endSkillBoom()
{
	skillManager::getInstance()->getButtonByID(4)->setEnable(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
}

bool GameLayer::boomTouchEvent(Touch *touch, Event  *event)
{
	auto pos = touch->getLocation();
	auto cicle = CCCircMake(pos, 200);

#if 1
	auto draw = DrawNode::create();
	draw->drawCircle(cicle.getMCenter(), cicle.getMRadius(),360, 100, false,Color4F::RED);
	addChild(draw);
#endif

	auto fishPool = FishManage::getInstance()->getAllFishInPool();
	auto data = GameData::getInstance();
	for (auto fish:fishPool)
	{
		auto rect = fish->getBoundingBox();
		if (cicle.intersectsRect(rect))
		{
			if (data->getIsOnMaridTask())
			{
				auto vec = data->getmermaidTask()->getMermaidTaskOnlineInfo().mermaidTaskItems;
				for (auto var : vec)
				{
					if (fish->getFishType() == var.fishId)
					{
						data->getmermaidTask()->addOneCatchFishById(fish->getFishType());
						break;
					}
				}
			}
			myTurret->getCoinByFish(fish);
			FishManage::getInstance()->removeFish(fish);
		}
		
	}
	endSkillBoom();
	return true;
}