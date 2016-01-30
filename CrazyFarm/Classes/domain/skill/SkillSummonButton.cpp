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

/** ���ܰ�ť����ص� */
void SkillSummonButton::skillClickCallBack(Ref* obj)
{
	if (JudgeUseSkill())
	{
		SkillButton::skillClickCallBack(obj);
		skillManager::getInstance()->useSkillSummon();
	}
}

/** ������ȴ��ɻص� */
void SkillSummonButton::skillCoolDownCallBack()
{
	SkillButton::skillCoolDownCallBack();

}

