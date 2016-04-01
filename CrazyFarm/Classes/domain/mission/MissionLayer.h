#pragma once
#include "cocos2d.h"
#include "MissionView.h"
#include "AchieveView.h"
USING_NS_CC;

class MissionLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	CREATE_FUNC(MissionLayer);

private:
	void closeButtonCallBack(Ref*psend);
	virtual bool onTouchBegan(Touch *touch, Event *unused_event){ return true; };
	void changeTypeCallBack(Ref*);
	void changeToMissionlist();
	void changeToAchievelist();
	MissionView* _MissionViewDelegate;
	MyTableView* tableView;
	LabelAtlas *labelRank;
	AchieveView* _achieveViewDelegate;

	LabelTTF* haveCoinTTF;
	Sprite* coinsp;
	LabelAtlas* CoinNumTTF;
};
