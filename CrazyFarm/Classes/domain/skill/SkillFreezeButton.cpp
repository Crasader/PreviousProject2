#include "SkillFreezeButton.h"
#include "domain/bag/BagManager.h"
SkillFreezeButton* SkillFreezeButton::createSkillFreezeButton()
{
	SkillConfigInfo info = ConfigSkill::getInstance()->getskillConfigInfoBySkillId(1);
	SkillFreezeButton* skillButton = new SkillFreezeButton();
	if (skillButton && skillButton->init(info.cd_time, "skillStencil.png", "item_1003.png", "item_1003.png", skillManager::getInstance()->getSKillNumById(info.skill_id)))
	{
		skillButton->itemID = 1003;
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
void SkillFreezeButton::skillClickCallBack(Ref* obj)
{
	if (mPropNum<=0)
	{
		return ;
	}
	mPropNum--;
	BagManager::getInstance()->changeItemCount(1, mPropNum);
	refreshPropNumLabel();
	SkillButton::skillClickCallBack(obj);
	skillManager::getInstance()->useSkillFreeze();
}

/** ������ȴ��ɻص� */
void SkillFreezeButton::skillCoolDownCallBack()
{
	SkillButton::skillCoolDownCallBack();
	skillManager::getInstance()->useSkillFreezeEnd();
}

