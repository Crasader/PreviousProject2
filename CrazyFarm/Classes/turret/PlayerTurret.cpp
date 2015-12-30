#include "Turret/PlayerTurret.h"
#include "bullet/BulletManage.h"
#include "utill/AnimationUtil.h"
#include "user.h"
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

	auto nowlevel = Value(nCurLevel->getString().c_str()).asInt();
	nCurLevel->setString(Value(++nowlevel).asString());
	m_turret->upgradeTurret();
}
void PlayerTurret::degradeTurret(Ref* psend)
{
	auto nowlevel = Value(nCurLevel->getString().c_str()).asInt();
	nCurLevel->setString(Value(--nowlevel).asString());
	m_turret->degradeTurret();
}

void PlayerTurret::rorateTurret(float angle)
{
	auto rotate = RotateTo::create(0.1, angle);
	m_turret->runAction(rotate);
}

void PlayerTurret::setMaxLevel(int maxlevel)
{
	
	nCurLevel->setString(Value(maxlevel).asString().c_str());
	setnMaxLevel(maxlevel);
}

void PlayerTurret::shoot(float degree){
	auto bullet = BulletManage::getInstance()->createBullet(rand() % 8, 90);
	bullet->setRotation(degree);
	bullet->setPosition(this->getPosition());
	getParent()->addChild(bullet);
	bullet->setPlayerTurret(this);

	//开火动画
	auto aniNode = Sprite::create();
	aniNode->setPosition(m_turret->getContentSize().width/2,m_turret->getContentSize().height*1.2);
	m_turret->addChild(aniNode, 5);
	aniNode->runAction(Sequence::create(AnimationUtil::getInstance()->getAnimate("aniShoot"),RemoveSelf::create(1),nullptr));

	//花费金币
	if (isRobot)
	{
		auto num = Value(nCurLevel->getString()).asInt();
		auto nowNum = Value(m_CoinLabel->getString()).asInt();
		m_CoinLabel->setString(Value(nowNum-num).asString().c_str());
	}
	else
	{
	auto num = Value(nCurLevel->getString()).asInt();
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
	auto walk = m_aiinfo->nextStep(10);
	if (walk.getFire())
	{
		shoot(walk.getAngle());
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
}



void PlayerTurret::initWithDate(User* user,int index)
{
	initWithType(100);
	setUpgradeButton();
	setMaxLevel(100);
	createPlayerCoin(user,index);
	
}
void PlayerTurret::initWithDate(RoomPlayer* user)
{
	initWithType(user->getMaxTurretLevel());
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
		auto num = 100;
		auto nowNum = Value(m_CoinLabel->getString()).asInt();
		m_CoinLabel->setString(Value(nowNum + num).asString().c_str());
	}
	else
	{
		auto num = 100;
		m_CoinLabel->setString(Value(User::getInstance()->addCoins(+num)).asString().c_str());
	}
}