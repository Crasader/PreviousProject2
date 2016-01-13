#include "domain/skill/skillManager.h"
#include "BagManager.h"
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


void skillManager::useSkillFreeze()
{
	auto fishes = FishManage::getInstance()->getAllFishInPool();
	for (auto fish:fishes)
	{
		fish->pause();
		m_gamelayer->unscheduleUpdate();
	}
}
void skillManager::useSkillSummon()
{
	auto fish = FishManage::getInstance()->createFishSingle(40 + rand() % 5);
	fish->setPosition(Vec2(800, 600));
	fish->runAction(MoveTo::create(10.0f, Vec2(-100, -100)));
	m_gamelayer->addChild(fish);
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