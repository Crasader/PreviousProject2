#include "Turret/PlayerTurret.h"
#include "bullet/BulletManage.h"
bool PlayerTurret::init(){
	if (!Sprite::initWithFile("turretBg.png")){
		return false;
	}
	auto levelBg = Sprite::create("multipleBg.png");
	levelBg->setPosition(getContentSize().width / 2, levelBg->getContentSize().height / 2);
	addChild(levelBg,10);
	nMaxLevel = LabelAtlas::create("0", "multipleNum.png", 15, 21, '0');
	nMaxLevel->setAnchorPoint(Point::ANCHOR_MIDDLE);
	nMaxLevel->setPosition(levelBg->getContentSize() / 2);
	levelBg->addChild(nMaxLevel);
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
	m_turret->upgradeTurret();
}
void PlayerTurret::degradeTurret(Ref* psend)
{
	m_turret->degradeTurret();
}

void PlayerTurret::rorateTurret(float angle)
{
	auto rotate = RotateTo::create(0.1, angle);
	m_turret->runAction(rotate);
}

void PlayerTurret::setMaxLevel(int maxlevel)
{
	nMaxLevel->setString(Value(maxlevel).asString().c_str());
	setnMaxLevel(maxlevel);
}

void PlayerTurret::shoot(float degree){
	//添加一颗子弹用于测试
	auto bullet = BulletManage::getInstance()->createBullet(rand() % 8, 90);
	bullet->setRotation(degree);
	bullet->setPosition(this->getPosition());
	getParent()->addChild(bullet);
}

void PlayerTurret::setAIinfo(AI info)
{
	/*unschedule(schedule_selector(doAIthing));*/
	m_aiinfo = info;
	schedule(schedule_selector(PlayerTurret::doAIthing), info.getReqSteps() , CC_REPEAT_FOREVER, 0);
}

void PlayerTurret::doAIthing(float dt)
{
	auto walk = m_aiinfo.nextStep(10);
	if (walk.getFire())
	{
		shoot(walk.getAngle());
	}
}