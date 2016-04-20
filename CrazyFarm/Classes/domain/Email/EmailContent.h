#pragma once
#include "cocos2d.h"
#include "server/HttpMsgDefine.h"
USING_NS_CC;

class EmailContent : public Sprite
{
public:
 
    virtual bool init(EmailListItem item);

	static EmailContent*create(EmailListItem item);
};
