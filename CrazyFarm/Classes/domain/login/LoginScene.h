#pragma once
#include "cocos2d.h"
USING_NS_CC;




class LoginScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
private:
	void loginCallBack(Ref*psend);
    virtual bool init();
	CREATE_FUNC(LoginScene);

};
