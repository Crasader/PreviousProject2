#include "Turret/PlayerTurret.h"
#include "bullet/BulletManage.h"
#include "utill/AnimationUtil.h"
#include "domain/user/User.h"
#include "config/ConfigRoom.h"
#include "data/GameData.h"
#include "config/ConfigVipTurrent.h"
#include "config/ConfigNormalTurrent.h"
#include "domain/bonuspool/BonusPoolManager.h"
#include "core/GameLayer.h"
#include "domain/mermaid/MermaidTask.h"
#include "core/showTurretLayer.h"
#include "domain/bankrupt/BankruptManager.h"
#include "domain/bag/BagManager.h"
#include "core/GameGuiLayer.h"
#include "utill/Audio.h"
#include "core/GetRewardNode.h"
#include "domain/logevent/LogEventMannger.h"
#include "domain/game/GameManage.h"
#include "lobby/Nobility/NobilityLayer.h"
#include "domain/logevent/LogEventPageChange.h"
#include "bullet/Laster.h"
#include "domain/gameConfig/gameConfig.h"
#include "config/ConfigChest.h"

enum 
{
	kTagBankrupt = 20
};


bool PlayerTurret::init(){
	if (!Sprite::initWithFile("turretBg.png")){
		return false;
	}
	setIsShowInfo(false);
	
	m_turret = Turret::create();

	m_turret->setPosition(getContentSize().width / 2, getContentSize().height*0.6);
	addChild(m_turret,1);

	
	scheduleUpdate();
	return true;
}
void PlayerTurret::setUpgradeButton()
{
	auto upgradeButton = MenuItemImage::create("add_nor.png", "add_click.png", CC_CALLBACK_1(PlayerTurret::upgradeTurret, this));
	upgradeButton->setPosition(this->getContentSize().width*0.9, this->getContentSize().height*0.2);
	auto degradeButton = MenuItemImage::create("minus_nor.png", "minus_click.png", CC_CALLBACK_1(PlayerTurret::degradeTurret, this));
	degradeButton->setPosition(this->getContentSize().width*0.1, this->getContentSize().height*0.2);
	auto menu = Menu::create(upgradeButton, degradeButton, nullptr);
	menu->setPosition(Point::ZERO);
	addChild(menu,11,"menuUpDe");
}
void PlayerTurret::initTurretWithType(){
	auto vipLevel = User::getInstance()->getVipLevel();
	if (vipLevel == 0)
	{
		auto var = ConfigNormalTurrent::getInstance()->getNormalTurrent(User::getInstance()->getMaxTurrentLevel());
		turretdata.init(var.normal_turrent_id, var.turrent_ui_id, var.net_per, var.catch_per, var.ui_type, var.net_type);
	}
	else
	{
		auto var = ConfigVipTurrent::getInstance()->getVipTurrent(User::getInstance()->getVipLevel());
		turretdata.init(var.vip_turrent_id, var.turrent_ui_id, var.net_per, var.catch_per,var.ui_type, var.net_type);
	}


	m_turret->initWithType(turretdata.turrent_ui_id);
	
}





