#pragma once

#include "cocos2d.h"
#include "server/HttpMannger.h"
#include "EmailLayer.h"
using namespace cocos2d;





class EmailManager {

public:
	static EmailManager* getInstance();
	void loadConfig();
	std::vector<EmailListItem> &getEmailListData(){ return _EmailList; };

	EmailListItem getEmailItemById(int emailId);
	void SendToGetRequestByEmailId(int emailid);
	void SendToGetRequestAll();
	int getNoReadNum();
private:
	EmailManager();
	std::vector<EmailListItem> _EmailList;
	static EmailManager* _instance;

	CC_SYNTHESIZE(EmailLayer*,_layer, EmaiLayer);

    
};

