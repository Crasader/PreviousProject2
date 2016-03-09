#ifndef _SERVER_H_
#define _SERVER_H_

#include "cocos2d.h"
#include <pomelo.h>
#include <pomelo_trans.h>
#include <pc_JSON.h>

#include "server/MsgObserver.h"

#define EV_HANDLER_EX ((void*)0x44)

#define REQ_ROUTE "connector.entryHandler.enter"

#define REQ_EX ((void*)0x22)
#define REQ_TIMEOUT 10

class Server{
public:
	static Server* getInstance();
    void conConnect(char* host, int port, char* session_id);
    void quit();
    
    void add_observer(MsgObserver *o);
    void remove_observer(MsgObserver *o);
    void notify_observer(const int msgId, const char* msgBody);

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
    
    char* username;
    
    std::vector<MsgObserver*> msgObserver;
};

#endif
