#pragma once
#include "cocos2d.h"
USING_NS_CC;

struct ImageElement
{
	std::string type;
	float xx;
	float yy;
	float height;
	float width;
	std::string defaultname;
	std::string specialname;
};



class PayUiConfig
{
public:
	~PayUiConfig();
	static PayUiConfig* getInstance();
	std::vector<ImageElement>  getPayUiConfigByPoint(int point);//����point��ȡ��ӦUI
	bool LoadConfig();
private:
	PayUiConfig();
	static PayUiConfig* _instance;
	std::map<int, std::vector<ImageElement>>  PayUiPoints;
};

