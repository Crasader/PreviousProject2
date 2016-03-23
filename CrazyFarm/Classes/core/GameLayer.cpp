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
#include "utill/OBB.h"
#include "domain/game/GameManage.h"
#include "domain/user/User.h"
#include "server/Server.h"
#include "server/MsgObserver.h"
#include "server/Msg/MsgHelp.h"
#include "core/ScrollTextEx.h"
#include "utill/define.h"
#include "turret/PlayerTurret.h"
#include "domain/ToolTip/TwiceSureDialog.h"
#include "core/showTurretLayer.h"
#include "core/showLockTurretLayer.h"
#define BOOMRADIUS 300
//#define TCPIDURL "106.75.141.82" //外网
#define TCPIDURL "172.23.1.34" //内网
enum
{
	kTagBaseturret= 10,
	kTagFrezzebg  = 11,
	kTagBoomAniNode = 12
};
const Point turretPos[4] =
{
	Vec2(288, 35.5),
	Vec2(672, 35.5),
	Vec2(672, 504.5),
	Vec2(288,504.5)
};

bool GameLayer::init(){
	if (!Layer::init())
	{
		return false;
	}
	setIsShowYourChairno(false);
	FishManage::getInstance()->setlayer(this);
	skillManager::getInstance()->setlayer(this);
	GameManage::getInstance()->setGameyer(this);
	//add game bg to this layer
	Size visibleSize = Director::getInstance()->getVisibleSize();
	game_bg = Sprite::create("aniWater1.jpg");
	game_bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(game_bg, -2);


	///水波纹
	auto anibowennode = Sprite::create();
	anibowennode->setScale(2);
	anibowennode->runAction(RepeatForever::create(AnimationUtil::getInstance()->getAnimate("aniBowen")));
	anibowennode->setPosition(0, 0);
	anibowennode->setAnchorPoint(Point::ZERO);
	addChild(anibowennode, -1);

	anibowennode = Sprite::create();
	anibowennode->setScale(2);
	anibowennode->runAction(RepeatForever::create(AnimationUtil::getInstance()->getAnimate("aniBowen")));
	anibowennode->setPosition(550, 0);
	anibowennode->setAnchorPoint(Point::ZERO);
	addChild(anibowennode, -1);




	//scheduleUpdate(); 




	addTouchEvent();
	auto roominfo = ConfigRoom::getInstance()->getRoombyId(GameData::getInstance()->getRoomID());
	players = RoomManager::getInstance()->initRoomConfig(roominfo.unlock_turrent_level);
	calculateFreeChair();

	schedule(schedule_selector(GameLayer::collisionUpdate), 0.1, CC_REPEAT_FOREVER, 0);

	schedule(schedule_selector(GameLayer::shootUpdata), 1.0 / 60.0f, CC_REPEAT_FOREVER, 0);

	schedule(schedule_selector(GameLayer::UpdateCreateFishByServer), 1.0 / 60.0f, CC_REPEAT_FOREVER, 0);


	runAction(Sequence::create(DelayTime::create(0.01f),
		CallFunc::create([&]{
		initFishAndBulletData();
		FishManage::getInstance()->LoadOnement(MomentManager::getInstance()->getNewMomentByType(rand() % 3 + 81,rand() % (300 - 35) + 10));
	for (int i = 0; i < 5;i++)
	{
		update(1);
	}
		for (auto var : FishManage::getInstance()->getAllFishInPool())
		{
			for (int i = 0; i < 5; i++)
			{
				var->moveUpdata(1);
			}
		}
 }), nullptr));

	runAction(Sequence::create(DelayTime::create(0.01f),
		CallFunc::create([&]{
		initFishAndBulletData();
		FishManage::getInstance()->LoadOnement(MomentManager::getInstance()->getNewMomentByType(rand() % 3 + 81,rand() % (300 - 35) + 10));
	for (int i = 0; i < 5;i++)
	{
		update(1);
	}
		for (auto var : FishManage::getInstance()->getAllFishInPool())
		{
			for (int i = 0; i < 5; i++)
			{
				var->moveUpdata(1);
			}
		}
 }), nullptr));

	setbisOnSkillLock(false);

	GameData::getInstance()->setDiamondevent(MagnateManager::getInstance()->getDiamandMagnateEvent());
	GameData::getInstance()->setpropevent(MagnateManager::getInstance()->getItemMagnateEvent());


	if (!NewbieMannger::getInstance()->getisOverTeachMode())
	{
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
		node->setPosition(myTurret->getPosition() + Vec2(0, 150));
		addChild(node);
	}

	createFishAcNode = Node::create();
	createFishAcNode->setPosition(0, 0);
	addChild(createFishAcNode);




	//初始化完毕，建立连接
	Server::getInstance()->conConnect(TCPIDURL, 3050, User::getInstance()->getSessionid().c_str(), GameData::getInstance()->getRoomID());   // TODO  : test init server
	Server::getInstance()->add_observer(this);
	schedule(schedule_selector(GameLayer::MsgUpdata), 1.0 / 60.0f, CC_REPEAT_FOREVER, 0);
	

	schedule(schedule_selector(GameLayer::UpdateUserinfo), 10.0f, CC_REPEAT_FOREVER, 0);

	
	_touchtypes.push_back(TouchInNormal);
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


void GameLayer::createTurret(){
	CCLOG("init turret!");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto vec = players;
	auto user = User::getInstance();

	myTurret = PlayerTurret::create();
	
	
	myTurret->initWithDate(user, m_index);
	myTurret->setAnchorPoint(ccp(0.5, 0.5));
	myTurret->setPosition(turretPos[m_index]);
	addChild(myTurret, kZorderTurrent);
	

	for (int i = 0; i < 4; i++)
	{
		auto sp = Sprite::create("WaitJoin.png");
		sp->setPosition(turretPos[i]);
		addChild(sp, kZorderTurrent);
		TxtWaitingTurrent[i] = sp;
		sp->runAction(RepeatForever::create(Sequence::create(FadeOut::create(0.5f), FadeIn::create(0.5f), DelayTime::create(0.2f), nullptr)));
	}
	TxtWaitingTurrent[m_index]->setVisible(false);
	showYourChairno();
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
		float degree = getTurretRotation(myTurret->getPosition(), touchpos);
		degree -= 360;
		if (degree<-90||degree>90)
		{
			//射击角度范围（-80，80）；
			return;
		}

		myTurret->shoot(degree);
		isShoot = false;
		runAction(Sequence::create(DelayTime::create(shootInterval), CallFunc::create([&]{
			isShoot = true;
		}), nullptr));
	}
}

