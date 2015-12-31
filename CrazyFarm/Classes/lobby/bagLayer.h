#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

















class BagLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	CREATE_FUNC(BagLayer);

private:
	void closeButtonCallBack(Ref*psend);

	void chankanCallBack(Ref*);

};