void PlayerTurret::addGoldFishForAi()
{
	goldfishcounts++;
	//Ê¹ÓÃ±ù¶³
	if (goldfishcounts%5 == 0&&GameData::getInstance()->getRoomID()>1)
	{
		skillManager::getInstance()->robotUseSkillFreeze(this);
	}
	//Ê¹ÓÃÕÙ»½
	if (goldfishcounts% 30 == 0 && GameData::getInstance()->getRoomID() > 1)
	{
		skillManager::getInstance()->robotUseSkillFreeze(this);
	}
}
void PlayerTurret::update(float delta)
{
	
	if (isRobot)
	{

	}
	else
	{
		auto num = User::getInstance()->getCoins();
		m_CoinLabel->setString(Value(num).asString().c_str());

		num = User::getInstance()->getDiamonds();
		auto lastnum = Value(m_DiamondLabel->getString()).asInt();
		if (num>lastnum)
		{
			GameManage::getInstance()->showLockTurrent();
		}
		m_DiamondLabel->setString(Value(num).asString().c_str());

		num = GameData::getInstance()->getnowLevel();
		nCurLevel->setString(Value(num).asString().c_str());
		if (GameData::getInstance()->getisOnBankrupt())
		{
			if (User::getInstance()->getCoins()>0)
			{
				GameData::getInstance()->setisOnBankrupt(false);
				getChildByTag(kTagBankrupt)->removeFromParentAndCleanup(1);
			}
		}
	}


}
void PlayerTurret::initTurretWithTypeForRobot(){
	//auto viplevel = rand() % 4;
	//if (viplevel == 0)
	//{
		auto var = ConfigNormalTurrent::getInstance()->getNormalTurrent(m_robotData->getMaxTurretLevel());
		turretdata.init(var.normal_turrent_id, var.turrent_ui_id, var.catch_per,var.net_per, var.ui_type, var.net_type);
	//}
	//else
	//{
	//	auto var = ConfigVipTurrent::getInstance()->getVipTurrent(User::getInstance()->getVipLevel());
	//	turretdata.init(var.vip_turrent_id, var.turrent_ui_id + 2, var.net_per, var.ui_type, var.net_type);
	//}




	m_turret->initWithType(turretdata.turrent_ui_id);
}

void PlayerTurret::upgradeTurret(Ref* psend)
{
	m_turretdata = GameData::getInstance()->getTurrentData();
	m_turretdata = ConfigTurrent::getInstance()->getNextTurrent(m_turretdata.multiple);
	if (m_turretdata.turrentId>User::getInstance()->getMaxTurrentLevel())
	{
		m_turretdata = ConfigTurrent::getInstance()->getTurrent(1);
	}
	nCurLevel->setString(Value(m_turretdata.turrentId).asString());
	GameData::getInstance()->setnowLevel(m_turretdata.multiple);
	m_turret->upgradeTurret();
}
void PlayerTurret::degradeTurret(Ref* psend)
{
	m_turretdata = GameData::getInstance()->getTurrentData();
	auto nowlevel = m_turretdata.turrentId;
	m_turretdata = ConfigTurrent::getInstance()->getLastTurrent(nowlevel);
	auto room = ConfigRoom::getInstance()->getRoombyId(GameData::getInstance()->getRoomID());
	if (m_turretdata.turrentId < room.unlock_turrent_level||m_turretdata.turrentId==-1)
	{
		m_turretdata = ConfigTurrent::getInstance()->getTurrent(User::getInstance()->getMaxTurrentLevel());
	}
	nCurLevel->setString(Value(m_turretdata.turrentId).asString());
	GameData::getInstance()->setnowLevel(m_turretdata.multiple);
	m_turret->degradeTurret();
	LogEventSpcEvent::getInstance()->addEventItems(2, 0);
}



void PlayerTurret::rorateTurret(float angle)
{
	auto rotate = RotateTo::create(0.1, angle);
	m_turret->runAction(rotate);
}


void PlayerTurret::shoot(float degree){

	if (!isRobot&&GameData::getInstance()->getisOnBankrupt())
	{
		return;
	}
	if (nChairNoIndex > 1)
	{
		degree = 180+degree;
	}
	auto bullet = BulletManage::getInstance()->createBullet(turretdata, 90);
	bullet->setRotation(degree);
	bullet->setPosition(/*this->getPosition()*/m_turret->getTampionPos());
	bullet->setPlayerTurret(this);
	getParent()->addChild(bullet);
	
	//ï¿½Ú¿ï¿½ï¿½ï¿½ï¿½ï¿½

	m_turret->shoot();

	//ï¿½ï¿½ï¿½ð¶¯»ï¿½
	auto aniNode = Sprite::create();
	aniNode->setPosition(m_turret->getContentSize().width/2,m_turret->getContentSize().height*1.0);
	m_turret->addChild(aniNode, 5);
	aniNode->runAction(Sequence::create(AnimationUtil::getInstance()->getAnimate("aniShoot"),RemoveSelf::create(1),nullptr));

	//ï¿½ï¿½ï¿½Ñ½ï¿½ï¿?
	costMoney();
	

}

