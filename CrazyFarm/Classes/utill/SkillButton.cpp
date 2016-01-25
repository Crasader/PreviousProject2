#include "SkillButton.h"
#include "domain/bag/BagManager.h"

USING_NS_CC;

SkillButton::SkillButton() :
mItemSkill(NULL),
mMenuSkill(NULL),
mStencil(NULL),
mProgressTimer(NULL),
mCDTime(1.f),
mPropNum(0)
{

}

SkillButton::~SkillButton()
{

}

SkillButton* SkillButton::createSkillButton(float cdTime, const char* stencil_file_name, const char* button_normal_name, const char* button_click_name,int propNum)
{
    SkillButton* skillButton = new SkillButton();
	if (skillButton && skillButton->init(cdTime, stencil_file_name, button_normal_name, button_click_name, propNum))
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

bool SkillButton::init(float cdTime, const char* stencil_file_name, const char* button_normal_name, const char* button_click_name, int propNum)
{
    CCAssert(stencil_file_name, "SkillButton::init stencil_file_name != NULL");
    CCAssert(button_normal_name, "SkillButton::init button_normal_name != NULL");
    CCAssert(button_click_name, "SkillButton::init button_click_name != NULL");

    // Notice:���childʱҪע�����²�
    // ���·���CCMenuItemImage �����ģ��ͼƬ ���Ϸ���CCProgressTimer

    // ��Ӽ��ܰ�ť
	mPropNum = propNum;
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

	auto labelPropNum = LabelAtlas::create(Value(mPropNum).asString().c_str(), "prop_num.png", 19, 23, '0');
	labelPropNum->setPosition(12, 12);
	addChild(labelPropNum,101,50);

	

    mCDTime = cdTime;
    return true;
}

void SkillButton::refreshPropNumLabel()
{
	mPropNum = BagManager::getInstance()->getItemNum(itemID);
	((LabelAtlas*)getChildByTag(50))->setString(Value(mPropNum).asString().c_str());
}

/** ���ܰ�ť����ص� */
void SkillButton::skillClickCallBack(Ref* obj)
{
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
    // �����ɰ岻�ɼ�
    mStencil->setVisible(false);

    // ���������ܲ��ɼ�
    mProgressTimer->setVisible(false);

    // ��ť��Ϊ����
    mItemSkill->setEnabled(true);
}

