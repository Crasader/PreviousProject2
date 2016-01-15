#include "SkillLockButton.h"
#include "domain/bag/BagManager.h"
SkillLockButton* SkillLockButton::createSkillLockButton()
{
	SkillConfigInfo info = ConfigSkill::getInstance()->getskillConfigInfoBySkillId(4);
	SkillLockButton* skillButton = new SkillLockButton();
	if (skillButton && skillButton->init(info.cd_time, "skillStencil.png", "item_1004.png", "item_1004.png", skillManager::getInstance()->getSKillNumById(info.skill_id)))
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

/** ������ȴ��ɻص� */
void SkillLockButton::skillCoolDownCallBack()
{
	SkillButton::skillCoolDownCallBack();

}

