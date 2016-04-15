#include "ReloginDialog.h"
#include "utill/AnimationUtil.h"
#include "utill/FunUtil.h"
#include "domain/login/LoginScene.h"
#include "utill/Audio.h"
ReloginDialog* ReloginDialog::createDialog(const char* tipStr)
{
	ReloginDialog* ref = new ReloginDialog();
	if (ref&&ref->init(tipStr))
	{
		ref->autorelease();
	}
	else
	{
		ref = nullptr;
	}
	return ref;
}

void ReloginDialog::reloginCB(Ref*psend)
{
	Audio::getInstance()->playSound(CLICKSURE);
	Director::getInstance()->replaceScene(LoginScene::createScene());

}
bool ReloginDialog::init(const  char* tipStr)
{
	Layer::init();
	bool bRet = false;
	do
	{

		auto colorLayer = LayerColor::create();
		colorLayer->setColor(ccc3(0, 0, 0));
		colorLayer->setOpacity(180);
		colorLayer->setPosition(0, 0);
		addChild(colorLayer, -1);
		auto bg = Sprite::create("TwiceSureDialog.png");
		bg->setPosition(480, 270);
		addChild(bg, 1,"bg");

		
		auto sure = MenuItemImage::create("btn_queding.png", "btn_queding_2.png", CC_CALLBACK_1(ReloginDialog::reloginCB,this));
		sure->setPosition(bg->getContentSize().width / 2, 48);
		
		auto menu = Menu::create(sure, nullptr);
		menu->setPosition(0,0);
		bg->addChild(menu);


		auto label = LabelTTF::create(tipStr, "arial", 20);
		label->setColor(Color3B(12, 64, 109));
		label->setAnchorPoint(Point::ANCHOR_MIDDLE);
		label->setDimensions(Size(261, 0));
		label->setPosition(bg->getContentSize().width / 2, 165);
			bg->addChild(label);

		auto listenr1 = EventListenerTouchOneByOne::create();
		listenr1->onTouchBegan = CC_CALLBACK_2(ReloginDialog::onTouchBegan, this);
		listenr1->setSwallowTouches(true);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenr1, this);

	
		/////////µ¯³ö¶¯»­
		bg->setScale(0);
		bg->runAction(Sequence::create(ScaleTo::create(0.2f, 1.0f), ScaleTo::create(0.07f, 0.8f), ScaleTo::create(0.07f, 1.0f), nullptr));
		showRandonBubbleAni();
		bRet = true;
	} while (0);


	return bRet;
}


void ReloginDialog::showRandonBubbleAni()
{
	auto node = getChildByName("bg");

	auto aniNode = Sprite::create();
	aniNode->setPosition(20,100);
	node->addChild(aniNode, 5);
	aniNode->runAction(getForeverAcByNameAndInterval("aniBubble",0));

	aniNode = Sprite::create();
	aniNode->setPosition(node->getContentSize().width-20, 100);
	node->addChild(aniNode, 5);
	runAction(Sequence::create(DelayTime::create(0.1f), CallFunc::create([=]{aniNode->runAction(getForeverAcByNameAndInterval("aniBubble", 0)); }), nullptr));
	
}