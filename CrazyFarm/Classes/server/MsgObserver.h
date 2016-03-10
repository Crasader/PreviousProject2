//
//  MsgObserver.h
//  LearnCppCode
//
//  Created by molo on 16/3/8.
//  Copyright © 2016年 molo. All rights reserved.
//

#ifndef MsgObserver_h
#define MsgObserver_h
#include "cocos2d.h"

class MsgObserver
{
public:
    virtual void handle_event(const char* msgId, const char* msgBody)=0;
};

class MsgUserOne : public MsgObserver {
public:
	void handle_event(const char* msgId, const char* msgBody) {
        CCLOG("[MsgUserOne]handle_event: msgId %d\n", msgId);
        CCLOG("[MsgUserOne]handle_event: msgBody %s\n", msgBody);
        // TODO : 演示简单的消息监听
    }
};

#endif /* MsgObserver_h */
