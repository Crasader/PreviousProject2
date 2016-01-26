#include "SkillBombButton.h"
#include "domain/bag/BagManager.h"
#include "data/GameData.h"
SkillBombButton* SkillBombButton::createSkillBombButton()
{
	SkillConfigInfo info = ConfigSkill::getInstance()->getskillConfigInfoBySkillId(4);
	SkillBombButton* skillButton = new SkillBombButton();
	if (skillButton && skillButton->init(4, "skillStencil.png", "item_1006.png", "item_1006.png"))
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
void SkillBombButton::skillClickCallBack(Ref* obj)
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
		if (userdm > price)
		{
			LogEventUseSkill::getInstance()->addUseSkillData(m_skillID, 1, price);
			User::getInstance()->addDiamonds(-price);
		}
		else
		{
			LogEventUseSkill::getInstance()->addUseSkillData(m_skillID, 2, price);
			auto layer = payLayer::createLayer(2);
			layer->setPosition(0, 0);
			Director::getInstance()->getRunningScene()->getChildByTag(888)->addChild(layer);
			return;
		}

	}
	else
	{
		LogEventUseSkill::getInstance()->addUseSkillData(m_skillID, 0, price);
		BagManager::getInstance()->changeItemCount(skillManager::getInstance()->getSkillInfoByID(m_skillID).item_id, -1);
	}


	SkillButton::skillClickCallBack(obj);
	skillManager::getInstance()->useSkillBoom();
}

/** ������ȴ��ɻص� */
void SkillBombButton::skillCoolDownCallBack()
{
	SkillButton::skillCoolDownCallBack();

}

