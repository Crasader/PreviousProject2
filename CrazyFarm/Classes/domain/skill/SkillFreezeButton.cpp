#include "SkillFreezeButton.h"
#include "domain/bag/BagManager.h"
#include "data/GameData.h"
SkillFreezeButton* SkillFreezeButton::createSkillFreezeButton()
{
	SkillConfigInfo info = ConfigSkill::getInstance()->getskillConfigInfoBySkillId(1);
	SkillFreezeButton* skillButton = new SkillFreezeButton();
	if (skillButton && skillButton->init(1, "skillStencil.png", "item_1003.png", "item_1003.png"))
	{
		skillButton->autorelease();
		return skillButton;
	}
	else
	{
		delete skillButton;
		skillButton = NULL;
	}

	return NULL;
}

/** 技能按钮点击回调 */
void SkillFreezeButton::skillClickCallBack(Ref* obj)
{
	if (GameData::getInstance()->getisOnBankrupt())
	{
		return;
	}
	auto num = skillManager::getInstance()->getSKillNumById(m_skillID);
	auto price = skillManager::getInstance()->getSkillPriceById(m_skillID);
	auto userdm = User::getInstance()->getDiamonds();
	if (num <= 0)
	{
		if (userdm > price)
		{
			LogEventUseSkill::getInstance()->addUseSkillData(m_skillID, 1, price);
			User::getInstance()->addDiamonds(-price);
		}
		else
		{
			LogEventUseSkill::getInstance()->addUseSkillData(m_skillID, 2, price);
			auto layer = payLayer::createLayer(2);
			layer->setPosition(0, 0);
			Director::getInstance()->getRunningScene()->getChildByTag(888)->addChild(layer);
			return;
		}

	}
	else
	{
		LogEventUseSkill::getInstance()->addUseSkillData(m_skillID, 0, price);
		BagManager::getInstance()->changeItemCount(skillManager::getInstance()->getSkillInfoByID(m_skillID).item_id, -1);
	}

	SkillButton::skillClickCallBack(obj);
	skillManager::getInstance()->useSkillFreeze();
}

/** 技能冷却完成回调 */
void SkillFreezeButton::skillCoolDownCallBack()
{
	SkillButton::skillCoolDownCallBack();
	skillManager::getInstance()->useSkillFreezeEnd();
}

