#include "SkillButton.h"
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

	std::string num = _skillNum >= 10 ? ":" : Value(num).asString().c_str();
	auto label = LabelAtlas::create(num, "cornerNum.png", 11, 14, '0');
	label->setPosition(circle->getContentSize() / 2);
	label->setAnchorPoint(Point::ANCHOR_MIDDLE);
	circle->addChild(label);

    

    return true;
}


void SkillButton::skillClickCallBack(Ref*psend)
{

}
