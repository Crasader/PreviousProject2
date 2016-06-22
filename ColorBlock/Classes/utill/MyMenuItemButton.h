#pragma once
#include "cocos2d.h"
USING_NS_CC;


class MyMenuItemButton : public MenuItemImage
{
public:
	static MyMenuItemButton* create(const std::string&normalImage, const std::string&selectedImage,Node* overNode, const ccMenuCallback& callback);

};


