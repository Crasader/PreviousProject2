#pragma once
#include "cocos2d.h"
#include "EmailView.h"
USING_NS_CC;

class EmailLayer : public cocos2d::Layer
{
public:
   

    virtual bool init();

	CREATE_FUNC(EmailLayer);
	void showContent(int emailid);
private:
	void closeButtonCallBack(Ref*psend);
	virtual bool onTouchBegan(Touch *touch, Event *unused_event){ return true; };
	void allReadCallBack(Ref*);
	
	
	EmailView* _EmailViewDelegate;
	MyTableView* tableView;
	

};
