#include "HttpClientUtill.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
HttpClientUtill* HttpClientUtill::_pInstance = NULL;

HttpClientUtill* HttpClientUtill::getInstance(){
	if(_pInstance == NULL){
		_pInstance = new HttpClientUtill();
	}
	return _pInstance;
}

void HttpClientUtill::destroyInstance(){
	if(_pInstance != NULL){
		delete _pInstance;
		_pInstance = NULL;
	}
}


void HttpClientUtill::onGetHttp(char* Url,const ccHttpRequestCallback& callback)
{

	HttpRequest* request = new (std::nothrow) HttpRequest();
	// required fields
	request->setUrl(Url);
	request->setRequestType(HttpRequest::Type::GET);
	request->setResponseCallback(callback);
	HttpClient::getInstance()->sendImmediate(request);

}


void HttpClientUtill::onPostHttp(std::string postData,char* Url, const ccHttpRequestCallback& callback)
{
	HttpRequest* request = new (std::nothrow) HttpRequest();
	request->setUrl(Url);
	request->setRequestData(postData.c_str(), postData.size());
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(callback);
	HttpClient::getInstance()->send(request);

}
