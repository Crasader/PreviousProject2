#include "Server.h"

Server* Server::_instance = NULL;

Server::Server(){
}


Server* Server::getInstance(){
	if(_instance == NULL){
		_instance = new Server();
	}
	return _instance;
}

void Server::event_cb(pc_client_t* client, int ev_type, void* ex_data, const char* arg1, const char* arg2) {
    printf("[server]event_cb: get eventtype %d\n", ev_type);
    printf("[server]event_cb: get event %s, arg1: %s, arg2: %s\n", pc_client_ev_str(ev_type),
           arg1 ? arg1 : "", arg2 ? arg2 : "");
    if(ev_type == 1) {
        Server::getInstance()->doConnect();
    }
    // TODO : 处理连接失败和重连的问题，并且要仔细测试下。
}

void Server::quit() {
    if(workingClient != NULL) {
        pc_client_disconnect(workingClient);
        pc_client_rm_ev_handler(workingClient, handler_id);
        pc_client_cleanup(workingClient);
        free(workingClient);
    }
    pc_lib_cleanup();
}

void Server::doConnect() {
    pc_request_with_timeout(workingClient, REQ_ROUTE, REQ_MSG, REQ_EX, REQ_TIMEOUT, connect_cb);
}


void Server::conConnect(char* host, int port) {
    pc_lib_init(NULL, NULL, NULL, NULL);
    workingClient = (pc_client_t*)malloc(pc_client_size());
    pc_client_init(workingClient, (void*)0x11, NULL);
    handler_id = pc_client_add_ev_handler(workingClient, event_cb, EV_HANDLER_EX, NULL);
    pc_client_connect(workingClient, host, port, NULL);
}

void Server::connect_cb(const pc_request_t* req, int rc, const char* resp) {
    printf("connect_cb: get rc %d\n", rc);
    printf("connect_cb: get resp %s\n", resp);
}


