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
	for (int i = 1; i <= 5;i++)
	{
		map_skill_isUsingnow[i] = false;
	}
	
}

skillManager* skillManager::getInstance(){
    if(_instance == NULL){
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
	Audio::getInstance()->playSound(SKILLSUMMON);
	auto randPos = Vec2(100, 150 + rand() % 200);


	auto SummonBottle = Sprite::create("SummonBottle.png");
	SummonBottle->setPosition(turret->getPosition());
	m_gamelayer->addChild(SummonBottle, 5);
	SummonBottle->runAction(Spawn::create(MoveTo::create(1.0f, randPos), RotateBy::create(1.0f, 360),RemoveSelf::create(), nullptr));


	auto aniNode = Sprite::create();
	aniNode->setPosition(randPos);
	m_gamelayer->addChild(aniNode, 10);
	aniNode->runAction(Sequence::create(DelayTime::create(1.0f),Repeat::create(AnimationUtil::getInstance()->getAnimate("aniZhaoHuan"), 2), CallFunc::create([=]{
	auto fish = FishManage::getInstance()->createFishSingle(40 + rand() % 5);
	fish->setPosition(randPos);
	fish->setMoveAngle(0);
	fish->setScale(0);
	fish->runAction(Sequence::create(ScaleTo::create(0.4, 1), CallFunc::create([=]{fish->move(3); aniNode->removeFromParentAndCleanup(1); }), nullptr));
	m_gamelayer->addChild(fish,5); 
	}),nullptr));
}
void skillManager::useSkillById(int skillid, PlayerTurret*turret)
{
	switch (skillid)
	{
	case 1:
		useSkillFreeze(turret);
		break;
	case 2:
		useSkillLock();
		break;
	case 3:
		useSkillSummon(turret);
		break;
	case 5:
		useSkillLight();
		break;
	case 4:
		useSkillBoom();
		break;
	default:
		break;
	}
}
void skillManager::robotUseSkillFreeze(PlayerTurret*turret)
{
	useSkillFreeze(turret);
}
void skillManager::useSkillFreeze(PlayerTurret*turret)
{
	if (map_skill_isUsingnow[1])
	{
		return;
	}
	map_skill_isUsingnow[1] = true;
	Audio::getInstance()->playSound(SKILLFREEZE);
	auto fishes = FishManage::getInstance()->getAllFishInPool();
	for (auto fish : fishes)
	{
		fish->pause();
	}
	m_gamelayer->useFreeze(turret);

	GameManage::getInstance()->getGuiLayer()->runAction(Sequence::create(DelayTime::create(getSkillInfoByID(1).cd_time), CallFunc::create([=]{useSkillFreezeEnd(turret); }), nullptr));

}

void skillManager::useSkillFreezeEnd(PlayerTurret*turret)
{
	map_skill_isUsingnow[1] = false;
	auto fishes = FishManage::getInstance()->getAllFishInPool();
	for (auto fish : fishes)
	{
		fish->resume();
	}
	m_gamelayer->onFreezeEnd(turret);
}

void skillManager::useSkillLock()
{
	if (map_skill_isUsingnow[2])
	{
		return;
	}
	map_skill_isUsingnow[2] = true;
	m_gamelayer->beginLock();
}
void skillManager::useSkillLockEnd()
{
	map_skill_isUsingnow[2] = false;
	m_gamelayer->endLock();
}

void skillManager::useSkillBoom()
{
	Audio::getInstance()->playSound(SKILLBOOM);
	m_gamelayer->beginSkillBoom();
}


void skillManager::useSkillLight()
{
	if (map_skill_isUsingnow[5])
	{
		return;
	}
	map_skill_isUsingnow[5] = true;
	m_gamelayer->beginLight();
}
void skillManager::useSkillLightEnd()
{
	map_skill_isUsingnow[5] = false;
	m_gamelayer->endLight();
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
	if (info.unlock_buy_vipLv >viplv)
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
	if (300> maxlv)
	{
		return 2;
	}
	return 0;
}