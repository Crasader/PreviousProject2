#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "GameWidget.h"
#include "Block/BlockGroup.h"
#include "tools/PopupLayer.h"

#include "ui/UIWidget.h"

#include <vector>
using std::vector;

typedef enum
{
	BLOCKMOVE_NONE = 0,	//���ƶ�
	BLOCKMOVE_LEFT,		//�����ƶ�
	BLOCKMOVE_RIGHT		//�����ƶ�
} BlockMove;

class GameScene : public cocos2d::Layer
{
public:
	GameScene();

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
    CREATE_FUNC(GameScene);

public:
	//�Զ��尴ť�¼�
	void buttonSpeedupCallback(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType event);
	void buttonDirectDownCallback(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType event);
	void buttonLeftCallback(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType event);
	void buttonRightCallback(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType event);
	void buttonRotateCallback(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType event);

	//������ť�¼�
	void buttonPopupCallback(cocos2d::Ref* sender, ButtonResult result);

	//��ʱ���ص�����
	void MoveDownSpeedup(float dt);				//�������亯��
	void MoveDownCurBlockGroup(float dt);		//�����ƶ���ǰͼ��
	void MoveLeftrightCurBlockGroup(float dt);	//�����ƶ���ǰͼ��
	void RemoveFullRowBlocks(float dt);			//��ȥ����

private:
	bool IsCurBlockGroupCanMoveDown();			//�жϵ�ǰͼ���Ƿ��������
	void AddCurBlockGroupToBlocks();			//��ӵ�ǰͼ���еķ��鵽���鼯����

	//ˢ�±�ǩ
	void RefreshLine();
	void RefreshLevel();

	bool ReleaseBlocksOnFullLine();				//��ȥͬ�еķ���
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
	GameWidget*		m_widget;

	//��ǩ
	cocos2d::LabelAtlas* m_labelLine;
	cocos2d::Label* m_labelLevel;

	//��ǰͼ��
	BlockGroup*		m_curGroup;

	//ͼ���ƶ�����
	BlockMove		m_moveState;

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

#endif // __GAME_SCENE_H__
