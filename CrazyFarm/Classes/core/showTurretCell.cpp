#include "showTurretCell.h"
#include "utill/Chinese.h"
#include "config/ConfigTurrent.h"
#include "User.h"
#include "lobby/shop/payLayer.h"
bool showTurretCell::init(){

	bg = Sprite::create();
	bg->setPosition(88, 121.5);
	bg->setContentSize(Size(176, 243));
	addChild(bg);
	auto size = bg->getContentSize();

	propSprite = Sprite::create();
	propSprite->setPosition(size / 2);
	addChild(propSprite);

	ShowPaoshade = Sprite::create("ShowPaoshade.png");
	ShowPaoshade->setPosition(size/2);
	addChild(ShowPaoshade);
	ShowPaoshade->setVisible(false);

	
	
	muptleTTF = LabelAtlas::create("0", "unLockNumTTF.png", 13, 19, '0');
	muptleTTF->setAnchorPoint(Point::ANCHOR_MIDDLE);
	muptleTTF->setPosition(size.width*0.55, size.height*0.9);
	addChild(muptleTTF);
	muptleTTF->setVisible(false);

	

	button = MenuItemImage::create();
	button->setContentSize(Size(161, 74));
	button->setPosition(size.width / 2, size.height*0.18);
	button->setCallback(CC_CALLBACK_1(showTurretCell::ButtonCallback,this));
	auto diamondNumTTF = LabelAtlas::create("0", "unLockNumTTF.png", 13, 19, '0');
	diamondNumTTF->setPosition(Point::ANCHOR_MIDDLE);
	diamondNumTTF->setPosition(button->getContentSize()/2);
	diamondNumTTF->setVisible(false);
	button->addChild(diamondNumTTF,1,10);

	auto menu = Menu::create(button, nullptr);
	menu->setPosition(0, 0);
	addChild(menu);
	lockSp = Sprite::create("smalllock.png");
	lockSp->setAnchorPoint(Point::ANCHOR_MIDDLE);
	lockSp->setPosition(160,243);
	addChild(lockSp);
	lockSp->setVisible(true);

	showVipPaoName = Sprite::create();
	showVipPaoName->setPosition(size.width / 2, size.height*0.95);
	addChild(showVipPaoName);
	showVipPaoName->setVisible(false);

	return true;
}



void showTurretCell::setMultipleValue(int index)
{
	m_type = 2;
	ShowPaoshade->setVisible(true);
	bg->setTexture("ShowPaobg.png");
	auto maxlevl = User::getInstance()->getMaxTurrentLevel();
	auto nextTurret = ConfigTurrent::getInstance()->getNextTurrent(maxlevl);
	auto turret = ConfigTurrent::getInstance()->getTurrentByIndex(index);
	muptleTTF->setString(Value(turret.multiple).asString().c_str());
	muptleTTF->setVisible(true);
	button->setNormalSpriteFrame(SpriteFrame::create("btn_big_1.png",Rect(0,0,161,74)));
	button->setSelectedSpriteFrame(SpriteFrame::create("btn_big_2.png", Rect(0, 0, 161, 74)));
	auto diamondNumTTF = (LabelAtlas*)button->getChildByTag(10);
	diamondNumTTF->setVisible(true);
	diamondNumTTF->setString(Value(turret.unlockPrice).asString().c_str());

	if (nextTurret.turrentId == turret.turrentId)
	{
		ShowPaoshade->setVisible(false);
	}

	if (turret.multiple>30)
	{
		propSprite->setTexture("pao_2.png");
	}
	else
	{
		propSprite->setTexture("pao_1.png");
	}
}
void showTurretCell::setVippaoValue(int index)
{
	m_type = 1;
	auto viplv = User::getInstance()->getVipLevel();
	bg->setTexture("VIPFrame.png");
	
	showVipPaoName->setVisible(true);
	auto path = String::createWithFormat("VIPname_%d.png", index);
	showVipPaoName->setTexture(path->getCString());

	button->setNormalSpriteFrame(SpriteFrame::create("btn_huoqu_1.png", Rect(0, 0, 161, 74)));
	button->setSelectedSpriteFrame(SpriteFrame::create("btn_huoqu_2.png", Rect(0, 0, 161, 74)));
	if (index==(++viplv))
	{
		ShowPaoshade->setVisible(false);
	}
	path = String::createWithFormat("pao_%d.png", index+2);
	propSprite->setTexture(path->getCString());
}


void showTurretCell::IsBeToued()
{

}

void showTurretCell::ButtonCallback(Ref* psend)
{

	if (m_type == 1)
	{
		///VIP³äÖµ	
	}
	else
	{
		auto layer = payLayer::createLayer(2);
		layer->setPosition(0, 0);
		Director::getInstance()->getRunningScene()->getChildByTag(888)->addChild(layer);
		Director::getInstance()->getRunningScene()->getChildByTag(888)->getChildByTag(50)->removeFromParentAndCleanup(1);
	}

}