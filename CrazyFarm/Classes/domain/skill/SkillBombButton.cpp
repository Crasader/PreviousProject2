#include "SkillBombButton.h"
#include "domain/bag/BagManager.h"
SkillBombButton* SkillBombButton::createSkillBombButton()
{
	SkillConfigInfo info = ConfigSkill::getInstance()->getskillConfigInfoBySkillId(6);
	SkillBombButton* skillButton = new SkillBombButton();
	if (skillButton && skillButton->init(info.cd_time, "skillStencil.png", "item_1006.png", "item_1006.png", skillManager::getInstance()->getSKillNumById(info.skill_id)))
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
void SkillBombButton::skillClickCallBack(Ref* obj)
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
void SkillBombButton::skillCoolDownCallBack()
{
	SkillButton::skillCoolDownCallBack();

}

