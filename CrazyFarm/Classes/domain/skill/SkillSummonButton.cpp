#include "SkillSummonButton.h"
#include "domain/bag/BagManager.h"
#include "data/GameData.h"
SkillSummonButton* SkillSummonButton::createSkillSummonButton()
{

	SkillSummonButton* skillButton = new SkillSummonButton();
	if (skillButton && skillButton->init(3, "skillStencil.png", "item_1005.png", "item_1005.png"))
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
void SkillSummonButton::skillClickCallBack(Ref* obj)
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
		if (userdm>price)
		{
			LogEventUseSkill::getInstance()->addUseSkillData(m_skillID, 1,price);
			User::getInstance()->addDiamonds(-price);
		}
		else
		{
			LogEventUseSkill::getInstance()->addUseSkillData(m_skillID, 2, price);
			auto layer = payLayer::createLayer(2);
			layer->setPosition(0, 0);
			Director::getInstance()->getRunningScene()->getChildByTag(888)->addChild(layer);
			return ;
		}
		
	}
	else
	{
		LogEventUseSkill::getInstance()->addUseSkillData(m_skillID, 0, price);
		BagManager::getInstance()->changeItemCount(skillManager::getInstance()->getSkillInfoByID(m_skillID).item_id, -1);
	}
	
	SkillButton::skillClickCallBack(obj);
	skillManager::getInstance()->useSkillSummon();
}

/** 技能冷却完成回调 */
void SkillSummonButton::skillCoolDownCallBack()
{
	SkillButton::skillCoolDownCallBack();

}

