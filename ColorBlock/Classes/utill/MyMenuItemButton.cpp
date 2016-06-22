#include "MyMenuItemButton.h"

MyMenuItemButton* MyMenuItemButton::create(const std::string&normalImage, const std::string&selectedImage, Node* overNode, const ccMenuCallback& callback)
{
	MyMenuItemButton* ret = new (std::nothrow) MyMenuItemButton();
	if (ret && ret->initWithNormalSprite(Sprite::createWithSpriteFrameName(normalImage), Sprite::createWithSpriteFrameName(selectedImage),nullptr,callback))
    {
        ret->autorelease();
		overNode->setPosition(ret->getContentSize() / 2);
		ret->addChild(overNode);
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}
