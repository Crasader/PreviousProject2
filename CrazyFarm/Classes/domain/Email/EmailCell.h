#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"
#include "server/HttpMsgDefine.h"
using namespace cocos2d;
USING_NS_CC_EXT;


class EmailCell : public TableViewCell{
public:
      
	CREATE_FUNC(EmailCell);
	void setValue(EmailListItem item);
	void IsBeToued();

	void setIsTouched(bool isTouched);
private:
	virtual bool init();
	Sprite* isReadIcon;
	Label* EmailTitle;
	Sprite* isHaveReward; //有附件，没附件，已领取
	

	EmailListItem _item;

};
