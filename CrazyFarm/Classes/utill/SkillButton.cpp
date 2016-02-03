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

    // Notice:添加child时要注意上下层
    // 最下方是CCMenuItemImage 其次是模版图片 最上方是CCProgressTimer

    // 添加技能按钮
    mItemSkill = MenuItemImage::create(button_normal_name, button_click_name, this, menu_selector(SkillButton::skillClickCallBack));
	mItemSkill->setPosition(Point::ZERO);

    mMenuSkill = Menu::create(mItemSkill, NULL);
	mMenuSkill->setPosition(Point::ZERO);
    addChild(mMenuSkill, -100);

    // 添加阴影模版
    mStencil = Sprite::create(stencil_file_name);
    mStencil->setPosition(Point::ZERO);
    mStencil->setVisible(false);
	addChild(mStencil);	
	
	

    // 添加旋转进度条精灵
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
			//todo:技能二次确认
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


/** 技能按钮点击回调 */
void SkillButton::skillClickCallBack(Ref* obj)
{
	skillManager::getInstance()->setIsUseSkillNow(true);
    // 冷却计时，即时状态技能按钮不可点击
    mItemSkill->setEnabled(false);

    // 模版可见
    mStencil->setVisible(true);

    // 设置精灵进度条为顺时针
    mProgressTimer->setVisible(true);
	mProgressTimer->setType(ProgressTimer::Type::RADIAL);
	mProgressTimer->stopAllActions();
    //准备一个5秒旋转360度的动画(逐渐覆盖半透模板形成冷却效果;这里进行计时冷却动画的实现和时间控制)
	ActionInterval* action_progress_to = Sequence::create(ProgressTo::create(mCDTime, 100), ProgressTo::create(0, 0),nullptr);
	auto action_callback = CallFunc::create(CC_CALLBACK_0(SkillButton::skillCoolDownCallBack, this));
	mProgressTimer->runAction(Sequence::create(action_progress_to,action_callback, NULL));
}

/** 技能冷却完成回调 */
void SkillButton::skillCoolDownCallBack()
{
	skillManager::getInstance()->setIsUseSkillNow(false);
    // 设置蒙板不可见
    mStencil->setVisible(false);

    // 进度条技能不可见
    mProgressTimer->setVisible(false);

    // 按钮置为可用
    mItemSkill->setEnabled(true);
}

