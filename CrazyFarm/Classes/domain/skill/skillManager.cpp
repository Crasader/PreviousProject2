#include "domain/skill/skillManager.h"
#include "domain/bag/BagManager.h"
#include "fish/FishManage.h"
#include "utill/AnimationUtil.h"
#include "utill/Audio.h"
#include "domain/logevent/LogEventMannger.h"
#include "config/ConfigItem.h"
#include "domain/game/GameManage.h"
skillManager* skillManager::_instance = NULL;

skillManager::skillManager(){
	this->init();
}


void skillManager::init(){
	for (int i = 1; i <= 5; i++)
	{
		map_skill_isUsingnow[i] = false;
	}

}

skillManager* skillManager::getInstance(){
	if (_instance == NULL){
		_instance = new skillManager();
	}
	return _instance;
}

SkillConfigInfo skillManager::getSkillInfoByID(int skillid)
{
	return ConfigSkill::getInstance()->getskillConfigInfoBySkillId(skillid);
}

SkillConfigInfo skillManager::getSkillInfoByitemId(int itemID)
{
	return ConfigSkill::getInstance()->getskillConfigInfoByItemId(itemID);
}

int skillManager::getSKillNumById(int skillid)
{
	auto info = ConfigSkill::getInstance()->getskillConfigInfoBySkillId(skillid);
	return BagManager::getInstance()->getItemNum(info.item_id);
}

void skillManager::useSkillSummon(PlayerTurret*turret)
{

	auto randPos = Vec2(100, 150 + getRand() % 200);


	auto SummonBottle = Sprite::create("SummonBottle.png");
	SummonBottle->setPosition(turret->getPosition());
	GameManage::getInstance()->getGuiLayer()->addChild(SummonBottle, 10);
	SummonBottle->runAction(Sequence::create(Spawn::create(MoveTo::create(1.0f, randPos), RotateBy::create(1.0f, 360), ScaleTo::create(1.0f, 0.5), nullptr), RemoveSelf::create(), nullptr));


	auto aniNode = Sprite::create();
	aniNode->setPosition(randPos);
	GameManage::getInstance()->getGuiLayer()->addChild(aniNode, 10);
	Audio::getInstance()->playSound(SKILLSUMMON);
	aniNode->setScale(2);
	aniNode->runAction(Sequence::create(DelayTime::create(1.0f), Repeat::create(AnimationUtil::getInstance()->getAnimate("aniZhaoHuan"), 2), CallFunc::create([=]{
		auto fish = FishManage::getInstance()->createFishSingle(40 + getRand() % 5);
		fish->setPosition(randPos);
		fish->setMoveAngle(0);
		fish->setScale(0);

		fish->runAction(Sequence::create(ScaleTo::create(0.4, 1), CallFunc::create([=]{fish->move(3); aniNode->removeFromParentAndCleanup(1); }), nullptr));
		fish->setZOrder(fish->getFishZorder());
	}), nullptr));
}
void skillManager::useSkillById(int skillid, PlayerTurret*turret)
{

	switch (skillid)
	{
	case 1:
		useSkillFreeze(turret);
		getButtonByID(skillid)->skillButonUi(getSkillInfoByID(skillid).cd_time);
		break;
	case 2:
		useSkillLock(turret);
		if (turret == GameManage::getInstance()->getGameLayer()->GetMyTurret())
		{
			getButtonByID(skillid)->skillButonUi(getSkillInfoByID(skillid).cd_time);
			getButtonByID(5)->skillButonUi(getSkillInfoByID(skillid).cd_time);
		}

		break;
	case 3:
		useSkillSummon(turret);
		if (turret == GameManage::getInstance()->getGameLayer()->GetMyTurret())
		{
			getButtonByID(skillid)->skillButonUi(getSkillInfoByID(skillid).cd_time);
		}
		break;
	case 5:
		useSkillLight();
		if (turret == GameManage::getInstance()->getGameLayer()->GetMyTurret())
		{
			getButtonByID(skillid)->skillButonUi(getSkillInfoByID(skillid).cd_time);
			getButtonByID(2)->skillButonUi(getSkillInfoByID(skillid).cd_time);
		}
		break;
	case 4:
		useSkillBoom(turret);
		if (turret == GameManage::getInstance()->getGameLayer()->GetMyTurret())
		{
			getButtonByID(skillid)->skillButonUi(getSkillInfoByID(skillid).cd_time);
		}
		break;
	default:
		break;
	}
}

