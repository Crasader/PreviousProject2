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
enum 
{
	kTagBankrupt = 20
};


bool PlayerTurret::init(){
	if (!Sprite::initWithFile("turretBg.png")){
		return false;
	}
	auto levelBg = Sprite::create("multipleBg.png");
	levelBg->setPosition(getContentSize().width / 2, levelBg->getContentSize().height / 2);
	addChild(levelBg,10);
	nCurLevel = LabelAtlas::create("0", "multipleNum.png", 15, 21, '0');
	nCurLevel->setAnchorPoint(Point::ANCHOR_MIDDLE);
	nCurLevel->setPosition(levelBg->getContentSize() / 2);
	levelBg->addChild(nCurLevel);
	m_turret = Turret::create();

	m_turret->setPosition(getContentSize().width / 2, getContentSize().height*0.6);
	addChild(m_turret);
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
	addChild(menu);
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
		turretdata.init(var.vip_turrent_id, var.turrent_ui_id+2, var.net_per, var.catch_per,var.ui_type, var.net_type);
	}


	m_turret->initWithType(turretdata.turrent_ui_id);
	
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
		m_DiamondLabel->setString(Value(num).asString().c_str());
		num = GameData::getInstance()->getnowLevel();
		nCurLevel->setString(Value(num).asString().c_str());
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



	m_turret = Turret::create();
	m_turret->initWithType(turretdata.turrent_ui_id);
	m_turret->setPosition(getContentSize().width / 2, getContentSize().height*0.5);
	addChild(m_turret);
}

