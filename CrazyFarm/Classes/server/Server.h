#ifndef _SERVER_H_
#define _SERVER_H_

#include "cocos2d.h"
#include <pomelo.h>
#include <pomelo_trans.h>
#include <pc_JSON.h>

#include "server/MsgObserver.h"
USING_NS_CC;
#define EV_HANDLER_EX ((void*)0x44)

#define REQ_ROUTE "connector.entryHandler.enter"

#define REQ_EX ((void*)0x22)
#define REQ_TIMEOUT 10

#define REQ_NEWEVENTS "game.gameHandler.newevents"
#define REQ_NEWEVENTS_EX ((void*)0x33)

#define REQ_USERINFOCHANGE "game.gameHandler.userinfochange"
#define REQ_USERINFOCHANGE_EX ((void*)0x55)

class Server{
public:
	static Server* getInstance();
    void conConnect(char* host, int port, const char* session_id,int room_id);
    void quit();
    
    void add_observer(MsgObserver *o);
    void remove_observer(MsgObserver *o);
	void notify_observer(const char* msgId, const char* msgBody);
    
    void sendNewEvents(const char* params);
    void sendUserInfoChange(const char* params);

private:
	Server();
	static Server* _instance;
    
    bool onConnecting = false;

    int handler_id;
    pc_client_t* workingClient;
    
    void doConnect();
    
    void disconnect();
    
    static void event_cb(pc_client_t* client, int ev_type, void* ex_data, const char* arg1, const char* arg2);
    static void connect_cb(const pc_request_t* req, int rc, const char* resp);
    static void notify_cb(const pc_notify_t* noti, int rc);
    
    std::string username;

	int _room_id;
    
    std::vector<MsgObserver*> msgObserver;
};

#endif
