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
#include "fish/FishAniMannage.h"
#include "utill/CollisionUtill.h"
#include "utill/Audio.h"

#define BOOMRADIUS 300
enum
{
	kZorderMenu = 10,
	kZorderDialog = 20,
	kZorderFish = 5,
	kZorderNet  = 6,
	kZorderBullet = 7,
	kZorderTurrent = 8
};
enum
{
	kTagBaseturret= 10,
	kTagFrezzebg  = 11,
	kTagBoomAniNode = 12
};


bool GameLayer::init(){
	if (!Layer::init())
	{
		return false;
	}
	FishManage::getInstance()->setlayer(this);
	skillManager::getInstance()->setlayer(this);
	//add game bg to this layer
	Size visibleSize = Director::getInstance()->getVisibleSize();
	game_bg = Sprite::create("game/ui/ani/water/aniWater1.jpg");
	game_bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(game_bg,-2);
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

	//TEST FISH
	//auto fish = FishManage::getInstance()->createFishArrange(103);
	//fish->setPosition(480, 270);
	//fish->unscheduleUpdate();
	//addChild(fish);
	//for (auto var:fish->getBoundingFigures())
	//{
	//	var->draw(this);
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
			this->addChild(fish,kZorderFish);
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
				addChild(fish, kZorderFish);
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
	this->addChild(myTurret, kZorderTurrent);

	for (auto player:vec)
	{
		auto otherTurret = PlayerTurret::create();
		otherTurret->setAnchorPoint(ccp(0.5, 0.5));
		otherTurret->setPosition(turretPos[player.getRoomPosition()]);
		otherTurret->initWithDate(&player);
		otherTurrets.pushBack(otherTurret);
		addChild(otherTurret, kZorderMenu, kTagBaseturret + player.getRoomPosition());
		
	}
	
}




void GameLayer::addTouchEvent(){
	touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	m_touchType = TouchInNormal;
}

bool GameLayer::onTouchBegan(Touch *touch, Event  *event)
{
	auto touchPos = touch->getLocation();
	if (onTouTurret(touchPos))
	{
		return true;
	}
	const float shootInterval = GameConfig::getInstance()->getShootData().shootInterval;
	if (!isShoot)
	{
		return true;
	}
	float degree = getTurretRotation(myTurret->getPosition(), touchPos);
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
	auto touchPos = touch->getLocation();
	if (onTouTurret(touchPos))
	{
		return false;
	}
	auto fish = FishManage::getInstance()->getFishByPosInPool(touchPos);
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
	this->addChild(fishNet, kZorderNet);
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
	for (auto bullet : allBullets)
	{
		for (auto fish : allFish)
		{
			if (/*collision(fish, bullet)*/CollisionUtill::isCollisionRect(fish->getBoundingFigures(), bullet->getBoundingBox())){
				//发生碰撞,移除子弹
				bulletNeedRemove.pushBack(bullet);
				bullet->removeFromParent();
				//TODO打开渔网
				createNet(bullet);
				fish->onHeart();
				break;
			}
		}
	}

	for (Bullet* bullet : bulletNeedRemove){
		bullet->retain();
		BulletManage::getInstance()->removeBullet(bullet);
	}


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
	m_lasttouchType = m_touchType;
	myTurret->beginLockShoot();
	changeTouchFunByTouchType(TouchInLock);
}
void GameLayer::endLock()
{
	myTurret->endLockShoot();
	changeTouchFunByTouchType(m_lasttouchType);
}


void GameLayer::beginSkillBoom()
{
	m_lasttouchType = m_touchType;
	skillManager::getInstance()->getButtonByID(4)->setEnable(false);
	changeTouchFunByTouchType(TouchInBoom);
}
void GameLayer::endSkillBoom()
{
	skillManager::getInstance()->getButtonByID(4)->setEnable(true);
	changeTouchFunByTouchType(m_lasttouchType);
}


void GameLayer::onBoomCatchFish(Point pos)
{

	auto cicle = CCircle(pos, 200);
#if 1
	auto draw = DrawNode::create();
	draw->drawCircle(cicle.getMCenter(), cicle.getMRadius(), 360, 100, false, Color4F::RED);
	addChild(draw);
#endif
	auto fishPool = FishManage::getInstance()->getAllFishInPool();
	auto data = GameData::getInstance();
	for (auto fish : fishPool)
	{
		if (CollisionUtill::isCollisionCircle(fish->getBoundingFigures(),cicle))
		{
			myTurret->getCoinByFish(fish);
			FishManage::getInstance()->removeFish(fish, 1);
		}

	}
	endSkillBoom();
}

