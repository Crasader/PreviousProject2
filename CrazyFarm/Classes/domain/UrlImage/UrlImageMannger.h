#pragma once
#include "cocos2d.h"
#include "utill/define.h"
#include "server/HttpMsgDefine.h"
using namespace cocos2d;


class UrlImageMannger{
public:
	static UrlImageMannger* getInstance();
	void LoadImgByUrl(std::string url);
	std::string getImgNameByUrl(std::string url);//��URL�в��ͼƬ·��
private:
	UrlImageMannger();
	static UrlImageMannger* _instance;


};

