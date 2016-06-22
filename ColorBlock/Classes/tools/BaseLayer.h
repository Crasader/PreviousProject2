#ifndef __BASE_LAYER_H__
#define __BASE_LAYER_H__

#include "cocos2d.h"
#include "MsgDefine.h"
USING_NS_CC;

class BaseLayer : public Layer
{
public:	
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(BaseLayer);

public:
	virtual void menuReStartCallback(cocos2d::Ref* sender);				 //���¿�ʼ
	virtual void menuExitCallback(cocos2d::Ref* sender);				//�뿪��Ϸ
	virtual void menuContinueCallback(cocos2d::Ref* sender);			//�ָ���Ϸ
};

#endif 