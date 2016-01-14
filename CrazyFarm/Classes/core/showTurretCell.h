#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
using namespace cocos2d;
USING_NS_CC_EXT;


class showTurretCell : public TableViewCell{
public:
      virtual bool init();
	  CREATE_FUNC(showTurretCell);
	  void setValue(int viplevel);
	  void IsBeToued();
private:
	LabelAtlas* VIPTTF;
	LabelTTF* PriceDecTTF;
	Sprite* VIPtitle;
	Sprite* propSprite;
	Sprite* VIPname;
	Sprite* VIPdec;


};