void PlayerTurret::setAIinfo(AI*info)
{
	m_aiinfo = info;
	schedule(schedule_selector(PlayerTurret::doAIthing), info->getReqSteps() , CC_REPEAT_FOREVER, 0);
}

void PlayerTurret::doAIthing(float dt)
{
	
	auto walk = m_aiinfo->nextStep(10, getPosition());
	rorateTurret(walk.getAngle());
	
	
	if (walk.getFire())
	{
		runAction(Sequence::create(DelayTime::create(0.10f), CallFunc::create([&]{shoot(m_turret->getRotation()); }), nullptr));
		
	}
}
void PlayerTurret::stopAI()
{
	unschedule(schedule_selector(PlayerTurret::doAIthing));
}


Point coinPos[4] =
{
	Vec2(-130, 45),
	Vec2(130+150, 45),
	Vec2(-130, 45),
	Vec2(130+150, 45)
};
void PlayerTurret::createPlayerCoin(User* user, int index)
{
	isRobot = false;
	auto spCoinBG = Sprite::create("coinAnddiamondBG.png");
	spCoinBG->setPosition(coinPos[index]);
	addChild(spCoinBG, 10, index);
	m_coinLabelPos = spCoinBG->getPosition();
	m_CoinLabel = LabelAtlas::create(Value(user->getCoins()).asString().c_str(), "multipleNum.png", 15, 21, '0');
	m_CoinLabel->setPosition(spCoinBG->getContentSize().width*0.9, spCoinBG->getContentSize().height*0.71);
	m_CoinLabel->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	spCoinBG->addChild(m_CoinLabel);

	m_DiamondLabel = LabelAtlas::create(Value(user->getDiamonds()).asString().c_str(), "multipleNum.png", 15, 21, '0');
	m_DiamondLabel->setPosition(spCoinBG->getContentSize().width*0.9, spCoinBG->getContentSize().height*0.29);
	m_DiamondLabel->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	spCoinBG->addChild(m_DiamondLabel);

}




void PlayerTurret::createPlayerCoin(RoomPlayer* user)
{
	
	auto spCoinBG = Sprite::create("coinAnddiamondBG.png");
	spCoinBG->setPosition(coinPos[user->getRoomPosition()]);
	addChild(spCoinBG, 10, user->getRoomPosition());
	m_coinLabelPos = spCoinBG->getPosition();
	nNowMoney = user->getCoins();
	m_CoinLabel = LabelAtlas::create(Value(user->getCoins()).asString().c_str(), "multipleNum.png", 15, 21, '0');
	m_CoinLabel->setPosition(spCoinBG->getContentSize().width*0.9, spCoinBG->getContentSize().height*0.71);
	m_CoinLabel->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	spCoinBG->addChild(m_CoinLabel);

	m_DiamondLabel = LabelAtlas::create(Value(user->getDiamonds()).asString().c_str(), "multipleNum.png", 15, 21, '0');
	m_DiamondLabel->setPosition(spCoinBG->getContentSize().width*0.9, spCoinBG->getContentSize().height*0.29);
	m_DiamondLabel->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	spCoinBG->addChild(m_DiamondLabel);

	if (user->getRoomPosition()>1)
	{
		spCoinBG->setRotation(180);
	}
}



