#include "domain/skill/skillManager.h"
#include "domain/bag/BagManager.h"
#include "fish/FishManage.h"
#include "utill/AnimationUtil.h"
#include "utill/Audio.h"
#include "domain/logevent/LogEventMannger.h"
#include "config/ConfigItem.h"
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

void skillManager::useSkillSummon()
{
	Audio::getInstance()->playSound(SKILLSUMMON);
	auto randPos = Vec2(100, 150 + rand() % 200);


	///TODO::动画扔出去
	auto aniNode = Sprite::create();
	aniNode->setPosition(randPos);
	m_gamelayer->addChild(aniNode, 10);
	aniNode->runAction(Sequence::create(Repeat::create(AnimationUtil::getInstance()->getAnimate("aniZhaoHuan"), 2), CallFunc::create([=]{
	auto fish = FishManage::getInstance()->createFishSingle(40 + rand() % 5);
	fish->setPosition(randPos);
	fish->setMoveAngle(0);
	fish->setScale(0);
	fish->runAction(Sequence::create(ScaleTo::create(0.4, 1), CallFunc::create([=]{fish->move(3); aniNode->removeFromParentAndCleanup(1); }), nullptr));
	m_gamelayer->addChild(fish); 
	}),nullptr));
}

void skillManager::useSkillFreeze()
{
	Audio::getInstance()->playSound(SKILLFREEZE);
	auto fishes = FishManage::getInstance()->getAllFishInPool();
	for (auto fish:fishes)
	{
		fish->pause();
		fish->ShadePause();
	}
	m_gamelayer->onFreezeBegin();
}

void skillManager::useSkillFreezeEnd()
{
	auto fishes = FishManage::getInstance()->getAllFishInPool();
	for (auto fish : fishes)
	{
		fish->resume();
		fish->ShadeResume();
	}
	m_gamelayer->onFreezeEnd();
}

void skillManager::useSkillLock()
{
	m_gamelayer->beginLock();
}
void skillManager::useSkillLockEnd()
{
	m_gamelayer->endLock();
}

void skillManager::useSkillBoom()
{
	Audio::getInstance()->playSound(SKILLBOOM);
	m_gamelayer->beginSkillBoom();
}


void skillManager::useSkillLight()
{
	m_gamelayer->beginLight();
}
void skillManager::useSkillLightEnd()
{
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
	if (info.unlock_buy_turretLv < maxlv)
	{
		return 2;
	}
	return 0;
}