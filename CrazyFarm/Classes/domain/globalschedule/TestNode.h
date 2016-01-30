#pragma once
#include "cocos2d.h"  
USING_NS_CC;  
   

class TestNode : public Node {
    public:

		CREATE_FUNC(TestNode);
	
		virtual bool init(){ this->scheduleUpdate(); return true; };
		virtual void update(float delta){ CCLOG("updata"); };

    private:  
    
};  
   
