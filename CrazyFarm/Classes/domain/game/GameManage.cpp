#include "domain/game/GameManage.h"
#include "domain/bag/BagManager.h"
#include "core/UpgradeSureDialog.h"
#include "utill/CShake.h"
#include "config/ConfigChest.h"
GameManage* GameManage::_instance = 0;

GameManage* GameManage::getInstance(){
	if (_instance == 0){
		_instance = new GameManage();
	}
	return _instance;
}

GameManage::GameManage(){

}
void GameManage::showLockTurrent()
{
	m_pGuilayer->showLockUpdataTurret();
}

void  GameManage::CatchTheFishOntheTurrent(Fish*fish, bool isDead, PlayerTurret* turret)
{
	if (turret==nullptr)
	{
		turret = m_pGameyer->GetMyTurret();
	}
	auto targetfish = turret->getLockFish();
	if (fish == targetfish)
	{
		turret->setLockFish(nullptr);
	}
	targetfish = turret->getLightFish();
	if (fish == targetfish)
	{
		turret->setLightFish(nullptr);
	}
	FishManage::getInstance()->getAllFishInPool().eraseObject(fish);
	if (isDead)
	{

		if (fish->getFishType() == GoldFish)
		{
			//»Æ½ðÓã²¶»ñ¶¯»­
			m_pGuilayer->runAction(CCShake::create(0.2, 10));
			auto aninode = Node::create();
			aninode->setPosition(0, 0);
			turret->addChild(aninode, 1, "goldfichCatch");


			auto sp = Sprite::create("goldFishCatchTable.png");
			sp->setPosition(Vec2(80, 180));
			aninode->addChild(sp);
			sp->runAction(RepeatForever::create(RotateBy::create(2, 360)));
			sp->setScale(0.7);

			auto num = fish->getFishGold()* turret->getTurrentMupltData().multiple*ConfigChest::getInstance()->getChestByLevel(User::getInstance()->getUserBoxLevel()).catch_per;
			auto lb = LabelAtlas::create(Value(Value(num).asInt()).asString(), "coinNum.png", 32, 48, '0');
			lb->setAnchorPoint(Point::ANCHOR_MIDDLE);
			lb->setPosition(Vec2(80, 180));
			lb->setRotation(-30);
			lb->runAction(RepeatForever::create(Sequence::create(RotateTo::create(0.5f, 30), RotateTo::create(0.5f, -30), nullptr)));
			aninode->addChild(lb);


			auto txtframe = Sprite::create("goldFishCatch.png");
			txtframe->setPosition(Vec2(80, 130));
			aninode->addChild(txtframe);
			auto str = String::createWithFormat("TXTGoldFish_%d.png", fish->getuiId());
			auto txt = Sprite::create(str->getCString());
			txt->setPosition(txtframe->getContentSize() / 2);
			txtframe->addChild(txt);
			txtframe->setScale(0.7);

			aninode->runAction(Sequence::create(DelayTime::create(3.0f), RemoveSelf::create(1), nullptr));
		}



		LogEventFish::getInstance()->addFishCatchTimes(fish->getFishID());
		switch (fish->getFishType())
		{
		case BoomFish:
			FishManage::getInstance()->onBoomFishDead(fish, turret);
			break;
		case AllKilledFish:
			FishManage::getInstance()->onAllKilledFishDead(fish, turret);
			break;
		default:
			break;
		}
		turret->getCoinByFish(fish);
		auto data = GameData::getInstance();
		if (data->getIsOnMaridTask())
		{
			auto vec = data->getmermaidTask()->getMermaidTaskOnlineInfo().mermaidTaskItems;
			for (auto var : vec)
			{
				if (fish->getFishID() == var.fishId&&!turret->isRobot)
				{
					data->getmermaidTask()->addOneCatchFishById(fish->getFishID());
					break;
				}
			}
		}
		fish->onDead();
	}
	else
	{
		fish->removeself();
	}
	fish = nullptr;

}

void GameManage::onPlayerUpgrade()
{
	Audio::getInstance()->playSound("UPDATALEVEL");
	auto aninode = Sprite::create();
	aninode->setPosition(480, 270);
	m_pGuilayer->addChild(aninode,10);
	aninode->setScale(2);
	aninode->runAction(Sequence::create(Repeat::create(AnimationUtil::getInstance()->getAnimate("aniShengji"), 10), RemoveSelf::create(), nullptr));	
	
	
	auto rewards = ConfigExp::getInstance()->getLevelRewardItemsByLevelId(User::getInstance()->getLevelData().levelId);

	auto node = UpgradeSureDialog::create(rewards);
	node->setPosition(0, 0);
	m_pGuilayer->addChild(node, 20);
}