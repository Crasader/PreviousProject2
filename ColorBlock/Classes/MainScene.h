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

	//监听Android平台下的按键按下
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	//监听Android平台下的按键弹起
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);

public:
	//按钮事件
	void menuStartCallback(cocos2d::Ref* pSender);
	void menuMoreGameCallback(cocos2d::Ref* pSender);
	void menuGiftCallback(cocos2d::Ref* pSender);
	void menuAboutCallback(cocos2d::Ref* pSender);
	void menuMusicCallback(Ref*psend);


	//定时器回调函数
	void DelayContinue(float dt);				//延时进入主界面

private:
	void loadRes();
	void ExitGame();							//退出游戏
	void CreateEffect();
private:
	cocos2d::Menu*		m_menu;
};

#endif // __MAIN_SCENE_H__
