#include "maridTaskPlane.h"
#include "fish/Fish.h"
#include "data/GameData.h"
#include "domain/coinBox/CoinBox.h"
#include "domain/bag/BagManager.h"
#include "core/GameGuiLayer.h"
#include "domain/logevent/LogEventMermaid.h"
#include "domain/game/GameManage.h"


bool maridTaskPlane::init()
{
	if (!Sprite::initWithFile("taskFrame.png"))
	{
		return false;
	}
	bool bRet = false;
	do
	{  
		auto size = getContentSize();
		auto info = GameData::getInstance()->getmermaidTask()->getMermaidTaskOnlineInfo();
		for (int i = 0; i < info.mermaidTaskItems.size();i++)
		{
			auto var = info.mermaidTaskItems[i];
			auto sp = Fish::create();
			sp->initFish(var.fishId);
			sp->unscheduleUpdate();
			sp->setPosition(size.width*0.53, 32+33*(2-i));
			addChild(sp);
			sp->setScaleX(65.0 / sp->getContentSize().width);
			sp->setScaleY(43.0 / sp->getContentSize().height);
			auto label = LabelAtlas::create(Value(var.current_num).asString(), "taskNum.png", 16, 22, '0');
			label->setPosition(size.width*0.77, 32+33*(2-i));
			label->setAnchorPoint(Point::ANCHOR_MIDDLE);
			addChild(label);
			label->setTag(var.fishId);
			scheduleUpdate();
		}
		
		
		bRet = true;
	} while (0);


	return bRet;
}


void maridTaskPlane::update(float delta)
{
	nNowtime += delta;
	auto info = GameData::getInstance()->getmermaidTask()->getMermaidTaskOnlineInfo().mermaidTaskItems;
	auto isSuccess = GameData::getInstance()->getmermaidTask()->isSuccess();
	for (auto var : info)
	{
		auto label = (LabelAtlas*)getChildByTag(var.fishId);
		label->setString(Value(var.current_num).asString().c_str());
	}
	if (isSuccess)//���
	{
		LogEventMermaid::getInstance()->addDataToSend(GameData::getInstance()->getRoomID(), nNowtime, GameData::getInstance()->getmermaidTask()->getMermaidTaskOnlineInfo().coins);
		CoinBox::getInstance()->addCoinBox(GameData::getInstance()->getmermaidTask()->getMermaidTaskOnlineInfo().coins);
		GameManage::getInstance()->getGameLayer()->onGetReward(1008, 1);
		((GameGuiLayer*)getParent())->beginMaridTaskTime();
		auto sp = Sprite::create("TXTFinished.png");
		sp->setPosition(480, 270);
		auto nameLabel = LabelTTF::create(User::getInstance()->getUserName(), "arial", 20);
		nameLabel->setPosition(192, 71);
		nameLabel->setAnchorPoint(Point::ANCHOR_MIDDLE);
		sp->addChild(nameLabel);
		getParent()->addChild(sp, 10);
		sp->runAction(Sequence::create(DelayTime::create(1.0f), RemoveSelf::create(1), nullptr));
		removeFromParentAndCleanup(1);
		return;
	}
	if (nNowtime>GameData::getInstance()->getmermaidTask()->getMermaidTaskConfigInfo().continue_time)//δ���
	{	
		LogEventMermaid::getInstance()->addDataToSend(GameData::getInstance()->getRoomID(), 0, GameData::getInstance()->getmermaidTask()->getMermaidTaskOnlineInfo().coins);
		((GameGuiLayer*)getParent())->beginMaridTaskTime();
		auto sp = Sprite::create("TXTNoFinished.png");
		sp->setPosition(480, 270);
		getParent()->addChild(sp, 10);
		sp->runAction(Sequence::create(DelayTime::create(1.0f), RemoveSelf::create(1), nullptr));

		removeFromParentAndCleanup(1);
		return;
	}
	
}