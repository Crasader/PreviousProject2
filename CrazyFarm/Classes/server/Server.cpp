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
    CCLOG("[server]event_cb: get eventtype %d\n", ev_type);
    CCLOG("[server]event_cb: get event %s, arg1: %s, arg2: %s\n", pc_client_ev_str(ev_type),
           arg1 ? arg1 : "", arg2 ? arg2 : "");
    if(ev_type == 1) {
        Server::getInstance()->doConnect(); 
    }else if(ev_type == 0) {
		Server::getInstance()->notify_observer(arg1, arg2);
    }else if(ev_type == 2) {
        Server::getInstance()->notify_observer("conError", "");
    }


	Server::getInstance()->notify_observer("fire", "400");
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
    onConnecting = false;
}

/**
 * 增加传入用户名参数：session_id
 */
void Server::doConnect() {
    if(!onConnecting) {
        onConnecting = true;
        // TODO : 组装username
        std::string reqParams = "{\"username\": \"" + std::string(username) + "\"}" ;
        pc_request_with_timeout(workingClient, REQ_ROUTE, reqParams.c_str(), REQ_EX, REQ_TIMEOUT, connect_cb);
    }
    
}


void Server::conConnect(char* host, int port, const char* session_id) {
    username = session_id;
    pc_lib_init(NULL, NULL, NULL, NULL);
    workingClient = (pc_client_t*)malloc(pc_client_size());
    pc_client_init(workingClient, (void*)0x11, NULL);
    handler_id = pc_client_add_ev_handler(workingClient, event_cb, EV_HANDLER_EX, NULL);
    pc_client_connect(workingClient, host, port, NULL);
}

void Server::connect_cb(const pc_request_t* req, int rc, const char* resp) {
    CCLOG("connect_cb: get rc %d\n", rc);
    CCLOG("connect_cb: get resp %s\n", resp);
    // TODO : 回调用户信息
	
}

void Server::add_observer(MsgObserver *o){
    msgObserver.push_back(o);
}

void Server::remove_observer(MsgObserver *o) {
    for(std::vector<MsgObserver*>::iterator it=msgObserver.begin(); it!=msgObserver.end(); it++) {
        if(o==*it) {
            msgObserver.erase(it);
            return;
        }
    }
}

void Server::notify_observer(const char* msgId, const char* msgBody) {
    // TODO : MsgId
    // 0 : 'conError' - connect error
    // 1 : 'init' - client defined info ...
    // 2 : 'onAdd' - new user coming ...
    // 3 : 'onLeave' - user leave room ...
    // 4 : 'onFishes' - broadcast fish info ...
    for(std::vector<MsgObserver*>::const_iterator it=msgObserver.begin(); it!=msgObserver.end(); it++) {
        (*it)->handle_event(msgId, msgBody);
    }
}


