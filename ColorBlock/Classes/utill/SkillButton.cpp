#include "SkillButton.h"
#include "MsgDefine.h"
USING_NS_CC;

SkillButton::SkillButton() 
{

}

SkillButton::~SkillButton()
{

}

SkillButton* SkillButton::createSkillButton(int skillID, int skillNum)
{
    SkillButton* skillButton = new SkillButton();
	if (skillButton && skillButton->init(skillID, skillNum))
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

bool SkillButton::init(int skillID, int skillNum)
{
	_skillID = skillID;
	_skillNum = skillNum;
	auto path = String::createWithFormat("skill_%d.png", _skillID-80);
	if (!Sprite::initWithSpriteFrameName(path->getCString()))
	{
		return false;
	}
	//addTouchEventListener(CC_CALLBACK_2(SkillButton::skillClickCallBack, this));
	
	auto circle = Sprite::create("circle.png");
	circle->setPosition(getContentSize() + Size(-10, -10));
	addChild(circle);

	std::string num = _skillNum >= 10 ? ":" : Value(_skillNum).asString().c_str();
	skillLabel = LabelAtlas::create(num, "cornerNum.png", 11, 14, '0');
	skillLabel->setPosition(circle->getContentSize() / 2);
	skillLabel->setAnchorPoint(Point::ANCHOR_MIDDLE);
	circle->addChild(skillLabel);

	auto box = Sprite::createWithSpriteFrameName("skillFrame.png");
	box->setPosition(getContentSize() / 2);
	addChild(box, -1);
    

    return true;
}


void SkillButton::skillClickCallBack(Ref*psend, cocos2d::ui::Widget::TouchEventType event)
{
	EventCustom _event(MSG_USESKILL);
	SkillInfo*skilli = new SkillInfo();
	skilli->Id = ((SkillType)_skillID);
	skilli->num = _skillNum;
	_event.setUserData(skilli);
	Director::getInstance()->getEventDispatcher()->dispatchEvent(&_event);
	CC_SAFE_DELETE(skilli);
}
void SkillButton::ChangeSkillNum(int diff)
{
	_skillNum += diff;
	std::string num = _skillNum >= 10 ? ":" : Value(_skillNum).asString().c_str();
	skillLabel->setString(num);
}