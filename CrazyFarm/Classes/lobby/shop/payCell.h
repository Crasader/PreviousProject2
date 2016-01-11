#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
using namespace cocos2d;
USING_NS_CC_EXT;


class PayCell : public Sprite{
public:
      virtual bool init();
	  CREATE_FUNC(PayCell);
	  void setValue(int propId,int num);
	  void IsBeToued();
private:
	CC_SYNTHESIZE(int, m_nCellId, propID);
	CC_SYNTHESIZE(int, m_nCellNum,propNum );
	Sprite* propSprite;
	LabelAtlas* propNum;

};
