#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"
#include "MissionManager.h"

using namespace cocos2d;
USING_NS_CC_EXT;


class MissionCell : public TableViewCell{
public:
      
	  CREATE_FUNC(MissionCell);
	  void setValue(MissionListItem item);
	  void IsBeToued();
private:
	virtual bool init();
	void btCallback(Ref*psend);
	LabelAtlas* _progressPercent;
	Sprite* _missionContant;
	ui::LoadingBar* _progressbar;
	Sprite* _rewardProp;
	LabelAtlas* _rewardPropNum;
	MenuItemImage*bt;
		MissionListItem _item;

};
