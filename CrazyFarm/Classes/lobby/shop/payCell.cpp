#include "payCell.h"
#include "domain/user/User.h"
#include "lobby/LobbyScene.h"
#include "core/GameLayer.h"
#include "server/HttpMannger.h"
#include "lobby/Nobility/NobilityLayer.h"
#include "domain/user/DeviceInfo.h"
#include "domain/logevent/LogEventPageChange.h"
#include "domain/game/GameManage.h"
#include "lobby/shop/payLayer.h"
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
	
	hotTxt = Sprite::create("hottxt.png");
	hotTxt->setAnchorPoint(Point::ZERO);
	hotTxt->setPosition(0, size.height*0.5);
	addChild(hotTxt);
	hotTxt->setVisible(false);

	return true;
}
Good coingood[7] = { Good(18, 180000), Good(38, 380000), Good(108, 1080000), Good(388, 3880000), Good(688, 6880000) , Good(8, 40000), Good(58, 580000)};
Good diamondGood[5] = { Good(18, 180), Good(38, 418), Good(58, 650), Good(108, 1346), Good(388, 4768) };
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
	if (goodId ==4)
	{
		hotTxt->setVisible(true);
	}
}

void PayCell::setVipValue()
{
	m_PayType = 3;
	paySprite->setTexture("payVip.png");
	propNum->setTexture("payVipNum.png");
	giftNum->setTexture("payVipGift.png");
}


void PayCell::IsBeToued()
{
	auto level =  ConfigVipLevel::getInstance()->getVipLevel(User::getInstance()->getVipLevel());
	switch (m_PayType)
	{
	case 1:
	{
		payData data;
		data.channel_id = 10000;
		data.order_id = 0;
		data.pay_event_id = 1000;
		data.pay_point_id = 1000;
		data.pay_event_vesion = 10001000;
		data.pay_result = 0;
		data.pay_type = 0;
		auto sessionid = User::getInstance()->getSessionid();
		HttpMannger::getInstance()->HttpToPostRequestBeforePay(sessionid, 100100, 1, 1, DeviceInfo::getChange_id());
		User::getInstance()->addCoins(coingood[m_nGoodId - 1].count*level.pay_reward);
		User::getInstance()->addChargeMoney(coingood[m_nGoodId - 1].RMB);
	}
		break;
	case 2:
		User::getInstance()->addDiamonds(diamondGood[m_nGoodId - 1].count*level.pay_reward);
		User::getInstance()->addChargeMoney(diamondGood[m_nGoodId - 1].RMB);
		break;
	case 3:
	{
		auto layer = NobilityLayer::createLayer();
		layer->setPosition(0, 0);
		auto scene = Director::getInstance()->getRunningScene();
		auto node = scene->getChildByTag(888);
		if (node)
		{
			node->addChild(layer,21);
			if ((GameGuiLayer*)node == GameManage::getInstance()->getGuiLayer())
			{
				LogEventPageChange::getInstance()->addEventItems(2, 8, 0);
			}
			else
			{
				auto node = (payView*)getParent();
				int shoptype = node->getShopType();
				if (shoptype ==1)
				{
					LogEventPageChange::getInstance()->addEventItems(12, 8, 0);
				}
				else if (shoptype ==2)
				{
					LogEventPageChange::getInstance()->addEventItems(13, 8, 0);
				}
			}
		}
		break;
	}
	default:
		break;
	}
	auto scene = Director::getInstance()->getRunningScene();
	auto node = scene->getChildByTag(777);
	if (node)
	{
		((GameLayer*)node)->RefreShmyPlayerTurret();
	}


}