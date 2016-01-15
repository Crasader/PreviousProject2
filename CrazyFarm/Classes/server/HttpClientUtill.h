#pragma once
#include "cocos2d.h"
#include "network/HttpClient.h"
#include "cocos-ext.h"


using namespace cocos2d::network;
using namespace cocos2d;

class HttpClientUtill{
public:
	static HttpClientUtill* getInstance();
	static void destroyInstance();


	
	void onGetHttp(char* Url, const ccHttpRequestCallback& callback);
	void onPostHttp(std::string postData, char* Url, const ccHttpRequestCallback& callback);
private:
	static HttpClientUtill* _pInstance;
	
};