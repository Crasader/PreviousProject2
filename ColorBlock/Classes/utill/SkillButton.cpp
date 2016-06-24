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
	auto path = String::createWithFormat("skill_%d.png", _skillID);
	initWithNormalImage(path->getCString(), path->getCString(), "", CC_CALLBACK_1(SkillButton::skillClickCallBack,this));
  
	auto circle = Sprite::create("circle.png");
	circle->setPosition(getContentSize());
	addChild(circle);

	std::string num = _skillNum >= 10 ? ":" : Value(_skillNum).asString().c_str();
	skillLabel = LabelAtlas::create(num, "cornerNum.png", 11, 14, '0');
	skillLabel->setPosition(circle->getContentSize() / 2);
	skillLabel->setAnchorPoint(Point::ANCHOR_MIDDLE);
	circle->addChild(skillLabel);

    

    return true;
}


void SkillButton::skillClickCallBack(Ref*psend)
{
	EventCustom event(MSG_USESKILL);
	SkillInfo*skilli = new SkillInfo();
	skilli->Id = ((SkillType)_skillID);
	skilli->num = _skillNum;
	event.setUserData(skilli);
	Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
	CC_SAFE_DELETE(skilli);
}
void SkillButton::ChangeSkillNum(int diff)
{
	_skillNum += diff;
	skillLabel->setString(Value(_skillNum).asString());
}