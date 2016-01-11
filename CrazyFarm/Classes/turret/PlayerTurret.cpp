#include "Turret/PlayerTurret.h"
#include "bullet/BulletManage.h"
#include "utill/AnimationUtil.h"
#include "user.h"
#include "config/ConfigRoom.h"
#include "data/GameData.h"
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
void PlayerTurret::initWithType(int type){
	m_turret = Turret::create();
	m_turret->initWithType(type);
	m_turret->setPosition(getContentSize().width/2,getContentSize().height*0.6);
	addChild(m_turret);
}

void PlayerTurret::upgradeTurret(Ref* psend)
{
	auto nowlevel = m_turretdata.turrentId;
	m_turretdata = ConfigTurrent::getInstance()->getNextTurrent(nowlevel);
	if (m_turretdata.turrentId>User::getInstance()->getMaxTurrentLevel())
	{
		m_turretdata = ConfigTurrent::getInstance()->getLastTurrent(m_turretdata.turrentId);
	}
	nCurLevel->setString(Value(m_turretdata.turrentId).asString());
	m_turret->upgradeTurret();
}
void PlayerTurret::degradeTurret(Ref* psend)
{
	auto nowlevel = m_turretdata.turrentId;
	m_turretdata = ConfigTurrent::getInstance()->getLastTurrent(nowlevel);
	auto room = ConfigRoom::getInstance()->getRoombyId(GAMEDATA::getInstance()->getRoomID());
	if (m_turretdata.turrentId < room.unlock_turrent_level)
	{
		m_turretdata = ConfigTurrent::getInstance()->getNextTurrent(m_turretdata.turrentId);
	}
	nCurLevel->setString(Value(m_turretdata.turrentId).asString());
	m_turret->degradeTurret();
}

void PlayerTurret::rorateTurret(float angle)
{
	auto rotate = RotateTo::create(0.1, angle);
	m_turret->runAction(rotate);
}

void PlayerTurret::setMaxLevel(int maxlevel)
{
	

	setnMaxLevel(maxlevel);
}

void PlayerTurret::shoot(float degree){
	if (nChairNoIndex > 1)
	{
		degree = 180+degree;
	}
	const int dd = 20;
	auto bullet = BulletManage::getInstance()->createBullet(1, 90);
	bullet->setRotation(degree);
	auto pos = m_turret->getTampionPos();
	CCLOG("shoot x:%f,y:%f,angle%f", pos.x, pos.y,degree);
	bullet->setPosition(/*this->getPosition()*/m_turret->getTampionPos());
	bullet->setPlayerTurret(this);
	getParent()->addChild(bullet);
	

	//开火动画
	auto aniNode = Sprite::create();
	aniNode->setPosition(m_turret->getContentSize().width/2,m_turret->getContentSize().height*1.2);
	m_turret->addChild(aniNode, 5);
	aniNode->runAction(Sequence::create(AnimationUtil::getInstance()->getAnimate("aniShoot"),RemoveSelf::create(1),nullptr));

	//花费金币
	if (isRobot)
	{
		auto num = Value(m_turretdata.multiple).asInt();
		auto nowNum = Value(m_CoinLabel->getString()).asInt();
		m_CoinLabel->setString(Value(nowNum-num).asString().c_str());
	}
	else
	{
		auto num = Value(m_turretdata.multiple).asInt();
		m_CoinLabel->setString(Value(User::getInstance()->addCoins(-num)).asString().c_str());
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

	m_CoinLabel = LabelAtlas::create(Value(user->getCoins()).asString().c_str(), "prop_num.png", 19, 23, '0');
	m_CoinLabel->setPosition(spCoinBG->getContentSize().width*0.9, spCoinBG->getContentSize().height*0.71);
	m_CoinLabel->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	spCoinBG->addChild(m_CoinLabel);

	m_DiamondLabel = LabelAtlas::create(Value(user->getDiamonds()).asString().c_str(), "prop_num.png", 19, 23, '0');
	m_DiamondLabel->setPosition(spCoinBG->getContentSize().width*0.9, spCoinBG->getContentSize().height*0.29);
	m_DiamondLabel->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	spCoinBG->addChild(m_DiamondLabel);

}




void PlayerTurret::createPlayerCoin(RoomPlayer* user)
{
	auto spCoinBG = Sprite::create("coinAnddiamondBG.png");
	spCoinBG->setPosition(coinPos[user->getRoomPosition()]);
	addChild(spCoinBG, 10, user->getRoomPosition());

	m_CoinLabel = LabelAtlas::create(Value(user->getCoins()).asString().c_str(), "prop_num.png", 19, 23, '0');
	m_CoinLabel->setPosition(spCoinBG->getContentSize().width*0.9, spCoinBG->getContentSize().height*0.71);
	m_CoinLabel->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	spCoinBG->addChild(m_CoinLabel);

	m_DiamondLabel = LabelAtlas::create(Value(user->getDiamonds()).asString().c_str(), "prop_num.png", 19, 23, '0');
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
	m_turretdata = ConfigTurrent::getInstance()->getTurrent(user->getMaxTurrentLevel());
	initWithType(user->getMaxTurrentLevel());
	setUpgradeButton();
	nCurLevel->setString(Value(m_turretdata.turrentId).asString().c_str());
	setMaxLevel(user->getMaxTurrentLevel());
	createPlayerCoin(user,index);
	nChairNoIndex = index;
}
void PlayerTurret::initWithDate(RoomPlayer* user)
{
	m_turretdata = ConfigTurrent::getInstance()->getTurrent(user->getMaxTurretLevel());
	nChairNoIndex = user->getRoomPosition();
	initWithType(user->getMaxTurretLevel());
	nCurLevel->setString(Value(m_turretdata.turrentId).asString().c_str());
	setMaxLevel(user->getMaxTurretLevel());
	createPlayerCoin(user);
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
		//获得金币
		auto num = fish->getFishGold()* m_turretdata.multiple;
		m_CoinLabel->setString(Value(User::getInstance()->addCoins(+num)).asString().c_str());
		//获得经验
		num = fish->getFishExperience();
		User::getInstance()->addExp(num);

	}
}

void PlayerTurret::onExit()
{
	Sprite::onExit();
	m_CoinLabel->removeFromParentAndCleanup(true);
	m_DiamondLabel->removeFromParentAndCleanup(true);
	m_turret->removeFromParentAndCleanup(true);
	
}