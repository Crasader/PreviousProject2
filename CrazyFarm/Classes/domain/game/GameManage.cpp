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
	m_pGuilayer->showLockUpgradeTurret();
}

void GameManage::showGainMoneyTurrent()
{
	m_pGuilayer->showGainMoneyTurrent();
}



void  GameManage::CatchTheFishOntheTurrent(Fish*fish, bool isDead, PlayerTurret* turret)
{
	if (fish->getTargeLightTurret())
	{
		fish->getTargeLightTurret()->setLightFish(nullptr);
	}
	if (fish->getTargeLockTurret())
	{
		fish->getTargeLockTurret()->setLockFish(nullptr);
	}
	FishManage::getInstance()->getAllFishInPool().eraseObject(fish);
	if (isDead)
	{

		if (fish->getFishType() == GoldFish)
		{
			
			//黄金鱼捕获动画
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
		{
			FishManage::getInstance()->onBoomFishDead(fish, turret);
			auto aninode = Sprite::create();
			aninode->setPosition(fish->getPosition());
			aninode->setScale(2);
			aninode->runAction(Sequence::create(AnimationUtil::getInstance()->getAnimate("aniTXTBoom"), RemoveSelf::create(1), nullptr));
			m_pGameyer->addChild(aninode, 1);
		}
			
			break;
		case AllKilledFish:
			FishManage::getInstance()->onAllKilledFishDead(fish, turret);
			break;
		default:
			break;
		}
		turret->getCoinByFish(fish);
		//如果是自己捕获到
		if (!turret->isRobot&&fish->getFishType()==GoldFish)
		{
			showGainMoneyTurrent();
		}
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
	auto rewards = ConfigExp::getInstance()->getLevelRewardItemsByLevelId(User::getInstance()->getLevelData().levelId);
	Audio::getInstance()->playSound("UPDATALEVEL");
	auto colorlayer = LayerColor::create();
	colorlayer->setColor(ccc3(0, 0, 0));
	colorlayer->setOpacity(180);
	m_pGuilayer->addChild(colorlayer, 20);
	auto aninode = Sprite::create();
	aninode->setPosition(480, 270);
	m_pGuilayer->addChild(aninode, 20);
	aninode->setScale(2);
	auto txt = Sprite::create("TXTUpGrade.png");
	txt->setPosition(480, 350);
	m_pGuilayer->addChild(txt, 20);

	aninode->runAction(Sequence::create(Repeat::create(AnimationUtil::getInstance()->getAnimate("aniShengji"), 2), CallFunc::create([=]{txt->removeFromParentAndCleanup(1); auto node = UpgradeSureDialog::create(rewards);
	node->setPosition(0, 0);
	m_pGuilayer->addChild(node, 20); colorlayer->removeFromParentAndCleanup(1); }), RemoveSelf::create(), nullptr));
	
	
	

	
}