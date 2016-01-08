#pragma once
#include "cocos2d.h"


USING_NS_CC;


class showFishCell :public cocos2d::Sprite
{
public:
	virtual bool init();
	static showFishCell* createCell();
	void setData(int fishid);
private:

};





class showFishLayer : public cocos2d::Node{
public:
	virtual bool init();
	CREATE_FUNC(showFishLayer);
private :

	MenuItemImage* setttingBoard;
	 
};
