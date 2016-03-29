#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "lobby/bag/SexHead.h"
USING_NS_CC;




class RegisterDialog : public cocos2d::Layer, public cocos2d::ui::EditBoxDelegate
{

private:
	void loginCallBack(Ref*psend);
	void btCallBack(Ref*psend);
    virtual bool init();
	CREATE_FUNC(RegisterDialog);
	void update(float delta);
	SexHead* sexBoy;
	SexHead* sexGirl;
	//edit box
	ui::EditBox *_editNickname;
	ui::EditBox *_editPassword;
	ui::EditBox *_editRepeatword;
	virtual void editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox);
	virtual void editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox);
	virtual void editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text);
	virtual void editBoxReturn(cocos2d::ui::EditBox* editBox);
};
