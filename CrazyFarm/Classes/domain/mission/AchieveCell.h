#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"
#include "MissionManager.h"
#include "AchieveStar.h"
#include "widget/MyLabelTTF.h"
#include "widget/MyLabelAtlas.h"
using namespace cocos2d;
USING_NS_CC_EXT;


class AchieveCell : public TableViewCell{
public:
      
	CREATE_FUNC(AchieveCell);
	void setValue(AchieveListItem item);
	  void IsBeToued();
private:
	virtual bool init();
	void btCallback(Ref*psend);
	Sprite* _icon;
	Sprite* _missionName;
	Sprite* _rewardProp;
	LabelAtlas* _rewardPropNum;
	AchieveStar*_stars;
	MyLabelTTF* _missionContant;
	//½ø¶ÈÌõ
	Sprite*_txtProgressContant;
	MyLabelAtlas* _progressPercent;
	ui::LoadingBar* _progressbar;
	MenuItemImage*bt;
	Sprite*_missionBarFrane;

	AchieveListItem _item;

};
