#ifndef __GAMEOVER_LAYER_H__
#define __GAMEOVER_LAYER_H__

#include "PopupLayer.h"

class GameOverLayer : public PopupLayer
{
public:	
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(GameOverLayer);

	//设置标题
	void SetTitle(const string& title);

	//设置文本内容
	void SetContent(const string& content);

	//设置按钮类型
	void SetButtonType(ButtonType type);

private:
	void buttonYesCallback(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType event);	//YES按钮回调函数
	void buttonNoCallback(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType event);		//NO按钮回调函数
	void buttonOkCallback(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType event);		//OK按钮回调函数
	void buttonCancelCallback(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType event);	//Cancel按钮回调函数

	void DestroySelf(cocos2d::Ref* sender, ButtonResult result);								//销毁layer并调用回调函数

private:
	cocos2d::Label*			m_title;			//标题
	cocos2d::Label*			m_content;			//文本内容
	cocos2d::Sprite*		m_background;		//背景图片
	cocos2d::Size			m_size;				//背景图片大小
};

#endif // __GAMEOVER_LAYER_H__