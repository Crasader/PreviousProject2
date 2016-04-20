#pragma once
#include "cocos2d.h"
USING_NS_CC;


class MyCustomLabelTTF : public Node
{
public:
	static MyCustomLabelTTF* create(const std::string& string,float fontSize);
private:
	bool init(const std::string& string,float fontSize);
	std::vector<std::string> ParseTheStringForCustom(std::string str);
};


