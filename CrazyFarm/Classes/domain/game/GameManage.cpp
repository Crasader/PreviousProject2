#include "domain/game/GameManage.h"
#include "domain/bag/BagManager.h"
#include "core/UpgradeSureDialog.h"
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