void skillManager::useSkillFreeze(PlayerTurret*turret)
{
	if (GameData::getInstance()->getIsOnMaridTask())
	{
		return;
	}
	if (map_skill_isUsingnow[1])
	{
		return;
	}
	map_skill_isUsingnow[1] = true;
	Audio::getInstance()->playSound(SKILLFREEZE);
	auto fishes = FishManage::getInstance()->getAllFishInPool();
	for (auto fish : fishes)
	{
		fish->onFreeze();
	}
	GameManage::getInstance()->getGameLayer()->useFreeze(turret);

	getButtonByID(1)->runAction(Sequence::create(DelayTime::create(getSkillInfoByID(1).cd_time), CallFunc::create([=]{useSkillFreezeEnd(turret); }), nullptr));

}

void skillManager::useSkillFreezeEnd(PlayerTurret*turret)
{
	map_skill_isUsingnow[1] = false;
	auto fishes = FishManage::getInstance()->getAllFishInPool();
	for (auto fish : fishes)
	{
		fish->onFreezeResume();
	}
	GameManage::getInstance()->getGameLayer()->onFreezeEnd(turret);
}

void skillManager::useSkillLock(PlayerTurret*turret)
{
	if (turret == GameManage::getInstance()->getGameLayer()->GetMyTurret())
	{
		if (map_skill_isUsingnow[2])
		{
			return;
		}
		map_skill_isUsingnow[2] = true;
		GameManage::getInstance()->getGameLayer()->beginLock();

		getButtonByID(2)->runAction(Sequence::create(DelayTime::create(getSkillInfoByID(2).cd_time), CallFunc::create([=]{useSkillLockEnd(turret); }), nullptr));
	}
	else
	{
		if (turret->getfireType()==Fire_Lock)
		{
			return;
		}
		turret->beginLockShoot();
		turret->runAction(Sequence::create(DelayTime::create(getSkillInfoByID(2).cd_time), CallFunc::create([=]{useSkillLockEnd(turret); }), nullptr));
	}
	
}
void skillManager::useSkillLockEnd(PlayerTurret*turret)
{
	if (turret == GameManage::getInstance()->getGameLayer()->GetMyTurret())
	{
		map_skill_isUsingnow[2] = false;
		GameManage::getInstance()->getGameLayer()->endLock();
	}
	else
	{
		turret->endLockShoot();
	}

}

void skillManager::useSkillBoom(PlayerTurret*turret)
{
	if (GameData::getInstance()->getIsOnMaridTask())
	{
		return;
	}
	Audio::getInstance()->playSound(SKILLBOOM);
	if (turret == GameManage::getInstance()->getGameLayer()->GetMyTurret())
	{
		GameManage::getInstance()->getGameLayer()->beginSkillBoom();
	}
	else
	{
		Vec2 pos = Vec2(480 + rand() % 400 - 200, 270 + rand() % 200 - 100);
		GameManage::getInstance()->getGameLayer()->doBoom(pos, turret, true);
	}
}


void skillManager::useSkillLight()
{
	if (map_skill_isUsingnow[5])
	{
		return;
	}
	map_skill_isUsingnow[5] = true;
	GameManage::getInstance()->getGameLayer()->beginLight();

	getButtonByID(5)->runAction(Sequence::create(DelayTime::create(getSkillInfoByID(5).cd_time), CallFunc::create([=]{useSkillLightEnd(); }), nullptr));
}
void skillManager::useSkillLightEnd()
{
	map_skill_isUsingnow[5] = false;
	GameManage::getInstance()->getGameLayer()->endLight();
}


int skillManager::getSkillPriceById(int skillid)
{
	auto info = ConfigSkill::getInstance()->getskillConfigInfoBySkillId(skillid);
	return ConfigItem::getInstance()->getItemById(info.item_id).buyPrice;
}

int skillManager::isSatisfyBuySkill(int skillid) //返回值1：VIP等级不够 2：炮塔等级不够 0: 满足
{
	auto info = ConfigSkill::getInstance()->getskillConfigInfoBySkillId(skillid);
	auto maxlv = User::getInstance()->getMaxTurrentLevel();
	auto viplv = User::getInstance()->getVipLevel();
	if (info.unlock_buy_vipLv > viplv)
	{
		return 1;
	}
	if (info.unlock_buy_turretLv > maxlv)
	{
		return 2;
	}
	return 0;
}

int skillManager::isSatisfyBuySkillInBag(int skillid) //返回值1：VIP等级不够 2：炮塔等级不够 0: 满足
{
	auto info = ConfigSkill::getInstance()->getskillConfigInfoBySkillId(skillid);
	auto maxlv = User::getInstance()->getMaxTurrentLevel();
	auto viplv = User::getInstance()->getVipLevel();
	if (info.unlock_buy_vipLv > viplv)
	{
		return 1;
	}
	if (300 > maxlv)
	{
		return 2;
	}
	return 0;
}