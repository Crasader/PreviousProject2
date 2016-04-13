#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include "domain/ranklist/RanklistManager.h"
#include "server/HttpMsgDefine.h"
using namespace cocos2d;
USING_NS_CC_EXT;


class RecordGiftCell : public TableViewCell{
public:
      virtual bool init();
	  CREATE_FUNC(RecordGiftCell);
	  void setValue(RecordGiftItem item);
	 ui::Scale9Sprite *bg;
private:

	LabelTTF* dataTTF;
	LabelTTF* stateTTF;
	LabelTTF* nameTTF;
};