void PlayerTurret::upgradeTurret(Ref* psend)
{
	m_turretdata = GameData::getInstance()->getTurrentData();
	m_turretdata = ConfigTurrent::getInstance()->getNextTurrent(m_turretdata.multiple);
	if (m_turretdata.turrentId>User::getInstance()->getMaxTurrentLevel())
	{
		m_turretdata = ConfigTurrent::getInstance()->getLastTurrent(m_turretdata.turrentId);
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
	if (m_turretdata.turrentId < room.unlock_turrent_level)
	{
		m_turretdata = ConfigTurrent::getInstance()->getNextTurrent(m_turretdata.turrentId);
	}
	nCurLevel->setString(Value(m_turretdata.turrentId).asString());
	GameData::getInstance()->setnowLevel(m_turretdata.multiple);
	m_turret->degradeTurret();
}



void PlayerTurret::rorateTurret(float angle)
{
	auto rotate = RotateTo::create(0.1, angle);
	m_turret->runAction(rotate);
}


void PlayerTurret::shoot(float degree){

	if (nChairNoIndex > 1)
	{
		degree = 180+degree;
	}
	auto bullet = BulletManage::getInstance()->createBullet(turretdata, 90);
	bullet->setRotation(degree);
	bullet->setPosition(/*this->getPosition()*/m_turret->getTampionPos());
	bullet->setPlayerTurret(this);
	getParent()->addChild(bullet);
	
	//炮口伸缩

	m_turret->shoot();

	//开火动画
	auto aniNode = Sprite::create();
	aniNode->setPosition(m_turret->getContentSize().width/2,m_turret->getContentSize().height*1.0);
	m_turret->addChild(aniNode, 5);
	aniNode->runAction(Sequence::create(AnimationUtil::getInstance()->getAnimate("aniShoot"),RemoveSelf::create(1),nullptr));

	//花费金币
	if (isRobot)
	{
		auto num = Value(m_turretdata.multiple).asInt();
		nNowMoney -= num;
		m_CoinLabel->setString(Value(nNowMoney).asString().c_str());
		if (nNowMoney<=0)
		{
			onBankrupt();
		}
	}
	else
	{
		
		auto num = Value(m_turretdata.multiple).asInt();
		m_CoinLabel->setString(Value(User::getInstance()->addCoins(-num)).asString().c_str());
		if (GameData::getInstance()->getIsOnMaridTask())
		{
			GameData::getInstance()->getmermaidTask()->addCoins(num);
		}
	}
	

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
	GameData::getInstance()->setnowLevel(User::getInstance()->getMaxTurrentLevel());
	m_turretdata = GameData::getInstance()->getTurrentData();
	initTurretWithType();
	setUpgradeButton();
	nCurLevel->setString(Value(m_turretdata.turrentId).asString().c_str());
	
	createPlayerCoin(user,index);
	nChairNoIndex = index;
}
void PlayerTurret::initWithDate(RoomPlayer* user)
{
	m_robotData = user;
	auto a = user->getMaxTurretLevel();
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
	
	///需要鱼的配置属性
	if (isRobot)
	{
		auto num = fish->getFishGold() * m_turretdata.multiple;
		auto nowNum = Value(m_CoinLabel->getString()).asInt();
		m_CoinLabel->setString(Value(nowNum + num).asString().c_str());
	}
	else
	{
		m_turretdata = GameData::getInstance()->getTurrentData();
		//获得金币
		auto num = fish->getFishGold()* m_turretdata.multiple;
		m_CoinLabel->setString(Value(User::getInstance()->addCoins(+num)).asString().c_str());
		//获得经验
		num = fish->getFishExperience();
		User::getInstance()->addExp(num);

		//奖金池
		BonusPoolManager::getInstance()->addCoins(fish->getBounsPoorGold());
		//钻石鱼
		auto event = GameData::getInstance()->getevent();
		if (GameData::getInstance()->getShotCount() >= event.fireTimes)
		{
			User::getInstance()->addDiamonds(event.num);
			GameData::getInstance()->setShotCount(0);
			GameData::getInstance()->setevent(MagnateManager::getInstance()->getDiamandMagnateEvent());
			//TODO::在鱼上得到奖品UI显示
		}
	}
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
		stopAI();
		auto bankrupt = BankruptManager::getInstance()->getBankrupt();
		int *k = new int();
		*k = bankrupt.coins;
		runAction(Sequence::create(DelayTime::create(bankrupt.wait_time), CallFunc::create(CC_CALLBACK_0(PlayerTurret::onAIResurgenceCallBack,this, this, k)), nullptr));
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



std::string PlayerTurret::getNetImgPath(int ui_type, int net_type)
{
	auto str = String::createWithFormat("bulletAndNet/net_%d_%d", ui_type, net_type);
	return str->getCString();
}

void PlayerTurret::refreshTurretInfo()
{
	initTurretWithType();
}


void PlayerTurret::beginLockShoot()
{
	schedule(schedule_selector(PlayerTurret::rorateAndShootOnlock),0.2f);
}
void PlayerTurret::endLockShoot()
{
	unschedule(schedule_selector(PlayerTurret::rorateAndShootOnlock));
}

void PlayerTurret::rorateAndShootOnlock(float dt)
{
	if (lockFish == nullptr)
	{
		return;
	}
	auto pos = lockFish->getPosition();
	float degree = GameLayer::getTurretRotation(getPosition(), pos);
	rorateTurret(degree);
	scheduleOnce(schedule_selector(PlayerTurret::shootOnLock), 0.1f);
}
void PlayerTurret::shootOnLock(float dt){

	if (lockFish == nullptr)
	{
		return;
	}
	//花费金币
	if (isRobot)
	{
		auto num = Value(m_turretdata.multiple).asInt();
		nNowMoney -= num;
		m_CoinLabel->setString(Value(nNowMoney).asString().c_str());
		if (nNowMoney <= 0)
		{
			onBankrupt();
		}
	}
	else
	{
		auto num = Value(m_turretdata.multiple).asInt();
		auto nowCoin = User::getInstance()->addCoins(-num);
		if (nowCoin < 0)
		{
			return;
		}
		m_CoinLabel->setString(Value(nowCoin).asString().c_str());
	}

	auto degree = m_turret->getRotation();
	auto bullet = BulletManage::getInstance()->createBulletNoinPool(turretdata, 90);
	bullet->setRotation(degree);
	bullet->setPosition(m_turret->getTampionPos());
	bullet->setPlayerTurret(this);
	getParent()->addChild(bullet);

	m_turret->shoot();

	//开火动画
	auto aniNode = Sprite::create();
	aniNode->setPosition(m_turret->getContentSize().width / 2, m_turret->getContentSize().height*1.0);
	m_turret->addChild(aniNode, 5);
	aniNode->runAction(Sequence::create(AnimationUtil::getInstance()->getAnimate("aniShoot"), RemoveSelf::create(1), nullptr));

}


void PlayerTurret::beginAutoShoot()
{
	setTargetPos(Vec2(-1, -1));
	schedule(CC_CALLBACK_1(PlayerTurret::rorateAndShootOnAuto,this),0.2f,"AutoShoot"); //TODO:子弹发射速度。需要配置
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
	float degree = GameLayer::getTurretRotation(getPosition(), targetPos);
	rorateTurret(degree);
	scheduleOnce(schedule_selector(PlayerTurret::shootOnAuto), 0.1f);
}
void PlayerTurret::shootOnAuto(float dt){


	//花费金币
	if (isRobot)
	{
		auto num = Value(m_turretdata.multiple).asInt();
		nNowMoney -= num;
		m_CoinLabel->setString(Value(nNowMoney).asString().c_str());
		if (nNowMoney <= 0)
		{
			onBankrupt();
		}
	}
	else
	{
		auto num = Value(m_turretdata.multiple).asInt();
		auto nowCoin = User::getInstance()->addCoins(-num);
		if (nowCoin < 0)
		{
			return;
		}
		m_CoinLabel->setString(Value(nowCoin).asString().c_str());
	}

	auto degree = m_turret->getRotation();
	auto bullet = BulletManage::getInstance()->createBullet(turretdata, 90);
	bullet->setRotation(degree);
	auto pos = m_turret->getTampionPos();
	bullet->setPosition(m_turret->getTampionPos());
	bullet->setPlayerTurret(this);
	getParent()->addChild(bullet);
	m_turret->shoot();

	//开火动画
	auto aniNode = Sprite::create();
	aniNode->setPosition(m_turret->getContentSize().width / 2, m_turret->getContentSize().height*1.0);
	m_turret->addChild(aniNode, 5);
	aniNode->runAction(Sequence::create(AnimationUtil::getInstance()->getAnimate("aniShoot"), RemoveSelf::create(1), nullptr));

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

}

void PlayerTurret::showPlayerInfo()
{
	auto node = getChildByName("showPlayerInfo");
	if (node)
	{
		return;
	}

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


void PlayerTurret::changeTurrentCallback(Ref*psend) 
{
	auto node = (Node*)psend;
	auto layer = showTurretLayer::create(1);
	layer->setPosition(Point::ZERO);
	Director::getInstance()->getRunningScene()->getChildByTag(888)->addChild(layer, 20);
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
		layer->beginAutoShoot();
	}
}