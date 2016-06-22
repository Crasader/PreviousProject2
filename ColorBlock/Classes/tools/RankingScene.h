#ifndef __RANKING_SCENE_H__
#define __RANKING_SCENE_H__

#include "cocos2d.h"

class RankingScene : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
	 // implement the "static create()" method manually
    CREATE_FUNC(RankingScene);

private:
	//void buttonReturnCallback(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType event);	//Return按钮回调函数

private:	
	cocos2d::Vec2	m_firstPoint;	//第一个触摸点
	cocos2d::Vec2	m_offset;		//scrollview的偏移
	int				m_curPage;		//scrollview当前显示的页数
	bool			m_horizontal;	//判断第一次滑动方向
	bool			m_vertical;
};

#endif	// __RANKING_SCENE_H__