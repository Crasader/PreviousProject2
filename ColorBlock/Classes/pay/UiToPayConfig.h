#pragma once
#include "cocos2d.h"
USING_NS_CC;

struct UitopayData
{
	int uiPoint;
	std::string pluginType;
	int payPoint;
};



class UiToPayConfig
{
public:
	~UiToPayConfig();
	static UiToPayConfig* getInstance();
	int getUiPointByPayPointAndPluginType(int point,std::string pluginType);//根据payPoint和插件类型获取对应的uipoint
	bool LoadConfig();
private:
	UiToPayConfig();
	static UiToPayConfig* _instance;
	std::vector<UitopayData>  _Uitopaydatas;
};