bool GameLayer::onTouchBegan(Touch *touch, Event  *event)
{
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
	fishNet->setAnchorPoint(Point::ANCHOR_MIDDLE);
	fishNet->setBullet(bullet);
	float dotdistance = bullet->getContentSize().height*0.2;
	float angle = bullet->getRotation();
	auto dotpos = Vec2(dotdistance*sin(CC_DEGREES_TO_RADIANS(angle)), dotdistance*cos(CC_DEGREES_TO_RADIANS(angle)));
	fishNet->setPosition(bullet->getPosition() + dotpos);
	fishNet->setRotation(bullet->getRotation());
	fishNet->initNetByType();
	this->addChild(fishNet, kZorderNet);
}


void GameLayer::calculateFreeChair()
{
	auto maxlv = User::getInstance()->getMaxTurrentLevel();
	if (maxlv<5)
	{
		m_index = 1;
	}
	else
	{
		m_index = getRand() % 1;
	}
	std::vector<int> freeChairno;
	for (int i = 0; i < 4;i++)
	{
		if (i==m_index)
		{
			continue;
		}
		else
		{
			freeChairno.push_back(i);
		}
	}
	for (int i = 0; i < 3;i++)
	{
		players[i].setRoomPosition(freeChairno[i]);
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
			if (CollisionUtill::isCollisionFishAAndBullet(fish, bullet)){
				//发生碰撞,移除子弹,在这里计算捕获鱼，渔网只有UI作用，无影响
				bulletNeedRemove.pushBack(bullet);
				bullet->setVisible(false);
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
		bullet->removeFromParentAndCleanup(1);
		BulletManage::getInstance()->removeBullet(bullet);
	}
	
	
	FishManage::getInstance()->removeFishWhichSwimOut();
}
void GameLayer::initFishAndBulletData()
{
	if (isInitData == false)
	{
		FishManage::getInstance()->cleanVector();
		BulletManage::getInstance()->ClearManage();
		GameData::getInstance()->setisOnGroupComing(false);
		isInitData = true;
	}
}
void GameLayer::onEnter()
{
	Layer::onEnter();
	
}
void GameLayer::onExit()
{

    Server::getInstance()->quit();  // TODO : disconnect con
	Msgs.clear();
	FishManage::getInstance()->clearServerItemFishs();
	Layer::onExit();
	
}
void GameLayer::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	
}
void GameLayer::loadNewMonent(int monmentType)
{
	FishManage::getInstance()->LoadOnement(MomentManager::getInstance()->getNewMomentByType(monmentType,0));
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
	_touchtypes.push_back(TouchInLight);
	m_lasttouchType = m_touchType;
	myTurret->beginLightShoot();
	changeTouchFunByTouchType(TouchInLight);

	auto txt = Sprite::create("TXTUseLight.png");
	txt->setPosition(myTurret->getPosition() + Vec2(0, 100));
	addChild(txt, kZorderDialog, "TXTTip");
}
void GameLayer::endLight()
{
	_touchtypes.remove(TouchInLight);
	myTurret->endLightShoot();
	changeTouchFunByTouchType(_touchtypes.back());
	auto node = getChildByName("TXTTip");
	if (node)
	{
		node->removeFromParentAndCleanup(1);
	}
}

