#ifndef _SERVER_H_
#define _SERVER_H_

#include <pomelo.h>
#include <pomelo_trans.h>
#include <pc_JSON.h>

#define EV_HANDLER_EX ((void*)0x44)

#define REQ_ROUTE "connector.entryHandler.enter"
#define REQ_MSG "{\"username\": \"molo\"}"  // TODO : test value. play change to seesion_id

#define REQ_EX ((void*)0x22)
#define REQ_TIMEOUT 10

class Server{
public:
	static Server* getInstance();
    void conConnect(char* host, int port);
    void quit();

private:
	Server();
	static Server* _instance;
    

    int handler_id;
    pc_client_t* workingClient;
    
    void doConnect();
    
    void disconnect();
    
    static void event_cb(pc_client_t* client, int ev_type, void* ex_data, const char* arg1, const char* arg2);
    static void connect_cb(const pc_request_t* req, int rc, const char* resp);
};

#endif
