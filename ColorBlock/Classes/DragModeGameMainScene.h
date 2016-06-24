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

	// 触摸开始事件
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);

	// 触摸滑动
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);

	// 触摸结束事件
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);

	//监听Android平台下的按键按下
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	//监听Android平台下的按键弹起
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

	void Restart();								//重新开始游戏
	void GameOver();							//游戏结束
	void ExitGame();							//退出游戏
	void DoExitGame();							//确认退出游戏

private:
	cocos2d::Size	m_winSize;		//窗口大小
	cocos2d::Size	m_visibleSize;	//可视区域大小
	cocos2d::Vec2	m_origin;		//绘图原点



	cocos2d::EventListenerTouchOneByOne*	m_touchListener;	//触屏事件监听器
	cocos2d::EventListenerKeyboard*			m_keyboardListener;	//键盘事件监听器

	bool			m_bPopupLayerWorking;	//弹出层是否启用

	//游戏部件
	DragModeGameWidget*		m_widget;

	//标签
	cocos2d::Label* m_labelLine;
	cocos2d::Label* m_labelLevel;

	//当前图形
	BlockGroup*		m_curGroup;


	//方块集合
	vector<BlockObject>	m_vecBlocks;

	//满行的行号集合
	vector<int>			m_vecFullRow;

private:
	//游戏参数
	int				m_level;		//级别
	int				m_score;		//分数
	int				m_line;			//消去的行数
};
