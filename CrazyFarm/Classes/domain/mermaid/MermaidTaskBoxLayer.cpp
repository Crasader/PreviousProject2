#include "MermaidTaskBoxLayer.h"
#include "utill/AnimationUtil.h"
#include "domain/game/GameManage.h"
bool MermaidTaskBoxLayer::init()
{
	bool bRet = false;
	do 
	{
		colorlayer = LayerColor::create();
		colorlayer->setColor(ccc3(0, 0, 0));
		colorlayer->setOpacity(180);
		addChild(colorlayer, -1);

		box = Sprite::create("game/ui/ani/firstBox/firstBox_1.png");
		box->setPosition(480, 254);
		addChild(box);
		box->setRotation(-0.3);
		auto ac = Sequence::create(RotateTo::create(0.05, 3), RotateTo::create(0.05, -3), RotateTo::create(0.05, 3), RotateTo::create(0.05, -3), RotateTo::create(0.025, 0), DelayTime::create(0.5f), nullptr);
		box->runAction(RepeatForever::create(ac));

		sLight = Sprite::create("rorateLightCoin.png");
		sLight->setScale(2.6);
		sLight->setOpacity(153);
		sLight->setPosition(box->getContentSize() / 2);
		sLight->runAction(RepeatForever::create(RotateBy::create(7.0f, 360)));
		box->addChild(sLight,-1);

		tipTxt = Sprite::create("TXTGetMermaidBox.png");
		tipTxt->setPosition(box->getContentSize().width/2, -60);
		box->addChild(tipTxt);
	

		listenr1 = EventListenerTouchOneByOne::create();
		listenr1->onTouchBegan = CC_CALLBACK_2(MermaidTaskBoxLayer::onTouchBegan, this);
		listenr1->setSwallowTouches(true);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenr1, this);


		auto aninode = Sprite::create();
		aninode->setPosition(480, 270);
		aninode->setScale(4);
		aninode->setName("aninode");
		addChild(aninode);
		aninode->runAction(Sequence::create(RepeatForever::create(AnimationUtil::getInstance()->getAnimate("aniShengji")),nullptr));
		bRet = true;
	} while (0);
	return bRet;
}
bool MermaidTaskBoxLayer::onTouchBegan(Touch *pTouch, Event *pEvent)
{
	if (istouched)
	{
		return true;
	}
	istouched = true;
	getChildByName("aninode")->removeFromParentAndCleanup(1);
	tipTxt->removeFromParentAndCleanup(1);
	box->stopAllActions();
	box->setRotation(0);
	sLight->removeFromParentAndCleanup(1);
	sLight = Sprite::create("light_2.png");
	sLight->setPosition(box->getContentSize() / 2);
	box->addChild(sLight);
	sLight->runAction(Sequence::create(Spawn::create(ScaleBy::create(2.0f, 5), FadeOut::create(2.0f), nullptr), CallFunc::create([=]{box->setVisible(false); }), RemoveSelf::create(), nullptr));
	box->runAction(Sequence::create(AnimationUtil::getInstance()->getAnimate("anifirstBox"), CallFunc::create([&]
	{
		auto coinnode = Sprite::create();
		coinnode->setPosition(0, 0);
		addChild(coinnode);
		coinnode->runAction(Sequence::create(AnimationUtil::getInstance()->getAnimate("aniCoinFly"), CallFunc::create([=]
		{
			colorlayer->removeFromParentAndCleanup(1);
			auto node = Node::create();
			node->setAnchorPoint(Point::ANCHOR_MIDDLE);
			node->setPosition(480,270);
			GameManage::getInstance()->getGuiLayer()->addChild(node,getZOrder()+1);
			auto belongPos = node->convertToNodeSpace(GameManage::getInstance()->getGameLayer()->GetMyTurret()->getPosition());
			Sprite*sp;
			for (int i = 0; i < 10; i++)
			{
				float diffX = 30;
				float diffY = 20;
				float orgY = 50;
				sp = Sprite::create();
				int perLine = 10/ 2;
				sp->setPosition(diffX*(i % perLine), orgY + diffY*(i / perLine));
				sp->runAction(RepeatForever::create(AnimationUtil::getInstance()->getAnimate("aniGold")));
				sp->runAction(Sequence::create(DelayTime::create(0.1f*i), MoveBy::create(0.23f, Vec2(0, 86)), MoveBy::create(0.13f, Vec2(0, -86)), MoveBy::create(0.1f, Vec2(0, 27.5)), MoveBy::create(0.1f, Vec2(0, -27.5)), DelayTime::create(0.6f), MoveTo::create(0.16f, belongPos), CallFunc::create([=]{Audio::getInstance()->playSound(GETCOIN); }), RemoveSelf::create(1), nullptr));
				node->addChild(sp);
			}
			runAction(Sequence::create(DelayTime::create(10 * 0.1f + 1.5f), CallFunc::create([=]{User::getInstance()->addCoins(_coins); }),RemoveSelf::create(), nullptr));


		}), nullptr));
		
	}
	), nullptr));
	
	return true;
}