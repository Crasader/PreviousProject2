﻿#include "core/GameLayer.h"
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
#include "domain/logevent/LogEventMannger.h"
#include "bullet/Laster.h"
#include "domain/bag/BagManager.h"
#include "domain/game/GameManage.h"
#include "domain/Newbie/NewbieMannger.h"
#include "domain/bankrupt/BankruptManager.h"
#include "config/ConfigNewbieFishCatch.h"
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
	setIsShowYourChairno(false);
	FishManage::getInstance()->setlayer(this);
	skillManager::getInstance()->setlayer(this);
	//add game bg to this layer
	Size visibleSize = Director::getInstance()->getVisibleSize();
	game_bg = Sprite::create("aniWater1.jpg");
	game_bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(game_bg,-2);
	

	///水波纹
	auto anibowennode = Sprite::create();
	anibowennode->setScale(2);
	anibowennode->runAction(RepeatForever::create(AnimationUtil::getInstance()->getAnimate("aniBowen")));
	anibowennode->setPosition(0, 0);
	anibowennode->setAnchorPoint(Point::ZERO);
	addChild(anibowennode,-1);

	anibowennode = Sprite::create();
	anibowennode->setScale(2);
	anibowennode->runAction(RepeatForever::create(AnimationUtil::getInstance()->getAnimate("aniBowen")));
	anibowennode->setPosition(550, 0);
	anibowennode->setAnchorPoint(Point::ZERO);
	addChild(anibowennode, -1);

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
	schedule(schedule_selector(GameLayer::shootUpdata), 1.0 / 60.0f, CC_REPEAT_FOREVER, 0);
	
	runAction(Sequence::create(DelayTime::create(0.01f), CallFunc::create([&]{FishManage::getInstance()->LoadOnement(MomentManager::getInstance()->getNewMomentByType(rand() % 3 + 81, rand() % (300 - 35) + 35)); }), nullptr));



	setbisOnSkillLock(false);

	GameData::getInstance()->setDiamondevent(MagnateManager::getInstance()->getDiamandMagnateEvent());
	GameData::getInstance()->setpropevent(MagnateManager::getInstance()->getItemMagnateEvent());


	if (!NewbieMannger::getInstance()->getisOverTeachMode())
	{
		myTurret->showPlayerInfo();
		auto txtclick = Sprite::create("TXTClickCatch.png");
		txtclick->setPosition(480, 270);
		addChild(txtclick, kZorderDialog, "clickcatch");
		txtclick->runAction(RepeatForever::create(Sequence::create(FadeOut::create(0.5f), FadeIn::create(0.5f), DelayTime::create(0.2f), nullptr)));
	}
	
	skillManager::getInstance()->init();


	auto node = BankruptManager::getInstance()->getgetRewardNode();
	if (node)
	{
		if (node->getParent())
		{
			node->removeFromParentAndCleanup(false);
		}
		node->setPosition(myTurret->getPosition()+Vec2(0,150));
		addChild(node);
	}

	//FishManage::getInstance()->createFishRand(201);


	//for (int i = 0; i <= 5;i++)
	//{
	//	
	//	runAction(Sequence::create(DelayTime::create(i * 5), CallFunc::create([=]{
	//		auto fish = FishManage::getInstance()->createFishSingle(42);
	//		GameManage::getInstance()->CatchTheFishOntheTurrent(fish, true, myTurret); }), nullptr));
	//}

	return true;
}


