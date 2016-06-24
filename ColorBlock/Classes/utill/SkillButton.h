#ifndef _SKILLBUTTON_H_
#define _SKILLBUTTON_H_
#include <cocos2d.h>
USING_NS_CC;

class SkillButton : public MenuItemImage
{
public:
    SkillButton();
    virtual ~SkillButton();
    static SkillButton* createSkillButton(int skillID,int skillNum);
	int getSkillNum(){ return _skillNum; };
	void ChangeSkillNum(int diff);
private:
	void skillClickCallBack(Ref*psend);
   bool    init(int skillID, int skillNum);
   int _skillID;
   int _skillNum;
   LabelAtlas*skillLabel;
};


#endif
