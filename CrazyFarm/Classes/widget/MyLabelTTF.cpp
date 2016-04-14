#include "MyLabelTTF.h"


MyLabelTTF* MyLabelTTF::create(const std::string& string, const std::string& fontName, float fontSize, float MaxWidth)
{
	MyLabelTTF* ret = new (std::nothrow) MyLabelTTF();
	if (ret && ret->init(string, fontName,fontSize,MaxWidth))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}
bool MyLabelTTF::init(const std::string& string, const std::string& fontName, float fontSize, float MaxWidth)
{
	initWithString(string, fontName, fontSize);
	_maxWidth = MaxWidth;
	scheduleUpdate();
	return true;
}

void MyLabelTTF::update(float delta)
{
	auto nWidth = getContentSize().width;
	if (nWidth>=_maxWidth)
	{
		setScale(_maxWidth / nWidth);
	}
}


