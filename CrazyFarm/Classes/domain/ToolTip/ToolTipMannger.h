#pragma once
#include "cocos2d.h"
USING_NS_CC;
class ToolTipMannger 
{
public:
	static void ShowPayTimeoutTip();
	static void ShowPaySuccessTip();

	static void ShowReloginTip(std::string str);


	static void showDioag(std::string str);
	void relogin(Ref*psend);
};