bool GameLayer::boomTouchEvent(Touch *touch, Event  *event)
{
	auto pos = touch->getLocation();
	if (onTouTurret(pos))
	{
		return true;
	}
	auto sp = Sprite::create("sign_1006.png");
	sp->setPosition(myTurret->getPosition());
	sp->runAction(Sequence::create(Spawn::create(ScaleTo::create(0.13f, 1), MoveTo::create(0.13f, pos), nullptr), RemoveSelf::create(), CallFunc::create([=]{
		auto anisp = Sprite::create();
		anisp->setPosition(pos);
		addChild(anisp);
		onBoomCatchFish(pos);
		anisp->runAction(Sequence::create(AnimationUtil::getInstance()->getAnimate("aniTXTBoom"),RemoveSelf::create(),nullptr));
	}),nullptr));
	addChild(sp);


	return true;
}


bool GameLayer::onTouTurret(Point pos)
{
	if (myTurret->onTurretTouch(pos))
	{
		return true;
	}
	for (auto var : otherTurrets)
	{
		if (var->onTurretTouch(pos))
		{
			return true;
		}
	}
	return false;
}

void GameLayer::changeTouchFunByTouchType(TouchType type)
{
	switch (type)
	{
	case TouchInNormal:
		touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
		break;
	case TouchInLock:
		touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::lockTouchEvent, this);
		break;
	case TouchInBoom:
		touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::boomTouchEvent, this);
		break;
	case TouchInAutoShoot:
		touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::AutoShootTouchEvent, this);
		break;
	default:
		break;
	}
	m_touchType = type;
}


void GameLayer::beginAutoShoot()
{
	autoShootPos = Point(-1, -1);
	m_lasttouchType = m_touchType;
	changeTouchFunByTouchType(TouchInAutoShoot);
	myTurret->beginAutoShoot();
	
}
void GameLayer::endAutoShoot()
{
	changeTouchFunByTouchType(m_lasttouchType);
	myTurret->endAutoShoot();
}
bool GameLayer::AutoShootTouchEvent(Touch *touch, Event *event)
{
	auto touchPos = touch->getLocation();
	if (onTouTurret(touchPos))
	{
		return false;
	}
	myTurret->setTargetPos(touchPos);
}

void GameLayer::onFreezeBegin()
{
	unscheduleUpdate();
	auto bg = ProgressTimer::create(Sprite::create("iceFram4.png"));
	bg->setType(ProgressTimer::Type::BAR);
	bg->setMidpoint(Vec2(0, 0));
	bg->setBarChangeRate(Vec2(1, 0));
	addChild(bg, 0, kTagFrezzebg);
	bg->setPosition(480,270);
	bg->runAction(ProgressTo::create(2, 100));

	auto aniSp = ProgressTimer::create(Sprite::create("ani/TX_DongJie/TX_qpdj_1.png"));
	aniSp->setType(ProgressTimer::Type::BAR);
	aniSp->setMidpoint(Vec2(0, 0));
	aniSp->setBarChangeRate(Vec2(1, 0));
	bg->addChild(aniSp);
	aniSp->setPosition(282, 412);
	aniSp->runAction(Sequence::create(ProgressTo::create(1, 100), CallFunc::create([=]{
		auto anisp = Sprite::create();
		anisp->setPosition(aniSp->getPosition());
		bg->addChild(anisp);
		anisp->runAction(RepeatForever::create(AnimationUtil::getInstance()->getAnimate("aniTXTdj")));
		aniSp->removeFromParentAndCleanup(1);
			
	}
	), nullptr));
	
}

void GameLayer::onFreezeEnd()
{
	scheduleUpdate();
	getChildByTag(kTagFrezzebg)->removeFromParentAndCleanup(1);
}

void GameLayer::onClearFish()
{
	auto txt = Sprite::create("yuchaoTXT.png");
	txt->setPosition(480, 270);
	addChild(txt,kZorderFish+1,"yuchaotxt");

	auto lang = Sprite::create("wave.png");
	lang->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	lang->setPosition(960, 270);
	lang->runAction(Sequence::create(MoveTo::create(10, Vec2(-300, 270)), CallFunc::create([&]{ unschedule(schedule_selector(GameLayer::onClearFishUpdata)); getChildByName("yuchaotxt")->removeFromParentAndCleanup(1); FishManage::getInstance()->cleanVector(); }), RemoveSelf::create(), nullptr));
	addChild(lang, kZorderFish+1, "lang");
	schedule(schedule_selector(GameLayer::onClearFishUpdata), 0, CC_REPEAT_FOREVER, 0);
	Audio::getInstance()->playSound("CLEARFISH");
}

void GameLayer::onClearFishUpdata(float dt)
{
	auto node = (Sprite*)getChildByName("lang");
	if (node)
	{
		auto rect = node->getBoundingBox();
		auto vec = FishManage::getInstance()->getAllFishInPool();
		Vector<Fish*> needRemove;
		for (auto var:vec)
		{
			if (CollisionUtill::isCollisionRect(var->getBoundingFigures(), rect))
			{
				needRemove.pushBack(var);
			}
			
		}
		for (auto fish : needRemove)
		{
			FishManage::getInstance()->removeFish(fish, 0);

		}
	}

}