void GameLayer::showYourChairno()
{
	auto sp = Sprite::create("TXTYourChairno.png");
	sp->setPosition(myTurret->getPosition() + Vec2(0, 80));
	addChild(sp, 20);
	sp->runAction(RepeatForever::create(Sequence::create(FadeOut::create(0.5f), FadeIn::create(0.5f), DelayTime::create(0.2f), nullptr)));
	sp->runAction(Sequence::create(DelayTime::create(8.0f), RemoveSelf::create(), nullptr));

	auto pos = myTurret->getPosition() + Vec2(0, 130);
	auto sPoint = Sprite::create("yellowSpoint.png");
	sPoint->setPosition(pos);
	addChild(sPoint, 20);
	sPoint->runAction(RepeatForever::create(Sequence::create(EaseSineOut::create(MoveBy::create(0.6f, Vec2(0, 30))), EaseSineOut::create(MoveBy::create(0.6f, Vec2(0, -30))), nullptr)));

	sPoint->runAction(Sequence::create(DelayTime::create(8.0f), RemoveSelf::create(), nullptr));
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
	touchListener->setSwallowTouches(false);
	touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	m_touchType = TouchInNormal;
}

void GameLayer::shootUpdata(float dt)
{
	if (istouched == true)
	{
		const float shootInterval = GameConfig::getInstance()->getShootData().shootInterval;
		if (!isShoot)
		{
			return ;
		}
		CCLOG("%f,%f", touchpos.x, touchpos.y);
		float degree = getTurretRotation(myTurret->getPosition(), touchpos);
		rotateTurret(degree, myTurret);
		runAction(Sequence::create(DelayTime::create(0.1f), CallFunc::create([&]{
			CCLOG("shot turret rotate%f", myTurret->getRarote());
			myTurret->shoot(myTurret->getRarote());
		}), nullptr));
		isShoot = false;
		runAction(Sequence::create(DelayTime::create(shootInterval), CallFunc::create([&]{
			isShoot = true;
		}), nullptr));
	}
}

bool GameLayer::onTouchBegan(Touch *touch, Event  *event)
{
	if (getIsShowYourChairno()==false)
	{
		showYourChairno();
		setIsShowYourChairno(true);
	}
	
	auto node = getChildByName("clickcatch");
	if (node)
	{
		node->removeFromParentAndCleanup(1);
		

		NewbieMannger::getInstance()->setisOverTeachMode(1);
	}
	auto touchPos = touch->getLocation();
	if (onTouTurret(touchPos))
	{
		return true;
	}
	if (GameData::getInstance()->getisOnBankrupt())
	{
		return true;
	}
	removePlayerInfo();
	
	istouched = true;
	touchpos = touch->getLocation();
	return true;
}
void GameLayer::removePlayerInfo()
{
	if (myTurret->getIsShowInfo())
	{
		myTurret->removePlayerInfo();
		myTurret->setIsShowInfo(false);
	}
	for (auto var:otherTurrets)
	{
		if (var->getIsShowInfo())
		{
			var->removePlayerInfo();
			var->setIsShowInfo(false);
		}
	}
}
bool GameLayer::lockTouchEvent(Touch *touch, Event  *event)
{
	auto touchPos = touch->getLocation();
	if (onTouTurret(touchPos))
	{
		return false;
	}
	auto node = getChildByName("TXTTip");
	if (node)
	{
		node->removeFromParentAndCleanup(1);
	}
	removePlayerInfo();
	auto fish = FishManage::getInstance()->getFishByPosInPool(touchPos);
	if (fish)
	{
		myTurret->setLockFish(fish);
	}
	return false;
}


void GameLayer::onTouchMoved(Touch *touch, Event  *event)
{
	touchpos = touch->getLocation();
	CCLOG("%f,%f", touchpos.x, touchpos.y);
}

void  GameLayer::onTouchEnded(Touch *touch, Event  *event)
{
	istouched = false; 
}




void GameLayer::rotateTurret(float degree,PlayerTurret* turret){
	turret->rorateTurret(degree);
}

void GameLayer::update(float dt){
	FishManage::getInstance()->UpdateWhenController(dt);
	FishManage::getInstance()->UpdataCreateFish(dt);
}


