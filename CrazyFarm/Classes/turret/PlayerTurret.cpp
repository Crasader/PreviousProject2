#include "Turret/PlayerTurret.h"

bool PlayerTurret::init(){
	if (!Sprite::initWithSpriteFrameName("gun_under.png")){
		return false;
	}
	return true;
}
void PlayerTurret::setUpgradeButton()
{
	auto upgradeButton = MenuItemImage::create("btn_icon_plus.png", "btn_icon_plus.png", CC_CALLBACK_1(PlayerTurret::upgradeTurret, this));
	upgradeButton->setPosition(this->getContentSize().width*0, this->getContentSize().height*0.2);
	auto degradeButton = MenuItemImage::create("btn_icon_minus.png", "btn_icon_minus.png", CC_CALLBACK_1(PlayerTurret::degradeTurret, this));
	degradeButton->setPosition(this->getContentSize().width*1, this->getContentSize().height*0.2);
	auto menu = Menu::create(upgradeButton, degradeButton, nullptr);
	menu->setPosition(Point::ZERO);
	addChild(menu);
}
void PlayerTurret::initWithType(int type){
	m_turret = Turret::create();
	m_turret->initWithType(type);
	m_turret->setPosition(getContentSize()/2);
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