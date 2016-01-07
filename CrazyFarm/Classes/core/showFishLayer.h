#pragma once
#include "cocos2d.h"


USING_NS_CC;


class showFishCell :public cocos2d::Sprite
{
public:
	virtual bool init(int type);
	static showFishCell* createCell(int type);
private:

};





class showFishLayer : public cocos2d::Node{
public:
	virtual bool init();
	CREATE_FUNC(showFishLayer);
private :

	MenuItemImage* setttingBoard;
	 
};
