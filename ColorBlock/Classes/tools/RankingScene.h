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
	//void buttonReturnCallback(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType event);	//Return��ť�ص�����

private:	
	cocos2d::Vec2	m_firstPoint;	//��һ��������
	cocos2d::Vec2	m_offset;		//scrollview��ƫ��
	int				m_curPage;		//scrollview��ǰ��ʾ��ҳ��
	bool			m_horizontal;	//�жϵ�һ�λ�������
	bool			m_vertical;
};

#endif	// __RANKING_SCENE_H__