void PlayerTurret::initWithDate(User* user,int index)
{



	int boxlv = user->getUserBoxLevel();
	
	if (boxlv>0)
	{
		auto sp = Sprite::create("circyleLight.png");
		sp->setPosition(getContentSize().width / 2, 0);
		sp->runAction(RepeatForever::create(RotateBy::create(5.0, 360)));
		addChild(sp, -1);
	}


	auto str = String::createWithFormat("turretBg_%d.png", boxlv);
	setTexture(str->getCString());

	str = String::createWithFormat("multipleBg_%d.png", boxlv);
	auto levelBg = Sprite::create(str->getCString());
	levelBg->setPosition(getContentSize().width/2, levelBg->getContentSize().height / 2);
	addChild(levelBg, 10, "multipleBg");
	nCurLevel = LabelAtlas::create("0", "multipleNum.png", 15, 21, '0');
	nCurLevel->setAnchorPoint(Point::ANCHOR_MIDDLE);
	nCurLevel->setPosition(107.0 / 2, 33.0 / 2);
	levelBg->addChild(nCurLevel);

	GameData::getInstance()->setnowLevel(User::getInstance()->getMaxTurrentLevel());
	m_turretdata = GameData::getInstance()->getTurrentData();
	initTurretWithType();
	setUpgradeButton();
	nCurLevel->setString(Value(m_turretdata.turrentId).asString().c_str());
	
	createPlayerCoin(user,index);
	nChairNoIndex = index;
	if (user->getCoins()<=0)
	{
		onBankrupt();
	}
}
void PlayerTurret::initWithDate(RoomPlayer* user)
{
	int boxlv = rand()%4;
	
	if (boxlv > 0)
	{
		auto sp = Sprite::create("circyleLight.png");
		sp->setPosition(getContentSize().width / 2, 0);
		sp->runAction(RepeatForever::create(RotateBy::create(5.0, 360)));
		addChild(sp, -1);
	}

	auto str = String::createWithFormat("turretBg_%d.png", boxlv);
	setTexture(str->getCString());

	str = String::createWithFormat("multipleBg_%d.png", boxlv);
	auto levelBg = Sprite::create(str->getCString());
	levelBg->setPosition(getContentSize().width / 2, levelBg->getContentSize().height / 2);
	addChild(levelBg, 10, "multipleBg");
	nCurLevel = LabelAtlas::create("0", "multipleNum.png", 15, 21, '0');
	nCurLevel->setAnchorPoint(Point::ANCHOR_MIDDLE);
	nCurLevel->setPosition(107.0 / 2, 33.0 / 2);
	levelBg->addChild(nCurLevel);


	m_robotData = user;
	m_turretdata = ConfigTurrent::getInstance()->getTurrent(user->getMaxTurretLevel());
	nChairNoIndex = user->getRoomPosition();
	initTurretWithTypeForRobot();
	nCurLevel->setString(Value(m_turretdata.turrentId).asString().c_str());
	
	createPlayerCoin(user);
    setAIinfo(user->getAi());
	if (user->getRoomPosition() > 1)
	{
		setRotation(180);
	}
	
	
}
void PlayerTurret::getCoinByFish(Fish* fish)
{

	int num = 0;
	LogEventFish::getInstance()->addFishCatchTimes(fish->getFishID());
		

	if (isRobot)
	{
		addGoldFishForAi();
		num = fish->getFishGold() * m_turretdata.multiple;
		auto nowNum = Value(m_CoinLabel->getString()).asInt();
		m_CoinLabel->setString(Value(nowNum + num).asString().c_str());
		
	}
	else
	{
		if (GameData::getInstance()->getisOnBankrupt())
		{
			return;
		}
		LogEventFish::getInstance()->addFishUserCatchTimes(fish->getFishID());
		m_turretdata = GameData::getInstance()->getTurrentData();
	
		Audio::getInstance()->playSound(CATCHGOLD);
		num = fish->getFishGold()* m_turretdata.multiple*ConfigChest::getInstance()->getChestByLevel(User::getInstance()->getUserBoxLevel()).catch_per;
		m_CoinLabel->setString(Value(User::getInstance()->addCoins(+num)).asString().c_str());
	
		auto exp = fish->getFishExperience();
		if (User::getInstance()->addExp(exp))
		{
			onPlayerUpgrade();
		}
		
		BonusPoolManager::getInstance()->addCoins(fish->getBounsPoorGold());

		auto event = GameData::getInstance()->getDiamondevent();
		if (GameData::getInstance()->getShotDiamondCount() >= event.fireTimes)
		{
		/*	User::getInstance()->addDiamonds(event.num);*/
			GameManage::getInstance()->getGameLayer()->onGetRewardByfish(this, fish, 1002, event.num);
			LogEventMagnate::getInstance()->addMagnateNum(event.itemId, event.num);
			GameData::getInstance()->setShotDiamondCount(0);
			GameData::getInstance()->setDiamondevent(MagnateManager::getInstance()->getDiamandMagnateEvent());

		
		}
		event = GameData::getInstance()->getpropevent();
		if (GameData::getInstance()->getShotPropCount() >= event.fireTimes)
		{
			GameManage::getInstance()->getGameLayer()->onGetRewardByfish(this, fish, event.itemId, event.num);
			LogEventMagnate::getInstance()->addMagnateNum(event.itemId, event.num);
			GameData::getInstance()->setShotPropCount(0);
			GameData::getInstance()->setpropevent(MagnateManager::getInstance()->getItemMagnateEvent());
	
		}
	}
	fish->createDropOutAniByCoin(getPosition(),num);
}

