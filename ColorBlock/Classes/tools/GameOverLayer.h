#ifndef __GAMEOVER_LAYER_H__
#define __GAMEOVER_LAYER_H__

#include "BaseLayer.h"

class GameOverLayer : public BaseLayer
{
public:	
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(GameOverLayer);

};

#endif // __GAMEOVER_LAYER_H__