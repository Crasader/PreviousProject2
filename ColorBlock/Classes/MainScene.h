#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include "tools/PopupLayer.h"

class MainScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	//����Androidƽ̨�µİ�������
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	//����Androidƽ̨�µİ�������
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);

public:
	//��ť�¼�
	void menuStartCallback(cocos2d::Ref* pSender);
	void menuMoreGameCallback(cocos2d::Ref* pSender);
	void menuGiftCallback(cocos2d::Ref* pSender);
	void menuAboutCallback(cocos2d::Ref* pSender);
	void menuDragModeGameCallback(Ref*psend);
	void menuMusicCallback(Ref*psend);
	//������ť�¼�
	void buttonPopupCallback(cocos2d::Ref* sender, ButtonResult result);

	//��ʱ���ص�����
	void DelayContinue(float dt);				//��ʱ����������

private:
	void loadRes();
	void ExitGame();							//�˳���Ϸ
	void DoExitGame();							//ȷ���˳���Ϸ

private:
	cocos2d::Menu*		m_menu;
	bool				m_bPopupLayerWorking;	//�������Ƿ�����
};

#endif // __MAIN_SCENE_H__
