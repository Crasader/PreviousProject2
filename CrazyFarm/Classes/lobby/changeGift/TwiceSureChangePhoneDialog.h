#pragma once
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "utill/Chinese.h"
#include "widget/MyDialog.h"
USING_NS_CC_EXT;
USING_NS_CC;





class TwiceSureChangePhoneDialog : public MyDialog, public cocos2d::ui::EditBoxDelegate
{
public:

	virtual bool init();

	CREATE_FUNC(TwiceSureChangePhoneDialog);

private:
	bool onTouchBegan(Touch *touch, Event *unused_event);
	void quedingcallback(Ref*);
	ui::EditBox *_editPhone;
	ui::EditBox *_editRepeatPhone;
	void closeButtonCallBack(Ref*psend);
	virtual void editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox);
	virtual void editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox);
	virtual void editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text);
	virtual void editBoxReturn(cocos2d::ui::EditBox* editBox);
};
