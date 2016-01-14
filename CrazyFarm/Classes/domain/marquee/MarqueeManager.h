#pragma once

#include "cocos2d.h"
#include "config/ConfigMagnate.h"

using namespace cocos2d;


struct MagnateEvent {
    int fireTimes;
    int itemId;
    int num;
    
};

class MagnateManager {

public:
    static MagnateManager* getInstance();
    
	void loadConfig();
	/*void onHttpRequestCompleted(HttpClient *sender, HttpResponse *response);*/
   
    
private:
    MagnateManager();
    void init();
    static MagnateManager* _instance;
    
    MagnateItem diamandConfig;
    MagnateItem itemConfig;
    
};

