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

/** ���ܰ�ť����ص� */
void SkillLockButton::skillClickCallBack(Ref* obj)
{
	if (JudgeUseSkill())
	{
		SkillButton::skillClickCallBack(obj);
		skillManager::getInstance()->useSkillLock();
	}
}

/** ������ȴ��ɻص� */
void SkillLockButton::skillCoolDownCallBack()
{
	SkillButton::skillCoolDownCallBack();
	skillManager::getInstance()->useSkillLockEnd();

}

