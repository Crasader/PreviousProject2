#include "payCell.h"

bool PayCell::init(){
	if (!Sprite::initWithFile("payframe.png")){
		return false;
	}
	auto size = getContentSize();
	paySprite = Sprite::create();
	paySprite->setPosition(size.width *0.2, size.height / 2);
	addChild(paySprite);

	propNum = Sprite::create();
	propNum->setPosition(size.width*0.7, size.height*0.8);
	addChild(propNum);

	giftNum = Sprite::create();
	giftNum->setPosition(size.width*0.7, size.height*0.25);
	addChild(giftNum);

	return true;
}

void PayCell::setValue(int goodId)
{
	auto spPath = String::createWithFormat("coin_%d.png", goodId);
	paySprite->setTexture(spPath->getCString());
	spPath = String::createWithFormat("coinPropNum_%d.png", goodId);
	propNum->setTexture(spPath->getCString());
	spPath = String::createWithFormat("coinGiftNum_%d.png", goodId);
	giftNum->setTexture(spPath->getCString());
}


void PayCell::setDiamondValue(int goodId)
{
	auto spPath = String::createWithFormat("diamond_%d.png", goodId);
	paySprite->setTexture(spPath->getCString());
	spPath = String::createWithFormat("diamondPropNum_%d.png", goodId);
	propNum->setTexture(spPath->getCString());
	spPath = String::createWithFormat("diamondGiftNum_%d.png", goodId);
	giftNum->setTexture(spPath->getCString());
}


void PayCell::IsBeToued()
{
	///TODO:道具被点击时候的回调;
	CCLOG("propIDl: %d is be touched", m_nCellId);
}