void GameLayer::beginLock()
{
	_touchtypes.push_back(TouchInLock);
	m_lasttouchType = m_touchType;
	myTurret->beginLockShoot();
	changeTouchFunByTouchType(TouchInLock);

	auto txt = Sprite::create("TXTUseLock.png");
	txt->setPosition(myTurret->getPosition() + Vec2(0, 100));
	txt->runAction(RepeatForever::create(Sequence::create(FadeIn::create(0.8f), FadeOut::create(0.8f), nullptr)));
	addChild(txt, kZorderDialog, "TXTTip");
}
void GameLayer::endLock()
{
	_touchtypes.remove(TouchInLock);
	myTurret->endLockShoot();
	changeTouchFunByTouchType(_touchtypes.back());
	auto node = getChildByName("TXTTip");
	if (node)
	{
		node->removeFromParentAndCleanup(1);
	}
}

void GameLayer::beginSkillBoom()
{
	_touchtypes.push_back(TouchInBoom);
	m_lasttouchType = m_touchType;
	changeTouchFunByTouchType(TouchInBoom);

	auto txt = Sprite::create("TXTUseBomb.png");
	txt->setPosition(myTurret->getPosition() + Vec2(0, 100));
	addChild(txt, kZorderDialog, "TXTTip");
}
void GameLayer::endSkillBoom()
{
	_touchtypes.remove(TouchInBoom);
	changeTouchFunByTouchType(_touchtypes.back());

	auto txttip = getChildByName("TXTTip");
	if (txttip)
	{
		txttip->removeFromParentAndCleanup(1);
	}
	
}


