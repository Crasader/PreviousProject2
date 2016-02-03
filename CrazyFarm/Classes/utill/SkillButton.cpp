#include "SkillButton.h"
#include "domain/bag/BagManager.h"
#include "domain/skill/skillManager.h"
#include "domain/logevent/LogEventUseSkill.h"
#include "data/GameData.h"
#include "domain/logevent/LogEventPageChange.h"
USING_NS_CC;

SkillButton::SkillButton() :
mItemSkill(NULL),
mMenuSkill(NULL),
mStencil(NULL),
mProgressTimer(NULL)
{

}

SkillButton::~SkillButton()
{

}

SkillButton* SkillButton::createSkillButton(int skillID, const char* stencil_file_name, const char* button_normal_name, const char* button_click_name)
{
    SkillButton* skillButton = new SkillButton();
	if (skillButton && skillButton->init(skillID, stencil_file_name, button_normal_name, button_click_name))
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

bool SkillButton::init(int skillID, const char* stencil_file_name, const char* button_normal_name, const char* button_click_name)
{
    CCAssert(stencil_file_name, "SkillButton::init stencil_file_name != NULL");
    CCAssert(button_normal_name, "SkillButton::init button_normal_name != NULL");
    CCAssert(button_click_name, "SkillButton::init button_click_name != NULL");

    // Notice:���childʱҪע�����²�
    // ���·���CCMenuItemImage �����ģ��ͼƬ ���Ϸ���CCProgressTimer

    // ��Ӽ��ܰ�ť
    mItemSkill = MenuItemImage::create(button_normal_name, button_click_name, this, menu_selector(SkillButton::skillClickCallBack));
	mItemSkill->setPosition(Point::ZERO);

    mMenuSkill = Menu::create(mItemSkill, NULL);
	mMenuSkill->setPosition(Point::ZERO);
    addChild(mMenuSkill, -100);

    // �����Ӱģ��
    mStencil = Sprite::create(stencil_file_name);
    mStencil->setPosition(Point::ZERO);
    mStencil->setVisible(false);
	addChild(mStencil);	
	
	

    // �����ת����������
    Sprite* progressSprite = Sprite::create(button_normal_name);
    mProgressTimer = ProgressTimer::create(progressSprite);
    mProgressTimer->setPosition(Point::ZERO);
    mProgressTimer->setVisible(false);
    addChild(mProgressTimer, 100);

	auto labelPropNum = LabelAtlas::create("0", "bagPropNum.png", 18, 26, '0');
	labelPropNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	labelPropNum->setPosition(17, 25);
	addChild(labelPropNum,101,50);

	auto labelPriceNum = LabelAtlas::create("0", "nowPoolNum.png", 13, 21, '0');
	labelPriceNum->setPosition(20, -35);
	labelPriceNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	addChild(labelPriceNum, 101, 51);
	
	auto sp = Sprite::create("smallDiamond.png");
	sp->setPosition(-30, -30);
	addChild(sp, 101, 52);
	
	
	m_skillID = skillID;
	mCDTime = skillManager::getInstance()->getSkillInfoByID(skillID).cd_time;
	scheduleUpdate();
    return true;
}

void SkillButton::update(float dt)
{
	auto PropNum = skillManager::getInstance()->getSKillNumById(m_skillID);
	auto price = skillManager::getInstance()->getSkillPriceById(m_skillID);
	if (PropNum > 0)
	{
		getChildByTag(50)->setVisible(true);
		getChildByTag(51)->setVisible(false);
		getChildByTag(52)->setVisible(false);
		((LabelAtlas*)getChildByTag(50))->setString(Value(PropNum).asString().c_str());
	}
	else
	{
		getChildByTag(50)->setVisible(false);
		getChildByTag(51)->setVisible(true);
		getChildByTag(52)->setVisible(true);
		((LabelAtlas*)getChildByTag(51))->setString(Value(price).asString().c_str());
	}


	


}
bool SkillButton::JudgeUseSkill()
{
	if (GameData::getInstance()->getisOnBankrupt())
	{
		return false;
	}
	if (skillManager::getInstance()->getIsUseSkillNow())
	{
		return false;
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
			//todo:���ܶ���ȷ��
			return true;
		}
		else
		{
			LogEventUseSkill::getInstance()->addUseSkillData(m_skillID, 2, 0);
			LogEventPageChange::getInstance()->addEventItems(2, m_skillID-1, 13);
			auto layer = payLayer::createLayer(2);
			layer->setPosition(0, 0);
			layer->setEventPont(m_skillID + 12);
			Director::getInstance()->getRunningScene()->getChildByTag(888)->addChild(layer);
			return false;
		}

	}
	else
	{
		LogEventUseSkill::getInstance()->addUseSkillData(m_skillID, 0, 0);
		BagManager::getInstance()->changeItemCount(skillManager::getInstance()->getSkillInfoByID(m_skillID).item_id, -1);
		return true;
	}
}


/** ���ܰ�ť����ص� */
void SkillButton::skillClickCallBack(Ref* obj)
{
	skillManager::getInstance()->setIsUseSkillNow(true);
    // ��ȴ��ʱ����ʱ״̬���ܰ�ť���ɵ��
    mItemSkill->setEnabled(false);

    // ģ��ɼ�
    mStencil->setVisible(true);

    // ���þ��������Ϊ˳ʱ��
    mProgressTimer->setVisible(true);
	mProgressTimer->setType(ProgressTimer::Type::RADIAL);
	mProgressTimer->stopAllActions();
    //׼��һ��5����ת360�ȵĶ���(�𽥸��ǰ�͸ģ���γ���ȴЧ��;������м�ʱ��ȴ������ʵ�ֺ�ʱ�����)
	ActionInterval* action_progress_to = Sequence::create(ProgressTo::create(mCDTime, 100), ProgressTo::create(0, 0),nullptr);
	auto action_callback = CallFunc::create(CC_CALLBACK_0(SkillButton::skillCoolDownCallBack, this));
	mProgressTimer->runAction(Sequence::create(action_progress_to,action_callback, NULL));
}

/** ������ȴ��ɻص� */
void SkillButton::skillCoolDownCallBack()
{
	skillManager::getInstance()->setIsUseSkillNow(false);
    // �����ɰ岻�ɼ�
    mStencil->setVisible(false);

    // ���������ܲ��ɼ�
    mProgressTimer->setVisible(false);

    // ��ť��Ϊ����
    mItemSkill->setEnabled(true);
}

