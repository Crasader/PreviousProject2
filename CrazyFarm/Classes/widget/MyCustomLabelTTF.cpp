#include "MyCustomLabelTTF.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
USING_NS_CC_EXT;
using namespace cocos2d::ui;
MyCustomLabelTTF* MyCustomLabelTTF::create(const std::string& string, float fontSize)
{
	MyCustomLabelTTF* ret = new (std::nothrow) MyCustomLabelTTF();
	if (ret && ret->init(string,fontSize))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}
bool MyCustomLabelTTF::init(const std::string& string, float fontSize)
{
	Node::init();
	auto vec = ParseTheStringForCustom(string);

	auto _richText = RichText::create();
	_richText->ignoreContentAdaptWithSize(false);
	
	
	for (int i = 0; i < vec.size();i++)
	{
		RichElementText* re;
		if (i==1)
		{
			re= RichElementText::create(i, Color3B::RED, 255, vec.at(i), "arial", 20);
		}
		else
		{
			re= RichElementText::create(i, Color3B::BLACK, 255, vec.at(i), "arial", 20);
		}
		_richText->pushBackElement(re);
	}
	_richText->setPosition(Vec2(0,0));
	_richText->setContentSize(Size());
	addChild(_richText);
	return true;
}



std::vector<std::string> MyCustomLabelTTF::ParseTheStringForCustom(std::string str)
{
	std::vector<std::string> vec;
	int k = str.find("<name>");
	int j= str.find("</name>");

	if (k>0&&j>0)
	{
		std::string str1;
		for (unsigned int i = 0; i < k;i++)
		{
			str1 += str[i];
		}
		vec.push_back(str1);

		std::string str2;
		for (unsigned int i = k+6; i < j; i++)
		{
			str2 += str[i];
		}
		vec.push_back(str2);

		std::string str3;
		for (unsigned int i = j + 7; i <str.size(); i++)
		{
			str3 += str[i];
		}
		vec.push_back(str3);
	}
	else
	{
		vec.push_back(str);
	}
	return vec;		
}