void GameLayer::onBoomCatchFish(Point pos)
{
	auto fishPool = FishManage::getInstance()->getAllFishInPool();
	auto data = GameData::getInstance();
	for (auto fish : fishPool)
	{
		if (CollisionUtill::isCollisionFishAAndRect(fish, Rect(pos.x - 200, pos.y - 200, 400, 400)))
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
	_touchtypes.push_back(TouchInAutoShoot);
	changeTouchFunByTouchType(TouchInAutoShoot);
	myTurret->beginAutoShoot();
	
}
void GameLayer::endAutoShoot()
{
	_touchtypes.remove(TouchInAutoShoot);
	changeTouchFunByTouchType(_touchtypes.back());
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
	createFishAcNode->pause();
	auto bg = ProgressTimer::create(Sprite::create("iceFram4.jpg"));
	bg->setType(ProgressTimer::Type::BAR);
	bg->setMidpoint(Vec2(0, 0));
	bg->setBarChangeRate(Vec2(1, 0));
	addChild(bg, 0, kTagFrezzebg);
	bg->setPosition(480, 270);
	bg->runAction(ProgressTo::create(2, 100));



	auto bg1 = ProgressTimer::create(Sprite::create("onFreezeTop.png"));
	bg1->setScale(2);
	bg1->setType(ProgressTimer::Type::BAR);
	bg1->setMidpoint(Vec2(0, 0));
	bg1->setBarChangeRate(Vec2(1, 0));
	addChild(bg1, kZorderFishXL+11, "kTagFrezzebg");
	bg1->setPosition(480, 270);
	bg1->runAction(ProgressTo::create(2, 100));




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
	createFishAcNode->resume();
	getChildByTag(kTagFrezzebg)->removeFromParentAndCleanup(1);
	getChildByName("kTagFrezzebg")->removeFromParentAndCleanup(1);
	turret->getChildByName("freezetxt")->removeFromParentAndCleanup(1);
}

void GameLayer::onClearFish()
{
	/*createFishAcNode->pause();*/

	auto txt = Sprite::create("yuchaoTXT.png");
	txt->setPosition(480, 270);
	addChild(txt,kZorderFishXL+2,"yuchaotxt");

	auto lang = Sprite::create("wave.png");
	lang->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	lang->setPosition(1100, 270);
	lang->runAction(Sequence::create(MoveTo::create(5, Vec2(-300, 270)), CallFunc::create([&]{
		unschedule(schedule_selector(GameLayer::onClearFishUpdata)); 
		getChildByName("yuchaotxt")->removeFromParentAndCleanup(1);
		loadNewMonent(_fishGroupMonentType);
	}), RemoveSelf::create(), nullptr));
	addChild(lang, kZorderFishXL+1, "lang");

	
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
			if (CollisionUtill::isCollisionFishAAndRect(var, rect))
			{
				needRemove.pushBack(var);
			}
			
		}
		for (auto fish : needRemove)
		{
			GameManage::getInstance()->CatchTheFishOntheTurrent(fish, 0, nullptr);

		}


		auto vec1 = BulletManage::getInstance()->getAllBullets();
		Vector<Bullet*> needRemove1;
		for (auto var : vec1)
		{
			if (CollisionUtill::isCollisionNodeAAndRect(var,rect))
			{
				needRemove1.pushBack(var);
			}

		}
		for (auto bullet : needRemove1)
		{
			BulletManage::getInstance()->removeBullet(bullet);
			if (bullet->getParent())
			{
				bullet->removeFromParentAndCleanup(1);
			}

		}
	}

}
void GameLayer::onClearFishFinish()
{
	Audio::getInstance()->playBGM(GAMEBGM);
	
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
	auto spPath = String::createWithFormat("sign_%d.png", itemid);

	auto sp = Sprite::create(spPath->getCString());
	sp->setPosition(480, 270);
	sp->setScale(0);
	GameManage::getInstance()->getGuiLayer()->addChild(sp, kZorderDialog+1);	


	auto txt = String::createWithFormat(":%d", num);
	auto spnum = LabelAtlas::create(txt->getCString(), "turntableCellNum.png", 15, 23, '0');
	spnum->setAnchorPoint(Point::ANCHOR_MIDDLE);
	spnum->setPosition(sp->getContentSize().width*0.5, sp->getContentSize().height*-0.05);
	sp->addChild(spnum);


	auto lightsp = Sprite::create("light1.png");
	lightsp->setPosition(sp->getContentSize()/2);
	lightsp->runAction(RotateBy::create(2.0f, 360.0));
	lightsp->setScale(2);
	sp->addChild(lightsp,-1);
	auto colorlayer = LayerColor::create();
	colorlayer->setColor(ccc3(0, 0, 0));
	colorlayer->setOpacity(180);
	GameManage::getInstance()->getGuiLayer()->addChild(colorlayer, kZorderDialog);

	auto aninode = Sprite::create();
	aninode->setPosition(480, 270);
	GameManage::getInstance()->getGuiLayer()->addChild(aninode, kZorderDialog);
	aninode->setScale(4);
	aninode->runAction(Sequence::create(Repeat::create(AnimationUtil::getInstance()->getAnimate("aniShengji"), 2), RemoveSelf::create(), nullptr));
	sp->runAction(Sequence::create( CallFunc::create([=]{colorlayer->removeFromParentAndCleanup(1); }),ScaleTo::create(1.0f, 1.0f), MoveTo::create(1.0f, myTurret->getPosition()), CallFunc::create([=]{addReward(itemid, num); }), RemoveSelf::create(1), nullptr));

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
		auto str = String::createWithFormat("item_%d.png", itemid);
		sp = Sprite::create(str->getCString());
	}
	sp->setPosition(480,270);
	sp->setScale(0);
	GameManage::getInstance()->getGuiLayer()->addChild(sp,20);
	auto distans = turrent->getCoinLabelPos().distance(sp->getPosition());

	Point curPos = GameManage::getInstance()->getGuiLayer()->getItemPos(itemid);



	sp->runAction(Sequence::create(Spawn::create(MoveBy::create(0.5f, Vec2(0, 0)), ScaleTo::create(0.5f, 1.0f), nullptr), EaseExponentialIn::create(MoveTo::create(1.0f, curPos)), CallFunc::create([=]
	{
		BagManager::getInstance()->addreward(itemid, num);
		if (itemid==1001)
		{
			turrent->ShowAddCoinAni(1, num);
		}
		else if (itemid == 1002)
		{
			turrent->ShowAddCoinAni(2, num);
			if (User::getInstance()->getMaxTurrentLevel()==1&&!NewbieMannger::getInstance()->getisTeachUpgradeTurrent())
			{
				NewbieMannger::getInstance()->setisTeachUpgradeTurrent(1);
				GameManage::getInstance()->getGuiLayer()->ShowUpgradeTurretTip();
			}


		}
		
	}), RemoveSelf::create(1), nullptr));

}

