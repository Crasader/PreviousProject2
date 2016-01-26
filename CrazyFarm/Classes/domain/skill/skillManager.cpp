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

int skillManager::getSKillNumById(int skillid)
{
	auto info = ConfigSkill::getInstance()->getskillConfigInfoBySkillId(skillid);
	return BagManager::getInstance()->getItemNum(info.item_id);
}

void skillManager::useSkillSummon()
{
	Audio::getInstance()->playSound(SKILLSUMMON);
	auto randPos = Vec2(100, 150 + rand() % 200);


	///TODO::¶¯»­ÈÓ³öÈ¥
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
	
}
void skillManager::useSkillLightEnd()
{
	
}


int skillManager::getSkillPriceById(int skillid)
{
	auto info = ConfigSkill::getInstance()->getskillConfigInfoBySkillId(skillid);
	return ConfigItem::getInstance()->getItemById(info.item_id).buyPrice;
}