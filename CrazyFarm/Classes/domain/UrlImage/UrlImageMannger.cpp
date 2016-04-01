#include "UrlImageMannger.h"
#include "server/HttpMannger.h"

UrlImageMannger* UrlImageMannger::_instance = NULL;

UrlImageMannger::UrlImageMannger(){
	
}


UrlImageMannger* UrlImageMannger::getInstance(){
	if (_instance == NULL){
		_instance = new UrlImageMannger();
	}
	return _instance;
}

void UrlImageMannger::LoadImgByUrl(std::string url)
{
	std::string path = getImgNameByUrl(url);
	if (FileUtils::getInstance()->isFileExist(path))
	{
		return;
	}

	EventListenerCustom* _listener2 = EventListenerCustom::create(url, [=](EventCustom* event){

		std::vector<char>*buffer = static_cast<std::vector<char>*>(event->getUserData());
		std::string buff(buffer->begin(), buffer->end());

		FILE *fp = fopen(path.c_str(), "wb+");
		fwrite(buff.c_str(), 1, buffer->size(), fp);
		fclose(fp);

		Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(url);

	});
	LoadingCircle::showLoadingCircle();
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_listener2, 1);
	HttpMannger::getInstance()->HttpToPostRequestToGetUrlImg(url);
}

std::string UrlImageMannger::getImgNameByUrl(std::string url)
{
	std::string temp;
	int i = url.find_last_of('/');
	for (; i<url.size(); i++)
	{
		temp.push_back(url.at(i));
	}
	temp = FileUtils::sharedFileUtils()->getWritablePath() + temp + ".png";
	return temp;
}
