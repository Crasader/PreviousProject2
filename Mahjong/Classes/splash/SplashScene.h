#ifndef __SPLSH_SCENE_H__
#define __SPLSH_SCENE_H__
#include "cocos2d.h"

USING_NS_CC;


class SplashScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void startGame();
 
	void loadResource();

	void loginByPhone();

	void loginByPass();
	
	void loginByVisitor();

	CREATE_FUNC(SplashScene);
};
#endif