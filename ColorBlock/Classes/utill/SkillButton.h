#ifndef _SKILLBUTTON_H_
#define _SKILLBUTTON_H_
#include "ui/UIButton.h"
#include <cocos2d.h>
USING_NS_CC;

class SkillButton : public ui::Button
{
public:
    SkillButton();
    virtual ~SkillButton();
    static SkillButton* createSkillButton(int skillID,int skillNum);
	int getSkillNum(){ return _skillNum; };
	void ChangeSkillNum(int diff);
private:
	void skillClickCallBack(Ref*psend, cocos2d::ui::Widget::TouchEventType event);
   bool    init(int skillID, int skillNum);
   int _skillID;
   int _skillNum;
   LabelAtlas*skillLabel;
};


#endif