void PlayerTurret::onExit()
{
	Sprite::onExit();
	m_CoinLabel->removeFromParentAndCleanup(true);
	m_DiamondLabel->removeFromParentAndCleanup(true);
	m_turret->removeFromParentAndCleanup(true);
	
}


void PlayerTurret::onBankrupt()
{
	if (Value(m_CoinLabel->getString()).asInt()>0)
	{
		return;
	}
	auto sp = Sprite::create("bankrupt.png");
	sp->setPosition(getContentSize() / 2);
	addChild(sp, 10, kTagBankrupt);
	m_CoinLabel->setString("0");
	nNowMoney = 0;
	
	if (isRobot)
	{
		auto bankrupt = BankruptManager::getInstance()->getRobotBankrupt();
		stopAI(); 
		
		int *k = new int();
		*k = bankrupt.coins;
		runAction(Sequence::create(DelayTime::create(bankrupt.wait_time), CallFunc::create(CC_CALLBACK_0(PlayerTurret::onAIResurgenceCallBack,this, this, k)), nullptr));
	}
	else
	{
		auto bankrupt = BankruptManager::getInstance()->getBankrupt();
		if (!BankruptManager::getInstance()->getgetRewardNode() && bankrupt.coins>0)
		{
			auto layer = Director::getInstance()->getRunningScene()->getChildByTag(888);
			auto node = GetRewardNode::create(bankrupt);
			node->setPosition(getPosition()+Vec2(0,150));
			layer->addChild(node, 10);
			BankruptManager::getInstance()->setgetRewardNode(node);
			LogEventBankrupt::getInstance()->sendDataToServer(GameData::getInstance()->getRoomID(),2, 1);
		}
		else if (bankrupt.coins==0)
		{
			auto pay = payLayer::createLayer(1);
			pay->setPosition(0, 0);
			pay->setEventPont(19);
			GameManage::getInstance()->getGuiLayer()->addChild(pay, 20);
		}
		
		GameData::getInstance()->setisOnBankrupt(true);	
		
	}
}
void PlayerTurret::onAIResurgenceCallBack(Node* sender, void* data)
{

	setAIinfo(m_aiinfo);
	auto var = *((int*)data);
	nNowMoney += var;
	m_CoinLabel->setString(Value(nNowMoney).asString().c_str());
	getChildByTag(kTagBankrupt)->removeFromParentAndCleanup(1);
}

