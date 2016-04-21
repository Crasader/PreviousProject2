#pragma once
#include "cocos2d.h"
#include "utill/Chinese.h"
#include "ui/CocosGUI.h"
#include "widget/BaseLayer.h"

USING_NS_CC;





class RedPackChangeCDkey : public BaseLayer, public cocos2d::ui::EditBoxDelegate
{
public:

    virtual bool init();

	CREATE_FUNC(RedPackChangeCDkey);

private:
	bool onTouchBegan(Touch *touch, Event *unused_event);
	void quedingcallback(Ref*);
	void closeButtonCallBack(Ref*psend);
	bool checkTheName(const char* name);
	CC_SYNTHESIZE(int, m_eventPoint, EventPoint);



	ui::EditBox *_editRepeatword;
	virtual void editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox);
	virtual void editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox);
	virtual void editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text);
	virtual void editBoxReturn(cocos2d::ui::EditBox* editBox);
};