void GameLayer::handle_event(const char* msgId, const char* msgBody)
{
	Msg_Base*msg = MsgHelp::getInfoByMsg(msgId, msgBody);
	if (msg)
	{
		Msgs.push_back(msg);
	}
	
}

void GameLayer::onSomeoneComing(Msg_onAdd* msg)
{
	if (msg->roomPos == m_curIndex)
	{
		return;
	}


	RoomPlayer* user = new RoomPlayer();
	user->setCoins(msg->coins);
	user->setDiamonds(msg->diamonds);
	user->setLevel(msg->turrent_level);
	user->setMaxTurretLevel(msg->turrent_level);
	user->setUserName(msg->username.c_str());
	user->setPlayerState(RoomPlayer::PLAYERSTATE_NEW);
	user->setChestLv(msg->box_level);
	AI* ai = AIManager::getInstance()->getAI(user->getMaxTurretLevel());
	user->setAi(ai);
	int uiPos = msg->roomPos - m_curIndex + m_index;
	if (uiPos>3)
	{
		uiPos -= 4;
	}
	if (uiPos<0)
	{
		uiPos += 4;
	}
	user->setRoomPosition(uiPos);

	auto otherTurret = PlayerTurret::create();
	otherTurret->setAnchorPoint(ccp(0.5, 0.5));
	otherTurret->setPosition(turretPos[user->getRoomPosition()]);
	otherTurret->initWithDate(user);
	otherTurrets.pushBack(otherTurret);
	addChild(otherTurret, kZorderMenu, kTagBaseturret + user->getRoomPosition());

	TxtWaitingTurrent[user->getRoomPosition()]->setVisible(false);
}
void GameLayer::onSomeoneLeave(Msg_onLeave* msg)
{
	for (auto var:otherTurrets)
	{
		if (var->getRoomPos() == msg->roomPos)
		{
			var->removeFromParentAndCleanup(1);
			otherTurrets.eraseObject(var);
			TxtWaitingTurrent[msg->roomPos]->setVisible(true);
			return;
		}
	}
}
void GameLayer::onClientInit(Msg_onInit* msg)
{
	//初始座位
	createTurret();
	m_curIndex = msg->roomPos;
	auto vec = msg->roomplayers;
	for (auto var:vec)
	{
		if (var->getRoomPosition() == m_curIndex)
		{
			return;
		}
		int uiPos = var->getRoomPosition() - m_curIndex + m_index;
		if (uiPos > 3)
		{
			uiPos -= 4;
		}
		if (uiPos < 0)
		{
			uiPos += 4;
		}
		var->setRoomPosition(uiPos);
		AI* ai = AIManager::getInstance()->getAI(var->getMaxTurretLevel());
		var->setAi(ai);
		auto otherTurret = PlayerTurret::create();
		otherTurret->setAnchorPoint(ccp(0.5, 0.5));
		otherTurret->setPosition(turretPos[var->getRoomPosition()]);
		otherTurret->initWithDate(var);
		otherTurrets.pushBack(otherTurret);
		addChild(otherTurret, kZorderMenu, kTagBaseturret + var->getRoomPosition());

		TxtWaitingTurrent[var->getRoomPosition()]->setVisible(false);
	}
	//初始时间
	init_creat_time = msg->initCreateTime;
	//初始鱼群
	auto FishesInfos = msg->_FishesInfos;
	//处理当前帧鱼群
	auto NowFpsFishInfo = FishesInfos.at(1);
	GameData::getInstance()->setRandomSeed(NowFpsFishInfo.fishGroupsItem.randomSTC);
	auto _fishGroupsItem = NowFpsFishInfo.fishGroupsItem;
	unsigned long  difTime = (init_creat_time - NowFpsFishInfo.seq_create_time) / 1000;
	_fishGroupType = _fishGroupsItem.group_type;
	if (_fishGroupsItem.group_type == 0)//鱼群
	{
		for (auto var : _fishGroupsItem.fishItems)
		{
			FishManage::getInstance()->addServerItemFishs(var);
		}
		
	}
	else if (_fishGroupsItem.group_type == 1)
	{
		_fishGroupMonentType = _fishGroupsItem.group_type;
		loadNewMonent(_fishGroupMonentType);
		difTime = (init_creat_time - NowFpsFishInfo.seq_create_time) / 1000;
		difTime +=(int)(NowFpsFishInfo.seq_interval*NowFpsFishInfo.fishGroupsItem.seq - 1)-7;
	}
	runAction(Sequence::create(DelayTime::create(0), CallFunc::create([=]{FFOneTimeToFishes(difTime); }), nullptr));

}
void GameLayer::onFishesMsg(Msg_OnFishes*msg)
{
	//鱼群信息
	//初始鱼群
	auto NowFpsFishInfo = msg->_info;
	auto _fishGroupsItem = NowFpsFishInfo.fishGroupsItem;
	GameData::getInstance()->setRandomSeed(NowFpsFishInfo.fishGroupsItem.randomSTC);
	unsigned long  difTime = (init_creat_time - NowFpsFishInfo.seq_create_time) / 1000;
	_fishGroupType = _fishGroupsItem.group_type;
	if (_fishGroupsItem.group_type == 0)//鱼群
	{
		for (auto var : _fishGroupsItem.fishItems)
		{
			FishManage::getInstance()->addServerItemFishs(var);
		}

	}
	else if (_fishGroupsItem.group_type == 1)
	{
		if (_fishGroupsItem.seq==1)
		{
			loadNewMonent(9);
		}
		_fishGroupMonentType = _fishGroupsItem.group_type;
		
	}
	//广播
	auto node = GameManage::getInstance()->getGuiLayer()->getChildByName("displayboard");
	if (node)
	{
		((ScrollTextEx*)node)->setScrollStrs(msg->eventstrs);
		return;
	}
	auto DisplayBoard = ScrollTextEx::create();
	DisplayBoard->setPosition(498, 463);
	DisplayBoard->setAutoScroll(true);
	DisplayBoard->setScrollStrs(msg->eventstrs);
	DisplayBoard->setName("displayboard");
	GameManage::getInstance()->getGuiLayer()->addChild(DisplayBoard, kZorderMenu);

}
void GameLayer::onConError(Msg_ConError*msg)
{
	pause();
	auto dioag = TwiceSureDialog::createDialog(ChineseWord("ConError").c_str(), CC_CALLBACK_1(GameLayer::exitCallback, this));
	dioag->setPosition(0, 0);
	dioag->setCloseButtonCallback(CC_CALLBACK_1(GameLayer::exitCallback, this));
	GameManage::getInstance()->getGuiLayer()->addChild(dioag, 30);
}