void PlayerTurret::refreshTurretInfo()
{
	initTurretWithType();
}
void PlayerTurret::setLightFish(Fish* fish)
{
	if (fish == nullptr)
	{

		auto node = getChildByName("Laster");
		if (node)
		{
			node->removeFromParentAndCleanup(1);
			node = nullptr;
		}
		return;
	}
	else
	{
		if (lightFish)
		{
			lightFish->stopLightShoot();
		}

		fish->onLightShoot();
	}
	lightFish = fish;


	auto node = getChildByName("Laster");
	if (node)
	{
		node->removeAllChildrenWithCleanup(1);
		node = nullptr;
	}
	auto spLaster = Laster::create();
	spLaster->setPlayerTurret(this);
	getParent()->addChild(spLaster,6,"Laster");

	
}

void PlayerTurret::rorateAndShootOnlight(float dt)
{
	if (lightFish == nullptr)
	{
		return;
	}
	if (!isRobot&&GameData::getInstance()->getisOnBankrupt())
	{
		return;
	};
	costMoney();

	auto pos = lightFish->getPosition();
	float degree = getTurretRotation(getPosition(), pos);
	rorateTurret(degree);

	LogEventFish::getInstance()->addFishUserCostCoin(lightFish->getFishID(), 2 * getTurrentMupltData().multiple);
	LogEventFish::getInstance()->addFishHitTimes(lightFish->getFishID());
	float k = rand_0_1();
	if (k < (lightFish->getGrabProbability()*turretdata.catch_per * 2))
	{
		GameManage::getInstance()->CatchTheFishOntheTurrent(lightFish, 1,this);
		lightFish = nullptr;
	}

}
void PlayerTurret::shootOnLight(float dt)
{

}

void PlayerTurret::beginLightShoot()
{
	getChildByName("menuUpDe")->setVisible(false);
	m_turret->changeToLightTurret();

	auto aniNode = Sprite::create();
	aniNode->setPosition(m_turret->getPosition());
	addChild(aniNode,0, "aniTurretLight");
	auto ac = RepeatForever::create(AnimationUtil::getInstance()->getAnimate("aniJiGuangBottom"));
	aniNode->runAction(ac);
	setLightFish(lightFish);
	schedule(schedule_selector(PlayerTurret::rorateAndShootOnlight), GameConfig::getInstance()->getShootData().shootInterval);
}
void PlayerTurret::endLightShoot()
{
	getChildByName("aniTurretLight")->removeFromParentAndCleanup(1);
	getChildByName("menuUpDe")->setVisible(true);
	m_turret->changeToNormalTurret();
	if (lightFish)
	{
		lightFish->stopLightShoot();
	}
	stopActionByTag(123);

	auto node = getParent()->getChildByName("Laster");
	if (node)
	{
		node->removeAllChildrenWithCleanup(1);
		node = nullptr;
	}
	unschedule(schedule_selector(PlayerTurret::rorateAndShootOnlight));
}


void PlayerTurret::setLockFish(Fish* fish)
{
	if (fish == nullptr)
	{
		
		
	}
	else
	{
		if (lockFish)
		{
			lockFish->stopLockShoot();
		}
	
		fish->onLockShoot();
	}	
	lockFish = fish;
}


void PlayerTurret::beginLockShoot()
{
	auto aniNode = Sprite::create();
	aniNode->setPosition(m_turret->getPosition());
	addChild(aniNode, 5, "aniTurretLock");
	aniNode->runAction(RepeatForever::create(AnimationUtil::getInstance()->getAnimate("aniTurretLock")));
	schedule(schedule_selector(PlayerTurret::rorateAndShootOnlock),0.2f);
}
void PlayerTurret::endLockShoot()
{
	getChildByName("aniTurretLock")->removeFromParentAndCleanup(1);
	if (lockFish)
	{
		lockFish->stopLockShoot();
	}
	unschedule(schedule_selector(PlayerTurret::rorateAndShootOnlock));
}

