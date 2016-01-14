#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
using namespace cocos2d;
USING_NS_CC_EXT;


class showTurretCell : public TableViewCell{
public:
      virtual bool init();
	  CREATE_FUNC(showTurretCell);
	  void setMultipleValue(int index);
	  void setVippaoValue(int index);
	  void IsBeToued();
	  void ButtonCallback(Ref* psend);
private:
	MenuItemImage* button;



	LabelAtlas* muptleTTF;
	LabelTTF* PriceDecTTF;
	Sprite* lockSp;
	Sprite* propSprite;
	Sprite* ShowPaoshade;

};