void GameLayer::onUpdateTurrent(Msg_OnUpdateTurrent*msg)
{

	int k = 0;
	if (msg->errorcode==0)
	{
		GameManage::getInstance()->getGameLayer()->GetMyTurret()->onLockTheTurrent(msg->_info.turrent_level,msg->_info.rewards,msg->_info.requireDiamonds);
	}
	else
	{
		Layer* layer;
		int type = GameData::getInstance()->getTouchLockTurretType();
		if (type ==1)
		{
			layer = payLayer::createLayer(2);
		}
		else
		{
			layer = showLockTurretLayer::create();
		}
		layer->setPosition(Point::ZERO);
		GameManage::getInstance()->getGuiLayer()->addChild(layer, 20, 50);
		GameData::getInstance()->setTouchLockTurretType(0);
	}

}
void GameLayer::exitCallback(Ref*psend)
{
	auto node = BankruptManager::getInstance()->getgetRewardNode();
	if (node)
	{
		node->retain();
		node->removeFromParentAndCleanup(false);

	}
	LogEventPageChange::getInstance()->addEventItems(2, 1, 0);
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, LobbyScene::createScene()));

	GameData::getInstance()->setisOnGameScene(false);
}
void GameLayer::onUpdateLevel(Msg_OnExpUpdate*msg)
{
	for (auto var:msg->_infos)
	{
		GameManage::getInstance()->onPlayerUpgrade(var);
	}
	
}

