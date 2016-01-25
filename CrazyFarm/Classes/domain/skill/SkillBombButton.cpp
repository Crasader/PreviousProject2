#include "SkillBombButton.h"
#include "domain/bag/BagManager.h"
SkillBombButton* SkillBombButton::createSkillBombButton()
{
	SkillConfigInfo info = ConfigSkill::getInstance()->getskillConfigInfoBySkillId(4);
	SkillBombButton* skillButton = new SkillBombButton();
	if (skillButton && skillButton->init(info.cd_time, "skillStencil.png", "item_1006.png", "item_1006.png", skillManager::getInstance()->getSKillNumById(info.skill_id)))
	{
		skillButton->itemID = 1006;
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
void SkillBombButton::skillClickCallBack(Ref* obj)
{
	if (mPropNum<=0)
	{
		return ;
	}
	mPropNum--;
	BagManager::getInstance()->changeItemCount(4, mPropNum);
	refreshPropNumLabel();
	SkillButton::skillClickCallBack(obj);
	skillManager::getInstance()->useSkillBoom();
}

/** ������ȴ��ɻص� */
void SkillBombButton::skillCoolDownCallBack()
{
	SkillButton::skillCoolDownCallBack();

}