void GameLayer::createNet(Bullet *bullet){
	Net* fishNet = Net::create();
	fishNet->setBullet(bullet);
	float dotPos = bullet->getContentSize().height*0.5;
	fishNet->setPosition(bullet->getPosition()+Vec2(0,dotPos*sin(bullet->getRotation())));
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
	//AIManager::getInstance()->mainUpdata(dt);
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
			if (CollisionUtill::isCollisionRect(fish->getBoundingFigures(), bullet->getBoundingBox())){
				//发生碰撞,移除子弹,在这里计算捕获鱼，渔网只有UI作用，无影响
				bulletNeedRemove.pushBack(bullet);
				bullet->removeFromParent();
				auto turretdata = bullet->getTurretdata();
				auto curryFish = fish;
				if (curryFish == nullptr)
				{
					return;
				}	
				LogEventFish::getInstance()->addFishHitTimes(curryFish->getFishID());
				float k = rand_0_1();
				float per = curryFish->getGrabProbability();

				if (!bullet->getPlayerTurret()->isRobot)
				{
					LogEventFish::getInstance()->addFishUserCostCoin(curryFish->getFishID(), bullet->getPlayerTurret()->getTurrentMupltData().multiple);
					float perForLevel = ConfigNewbieFishCatch::getInstance()->getperByLevelAndFishID(User::getInstance()->getLevelData().levelId, fish->getFishID());
					if (perForLevel>0)
					{
						per = perForLevel;
					}
				}
				if (k < (per*turretdata.catch_per))
				{
					GameManage::getInstance()->CatchTheFishOntheTurrent(curryFish, 1, bullet->getPlayerTurret());
				}
				//打开渔网
				createNet(bullet);
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

void GameLayer::loadNewMonent(float ffTime)
{
	FishManage::getInstance()->LoadOnement(MomentManager::getInstance()->getNewMoment(ffTime));
}

void GameLayer::RefreShmyPlayerTurret()
{
	myTurret->refreshTurretInfo();
}
bool GameLayer::lightTouchEvent(Touch *touch, Event *event)
{
	auto touchPos = touch->getLocation();
	if (onTouTurret(touchPos))
	{
		return false;
	}
	auto node = getChildByName("TXTTip");
	if (node)
	{
		node->removeFromParentAndCleanup(1);
	}
	removePlayerInfo();
	auto fish = FishManage::getInstance()->getFishByPosInPool(touchPos);
	if (fish)
	{
		myTurret->setLightFish(fish);
	}
	return false;
}
void GameLayer::beginLight()
{
	m_lasttouchType = m_touchType;
	myTurret->beginLightShoot();
	changeTouchFunByTouchType(TouchInLight);

	auto txt = Sprite::create("TXTUseLight.png");
	txt->setPosition(myTurret->getPosition() + Vec2(0, 100));
	addChild(txt, kZorderDialog, "TXTTip");
}
void GameLayer::endLight()
{
	myTurret->endLightShoot();
	changeTouchFunByTouchType(m_lasttouchType);
	auto node = getChildByName("TXTTip");
	if (node)
	{
		node->removeFromParentAndCleanup(1);
	}
}

void GameLayer::beginLock()
{
	m_lasttouchType = m_touchType;
	myTurret->beginLockShoot();
	changeTouchFunByTouchType(TouchInLock);

	auto txt = Sprite::create("TXTUseLock.png");
	txt->setPosition(myTurret->getPosition() + Vec2(0, 100));
	addChild(txt, kZorderDialog, "TXTTip");
}
void GameLayer::endLock()
{
	myTurret->endLockShoot();
	changeTouchFunByTouchType(m_lasttouchType);
	auto node = getChildByName("TXTTip");
	if (node)
	{
		node->removeFromParentAndCleanup(1);
	}
}

void GameLayer::beginSkillBoom()
{
	m_lasttouchType = m_touchType;
	skillManager::getInstance()->getButtonByID(4)->setEnable(false);
	changeTouchFunByTouchType(TouchInBoom);

	auto txt = Sprite::create("TXTUseBomb.png");
	txt->setPosition(myTurret->getPosition() + Vec2(0, 100));
	addChild(txt, kZorderDialog, "TXTTip");
}
void GameLayer::endSkillBoom()
{
	skillManager::getInstance()->getButtonByID(4)->setEnable(true);
	changeTouchFunByTouchType(m_lasttouchType);

	getChildByName("TXTTip")->removeFromParentAndCleanup(1);
}


void GameLayer::onBoomCatchFish(Point pos)
{

	auto cicle = CCircle(pos, 200);

	auto fishPool = FishManage::getInstance()->getAllFishInPool();
	auto data = GameData::getInstance();
	for (auto fish : fishPool)
	{
		if (CollisionUtill::isCollisionCircle(fish->getBoundingFigures(),cicle))
		{
			GameManage::getInstance()->CatchTheFishOntheTurrent(fish, 1, myTurret);
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
	removePlayerInfo();
	auto sp = Sprite::create("sign_1006.png");
	sp->setPosition(myTurret->getPosition());
	sp->runAction(Sequence::create(Spawn::create(ScaleTo::create(0.13f, 1), MoveTo::create(0.13f, pos), nullptr), RemoveSelf::create(), CallFunc::create([=]{
		auto boombg = Sprite::create("boomBg.png");
		boombg->setPosition(pos);
		boombg->setScale(2);
		addChild(boombg);
		boombg->runAction(Sequence::create(DelayTime::create(3.0f), RemoveSelf::create(), nullptr));

		auto anisp = Sprite::create();
		anisp->setPosition(pos);
		anisp->setScale(2);
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
	case TouchInLight:
		touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::lightTouchEvent, this);
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

void GameLayer::useFreeze(PlayerTurret*turret)
{
	unscheduleUpdate();
	auto bg = ProgressTimer::create(Sprite::create("iceFram4.jpg"));
	bg->setType(ProgressTimer::Type::BAR);
	bg->setMidpoint(Vec2(0, 0));
	bg->setBarChangeRate(Vec2(1, 0));
	addChild(bg, 0, kTagFrezzebg);
	bg->setPosition(480, 270);
	bg->runAction(ProgressTo::create(2, 100));

	auto aniSp = ProgressTimer::create(Sprite::create("game/ui/ani/TX_DongJie/TX_qpdj_1.png"));
	aniSp->setType(ProgressTimer::Type::BAR);
	aniSp->setMidpoint(Vec2(0, 0));
	aniSp->setBarChangeRate(Vec2(1, 0));
	aniSp->setAnchorPoint(Point::ANCHOR_MIDDLE);
	aniSp->setPosition(Vec2(aniSp->getContentSize().width*0.4,150));
	turret->addChild(aniSp);

	aniSp->runAction(Sequence::create(ProgressTo::create(1, 100), CallFunc::create([=]{
		auto anisp = Sprite::create();
		anisp->setPosition(aniSp->getPosition());
		turret->addChild(anisp, 0, "freezetxt");
		anisp->runAction(RepeatForever::create(AnimationUtil::getInstance()->getAnimate("aniTXTdj")));
		aniSp->removeFromParentAndCleanup(1);

	}
	), nullptr));
}

void GameLayer::onFreezeEnd(PlayerTurret*turret)
{
	scheduleUpdate();
	getChildByTag(kTagFrezzebg)->removeFromParentAndCleanup(1);
	turret->getChildByName("freezetxt")->removeFromParentAndCleanup(1);
}

void GameLayer::onClearFish()
{
	auto txt = Sprite::create("yuchaoTXT.png");
	txt->setPosition(480, 270);
	addChild(txt,kZorderFish+2,"yuchaotxt");

	auto lang = Sprite::create("wave.png");
	lang->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	lang->setPosition(1100, 270);
	lang->runAction(Sequence::create(MoveTo::create(10, Vec2(-300, 270)), CallFunc::create([&]{ unschedule(schedule_selector(GameLayer::onClearFishUpdata)); getChildByName("yuchaotxt")->removeFromParentAndCleanup(1); FishManage::getInstance()->cleanVector(); }), RemoveSelf::create(), nullptr));
	addChild(lang, kZorderFish+1, "lang");
	schedule(schedule_selector(GameLayer::onClearFishUpdata), 0, CC_REPEAT_FOREVER, 0);
	Audio::getInstance()->playSound(CLEARFISH);
}

void GameLayer::onClearFishUpdata(float dt)
{
	auto node = (Sprite*)getChildByName("lang");
	if (node)
	{
		auto rect = node->getBoundingBox();
		rect.setRect(rect.origin.x,rect.origin.y-200, rect.size.width, rect.size.height + 400);
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
			GameManage::getInstance()->CatchTheFishOntheTurrent(fish, 0, nullptr);

		}
	}

}

void GameLayer::addReward(int itemid, int num)
{
	BagManager::getInstance()->changeItemCount(itemid, num);
	if (itemid==1001)
	{
		User::getInstance()->addCoins(num);
	}
	else if (itemid ==1002)
	{

		User::getInstance()->addDiamonds(num);
	}
}

void GameLayer::onGetReward(int itemid, int num)
{
	auto spPath = String::createWithFormat("item_%d.png", itemid);
	auto lightsp = Sprite::create("light1.png");
	lightsp->setPosition(480, 270);
	addChild(lightsp);
	lightsp->runAction(RotateTo::create(3.0f, 360.0));
	auto sp = Sprite::create(spPath->getCString());
	sp->setPosition(480, 270);
	sp->setScale(0);
	sp->runAction(ScaleTo::create(0.2, 1.0f));
	addChild(sp);
	//缺少放烟花素材
	auto aninode = Sprite::create();
	aninode->setPosition(480, 270);
	addChild(aninode);
	aninode->setScale(2);
	aninode->runAction(Sequence::create(Repeat::create(AnimationUtil::getInstance()->getAnimate("aniShengji"), 3), RemoveSelf::create(), nullptr));
	sp->runAction(Sequence::create(DelayTime::create(1.0f), CallFunc::create([=]{lightsp->removeFromParentAndCleanup(1); }), MoveTo::create(1.0f, myTurret->getPosition()), CallFunc::create([=]{addReward(itemid, num); }), RemoveSelf::create(1), nullptr));

}


void GameLayer::onGetRewardByfish(PlayerTurret*turrent, Fish*fish, int itemid, int num)
{
	Sprite*sp;
	if (itemid ==1002)
	{
		sp = Sprite::create("bigDiamond.png");
		auto ani = Sprite::create("dropLightRorate.png");
		ani->setPosition(sp->getContentSize() / 2);
		sp->addChild(ani, -1);
		ani->runAction(RepeatForever::create(RotateBy::create(5.0, 360)));
	}
	else
	{
		auto str = String::createWithFormat("sign_%d.png", itemid);
		sp = Sprite::create(str->getCString());
	}
	sp->setPosition(480,270);
	sp->setScale(0);
	addChild(sp,10);
	auto distans = turrent->getCoinLabelPos().distance(sp->getPosition());
	sp->runAction(Sequence::create(Spawn::create(MoveBy::create(0.5f, Vec2(0,0)), ScaleTo::create(0.5f, 1.0f), nullptr), EaseExponentialIn::create(MoveTo::create(2.0f, turrent->getCoinLabelPos())), CallFunc::create([=]
	{
		BagManager::getInstance()->addreward(itemid, num);
		if (itemid==1001)
		{
			turrent->ShowAddCoinAni(1, num);
		}
		else if (itemid == 1002)
		{
			turrent->ShowAddCoinAni(2, num);
		}
		
	}), RemoveSelf::create(1), nullptr));

}