void PlayerTurret::rorateAndShootOnlock(float dt)
{
	if (lockFish == nullptr)
	{
		return;
	}
	if (!isRobot&&GameData::getInstance()->getisOnBankrupt())
	{
		return;
	}
	auto pos = lockFish->getPosition();
	float degree =getTurretRotation(getPosition(), pos);
	rorateTurret(degree);
	scheduleOnce(schedule_selector(PlayerTurret::shootOnLock), 0.1f);
}
void PlayerTurret::shootOnLock(float dt){

	if (lockFish == nullptr)
	{
		return;
	}

	auto degree = m_turret->getRotation();
	auto bullet = BulletManage::getInstance()->createBulletNoinPool(turretdata, 90);
	bullet->setRotation(degree);
	bullet->unscheduleUpdate();
	auto pos = m_turret->getTampionPos();
	bullet->setPosition(m_turret->getTampionPos());
	bullet->setPlayerTurret(this);
	auto duration = pos.distance(lockFish->getPosition()) / 800.0f;
	bullet->moveToLockfish(duration, lockFish);
	getParent()->addChild(bullet);




	m_turret->shoot();

	//ï¿½ï¿½ï¿½ð¶¯»ï¿½
	auto aniNode = Sprite::create();
	aniNode->setPosition(m_turret->getContentSize().width / 2, m_turret->getContentSize().height*1.0);
	m_turret->addChild(aniNode, 5);
	aniNode->runAction(Sequence::create(AnimationUtil::getInstance()->getAnimate("aniShoot"), RemoveSelf::create(1), nullptr));


	//ï¿½ï¿½ï¿½Ñ½ï¿½ï¿?
	costMoney();
}


void PlayerTurret::beginAutoShoot()
{
	setTargetPos(Vec2(-1, -1));

	schedule(CC_CALLBACK_1(PlayerTurret::rorateAndShootOnAuto,this),0.2f,"AutoShoot"); //TODO:ï¿½Óµï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ù¶È¡ï¿½ï¿½ï¿½Òªï¿½ï¿½ï¿½ï¿½
}
void PlayerTurret::endAutoShoot()
{

	unschedule("AutoShoot");
}

void PlayerTurret::rorateAndShootOnAuto(float dt)
{
	CCLOG("%f", dt);
	if (targetPos == Point(-1,-1))
	{
		return;
	}
	if (!isRobot&&GameData::getInstance()->getisOnBankrupt())
	{
		return;
	}

	float degree =getTurretRotation(getPosition(), targetPos);
	rorateTurret(degree);
	scheduleOnce(schedule_selector(PlayerTurret::shootOnAuto), 0.1f);
}
void PlayerTurret::shootOnAuto(float dt){



	auto degree = m_turret->getRotation();
	auto bullet = BulletManage::getInstance()->createBullet(turretdata, 90);
	bullet->setRotation(degree);
	auto pos = m_turret->getTampionPos();
	bullet->setPosition(m_turret->getTampionPos());
	bullet->setPlayerTurret(this);
	getParent()->addChild(bullet);
	m_turret->shoot();

	//ï¿½ï¿½ï¿½ð¶¯»ï¿½
	auto aniNode = Sprite::create();
	aniNode->setPosition(m_turret->getContentSize().width / 2, m_turret->getContentSize().height*1.0);
	m_turret->addChild(aniNode, 5);
	aniNode->runAction(Sequence::create(AnimationUtil::getInstance()->getAnimate("aniShoot"), RemoveSelf::create(1), nullptr));


	//ï¿½ï¿½ï¿½Ñ½ï¿½ï¿?
	costMoney();
}






