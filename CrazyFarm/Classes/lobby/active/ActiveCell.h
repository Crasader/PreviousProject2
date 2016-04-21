#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include "domain/ranklist/RanklistManager.h"
using namespace cocos2d;
USING_NS_CC_EXT;


class ActiveCell : public TableViewCell{
public:
      virtual bool init();
	  CREATE_FUNC(ActiveCell);
	  void setImg(std::string path);
private:
	Sprite*bg;

};
