#include "core/GameLayer.h"
#include "net/Net.h"
#include "utill/FunUtil.h"
#include "utill/AnimationUtil.h"
#include "utill/CircleMoveTo.h"
#include "User.h"
#include "AIManager.h"
#include "fish/FishGroupData.h"
#include "MomentControllerOne.h"
#define kTagBaseturret 10



bool GameLayer::init(){
	if (!Layer::init())
	{
		return false;
	}
	m_nowMonentController = nullptr;
	//add game bg to this layer
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* game_bg = Sprite::create("lobby_bg.jpg");
	game_bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(game_bg);
	game_bg->runAction(RepeatForever::create(AnimationUtil::getInstance()->getAnimate("aniWater")));
	//TODO 游戏核心界面
	
	//TODO 产生鱼
	/*schedule(schedule_selector(GameLayer::createFish), 0.3f,CC_REPEAT_FOREVER, 20.0f);
	schedule(schedule_selector(GameLayer::createFishGroup), 180.0f, CC_REPEAT_FOREVER, 2.0f);*/
	scheduleUpdate();
	addTouchEvent();	

	players = RoomManager::getInstance()->initRoomConfig();
	calculateFreeChair();
	createTurret();
	createAI();
	schedule(schedule_selector(GameLayer::collisionUpdate), 1.0 / 60.0f, CC_REPEAT_FOREVER, 0);

	loadNewMonent();
	////test
	//auto fish = Sprite::create("16_02.png");
	//fish->setPosition(480, 240);
	//addChild(fish);
	//fish->runAction(CircleMoveTo::create(10, Vec2(200, 200), 0.0f, 1800));


	FishManage::getInstance()->setlayer(this);
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
		struct timeval tv;
		gettimeofday(&tv, NULL);
		CCLOG("i:%d  time:%f", i, tv.tv_sec * 1000 + tv.tv_usec / 1000);
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



void GameLayer::shoot(float degree, PlayerTurret* turret){
	//添加一颗子弹用于测试
	auto bullet = BulletManage::getInstance()->createBullet(rand()%8, 90);
	bullet->setRotation(degree);
	bullet->setPosition(turret->getPosition());
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
	rotateTurret(degree,myTurret);
	myTurret->shoot(degree);
	return true;
}

void GameLayer::onTouchMoved(Touch *touch, Event  *event)
{
	//TODO 需要添加子弹间隔
	//float degree = getTurretRotation(myTurret->getPosition(), touch->getLocation());
	//rotateTurret(degree);
	//shoot(degree);

}

void  GameLayer::onTouchEnded(Touch *touch, Event  *event)
{
	//暂时不做处理
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
	fishNet->setPosition(bullet->getPosition());
	fishNet->initNetByType(bullet->getType());
	this->addChild(fishNet, 3);
	fishNet->checkCatchFish(bullet);
}

void GameLayer::createPlayerCoin()
{
	Point coinPos[4] =
	{
		Vec2(85, 45),
		Vec2(875, 45),
		Vec2(85, 495),
		Vec2(875, 495)
	};



	auto vec = players;
	for (auto player : vec)
	{
		auto spCoinBG = Sprite::create("coinAnddiamondBG.png");
		spCoinBG->setPosition(coinPos[player.getRoomPosition()]);
		addChild(spCoinBG, 10, player.getRoomPosition());

		auto coinLabel = LabelAtlas::create(Value(player.getCoins()).asString().c_str(), "prop_num.png", 19, 23, '0');
		coinLabel->setPosition(spCoinBG->getContentSize().width*0.9 , spCoinBG->getContentSize().height*0.29);
		coinLabel->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
		spCoinBG->addChild(coinLabel);

		auto diamondLabel = LabelAtlas::create(Value(player.getDiamonds()).asString().c_str(), "prop_num.png", 19, 23, '0');
		diamondLabel->setPosition(spCoinBG->getContentSize().width*0.9, spCoinBG->getContentSize().height*0.71);
		diamondLabel->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
		spCoinBG->addChild(diamondLabel);
		
	}
	//构建自己的位置	
	int freeIndex = m_index;
	auto user = User::getInstance();
	auto spCoinBG = Sprite::create("coinAnddiamondBG.png");
	spCoinBG->setPosition(coinPos[freeIndex]);
	addChild(spCoinBG, 10, freeIndex);

	auto coinLabel = LabelAtlas::create(Value(user->getCoins()).asString().c_str(), "prop_num.png", 19, 23, '0');
	coinLabel->setPosition(spCoinBG->getContentSize().width*0.9, spCoinBG->getContentSize().height*0.29);
	coinLabel->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	spCoinBG->addChild(coinLabel);

	auto diamondLabel = LabelAtlas::create(Value(user->getDiamonds()).asString().c_str(), "prop_num.png", 19, 23, '0');
	diamondLabel->setPosition(spCoinBG->getContentSize().width*0.9, spCoinBG->getContentSize().height*0.71);
	diamondLabel->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	spCoinBG->addChild(diamondLabel);

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

void GameLayer::createAI()
{
	
	for (auto otherT:otherTurrets)
	{
		auto aiinfo = AIManager::getInstance()->getAI(0, 0, otherT->getnMaxLevel());
		otherT->setAIinfo(aiinfo);
	}
	
}

void GameLayer::collisionUpdate(float dt)
{

	//TODO 碰撞逻辑
	//step1 获取子弹列表
	auto allBullets = BulletManage::getInstance()->getAllBullets();
	//step2 获取鱼的列表
	auto allFish = FishManage::getInstance()->getAllFishInPool();
	//step3 碰撞检查
	Vector<Fish*>::iterator it;
	Vector<Bullet*> bulletNeedRemove;
	for (it = allFish.begin(); it != allFish.end(); it++){
		Vector<Bullet*>::iterator it2;
		for (it2 = allBullets.begin(); it2 != allBullets.end();){
			Fish* fish = *it;
			Bullet* bullet = *it2;
			if (collision(fish, bullet)){
				//发生碰撞,移除子弹
				bulletNeedRemove.pushBack(bullet);
				bullet->removeFromParent();
				it2 = allBullets.erase(it2);
				//TODO打开渔网
				createNet(bullet);
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

	FishManage::getInstance()->removeFishWhichSwimOut();
}

void GameLayer::onExit()
{
	Layer::onExit();
	FishManage::getInstance()->cleanVector();
}

void GameLayer::loadNewMonent()
{
	FishManage::getInstance()->LoadOnement(ConfigOnemoment::getInstance()->LoadConfig("config/config_onemoment_1.json"));
}