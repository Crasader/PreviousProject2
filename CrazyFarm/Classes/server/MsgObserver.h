//
//  MsgObserver.h
//  LearnCppCode
//
//  Created by molo on 16/3/8.
//  Copyright © 2016年 molo. All rights reserved.
//

#ifndef MsgObserver_h
#define MsgObserver_h

class MsgObserver
{
public:
    virtual void handle_event(const int msgId, const char* msgBody)=0;
};

class MsgUserOne : public MsgObserver {
public:
    void handle_event(const int msgId, const char* msgBody) {
        printf("[MsgUserOne]handle_event: msgId %d\n", msgId);
        printf("[MsgUserOne]handle_event: msgBody %s\n", msgBody);
        // TODO : 演示简单的消息监听
    }
};

#endif /* MsgObserver_h */
