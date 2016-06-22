#ifndef __SETUP_SCENE_H__
#define __SETUP_SCENE_H__

#include "cocos2d.h"
#include "tools/PopupLayer.h"

class SetupScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(SetupScene);

public:
	//按钮事件
	void menuVolumeCallback(cocos2d::Ref* pSender);
	void menuLevelCallback(cocos2d::Ref* pSender);
	void menuRankingCallback(cocos2d::Ref* pSender);
	void menuReturnCallback(cocos2d::Ref* pSender);

	//弹出框按钮事件
	void buttonPopupCallback(cocos2d::Ref* sender, ButtonResult result);
};

#endif // __SETUP_SCENE_H__