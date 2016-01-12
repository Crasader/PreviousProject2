#include "payCell.h"
#include "User.h"
#include "lobby/LobbyScene.h"
bool PayCell::init(){
	if (!Sprite::initWithFile("payframe.png")){
		return false;
	}
	auto size = getContentSize();
	paySprite = Sprite::create();
	paySprite->setPosition(size.width *0.21, size.height / 2);
	addChild(paySprite);

	propNum = Sprite::create();
	propNum->setPosition(size.width*0.68, size.height*0.76);
	addChild(propNum);

	giftNum = Sprite::create();
	giftNum->setPosition(size.width*0.68, size.height*0.30);
	addChild(giftNum);

	return true;
}

void PayCell::setValue(int goodId)
{
	setgoodID(goodId);
	m_PayType = 1;
	auto spPath = String::createWithFormat("coin_%d.png", goodId);
	paySprite->setTexture(spPath->getCString());
	spPath = String::createWithFormat("coinPropNum_%d.png", goodId);
	propNum->setTexture(spPath->getCString());
	spPath = String::createWithFormat("coinGiftNum_%d.png", goodId);
	giftNum->setTexture(spPath->getCString());
}


void PayCell::setDiamondValue(int goodId)
{
	setgoodID(goodId);
	m_PayType = 2;
	auto spPath = String::createWithFormat("diamond_%d.png", goodId);
	paySprite->setTexture(spPath->getCString());
	spPath = String::createWithFormat("diamondPropNum_%d.png", goodId);
	propNum->setTexture(spPath->getCString());
	spPath = String::createWithFormat("diamondGiftNum_%d.png", goodId);
	giftNum->setTexture(spPath->getCString());
}

void PayCell::setVipValue()
{
	m_PayType = 3;
	paySprite->setTexture("payVip.png");
	propNum->setTexture("payVipNum.png");
	giftNum->setTexture("payVipGift.png");
}

Good coingood[7] = {Good(8, 40000), Good(18, 90000), Good(38, 1900000), Good(58, 290000), Good(108, 540000), Good(388, 1940000), Good(688, 3440000) };
Good diamondGood[5] = { Good(18, 180), Good(38, 380), Good(58, 580), Good(108, 1080), Good(388, 3880) };
void PayCell::IsBeToued()
{
	auto level =  ConfigVipLevel::getInstance()->getVipLevel(User::getInstance()->getVipLevel());
	switch (m_PayType)
	{
	case 1:
		User::getInstance()->addCoins(coingood[m_nGoodId - 1].count*level.pay_reward);
		User::getInstance()->addChargeMoney(coingood[m_nGoodId - 1].RMB);
		break;
	case 2:
		User::getInstance()->addDiamonds(diamondGood[m_nGoodId - 1].count*level.pay_reward);
		User::getInstance()->addChargeMoney(diamondGood[m_nGoodId - 1].RMB);
		break;
	case 3:

		break;
	default:
		break;
	}
	auto node = Director::getInstance()->getRunningScene()->getChildByTag(888);
	((LobbyScene*)node)->refreshCoinLabel();
	
}