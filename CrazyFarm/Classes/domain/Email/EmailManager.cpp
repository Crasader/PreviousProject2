#include "EmailManager.h"
#include "server/HttpClientUtill.h"
#include "utill/FunUtil.h"
#include "domain/bag/BagManager.h"
#include "domain/user/User.h"
EmailManager* EmailManager::_instance = NULL;

EmailManager::EmailManager(){

}
EmailManager* EmailManager::getInstance(){
    if(_instance == NULL){
		_instance = new EmailManager();
    }
    return _instance;
}
void EmailManager::loadConfig()
{
	
	EventListenerCustom* _listener2 = EventListenerCustom::create("get_email_info", [=](EventCustom* event1){
			Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("get_email_info");
			EmailListValue*value = static_cast<EmailListValue*>(event1->getUserData());
			if (value->_errorcode==0)
			{
				_EmailList = value->_emailListItems;
			}
	});
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_listener2, 1);
	HttpMannger::getInstance()->HttpToPostRequestGetEmailList();
}
EmailListItem EmailManager::getEmailItemById(int emailId)
{
	EmailListItem item;
	item.mailbox_id = -1;
	for (auto var : _EmailList)
	{
		if (var.mailbox_id == emailId)
		{
			item = var;
			break;
		}
	}
	return item;
}
void EmailManager::SendToGetRequestByEmailId(int emailid)
{


	EventListenerCustom* _listener2 = EventListenerCustom::create("get_email_rewards", [=](EventCustom* event1){
		Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("get_email_rewards");
		EmailRewardValue*value = static_cast<EmailRewardValue*>(event1->getUserData());
		if (value->_errorcode == 0)
		{
			for (auto var : value->rewards)
			{
				BagManager::getInstance()->addreward(var._itemid, var._num);
			}
		}

		for (auto &var : _EmailList)
		{
			if (var.mailbox_id == emailid)
			{
				var.isRead = true;
				break;
			}
		}

		if (_layer)
		{
			_layer->showContent(emailid);
		}
	});
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_listener2, 1);
	HttpMannger::getInstance()->HttpToPostRequestGetEmailReward(emailid);

}
int EmailManager::getNoReadNum()
{
	int i = 0;
	for (auto var:_EmailList)
	{
		if (!var.isRead)
		{
			i++;
		}
	}
	return i;
}
void EmailManager::SendToGetRequestAll()
{


		EventListenerCustom* _listener2 = EventListenerCustom::create("get_email_rewardsAll", [=](EventCustom* event1){
			Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("get_email_rewardsAll");
			EmailRewardValue*value = static_cast<EmailRewardValue*>(event1->getUserData());
			if (value->_errorcode == 0)
			{
				for (auto var : value->rewards)
				{
					BagManager::getInstance()->addreward(var._itemid, var._num);
				}
			}
			
			for (auto var:_EmailList)
			{
				var.isRead = true;
			}
			if (_layer)
			{
				_layer->showContent(_EmailList.at(0).mailbox_id);
			}
		});
		Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_listener2, 1);
		HttpMannger::getInstance()->HttpToPostRequestGetEmailRewardByAll();
	
}