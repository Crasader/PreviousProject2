#include "domain/skill/skillManager.h"
#include "domain/bag/BagManager.h"
#include "fish/FishManage.h"
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
	auto fish = FishManage::getInstance()->createFishSingle(40 + rand() % 5);
	fish->setPosition(Vec2(-100, 150+rand()%200));
	fish->setMoveAngle(0);
	fish->move(3);
	m_gamelayer->addChild(fish);
}

void skillManager::useSkillFreeze()
{
	auto fishes = FishManage::getInstance()->getAllFishInPool();
	for (auto fish:fishes)
	{
		fish->pause();
		m_gamelayer->unscheduleUpdate();
	}
}

void skillManager::useSkillFreezeEnd()
{
	auto fishes = FishManage::getInstance()->getAllFishInPool();
	for (auto fish : fishes)
	{
		fish->resume();
		m_gamelayer->scheduleUpdate();
	}
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
	m_gamelayer->beginSkillBoom();
}
