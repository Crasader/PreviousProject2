#ifndef __LOBBY_SCENE_H__
#define __LOBBY_SCENE_H__
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class PlayInfoLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	CREATE_FUNC(PlayInfoLayer);

};
#endif