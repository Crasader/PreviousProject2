#ifndef __POPUP_LAYER_H__
#define __POPUP_LAYER_H__

#include "cocos2d.h"

#include "ui/UIWidget.h"
#include "ui/UIButton.h"
#include <string>

using std::string;

typedef enum
{
	BUTTONTYPE_NONE = 0,	//不显示按钮
	BUTTONTYPE_YESNO,		//显示YesNo按钮
	BUTTONTYPE_OKCANCEL,	//显示OKCancel按钮
	BUTTONTYPE_OK			//显示OK按钮
} ButtonType;

typedef enum
{
	BUTTONRESULT_NONE = 0,	//没有按钮(不作任何处理)
	BUTTONRESULT_YES,		//YES按钮
	BUTTONRESULT_NO,		//NO按钮
	BUTTONRESULT_OK,		//OK按钮
	BUTTONRESULT_CANCEL,	//CANCEL按钮
	BUTTONRESULT_EXIT,		//Exit按钮
	BUTTONRESULT_CONTINUE	//Continue按钮
} ButtonResult;

typedef std::function<void(cocos2d::Ref*, ButtonResult)> ButtonTouchCallback;

class PopupLayer : public cocos2d::Layer
{
public:
	PopupLayer();
	
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init() override;

	// 触摸事件
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event);

	virtual void onEnter();
	virtual void onExit();

	// implement the "static create()" method manually
	CREATE_FUNC(PopupLayer);

	//设置按钮回调函数
	void SetCallBackFunc(ButtonTouchCallback callfunc);

protected:
	void DestroySelf(cocos2d::Ref* sender, ButtonResult result);								//销毁layer并调用回调函数

protected:
	cocos2d::EventListenerTouchOneByOne*	m_touchListener;	//触屏事件监听器
	ButtonTouchCallback						m_callback;			//按钮回调函数

	cocos2d::ui::Button*	m_btnOK;		//Ok按钮
	cocos2d::ui::Button*	m_btnCancel;	//Cancel按钮
	cocos2d::ui::Button*	m_btnYes;		//Yes按钮
	cocos2d::ui::Button*	m_btnNo;		//No按钮
	cocos2d::ui::Button*	m_btnExit;		//Exit按钮
};

#endif // __POPUP_LAYER_H__