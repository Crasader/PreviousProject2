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

	//���ñ���
	void SetTitle(const string& title);

	//�����ı�����
	void SetContent(const string& content);

	//���ð�ť����
	void SetButtonType(ButtonType type);

private:
	void buttonYesCallback(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType event);	//YES��ť�ص�����
	void buttonNoCallback(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType event);		//NO��ť�ص�����
	void buttonOkCallback(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType event);		//OK��ť�ص�����
	void buttonCancelCallback(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType event);	//Cancel��ť�ص�����

	void DestroySelf(cocos2d::Ref* sender, ButtonResult result);								//����layer�����ûص�����

private:
	cocos2d::Label*			m_title;			//����
	cocos2d::Label*			m_content;			//�ı�����
	cocos2d::Sprite*		m_background;		//����ͼƬ
	cocos2d::Size			m_size;				//����ͼƬ��С
};

#endif // __GAMEOVER_LAYER_H__