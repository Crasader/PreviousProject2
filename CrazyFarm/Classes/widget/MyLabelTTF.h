#pragma once
#include "cocos2d.h"
USING_NS_CC;
class MyLabelTTF : public LabelTTF
{
public:
	static MyLabelTTF* create(const std::string& string, const std::string& fontName, float fontSize, float MaxWidth);
private:
	bool init(const std::string& string, const std::string& fontName, float fontSize, float MaxWidth);
	void update(float delta);
	float _maxWidth;
};


