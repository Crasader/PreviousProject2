#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;




class LoginScene : public cocos2d::Layer, public cocos2d::ui::EditBoxDelegate
{
public:
    static cocos2d::Scene* createScene();
	void setChangeNickName(std::string srt);
private:
	void openUrl(Ref*psend);

	void endGame(Ref*psend);
	void onExitCallback(Ref*psend);
	void loginCallBack(Ref*psend);
	void RegisterCallBack(Ref*psend);
	void findPasswordCallBack(Ref*psend);
	void moreIdCallback(Ref*psend);
    virtual bool init();
	CREATE_FUNC(LoginScene);
	std::list<std::string> nicknames;
	//edit box
	bool CheickLogin(std::string nickname, std::string password);
public:
	ui::EditBox *_editName;
	ui::EditBox *_editPassword;
private:
	virtual void editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox);
	virtual void editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox);
	virtual void editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text);
	virtual void editBoxReturn(cocos2d::ui::EditBox* editBox);
};
