#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;




class LoginScene : public cocos2d::Layer, public cocos2d::ui::EditBoxDelegate
{
public:
    static cocos2d::Scene* createScene();
private:
	void loginCallBack(Ref*psend);
	void changeIdCallBack(Ref*psend);
	void findPasswordCallBack(Ref*psend);
    virtual bool init();
	CREATE_FUNC(LoginScene);
	void update(float delta);
	float  nTempTime = 0;
	//edit box
	ui::EditBox *_editName;
	ui::EditBox *_editPassword;
	virtual void editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox);
	virtual void editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox);
	virtual void editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text);
	virtual void editBoxReturn(cocos2d::ui::EditBox* editBox);
};
