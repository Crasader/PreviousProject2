#include "SkillSummonButton.h"
#include "BagManager.h"
SkillSummonButton* SkillSummonButton::createSkillSummonButton()
{
	SkillConfigInfo info = ConfigSkill::getInstance()->getskillConfigInfoBySkillId(3);
	SkillSummonButton* skillButton = new SkillSummonButton();
	if (skillButton && skillButton->init(info.cd_time, "skillStencil.png", "item_1005.png", "item_1005.png", skillManager::getInstance()->getSKillNumById(info.skill_id)))
	{
		skillButton->setScale(0.7);
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
	if (mPropNum<=0)
	{
		return ;
	}
	mPropNum--;
	BagManager::getInstance()->changeItemCount(3, mPropNum);
	refreshPropNumLabel();
	SkillButton::skillClickCallBack(obj);
	skillManager::getInstance()->useSkillSummon();
}

/** 技能冷却完成回调 */
void SkillSummonButton::skillCoolDownCallBack()
{
	SkillButton::skillCoolDownCallBack();

}

