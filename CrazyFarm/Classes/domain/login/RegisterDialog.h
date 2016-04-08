#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "lobby/bag/SexHead.h"
USING_NS_CC;




class RegisterDialog : public cocos2d::Layer, public cocos2d::ui::EditBoxDelegate
{
public:
	CREATE_FUNC(RegisterDialog);
private:
	void loginCallBack(Ref*psend);
	void closeCallBack(Ref*psend);
	int checkRegister(std::string nickname, std::string password, std::string repetPassword);
    virtual bool init();
	bool onTouchBegan(Touch *touch, Event *unused_event);
	SexHead* sexBoy;
	SexHead* sexGirl;
	int sex;
	//edit box
	ui::EditBox *_editNickname;
	ui::EditBox *_editPassword;
	ui::EditBox *_editRepeatword;
	virtual void editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox);
	virtual void editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox);
	virtual void editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text);
	virtual void editBoxReturn(cocos2d::ui::EditBox* editBox);
	void openUrl(Ref*psend);
};
