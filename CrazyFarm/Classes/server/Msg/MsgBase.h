#pragma once
#include "cocos2d.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
using namespace cocos2d;

class Msg_Base
{
public:
	virtual void setBody(const char* msgBody) = 0;

};