void GameLayer::onUseSkill(Msg_UseSkill*msg)
{
	if (msg->errorcode==0)
	{
		if (msg->use_type == 0)
		{
			BagManager::getInstance()->changeItemCount(msg->itemid, -1);
			auto skillid = skillManager::getInstance()->getSkillInfoByitemId(msg->itemid).skill_id;
			skillManager::getInstance()->useSkillById(skillid, GameManage::getInstance()->getGameLayer()->GetMyTurret());
		}
		else
		{
			User::getInstance()->addDiamonds(-msg->price);
			auto skillid = skillManager::getInstance()->getSkillInfoByitemId(msg->itemid).skill_id;
			skillManager::getInstance()->useSkillById(skillid, GameManage::getInstance()->getGameLayer()->GetMyTurret());
		}
	}
	else if (msg->errorcode == 302)
	{
		auto dialog = TwiceSureDialog::createDialog(ChineseWord("havanoDmToUseskill").c_str(), CC_CALLBACK_1(GameLayer::ToPayShopCallBack, this));
		dialog->setPosition(Point::ZERO);
		dialog->setName("havanoDmToUseskill");
		GameManage::getInstance()->getGuiLayer()->addChild(dialog, 20);
	}


}
void GameLayer::ToPayShopCallBack(Ref*psend)
{
	auto layer = payLayer::createLayer(2);
	layer->setPosition(0, 0);
	GameManage::getInstance()->getGuiLayer()->addChild(layer, 20);
	auto node = GameManage::getInstance()->getGuiLayer()->getChildByName("havanoDmToUseskill");
	node->removeFromParentAndCleanup(1);
}
void GameLayer::MsgUpdata(float dt)
{
	auto msg = Msgs;
	//防止异步线程加入时，Msgs越界处理
	for (auto var : msg)
	{
		switch (var->getMsgId())
		{
		case MsgInit:
			onClientInit((Msg_onInit*)(var));
			break;
		case MsgConError:
			onConError((Msg_ConError*)(var));
			break;
		case MsgOnLeave:
			onSomeoneLeave((Msg_onLeave*)(var));
			break;
		case MsgOnAdd:
			onSomeoneComing((Msg_onAdd*)(var));
			break;
		case MsgOnFishes:
			onFishesMsg((Msg_OnFishes*)var);
			break;
		case MsgOnUpdateTurrent:
			onUpdateTurrent((Msg_OnUpdateTurrent*)var);
			break;
		case MsgOnExpUpdate:
			onUpdateLevel((Msg_OnExpUpdate*)var);
			break;
		case MsgUseSkill:
			onUseSkill((Msg_UseSkill*)var);
			break;
		default:
			break;
		}
		Msgs.pop_front();
		delete var;
	}
	
}



void GameLayer::FFOneTimeToFishes(float FFTime)
{
	
	if (FFTime<0)
	{
		return;
	}
	int time = (int)FFTime;
	for (int i = 0; i < time*10; i++)
	{
		UpdateCreateFishByServer(0.1);
		auto vec = FishManage::getInstance()->getAllFishInPool();
		for (auto var : vec)
		{
			var->moveUpdata(0.1);
			auto move = var->getActionByTag(kTagAcMove);
			if (move)
			{
				move->step(0.1);
			}
		}
	}
	

}

void GameLayer::UpdateCreateFishByServer(float dt)
{
	FishManage::getInstance()->UpdateServerWhenController(dt);

	if (_fishGroupType == 0)
	{
		FishManage::getInstance()->UpdataServerCreateFish(dt);
	}
	else if (_fishGroupType == 1)
	{
		FishManage::getInstance()->UpdateWhenController(dt);
	}
	
}

void GameLayer::UpdateUserinfo(float dt)
{
	auto difCoins = GameData::getInstance()->getchangeCoin();
	auto difExp = GameData::getInstance()->getchangeExp();
	GameData::getInstance()->setchangeCoin(0);
	GameData::getInstance()->setchangeExp(0);


	Server::getInstance()->sendUserInfoChange(difCoins, difExp);
}