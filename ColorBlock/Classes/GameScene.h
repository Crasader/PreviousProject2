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
	BLOCKMOVE_NONE = 0,	//不移动
	BLOCKMOVE_LEFT,		//向左移动
	BLOCKMOVE_RIGHT		//向右移动
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
    CREATE_FUNC(GameScene);

public:
	//自定义按钮事件
	void buttonSpeedupCallback(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType event);
	void buttonDirectDownCallback(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType event);
	void buttonLeftCallback(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType event);
	void buttonRightCallback(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType event);
	void buttonRotateCallback(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType event);

	//弹出框按钮事件
	void buttonPopupCallback(cocos2d::Ref* sender, ButtonResult result);

	//定时器回调函数
	void MoveDownSpeedup(float dt);				//加速下落函数
	void MoveDownCurBlockGroup(float dt);		//向下移动当前图形
	void MoveLeftrightCurBlockGroup(float dt);	//左右移动当前图形
	void RemoveFullRowBlocks(float dt);			//消去方块

private:
	bool IsCurBlockGroupCanMoveDown();			//判断当前图形是否可以下落
	void AddCurBlockGroupToBlocks();			//添加当前图形中的方块到方块集合中

	//刷新标签
	void RefreshLine();
	void RefreshLevel();

	bool ReleaseBlocksOnFullLine();				//消去同行的方块
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
	GameWidget*		m_widget;

	//标签
	cocos2d::LabelAtlas* m_labelLine;
	cocos2d::Label* m_labelLevel;

	//当前图形
	BlockGroup*		m_curGroup;

	//图形移动方向
	BlockMove		m_moveState;

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

#endif // __GAME_SCENE_H__
