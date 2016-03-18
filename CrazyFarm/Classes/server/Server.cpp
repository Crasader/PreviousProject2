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
	msgObserver.clear();
}

/**
 * 增加传入用户名参数：session_id
 */
void Server::doConnect() {
    if(!onConnecting) {
        onConnecting = true;
        // TODO : 组装username
		std::string reqParams = "{\"username\": \"" + username + "\",\"room_id\": \"" + Value(_room_id).asString() + "\" }";
		CCLOG("doConnect %s", reqParams.c_str());
        pc_request_with_timeout(workingClient, REQ_ROUTE, reqParams.c_str(), REQ_EX, REQ_TIMEOUT, connect_cb);
    }
    
}

void Server::sendNewEvents(const char* params) {
    std::string testParams = "{\"type\": \"catch_mermaid\"}" ;
	CCLOG("sendNewEvents %s", testParams.c_str());
    pc_notify_with_timeout(workingClient, REQ_NEWEVENTS, testParams.c_str(), REQ_NEWEVENTS_EX, REQ_TIMEOUT, notify_cb);
}

void Server::sendUserInfoChange(int difCoins, int difDiamonds, int difExp) {
    
	auto Params = String::createWithFormat("{\"coins\": %d, \"diamonds\": %d, \"exps\": %d }", difCoins, difDiamonds, difExp);
	
	CCLOG("sendUserInfoChange %s",Params->getCString());
		pc_notify_with_timeout(workingClient, REQ_USERINFOCHANGE, Params->getCString(), REQ_USERINFOCHANGE_EX, REQ_TIMEOUT, notify_cb);
}

void Server::reqTurrentLevelUpdate() {
    char* Params = "{}";
    pc_request_with_timeout(workingClient, REQ_ROUTE_LEVELUPDATE, Params, REQ_LEVELUPDATE_EX, REQ_TIMEOUT, levelupdate_cb);
}



void Server::conConnect(char* host, int port, const char* session_id,int room_id) {
    username = session_id;
	_room_id = room_id;
    pc_lib_init(NULL, NULL, NULL, NULL);
    workingClient = (pc_client_t*)malloc(pc_client_size());
    pc_client_init(workingClient, (void*)0x11, NULL);
    handler_id = pc_client_add_ev_handler(workingClient, event_cb, EV_HANDLER_EX, NULL);
    pc_client_connect(workingClient, host, port, NULL);
}

void Server::connect_cb(const pc_request_t* req, int rc, const char* resp) {
    CCLOG("connect_cb: get rc %d\n", rc);
    CCLOG("connect_cb: get resp %s\n", resp);
    Server::getInstance()->notify_observer("init", resp);
    Server::getInstance()->sendNewEvents(resp);
	
}

void Server::levelupdate_cb(const pc_request_t* req, int rc, const char* resp) {
    CCLOG("levelupdate_cb: get rc %d\n", rc);
    CCLOG("levelupdate_cb: get resp %s\n", resp);
    Server::getInstance()->notify_observer("level_update", resp);
    Server::getInstance()->sendNewEvents(resp);
    
}



void Server::notify_cb(const pc_notify_t* noti, int rc) {
    CCLOG("notify_cb: get rc %d\n", rc);
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
    // 5 : 'level_update' - level update request
    // 6 : 'expUpdate' - user exp update
    for(std::vector<MsgObserver*>::const_iterator it=msgObserver.begin(); it!=msgObserver.end(); it++) {
        (*it)->handle_event(msgId, msgBody);
    }
}


