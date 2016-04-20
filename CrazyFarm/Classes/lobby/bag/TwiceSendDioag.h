#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "widget/BaseLayer.h"
USING_NS_CC;


class TwiceSendDioag :public BaseLayer, public cocos2d::ui::EditBoxDelegate
{
public:
    virtual bool init(int itemid,int itemidnum);
	static TwiceSendDioag* createTwiceSendDioag(int itemid,int itemnum);
private:
	bool onTouchBegan(Touch *touch, Event *unused_event){ return true; };
	void sureButtonCallBack(Ref*psend);
	void closeButtonCallBack(Ref*psend);
	int m_itemid;
	int m_itemnum;

	ui::EditBox *_editRepeatword;
	virtual void editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox);
	virtual void editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox);
	virtual void editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text);
	virtual void editBoxReturn(cocos2d::ui::EditBox* editBox);
};
