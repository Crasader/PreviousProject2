#ifndef __POPUP_LAYER_H__
#define __POPUP_LAYER_H__

#include "cocos2d.h"

#include "ui/UIWidget.h"
#include "ui/UIButton.h"
#include <string>

using std::string;

typedef enum
{
	BUTTONTYPE_NONE = 0,	//����ʾ��ť
	BUTTONTYPE_YESNO,		//��ʾYesNo��ť
	BUTTONTYPE_OKCANCEL,	//��ʾOKCancel��ť
	BUTTONTYPE_OK			//��ʾOK��ť
} ButtonType;

typedef enum
{
	BUTTONRESULT_NONE = 0,	//û�а�ť(�����κδ���)
	BUTTONRESULT_YES,		//YES��ť
	BUTTONRESULT_NO,		//NO��ť
	BUTTONRESULT_OK,		//OK��ť
	BUTTONRESULT_CANCEL,	//CANCEL��ť
	BUTTONRESULT_EXIT,		//Exit��ť
	BUTTONRESULT_CONTINUE	//Continue��ť
} ButtonResult;

typedef std::function<void(cocos2d::Ref*, ButtonResult)> ButtonTouchCallback;

class PopupLayer : public cocos2d::Layer
{
public:
	PopupLayer();
	
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init() override;

	// �����¼�
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event);

	virtual void onEnter();
	virtual void onExit();

	// implement the "static create()" method manually
	CREATE_FUNC(PopupLayer);

	//���ð�ť�ص�����
	void SetCallBackFunc(ButtonTouchCallback callfunc);

protected:
	void DestroySelf(cocos2d::Ref* sender, ButtonResult result);								//����layer�����ûص�����

protected:
	cocos2d::EventListenerTouchOneByOne*	m_touchListener;	//�����¼�������
	ButtonTouchCallback						m_callback;			//��ť�ص�����

	cocos2d::ui::Button*	m_btnOK;		//Ok��ť
	cocos2d::ui::Button*	m_btnCancel;	//Cancel��ť
	cocos2d::ui::Button*	m_btnYes;		//Yes��ť
	cocos2d::ui::Button*	m_btnNo;		//No��ť
	cocos2d::ui::Button*	m_btnExit;		//Exit��ť
};

#endif // __POPUP_LAYER_H__