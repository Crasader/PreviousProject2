#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include "BagItem.h"
using namespace cocos2d;
USING_NS_CC_EXT;


class BagCell : public Sprite{
public:
      virtual bool init();
	  CREATE_FUNC(BagCell);
	  void setValue(BagItem item);
	  void IsBeToued();
private:
	CC_SYNTHESIZE(int, m_nCellId, propID);
	CC_SYNTHESIZE(int, m_nCellNum,propNum );
	Sprite* propSprite;
	LabelAtlas* propNum;

};
