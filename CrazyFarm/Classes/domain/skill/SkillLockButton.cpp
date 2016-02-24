#include "SkillLockButton.h"
#include "domain/bag/BagManager.h"
#include "data/GameData.h"
SkillLockButton* SkillLockButton::createSkillLockButton()
{
	SkillLockButton* skillButton = new SkillLockButton();
	if (skillButton && skillButton->init(2,"skillStencil.png", "item_1004.png", "item_1004.png"))
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
void SkillLockButton::skillClickCallBack(Ref* obj)
{
	auto nd = getChildByName("tipnode");
	if (nd)
	{
		nd->removeFromParentAndCleanup(1);
	}
	//if (JudgeUseSkill())
	//{
	//	SkillButton::skillClickCallBack(obj);
	//	skillManager::getInstance()->useSkillLock();
	//}
	useSkill();
}

/** 技能冷却完成回调 */
void SkillLockButton::skillCoolDownCallBack()
{
	SkillButton::skillCoolDownCallBack();
	skillManager::getInstance()->useSkillLockEnd();

}

