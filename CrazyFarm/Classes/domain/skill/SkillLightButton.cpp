#include "SkillLightButton.h"
#include "domain/bag/BagManager.h"
SkillLightButton* SkillLightButton::createSkillLightButton()
{
	SkillConfigInfo info = ConfigSkill::getInstance()->getskillConfigInfoBySkillId(5);
	SkillLightButton* skillButton = new SkillLightButton();
	if (skillButton && skillButton->init(info.cd_time, "skillStencil.png", "item_1007.png", "item_1007.png", skillManager::getInstance()->getSKillNumById(info.skill_id)))
	{
		skillButton->itemID = 1007;
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
void SkillLightButton::skillClickCallBack(Ref* obj)
{
	if (mPropNum<=0)
	{
		return ;
	}
	mPropNum--;
	BagManager::getInstance()->changeItemCount(5, mPropNum);
	refreshPropNumLabel();
	SkillButton::skillClickCallBack(obj);
	skillManager::getInstance()->useSkillSummon();
}

/** ������ȴ��ɻص� */
void SkillLightButton::skillCoolDownCallBack()
{
	SkillButton::skillCoolDownCallBack();

}