bool PlayerTurret::onTurretTouch(Point pos)
{
	if (isTurretBeTouch(pos))
	{
		if (isRobot)
		{
			showRobotInfo();
		}
		else
		{
			showPlayerInfo();
			auto layer = (GameLayer*)(Director::getInstance()->getRunningScene()->getChildByTag(777));
			if (isScheduled("AutoShoot"))
			{

				layer->endAutoShoot();
			}
		}
		return true;
	}
	return false;
}

bool PlayerTurret::isTurretBeTouch(Point pos)
{
	auto rect = getBoundingBox();
	if (rect.containsPoint(pos))
	{
		return true;
	}
	return false;
}
void PlayerTurret::showRobotInfo()
{
	setIsShowInfo(true);
}

void PlayerTurret::showPlayerInfo()
{
	auto node = getChildByName("showPlayerInfo");
	if (node)
	{
		return;
	}
	setIsShowInfo(true);
	auto menu = Menu::create();
	menu->setPosition(Point::ZERO);
	addChild(menu, 10, "showPlayerInfo");
	auto changeTurrent = MenuItemImage::create("changeTurrent.png", "changeTurrent.png", CC_CALLBACK_1(PlayerTurret::changeTurrentCallback, this));
	changeTurrent->setPosition(15, 110);
	menu->addChild(changeTurrent);

	auto autoShoot = MenuItemImage::create("autoShoot.png", "autoShoot.png", CC_CALLBACK_1(PlayerTurret::autoShootCallback, this));
	autoShoot->setPosition(getContentSize().width-15, 110);
	menu->addChild(autoShoot);
}

void PlayerTurret::removePlayerInfo()
{
	auto node = getChildByName("showPlayerInfo");
	if (node)
	{
		node->removeFromParentAndCleanup(1);
	}

	
}
void PlayerTurret::removeRobotInfo()
{

}
void PlayerTurret::changeTurrentCallback(Ref*psend) 
{
	auto node = (Node*)psend;
	auto layer = showTurretLayer::create(1);
	layer->setPosition(Point::ZERO);
	GameManage::getInstance()->getGuiLayer()->addChild(layer, 20,50);
	node->getParent()->removeFromParentAndCleanup(1);
	
}
void PlayerTurret::autoShootCallback(Ref*psend)
{
	auto node = (Node*)psend;
	node->getParent()->removeFromParentAndCleanup(1);

	auto layer = (GameLayer*)(Director::getInstance()->getRunningScene()->getChildByTag(777));
	if (isScheduled("AutoShoot"))
	{
		
		layer->endAutoShoot();
	}
	else
	{
		if (User::getInstance()->getNobillityCount()>0)
		{
			layer->beginAutoShoot();
		}
		else
		{
			auto layer = NobilityLayer::createLayer();
			layer->setPosition(0,0);
			GameManage::getInstance()->getGuiLayer()->addChild(layer,20);
		}
		
	}
}

void PlayerTurret::onPlayerUpgrade()
{
	GameManage::getInstance()->onPlayerUpgrade();
}

void PlayerTurret::costMoney()
{

	if (isRobot)
	{
		auto num = (Value(m_turretdata.multiple).asInt());
		nNowMoney -= num;
		m_CoinLabel->setString(Value(nNowMoney).asString().c_str());
		if (nNowMoney <= 0)
		{
			onBankrupt();
		}
	}
	else
	{
		GameData::getInstance()->setShotDiamondCount(1 + (GameData::getInstance()->getShotDiamondCount()));
		GameData::getInstance()->setShotPropCount(1 + (GameData::getInstance()->getShotPropCount()));
		auto num = Value(m_turretdata.multiple).asInt();
		auto nowCoin = User::getInstance()->addCoins(-num);
		if (nowCoin <= 0)
		{
			onBankrupt();
		}
		m_CoinLabel->setString(Value(nowCoin).asString().c_str());

		if (GameData::getInstance()->getIsOnMaridTask())
		{
			GameData::getInstance()->getmermaidTask()->addCoins(num);
		}
	}
}
