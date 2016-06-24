#pragma once
#include "cocos2d.h"
#include "DragModeGameWidget.h"
#include "Block/BlockGroup.h"
#include "tools/PopupLayer.h"
#include "BaseGame.h"

#include "ui/UIWidget.h"


class DragModeGameMainScene : public BaseGame
{
public:
	DragModeGameMainScene();

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	// Update method will be called automatically every frame if "scheduleUpdate" is called, and the node is "live"
	virtual void update(float delta);

	// ������ʼ�¼�
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);

	// ��������
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);

	// ���������¼�
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);

	//����Androidƽ̨�µİ�������
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	//����Androidƽ̨�µİ�������
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	virtual void onExit();
    
    // implement the "static create()" method manually
	CREATE_FUNC(DragModeGameMainScene);

private:
	virtual void onPause();
	virtual void onResum();
	virtual void onBackMainScene();
	virtual void onRebegin();
	virtual void onUseSkill(int skillid);

private:

	void Restart();								//���¿�ʼ��Ϸ
	void GameOver();							//��Ϸ����
	void ExitGame();							//�˳���Ϸ
	void DoExitGame();							//ȷ���˳���Ϸ

private:
	cocos2d::Size	m_winSize;		//���ڴ�С
	cocos2d::Size	m_visibleSize;	//���������С
	cocos2d::Vec2	m_origin;		//��ͼԭ��



	cocos2d::EventListenerTouchOneByOne*	m_touchListener;	//�����¼�������
	cocos2d::EventListenerKeyboard*			m_keyboardListener;	//�����¼�������

	bool			m_bPopupLayerWorking;	//�������Ƿ�����

	//��Ϸ����
	DragModeGameWidget*		m_widget;

	//��ǩ
	cocos2d::Label* m_labelLine;
	cocos2d::Label* m_labelLevel;

	//��ǰͼ��
	BlockGroup*		m_curGroup;


	//���鼯��
	vector<BlockObject>	m_vecBlocks;

	//���е��кż���
	vector<int>			m_vecFullRow;

private:
	//��Ϸ����
	int				m_level;		//����
	int				m_score;		//����
	int				m_line;			//��ȥ������
};
